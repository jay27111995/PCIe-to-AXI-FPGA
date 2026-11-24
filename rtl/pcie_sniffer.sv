//-----------------------------------------------------------------------------
// pcie_sniffer.sv - Simple RAM-based PCIe TLP Trace
//
// Direct 64-bit AXI interface - host reads RAM directly, no register decode.
//
// Memory Map (0x000-0xFFF within sniffer region):
//   0x000: control/status  - write [0]=start, [1]=stop, [2]=clear
//                          - read  [0]=running, [1]=full
//   0x008: write_ptr       - [7:0] current entry (0-31)
//   0x010: entry_count     - [8:0] entries captured
//   0x018: rx_count        - total RX TLPs seen
//   0x020: tx_count        - total TX TLPs seen
//   0x028: timestamp       - current global timestamp
//   0x030: reserved
//   0x038: reserved
//   0x040-0x07F: last RX (hdr[128] + data[256] = 6 QWs)
//   0x080-0x0BF: last TX (hdr[128] + data[256] = 6 QWs)
//   0x100-0x8FF: trace entries (32 entries x 64 bytes each)
//
// Trace entry format (512 bits = 8 QWs = 64 bytes):
//   QW0 [63:0]:    hdr[63:0]
//   QW1 [127:64]:  hdr[127:64]
//   QW2 [191:128]: data[63:0]
//   QW3 [255:192]: data[127:64]
//   QW4 [319:256]: data[191:128]
//   QW5 [383:320]: data[255:192]
//   QW6 [447:384]: {31'b0, timestamp[31:0], dir}
//   QW7 [511:448]: {ctrl signals, reserved}
//-----------------------------------------------------------------------------
module pcie_sniffer #(
    parameter DEPTH = 32
)(
    input  logic        clk,
    input  logic        rst_n,

    // Global timestamp
    input  logic [31:0] global_timestamp,

    // RX path
    input  logic [127:0] rx_st_hdr,
    input  logic [255:0] rx_st_data,
    input  logic         rx_st_sop,
    input  logic         rx_st_eop,
    input  logic         rx_st_hvalid,
    input  logic         rx_st_dvalid,
    input  logic [2:0]   rx_st_bar,
    input  logic         rx_st_ready,

    // TX path
    input  logic [127:0] tx_st_hdr,
    input  logic [255:0] tx_st_data,
    input  logic         tx_st_sop,
    input  logic         tx_st_eop,
    input  logic         tx_st_hvalid,
    input  logic         tx_st_dvalid,
    input  logic         tx_st_ready,

    // AXI-lite style interface (directly from bridge)
    input  logic [11:0]  axi_araddr,
    input  logic         axi_arvalid,
    output logic         axi_arready,
    output logic [63:0]  axi_rdata,
    output logic         axi_rvalid,
    input  logic         axi_rready,

    input  logic [11:0]  axi_awaddr,
    input  logic [63:0]  axi_wdata,
    input  logic         axi_awvalid,
    input  logic         axi_wvalid,
    output logic         axi_awready,
    output logic         axi_wready,
    output logic         axi_bvalid,
    input  logic         axi_bready
);

    //=========================================================================
    // State registers
    //=========================================================================
    logic running;
    logic full;
    logic [7:0] write_ptr;
    logic [8:0] entry_count;
    logic [31:0] rx_count;
    logic [31:0] tx_count;

    // Last captured TLPs (always captured regardless of running)
    logic [127:0] last_rx_hdr;
    logic [255:0] last_rx_data;
    logic [127:0] last_tx_hdr;
    logic [255:0] last_tx_data;

    //=========================================================================
    // Trace RAM: 32 entries x 8 QWs = 256 x 64-bit words
    //=========================================================================
    logic [63:0] trace_ram [0:DEPTH*8-1];

    //=========================================================================
    // Capture logic
    //=========================================================================
    wire capture_rx = running && !full && rx_st_hvalid && rx_st_sop;
    wire capture_tx = running && !full && tx_st_hvalid && tx_st_sop && !(rx_st_hvalid && rx_st_sop);

    // Build trace entry QWs
    wire [63:0] rx_qw0 = rx_st_hdr[63:0];
    wire [63:0] rx_qw1 = rx_st_hdr[127:64];
    wire [63:0] rx_qw2 = rx_st_data[63:0];
    wire [63:0] rx_qw3 = rx_st_data[127:64];
    wire [63:0] rx_qw4 = rx_st_data[191:128];
    wire [63:0] rx_qw5 = rx_st_data[255:192];
    wire [63:0] rx_qw6 = {31'b0, global_timestamp, 1'b0};  // dir=0 for RX
    wire [63:0] rx_qw7 = {51'b0, tx_st_ready, tx_st_dvalid, tx_st_hvalid, tx_st_eop, tx_st_sop,
                          rx_st_ready, rx_st_bar, rx_st_dvalid, rx_st_hvalid, rx_st_eop, rx_st_sop};

    wire [63:0] tx_qw0 = tx_st_hdr[63:0];
    wire [63:0] tx_qw1 = tx_st_hdr[127:64];
    wire [63:0] tx_qw2 = tx_st_data[63:0];
    wire [63:0] tx_qw3 = tx_st_data[127:64];
    wire [63:0] tx_qw4 = tx_st_data[191:128];
    wire [63:0] tx_qw5 = tx_st_data[255:192];
    wire [63:0] tx_qw6 = {31'b0, global_timestamp, 1'b1};  // dir=1 for TX
    wire [63:0] tx_qw7 = {51'b0, tx_st_ready, tx_st_dvalid, tx_st_hvalid, tx_st_eop, tx_st_sop,
                          rx_st_ready, rx_st_bar, rx_st_dvalid, rx_st_hvalid, rx_st_eop, rx_st_sop};

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            running <= 0;
            full <= 0;
            write_ptr <= 0;
            entry_count <= 0;
            rx_count <= 0;
            tx_count <= 0;
            last_rx_hdr <= 0;
            last_rx_data <= 0;
            last_tx_hdr <= 0;
            last_tx_data <= 0;
        end else begin
            // Always capture last TLPs
            if (rx_st_hvalid && rx_st_sop) begin
                last_rx_hdr <= rx_st_hdr;
                last_rx_data <= rx_st_data;
                rx_count <= rx_count + 1;
            end
            if (tx_st_hvalid && tx_st_sop) begin
                last_tx_hdr <= tx_st_hdr;
                last_tx_data <= tx_st_data;
                tx_count <= tx_count + 1;
            end

            // Trace capture
            if (capture_rx) begin
                trace_ram[{write_ptr[4:0], 3'd0}] <= rx_qw0;
                trace_ram[{write_ptr[4:0], 3'd1}] <= rx_qw1;
                trace_ram[{write_ptr[4:0], 3'd2}] <= rx_qw2;
                trace_ram[{write_ptr[4:0], 3'd3}] <= rx_qw3;
                trace_ram[{write_ptr[4:0], 3'd4}] <= rx_qw4;
                trace_ram[{write_ptr[4:0], 3'd5}] <= rx_qw5;
                trace_ram[{write_ptr[4:0], 3'd6}] <= rx_qw6;
                trace_ram[{write_ptr[4:0], 3'd7}] <= rx_qw7;
                write_ptr <= write_ptr + 1;
                if (entry_count < DEPTH) entry_count <= entry_count + 1;
                if (write_ptr == DEPTH - 1) full <= 1;
            end else if (capture_tx) begin
                trace_ram[{write_ptr[4:0], 3'd0}] <= tx_qw0;
                trace_ram[{write_ptr[4:0], 3'd1}] <= tx_qw1;
                trace_ram[{write_ptr[4:0], 3'd2}] <= tx_qw2;
                trace_ram[{write_ptr[4:0], 3'd3}] <= tx_qw3;
                trace_ram[{write_ptr[4:0], 3'd4}] <= tx_qw4;
                trace_ram[{write_ptr[4:0], 3'd5}] <= tx_qw5;
                trace_ram[{write_ptr[4:0], 3'd6}] <= tx_qw6;
                trace_ram[{write_ptr[4:0], 3'd7}] <= tx_qw7;
                write_ptr <= write_ptr + 1;
                if (entry_count < DEPTH) entry_count <= entry_count + 1;
                if (write_ptr == DEPTH - 1) full <= 1;
            end

            // Control writes
            if (axi_awvalid && axi_wvalid && axi_awaddr[11:3] == 0) begin
                if (axi_wdata[0]) running <= 1;  // start
                if (axi_wdata[1]) running <= 0;  // stop
                if (axi_wdata[2]) begin          // clear
                    write_ptr <= 0;
                    entry_count <= 0;
                    full <= 0;
                    rx_count <= 0;
                    tx_count <= 0;
                end
            end
        end
    end

    //=========================================================================
    // Write response (immediate)
    //=========================================================================
    logic wr_pending;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            wr_pending <= 0;
        end else begin
            if (axi_awvalid && axi_wvalid && !wr_pending)
                wr_pending <= 1;
            else if (wr_pending && axi_bready)
                wr_pending <= 0;
        end
    end
    assign axi_awready = !wr_pending;
    assign axi_wready = !wr_pending;
    assign axi_bvalid = wr_pending;

    //=========================================================================
    // Read logic - combinational mux, registered output
    //=========================================================================
    logic [63:0] rdata_next;
    logic rd_pending;
    logic [11:0] rd_addr;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            rd_pending <= 0;
            rd_addr <= 0;
            axi_rdata <= 0;
            axi_rvalid <= 0;
        end else begin
            if (axi_arvalid && axi_arready) begin
                rd_pending <= 1;
                rd_addr <= axi_araddr;
            end else if (rd_pending && !axi_rvalid) begin
                axi_rdata <= rdata_next;
                axi_rvalid <= 1;
                rd_pending <= 0;
            end else if (axi_rvalid && axi_rready) begin
                axi_rvalid <= 0;
            end
        end
    end
    assign axi_arready = !rd_pending && !axi_rvalid;

    // Read data mux
    always_comb begin
        rdata_next = 64'hDEAD_0001;  // Default for debug

        if (rd_addr < 12'h040) begin
            // Status registers 0x000-0x03F
            case (rd_addr[5:3])
                3'd0: rdata_next = {62'b0, full, running};          // 0x000
                3'd1: rdata_next = {56'b0, write_ptr};              // 0x008
                3'd2: rdata_next = {55'b0, entry_count};            // 0x010
                3'd3: rdata_next = {32'b0, rx_count};               // 0x018
                3'd4: rdata_next = {32'b0, tx_count};               // 0x020
                3'd5: rdata_next = {32'b0, global_timestamp};       // 0x028
                default: rdata_next = 64'b0;
            endcase
        end else if (rd_addr < 12'h080) begin
            // Last RX TLP 0x040-0x07F
            case (rd_addr[5:3])
                3'd0: rdata_next = last_rx_hdr[63:0];               // 0x040
                3'd1: rdata_next = last_rx_hdr[127:64];             // 0x048
                3'd2: rdata_next = last_rx_data[63:0];              // 0x050
                3'd3: rdata_next = last_rx_data[127:64];            // 0x058
                3'd4: rdata_next = last_rx_data[191:128];           // 0x060
                3'd5: rdata_next = last_rx_data[255:192];           // 0x068
                default: rdata_next = 64'b0;
            endcase
        end else if (rd_addr < 12'h0C0) begin
            // Last TX TLP 0x080-0x0BF
            case (rd_addr[5:3])
                3'd0: rdata_next = last_tx_hdr[63:0];               // 0x080
                3'd1: rdata_next = last_tx_hdr[127:64];             // 0x088
                3'd2: rdata_next = last_tx_data[63:0];              // 0x090
                3'd3: rdata_next = last_tx_data[127:64];            // 0x098
                3'd4: rdata_next = last_tx_data[191:128];           // 0x0A0
                3'd5: rdata_next = last_tx_data[255:192];           // 0x0A8
                default: rdata_next = 64'b0;
            endcase
        end else if (rd_addr >= 12'h100) begin
            // Trace RAM 0x100+
            // Entry N at 0x100 + N*0x40 (64 bytes each), QW M at offset M*8
            rdata_next = trace_ram[{(rd_addr[10:6] - 5'd4), rd_addr[5:3]}];
        end
    end

endmodule
