//-----------------------------------------------------------------------------
// pcie_sniffer.sv - PCIe TLP Trace Capture with Trigger
//
// 256-entry ring buffer for capturing full TLP headers + data.
// Supports trigger modes: continuous, stop-on-full, stop-on-trigger.
//
// Each trace entry (512 bits = 16 DWORDs):
//   [127:0]   TLP header (128 bits)
//   [383:128] TLP data (256 bits = 8 DW)
//   [384]     Direction: 0=RX (from host), 1=TX (to host)
//   [416:385] Timestamp (32 bits of cycle counter)
//   [417]     rx_st_sop
//   [418]     rx_st_eop
//   [419]     rx_st_hvalid
//   [420]     rx_st_dvalid
//   [423:421] rx_st_bar
//   [424]     rx_st_ready
//   [425]     tx_st_sop
//   [426]     tx_st_eop
//   [427]     tx_st_hvalid
//   [428]     tx_st_dvalid
//   [429]     tx_st_ready
//   [511:430] Reserved
//
// Register Map (BAR 0x2000-0x2FFF):
//   0x000: status      - [0] rx_seen, [1] tx_seen, [16] running,
//                        [9] triggered, [10] full, [15:12] mode
//   0x004: control     - [0] start, [1] stop, [2] clear, [3] arm_trigger
//   0x008: mode        - [1:0] capture mode: 0=continuous, 1=stop-on-full,
//                                            2=stop-on-trigger, 3=start-on-trigger
//                        [5:4] filter: 0=all, 1=RX only, 2=TX only, 3=errors only
//   0x00C: trigger_cfg - [7:0] trigger on TLP type (fmt+type), [8] type_en,
//                        [9] trigger on error response
//   0x010: write_ptr   - Current write pointer (0-255)
//   0x014: entry_count - Number of entries captured
//   0x018: rx_count    - Total RX TLPs seen
//   0x01C: tx_count    - Total TX TLPs seen
//   0x020: cycle_lo    - Cycle counter low
//   0x024: cycle_hi    - Cycle counter high
//   0x028-0x02C: reserved
//
//   0x030: read_ptr    - Software sets this to select trace entry (0-255)
//   0x034: trace_hdr0  - Selected entry header [31:0]
//   0x038: trace_hdr1  - Selected entry header [63:32]
//   0x03C: trace_hdr2  - Selected entry header [95:64]
//   0x040: trace_hdr3  - Selected entry header [127:96]
//   0x044: trace_data0 - Selected entry data [31:0]
//   0x048: trace_data1 - Selected entry data [63:32]
//   0x04C: trace_data2 - Selected entry data [95:64]
//   0x050: trace_data3 - Selected entry data [127:96]
//   0x054: trace_data4 - Selected entry data [159:128]
//   0x058: trace_data5 - Selected entry data [191:160]
//   0x05C: trace_data6 - Selected entry data [223:192]
//   0x060: trace_data7 - Selected entry data [255:224]
//   0x064: trace_meta0 - timestamp[31:0]
//   0x068: trace_meta1 - [0] dir, [1] rx_sop, [2] rx_eop, [3] rx_hvalid, [4] rx_dvalid,
//                        [7:5] rx_bar, [8] rx_ready, [9] tx_sop, [10] tx_eop,
//                        [11] tx_hvalid, [12] tx_dvalid, [13] tx_ready
//
//   0x070-0x07C: last_rx_hdr[0-3]  (most recent RX, always captured)
//   0x080-0x09C: last_rx_data[0-7] (256 bits)
//   0x0A0-0x0AC: last_tx_hdr[0-3]  (most recent TX, always captured)
//   0x0B0-0x0CC: last_tx_data[0-7] (256 bits)
//-----------------------------------------------------------------------------
module pcie_sniffer (
    input  logic        clk,
    input  logic        rst_n,

    // Global timestamp (shared across all sniffers)
    input  logic [31:0] global_timestamp,

    // Snoop RX path (all signals for complete capture)
    input  logic [127:0] rx_st_hdr,
    input  logic [255:0] rx_st_data,
    input  logic         rx_st_sop,
    input  logic         rx_st_eop,
    input  logic         rx_st_hvalid,
    input  logic         rx_st_dvalid,
    input  logic [2:0]   rx_st_bar,
    input  logic         rx_st_ready,

    // Snoop TX path (all signals for complete capture)
    input  logic [127:0] tx_st_hdr,
    input  logic [255:0] tx_st_data,
    input  logic         tx_st_sop,
    input  logic         tx_st_eop,
    input  logic         tx_st_hvalid,
    input  logic         tx_st_dvalid,
    input  logic         tx_st_ready,

    // Debug interface
    input  logic [11:0]  dbg_addr,      // Byte address within debug space (0x000-0xFFF)
    input  logic [31:0]  dbg_wdata,     // Write data
    input  logic         dbg_wen,       // Write enable
    output logic [31:0]  dbg_rdata
);

    //=========================================================================
    // Trace RAM - 256 entries x 512 bits (uses more BRAM but captures full TLP data)
    //=========================================================================
    logic [511:0] trace_ram [0:255];
    logic [7:0]   write_ptr;
    logic [8:0]   entry_count;  // 0-256
    logic         running;
    logic         triggered;
    logic         full;

    // Configuration
    logic [1:0]   capture_mode;   // 0=continuous, 1=stop-on-full, 2=stop-on-trigger, 3=start-on-trigger
    logic [1:0]   filter_mode;    // 0=all, 1=RX only, 2=TX only, 3=errors only
    logic [7:0]   trigger_type;   // TLP type to trigger on
    logic         trigger_type_en;
    logic         trigger_on_err;
    logic         armed;          // For start-on-trigger mode

    // Read interface
    logic [7:0]   read_ptr;
    logic [511:0] read_entry;

    // Counters and last-seen (now with 256-bit data)
    logic [31:0]  rx_count, tx_count;
    logic [127:0] last_rx_hdr, last_tx_hdr;
    logic [255:0] last_rx_data, last_tx_data;
    logic         rx_seen, tx_seen;
    logic [7:0]   last_rx_type;

    //=========================================================================
    // TLP Detection and Filtering
    //=========================================================================
    wire rx_valid = rx_st_hvalid && rx_st_sop && rx_st_ready;
    wire tx_valid = tx_st_hvalid && tx_st_sop;
    
    wire [7:0] rx_tlp_type = {rx_st_hdr[127:125], rx_st_hdr[124:120]};  // fmt + type
    wire [7:0] tx_tlp_type = {tx_st_hdr[127:125], tx_st_hdr[124:120]};
    
    // Error detection (CplD with non-zero status in bits [47:45])
    wire rx_is_cpl_err = rx_valid && (rx_tlp_type[4:0] == 5'b01010) && (rx_st_hdr[47:45] != 3'b000);
    wire tx_is_cpl_err = tx_valid && (tx_tlp_type[4:0] == 5'b01010) && (tx_st_hdr[47:45] != 3'b000);
    
    // Filter logic
    wire rx_pass_filter = (filter_mode == 2'd0) ||  // all
                          (filter_mode == 2'd1) ||  // RX only
                          (filter_mode == 2'd3 && rx_is_cpl_err);  // errors only
    wire tx_pass_filter = (filter_mode == 2'd0) ||  // all
                          (filter_mode == 2'd2) ||  // TX only
                          (filter_mode == 2'd3 && tx_is_cpl_err);  // errors only

    wire capture_rx = rx_valid && rx_pass_filter;
    wire capture_tx = tx_valid && tx_pass_filter;
    
    // Trigger detection
    wire rx_trigger = capture_rx && trigger_type_en && (rx_tlp_type == trigger_type);
    wire tx_trigger = capture_tx && trigger_type_en && (tx_tlp_type == trigger_type);
    wire err_trigger = trigger_on_err && (rx_is_cpl_err || tx_is_cpl_err);
    wire trigger_hit = rx_trigger || tx_trigger || err_trigger;

    //=========================================================================
    // Control Logic
    //=========================================================================
    wire ctrl_start = dbg_wen && (dbg_addr[11:2] == 10'h001) && dbg_wdata[0];
    wire ctrl_stop  = dbg_wen && (dbg_addr[11:2] == 10'h001) && dbg_wdata[1];
    wire ctrl_clear = dbg_wen && (dbg_addr[11:2] == 10'h001) && dbg_wdata[2];
    wire ctrl_arm   = dbg_wen && (dbg_addr[11:2] == 10'h001) && dbg_wdata[3];

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            write_ptr <= 0;
            entry_count <= 0;
            running <= 0;
            triggered <= 0;
            full <= 0;
            armed <= 0;
            capture_mode <= 0;
            filter_mode <= 0;
            trigger_type <= 0;
            trigger_type_en <= 0;
            trigger_on_err <= 0;
            read_ptr <= 0;
            rx_count <= 0;
            tx_count <= 0;
            last_rx_hdr <= 0;
            last_tx_hdr <= 0;
            last_rx_data <= 0;
            last_tx_data <= 0;
            rx_seen <= 0;
            tx_seen <= 0;
            last_rx_type <= 0;
        end else begin

            // Control register writes
            if (ctrl_clear) begin
                write_ptr <= 0;
                entry_count <= 0;
                triggered <= 0;
                full <= 0;
                rx_count <= 0;
                tx_count <= 0;
                rx_seen <= 0;
                tx_seen <= 0;
            end
            
            if (ctrl_start) begin
                running <= 1;
                if (capture_mode == 2'd3) armed <= 1;  // start-on-trigger needs arming
            end
            
            if (ctrl_stop) begin
                running <= 0;
                armed <= 0;
            end
            
            if (ctrl_arm) armed <= 1;

            // Mode register write
            if (dbg_wen && dbg_addr[11:2] == 10'h002) begin
                capture_mode <= dbg_wdata[1:0];
                filter_mode <= dbg_wdata[5:4];
            end
            
            // Trigger config write
            if (dbg_wen && dbg_addr[11:2] == 10'h003) begin
                trigger_type <= dbg_wdata[7:0];
                trigger_type_en <= dbg_wdata[8];
                trigger_on_err <= dbg_wdata[9];
            end
            
            // Read pointer write
            if (dbg_wen && dbg_addr[11:2] == 10'h00C) begin
                read_ptr <= dbg_wdata[7:0];
            end

            // Always capture last-seen TLPs (even when not running)
            if (rx_valid) begin
                last_rx_hdr <= rx_st_hdr;
                last_rx_data <= rx_st_data;  // Full 256-bit data
                rx_count <= rx_count + 1;
                rx_seen <= 1;
                last_rx_type <= rx_tlp_type;
            end
            
            if (tx_valid) begin
                last_tx_hdr <= tx_st_hdr;
                last_tx_data <= tx_st_data;  // Full 256-bit data
                tx_count <= tx_count + 1;
                tx_seen <= 1;
            end

            // Trigger handling
            if (running && trigger_hit) begin
                triggered <= 1;
                if (capture_mode == 2'd2) running <= 0;  // stop-on-trigger
                if (capture_mode == 2'd3 && armed) armed <= 0;  // start capturing
            end

            // Trace capture
            if (running && !full) begin
                // In start-on-trigger mode, only capture after triggered
                logic should_capture;
                should_capture = (capture_mode != 2'd3) || triggered;
                
                if (should_capture && (capture_rx || capture_tx)) begin
                    // Build 512-bit trace entry with ALL signals
                    logic [511:0] entry;
                    if (capture_rx) begin
                        entry[127:0] = rx_st_hdr;
                        entry[383:128] = rx_st_data;
                        entry[384] = 1'b0;  // RX direction
                    end else begin
                        entry[127:0] = tx_st_hdr;
                        entry[383:128] = tx_st_data;
                        entry[384] = 1'b1;  // TX direction
                    end
                    entry[416:385] = global_timestamp;  // 32-bit timestamp
                    // Capture all RX signals
                    entry[417] = rx_st_sop;
                    entry[418] = rx_st_eop;
                    entry[419] = rx_st_hvalid;
                    entry[420] = rx_st_dvalid;
                    entry[423:421] = rx_st_bar;
                    entry[424] = rx_st_ready;
                    // Capture all TX signals
                    entry[425] = tx_st_sop;
                    entry[426] = tx_st_eop;
                    entry[427] = tx_st_hvalid;
                    entry[428] = tx_st_dvalid;
                    entry[429] = tx_st_ready;
                    entry[511:430] = 82'b0;  // Reserved
                    
                    trace_ram[write_ptr] <= entry;
                    write_ptr <= write_ptr + 1;
                    
                    if (entry_count < 256) entry_count <= entry_count + 1;
                    
                    // Check for full
                    if (write_ptr == 8'd255) begin
                        if (capture_mode == 2'd1) begin
                            full <= 1;
                            running <= 0;
                        end
                        // In continuous mode, just wrap around
                    end
                end
            end
        end
    end

    // Read from trace RAM
    assign read_entry = trace_ram[read_ptr];

    //=========================================================================
    // Read Mux - registered output for clean timing
    // 512-bit entry format:
    //   [127:0]   TLP header
    //   [383:128] TLP data (256 bits)
    //   [384]     direction (0=RX, 1=TX)
    //   [416:385] timestamp (32 bits)
    //   [429:417] control signals (sop/eop/hvalid/dvalid/bar/ready for RX and TX)
    //   [511:430] reserved
    //=========================================================================
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            dbg_rdata <= 32'h0;
        end else begin
            case (dbg_addr[11:2])
                // Status and control (0x000-0x02F)
                10'h000: dbg_rdata <= {11'b0, capture_mode, full, triggered, running,
                                      last_rx_type, 4'b0, 2'b0, tx_seen, rx_seen};
                10'h001: dbg_rdata <= 32'b0;  // Control (write-only)
                10'h002: dbg_rdata <= {26'b0, filter_mode, 2'b0, capture_mode};
                10'h003: dbg_rdata <= {22'b0, trigger_on_err, trigger_type_en, trigger_type};
                10'h004: dbg_rdata <= {24'b0, write_ptr};
                10'h005: dbg_rdata <= {23'b0, entry_count};
                10'h006: dbg_rdata <= rx_count;
                10'h007: dbg_rdata <= tx_count;
                10'h008: dbg_rdata <= global_timestamp;
                10'h009: dbg_rdata <= 32'b0;  // Reserved (timestamp is 32-bit)
                
                // Trace entry read (0x030-0x064)
                10'h00C: dbg_rdata <= {24'b0, read_ptr};
                10'h00D: dbg_rdata <= read_entry[31:0];      // hdr0
                10'h00E: dbg_rdata <= read_entry[63:32];     // hdr1
                10'h00F: dbg_rdata <= read_entry[95:64];     // hdr2
                10'h010: dbg_rdata <= read_entry[127:96];    // hdr3
                10'h011: dbg_rdata <= read_entry[159:128];   // data0
                10'h012: dbg_rdata <= read_entry[191:160];   // data1
                10'h013: dbg_rdata <= read_entry[223:192];   // data2
                10'h014: dbg_rdata <= read_entry[255:224];   // data3
                10'h015: dbg_rdata <= read_entry[287:256];   // data4
                10'h016: dbg_rdata <= read_entry[319:288];   // data5
                10'h017: dbg_rdata <= read_entry[351:320];   // data6
                10'h018: dbg_rdata <= read_entry[383:352];   // data7
                10'h019: dbg_rdata <= read_entry[416:385];   // trace_meta0: timestamp[31:0]
                10'h01A: dbg_rdata <= {17'b0,                  // trace_meta1: all control signals
                                      read_entry[429],        // tx_st_ready
                                      read_entry[428],        // tx_st_dvalid
                                      read_entry[427],        // tx_st_hvalid
                                      read_entry[426],        // tx_st_eop
                                      read_entry[425],        // tx_st_sop
                                      read_entry[424],        // rx_st_ready
                                      read_entry[423:421],    // rx_st_bar[2:0]
                                      read_entry[420],        // rx_st_dvalid
                                      read_entry[419],        // rx_st_hvalid
                                      read_entry[418],        // rx_st_eop
                                      read_entry[417],        // rx_st_sop
                                      read_entry[384]};       // direction
                
                // Last-seen RX TLP (0x070-0x09C) - header + 256-bit data
                10'h01C: dbg_rdata <= last_rx_hdr[31:0];
                10'h01D: dbg_rdata <= last_rx_hdr[63:32];
                10'h01E: dbg_rdata <= last_rx_hdr[95:64];
                10'h01F: dbg_rdata <= last_rx_hdr[127:96];
                10'h020: dbg_rdata <= last_rx_data[31:0];
                10'h021: dbg_rdata <= last_rx_data[63:32];
                10'h022: dbg_rdata <= last_rx_data[95:64];
                10'h023: dbg_rdata <= last_rx_data[127:96];
                10'h024: dbg_rdata <= last_rx_data[159:128];
                10'h025: dbg_rdata <= last_rx_data[191:160];
                10'h026: dbg_rdata <= last_rx_data[223:192];
                10'h027: dbg_rdata <= last_rx_data[255:224];
                
                // Last-seen TX TLP (0x0A0-0x0CC) - header + 256-bit data
                10'h028: dbg_rdata <= last_tx_hdr[31:0];
                10'h029: dbg_rdata <= last_tx_hdr[63:32];
                10'h02A: dbg_rdata <= last_tx_hdr[95:64];
                10'h02B: dbg_rdata <= last_tx_hdr[127:96];
                10'h02C: dbg_rdata <= last_tx_data[31:0];
                10'h02D: dbg_rdata <= last_tx_data[63:32];
                10'h02E: dbg_rdata <= last_tx_data[95:64];
                10'h02F: dbg_rdata <= last_tx_data[127:96];
                10'h030: dbg_rdata <= last_tx_data[159:128];
                10'h031: dbg_rdata <= last_tx_data[191:160];
                10'h032: dbg_rdata <= last_tx_data[223:192];
                10'h033: dbg_rdata <= last_tx_data[255:224];
                
                default: dbg_rdata <= {22'b0, dbg_addr[11:2]};  // Return word address for debug
            endcase
        end
    end

endmodule
