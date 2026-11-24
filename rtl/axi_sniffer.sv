//-----------------------------------------------------------------------------
// axi_sniffer.sv - AXI Bus Trace Capture
//
// Captures AXI transactions for debugging. Used for both:
//   - AXI Slave sniffer (BAR access from host)
//   - AXI Master sniffer (DMA to host memory)
//
// Uses global_timestamp input for event correlation across all sniffers.
// 64-entry trace buffer (configurable via DEPTH parameter).
//
// Each trace entry (128 bits = 4 DWORDs):
//   [31:0]    Address (AW or AR)
//   [95:32]   Data (W or R, 64 bits)
//   [103:96]  Strobe (W) or Response (R)
//   [104]     Channel: 0=Write (AW/W/B), 1=Read (AR/R)
//   [105]     Phase: 0=Request (AW/AR/W), 1=Response (B/R)
//   [127:106] Timestamp (22 bits from global_timestamp)
//
// Register Map:
//   0x00: status      - [0] running, [1] full, [8] aw_seen, [9] w_seen, 
//                       [10] b_seen, [11] ar_seen, [12] r_seen
//   0x04: control     - [0] start, [1] stop, [2] clear
//   0x08: write_ptr   - Current write pointer (0-63)
//   0x0C: entry_count - Number of entries captured (0-64)
//   0x10: aw_count    - AW transactions seen
//   0x14: ar_count    - AR transactions seen
//   0x20: read_ptr    - Software sets this to select trace entry (0-63)
//   0x24: trace_addr  - Selected entry address
//   0x28: trace_data0 - Selected entry data [31:0]
//   0x2C: trace_data1 - Selected entry data [63:32]
//   0x30: trace_meta  - [7:0] strobe/resp, [8] channel, [9] phase, [31:10] timestamp
//-----------------------------------------------------------------------------
module axi_sniffer #(
    parameter DEPTH = 64
)(
    input  logic        clk,
    input  logic        rst_n,

    // Global timestamp (shared across all sniffers)
    input  logic [31:0] global_timestamp,

    // Snoop AXI Write Channel
    input  logic [31:0] axi_awaddr,
    input  logic        axi_awvalid,
    input  logic        axi_awready,
    input  logic [63:0] axi_wdata,
    input  logic [7:0]  axi_wstrb,
    input  logic        axi_wvalid,
    input  logic        axi_wready,
    input  logic [1:0]  axi_bresp,
    input  logic        axi_bvalid,
    input  logic        axi_bready,

    // Snoop AXI Read Channel
    input  logic [31:0] axi_araddr,
    input  logic        axi_arvalid,
    input  logic        axi_arready,
    input  logic [63:0] axi_rdata,
    input  logic [1:0]  axi_rresp,
    input  logic        axi_rvalid,
    input  logic        axi_rready,

    // Debug interface
    input  logic [7:0]  dbg_addr,
    input  logic [31:0] dbg_wdata,
    input  logic        dbg_wen,
    output logic [31:0] dbg_rdata
);

    localparam PTR_W = $clog2(DEPTH);

    //=========================================================================
    // Trace RAM
    //=========================================================================
    logic [127:0] trace_ram [0:DEPTH-1];
    logic [PTR_W-1:0] write_ptr;
    logic [PTR_W:0]   entry_count;  // 0 to DEPTH
    logic             running;
    logic             full;

    // Read interface
    logic [PTR_W-1:0] read_ptr;
    logic [127:0]     read_entry;

    // Counters
    logic [31:0] aw_count, ar_count;
    
    // Seen flags
    logic aw_seen, w_seen, b_seen, ar_seen, r_seen;

    // Pending write address (to pair with W channel)
    logic [31:0] pending_awaddr;
    logic        pending_awvalid;

    //=========================================================================
    // AXI Transaction Detection
    //=========================================================================
    wire aw_handshake = axi_awvalid && axi_awready;
    wire w_handshake  = axi_wvalid  && axi_wready;
    wire b_handshake  = axi_bvalid  && axi_bready;
    wire ar_handshake = axi_arvalid && axi_arready;
    wire r_handshake  = axi_rvalid  && axi_rready;

    //=========================================================================
    // Control Logic
    //=========================================================================
    wire ctrl_start = dbg_wen && (dbg_addr[7:2] == 6'h01) && dbg_wdata[0];
    wire ctrl_stop  = dbg_wen && (dbg_addr[7:2] == 6'h01) && dbg_wdata[1];
    wire ctrl_clear = dbg_wen && (dbg_addr[7:2] == 6'h01) && dbg_wdata[2];

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            write_ptr <= 0;
            entry_count <= 0;
            running <= 0;
            full <= 0;
            read_ptr <= 0;
            aw_count <= 0;
            ar_count <= 0;
            aw_seen <= 0;
            w_seen <= 0;
            b_seen <= 0;
            ar_seen <= 0;
            r_seen <= 0;
            pending_awaddr <= 0;
            pending_awvalid <= 0;
        end else begin

            // Control
            if (ctrl_clear) begin
                write_ptr <= 0;
                entry_count <= 0;
                full <= 0;
                aw_count <= 0;
                ar_count <= 0;
                aw_seen <= 0;
                w_seen <= 0;
                b_seen <= 0;
                ar_seen <= 0;
                r_seen <= 0;
            end
            
            if (ctrl_start) running <= 1;
            if (ctrl_stop)  running <= 0;
            
            // Read pointer write
            if (dbg_wen && dbg_addr[7:2] == 6'h08) begin
                read_ptr <= dbg_wdata[PTR_W-1:0];
            end

            // Track AW for pairing with W
            if (aw_handshake) begin
                pending_awaddr <= axi_awaddr;
                pending_awvalid <= 1;
                aw_count <= aw_count + 1;
                aw_seen <= 1;
            end

            // Capture W (write data) - pair with pending AW
            if (running && !full && w_handshake && pending_awvalid) begin
                logic [127:0] entry;
                entry[31:0]    = pending_awaddr;
                entry[95:32]   = axi_wdata;
                entry[103:96]  = axi_wstrb;
                entry[104]     = 1'b0;  // Write channel
                entry[105]     = 1'b0;  // Request phase
                entry[127:106] = global_timestamp[21:0];
                
                trace_ram[write_ptr] <= entry;
                write_ptr <= write_ptr + 1;
                if (entry_count < DEPTH) entry_count <= entry_count + 1;
                if (write_ptr == DEPTH-1) full <= 1;
                
                pending_awvalid <= 0;
                w_seen <= 1;
            end

            // Capture B (write response)
            if (running && !full && b_handshake) begin
                logic [127:0] entry;
                entry[31:0]    = 32'h0;  // No address for B
                entry[95:32]   = 64'h0;
                entry[103:96]  = {6'b0, axi_bresp};
                entry[104]     = 1'b0;  // Write channel
                entry[105]     = 1'b1;  // Response phase
                entry[127:106] = global_timestamp[21:0];
                
                trace_ram[write_ptr] <= entry;
                write_ptr <= write_ptr + 1;
                if (entry_count < DEPTH) entry_count <= entry_count + 1;
                if (write_ptr == DEPTH-1) full <= 1;
                
                b_seen <= 1;
            end

            // Capture AR (read address)
            if (ar_handshake) begin
                ar_count <= ar_count + 1;
                ar_seen <= 1;
                
                if (running && !full) begin
                    logic [127:0] entry;
                    entry[31:0]    = axi_araddr;
                    entry[95:32]   = 64'h0;
                    entry[103:96]  = 8'h0;
                    entry[104]     = 1'b1;  // Read channel
                    entry[105]     = 1'b0;  // Request phase
                    entry[127:106] = global_timestamp[21:0];
                    
                    trace_ram[write_ptr] <= entry;
                    write_ptr <= write_ptr + 1;
                    if (entry_count < DEPTH) entry_count <= entry_count + 1;
                    if (write_ptr == DEPTH-1) full <= 1;
                end
            end

            // Capture R (read data/response)
            if (running && !full && r_handshake) begin
                logic [127:0] entry;
                entry[31:0]    = 32'h0;  // No address for R
                entry[95:32]   = axi_rdata;
                entry[103:96]  = {6'b0, axi_rresp};
                entry[104]     = 1'b1;  // Read channel
                entry[105]     = 1'b1;  // Response phase
                entry[127:106] = global_timestamp[21:0];
                
                trace_ram[write_ptr] <= entry;
                write_ptr <= write_ptr + 1;
                if (entry_count < DEPTH) entry_count <= entry_count + 1;
                if (write_ptr == DEPTH-1) full <= 1;
                
                r_seen <= 1;
            end
        end
    end

    // Read from trace RAM
    assign read_entry = trace_ram[read_ptr];

    //=========================================================================
    // Read Mux
    //=========================================================================
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            dbg_rdata <= 32'h0;
        end else begin
        case (dbg_addr[7:2])
            6'h00: dbg_rdata <= {19'b0, r_seen, ar_seen, b_seen, w_seen, aw_seen,
                                6'b0, full, running};
            6'h01: dbg_rdata <= 32'b0;  // Control (write-only)
            6'h02: dbg_rdata <= {{(32-PTR_W){1'b0}}, write_ptr};
            6'h03: dbg_rdata <= {{(32-PTR_W-1){1'b0}}, entry_count};
            6'h04: dbg_rdata <= aw_count;
            6'h05: dbg_rdata <= ar_count;
            
            6'h08: dbg_rdata <= {{(32-PTR_W){1'b0}}, read_ptr};
            6'h09: dbg_rdata <= read_entry[31:0];    // addr
            6'h0A: dbg_rdata <= read_entry[63:32];   // data_lo
            6'h0B: dbg_rdata <= read_entry[95:64];   // data_hi
            6'h0C: dbg_rdata <= {read_entry[127:106], // timestamp
                               read_entry[105],      // phase
                               read_entry[104],      // channel
                               read_entry[103:96]};  // strobe/resp
            
            default: dbg_rdata <= 32'hDEAD_BEEF;
        endcase
        end
    end

endmodule
