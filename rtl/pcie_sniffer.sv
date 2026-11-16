//-----------------------------------------------------------------------------
// pcie_sniffer.sv - PCIe TLP Logger for Debug
//
// Captures incoming and outgoing TLPs for debugging.
// Accessible via a debug register window.
//
// Debug Register Map (directly mapped to BAR, e.g., 0x2000-0x2FFF):
//   0x00: status      - [0] rx_seen, [1] tx_seen, [7:4] tx_state, [15:8] last_rx_type
//   0x04: rx_count    - Number of RX TLPs seen
//   0x08: tx_count    - Number of TX TLPs seen
//   0x0C: control     - [0] clear counts (write 1 to clear)
//   0x10: last_rx_hdr0
//   0x14: last_rx_hdr1
//   0x18: last_rx_hdr2
//   0x1C: last_rx_hdr3
//   0x20: last_rx_data0
//   0x24: last_rx_data1
//   0x28: last_tx_hdr0
//   0x2C: last_tx_hdr1
//   0x30: last_tx_hdr2
//   0x34: last_tx_hdr3
//   0x38: last_tx_data0
//   0x3C: last_tx_data1
//   0x40: cycle_count_lo
//   0x44: cycle_count_hi
//   0x48: rx_st_ready_cnt - How many cycles rx_st_ready was high
//   0x4C: tx_st_ready_cnt - How many cycles tx_st_ready was high
//-----------------------------------------------------------------------------
module pcie_sniffer (
    input  logic        clk,
    input  logic        rst_n,

    // Snoop RX path
    input  logic [127:0] rx_st_hdr,
    input  logic [255:0] rx_st_data,
    input  logic         rx_st_sop,
    input  logic         rx_st_hvalid,
    input  logic         rx_st_ready,

    // Snoop TX path
    input  logic [127:0] tx_st_hdr,
    input  logic [255:0] tx_st_data,
    input  logic         tx_st_sop,
    input  logic         tx_st_hvalid,
    input  logic         tx_st_ready,

    // State machine state (for debug)
    input  logic [3:0]   tx_state,

    // Debug read interface (directly addressable)
    input  logic [7:0]   dbg_addr,      // Byte address within debug space
    output logic [31:0]  dbg_rdata
);

    // Capture registers
    logic [127:0] last_rx_hdr;
    logic [63:0]  last_rx_data;
    logic [127:0] last_tx_hdr;
    logic [63:0]  last_tx_data;
    logic [31:0]  rx_count;
    logic [31:0]  tx_count;
    logic [63:0]  cycle_count;
    logic [31:0]  rx_ready_cnt;
    logic [31:0]  tx_ready_cnt;
    logic         rx_seen, tx_seen;
    logic [7:0]   last_rx_type;

    // Capture on valid TLPs
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            last_rx_hdr <= 128'b0;
            last_rx_data <= 64'b0;
            last_tx_hdr <= 128'b0;
            last_tx_data <= 64'b0;
            rx_count <= 32'b0;
            tx_count <= 32'b0;
            cycle_count <= 64'b0;
            rx_ready_cnt <= 32'b0;
            tx_ready_cnt <= 32'b0;
            rx_seen <= 0;
            tx_seen <= 0;
            last_rx_type <= 8'b0;
        end else begin
            cycle_count <= cycle_count + 1;
            
            // Count ready cycles
            if (rx_st_ready) rx_ready_cnt <= rx_ready_cnt + 1;
            if (tx_st_ready) tx_ready_cnt <= tx_ready_cnt + 1;

            // Capture RX TLP
            if (rx_st_hvalid && rx_st_sop && rx_st_ready) begin
                last_rx_hdr <= rx_st_hdr;
                last_rx_data <= rx_st_data[63:0];
                rx_count <= rx_count + 1;
                rx_seen <= 1;
                last_rx_type <= {rx_st_hdr[127:125], rx_st_hdr[124:120]}; // fmt + type
            end

            // Capture TX TLP
            if (tx_st_hvalid && tx_st_sop) begin
                last_tx_hdr <= tx_st_hdr;
                last_tx_data <= tx_st_data[63:0];
                tx_count <= tx_count + 1;
                tx_seen <= 1;
            end
        end
    end

    // Read mux
    always_comb begin
        case (dbg_addr[7:2])  // Word address
            6'h00: dbg_rdata = {16'b0, last_rx_type, tx_state, 2'b0, tx_seen, rx_seen};
            6'h01: dbg_rdata = rx_count;
            6'h02: dbg_rdata = tx_count;
            6'h03: dbg_rdata = 32'b0;  // Control (write-only)
            6'h04: dbg_rdata = last_rx_hdr[31:0];
            6'h05: dbg_rdata = last_rx_hdr[63:32];
            6'h06: dbg_rdata = last_rx_hdr[95:64];
            6'h07: dbg_rdata = last_rx_hdr[127:96];
            6'h08: dbg_rdata = last_rx_data[31:0];
            6'h09: dbg_rdata = last_rx_data[63:32];
            6'h0A: dbg_rdata = last_tx_hdr[31:0];
            6'h0B: dbg_rdata = last_tx_hdr[63:32];
            6'h0C: dbg_rdata = last_tx_hdr[95:64];
            6'h0D: dbg_rdata = last_tx_hdr[127:96];
            6'h0E: dbg_rdata = last_tx_data[31:0];
            6'h0F: dbg_rdata = last_tx_data[63:32];
            6'h10: dbg_rdata = cycle_count[31:0];
            6'h11: dbg_rdata = cycle_count[63:32];
            6'h12: dbg_rdata = rx_ready_cnt;
            6'h13: dbg_rdata = tx_ready_cnt;
            default: dbg_rdata = 32'hDEAD_BEEF;
        endcase
    end

endmodule
