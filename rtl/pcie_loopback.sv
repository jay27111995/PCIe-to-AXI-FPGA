//-----------------------------------------------------------------------------
// pcie_loopback.sv - Minimal PCIe loopback for debugging
//
// Returns 0xDEADBEEF_12345678 for any BAR0 read.
// No DMA, no AXI, just the simplest possible response.
//-----------------------------------------------------------------------------
`timescale 1ps/1ps
`default_nettype none

module pcie_loopback
    import rtile_pkg::*;
#(
    parameter logic [15:0] COMPLETER_ID = 16'hB400  // BDF b4:00.0
)
(
    input  logic clk,
    input  logic rst_n,

    // RX TLP from R-Tile (one segment)
    input  logic [127:0] rx_st_hdr,
    input  logic [255:0] rx_st_data,
    input  logic         rx_st_sop,
    input  logic         rx_st_eop,
    input  logic         rx_st_hvalid,
    input  logic         rx_st_dvalid,
    input  logic [2:0]   rx_st_bar,
    output logic         rx_st_ready,

    // TX TLP to R-Tile (one segment)
    output logic [127:0] tx_st_hdr,
    output logic [255:0] tx_st_data,
    output logic         tx_st_sop,
    output logic         tx_st_eop,
    output logic         tx_st_hvalid,
    output logic         tx_st_dvalid,
    input  logic         tx_st_ready,

    // Credits
    output logic [2:0]   rx_hcrdt_init,
    output logic [2:0]   rx_hcrdt_update,
    output logic [5:0]   rx_hcrdt_update_cnt,
    output logic [2:0]   rx_dcrdt_init,
    output logic [2:0]   rx_dcrdt_update,
    output logic [11:0]  rx_dcrdt_update_cnt,
    input  logic [2:0]   tx_hcrdt_init,
    output logic [2:0]   tx_hcrdt_init_ack,
    input  logic [2:0]   tx_hcrdt_update,
    input  logic [5:0]   tx_hcrdt_update_cnt,
    input  logic [2:0]   tx_dcrdt_init,
    output logic [2:0]   tx_dcrdt_init_ack,
    input  logic [2:0]   tx_dcrdt_update,
    input  logic [11:0]  tx_dcrdt_update_cnt,

    // Status (unused but kept for interface compatibility)
    input  logic         link_up,
    input  logic [5:0]   ltssm_state
);

    // Simple credit init - advertise infinite
    logic [3:0] credit_cnt;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            credit_cnt <= 0;
            rx_hcrdt_init <= 0;
            rx_dcrdt_init <= 0;
            rx_hcrdt_update <= 0;
            rx_dcrdt_update <= 0;
            tx_hcrdt_init_ack <= 0;
            tx_dcrdt_init_ack <= 0;
        end else begin
            credit_cnt <= credit_cnt + 1;
            
            // Credit init sequence
            if (credit_cnt < 4) begin
                rx_hcrdt_init <= 3'b111;
                rx_dcrdt_init <= 3'b111;
                rx_hcrdt_update <= 3'b111;
                rx_dcrdt_update <= 3'b111;
            end else begin
                rx_hcrdt_init <= 0;
                rx_dcrdt_init <= 0;
                rx_hcrdt_update <= 0;
                rx_dcrdt_update <= 0;
            end
            
            // Ack TX credits from host
            tx_hcrdt_init_ack <= tx_hcrdt_init;
            tx_dcrdt_init_ack <= tx_dcrdt_init;
        end
    end
    
    assign rx_hcrdt_update_cnt = 6'h3F;  // Max credits
    assign rx_dcrdt_update_cnt = 12'hFFF;

    // RX Header decode
    wire [2:0]  rx_fmt  = rx_st_hdr[127:125];
    wire [4:0]  rx_type = rx_st_hdr[124:120];
    wire [15:0] rx_rid  = rx_st_hdr[95:80];
    wire [7:0]  rx_tag  = rx_st_hdr[79:72];
    wire [6:0]  rx_lower_addr = rx_st_hdr[38:32];  // For 3DW: addr[6:0] from DW2

    wire rx_is_mrd = rx_st_hvalid && rx_st_sop && (rx_type == 5'b00000) && !rx_fmt[1];
    wire rx_is_mwr = rx_st_hvalid && rx_st_sop && (rx_type == 5'b00000) && rx_fmt[1];

    // State machine
    typedef enum logic [1:0] {
        IDLE,
        SEND_CPL
    } state_e;
    
    state_e state;
    
    // Captured request info
    logic [15:0] req_rid;
    logic [7:0]  req_tag;
    logic [6:0]  req_lower_addr;
    
    // TX registers
    logic [127:0] tx_hdr_r;
    logic [63:0]  tx_data_r;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            state <= IDLE;
            tx_st_hvalid <= 0;
            tx_st_dvalid <= 0;
            tx_st_sop <= 0;
            tx_st_eop <= 0;
            req_rid <= 0;
            req_tag <= 0;
            req_lower_addr <= 0;
        end else begin
            case (state)
                IDLE: begin
                    tx_st_hvalid <= 0;
                    tx_st_dvalid <= 0;
                    tx_st_sop <= 0;
                    tx_st_eop <= 0;
                    
                    // Capture MRd and prepare completion
                    if (rx_is_mrd && rx_st_bar == 3'd0) begin
                        req_rid <= rx_rid;
                        req_tag <= rx_tag;
                        req_lower_addr <= rx_lower_addr;
                        
                        // Build CplD header (Big Endian: DW0 at [127:96])
                        tx_hdr_r <= {
                            // DW0: Fmt=010 (3DW+data), Type=01010 (CplD), Length=2DW
                            {3'b010, 5'b01010, 1'b0, 3'b000, 4'b0, 1'b0, 1'b0, 2'b00, 10'd2},
                            // DW1: Completer ID, Status=000, BCM=0, Byte Count=8
                            {COMPLETER_ID, 3'b000, 1'b0, 12'd8},
                            // DW2: Requester ID, Tag, Lower Address
                            {rx_rid, rx_tag, 1'b0, rx_lower_addr},
                            // DW3: unused
                            32'b0
                        };
                        tx_data_r <= 64'hDEADBEEF_12345678;
                        
                        tx_st_sop <= 1;
                        tx_st_eop <= 1;
                        tx_st_hvalid <= 1;
                        tx_st_dvalid <= 1;
                        state <= SEND_CPL;
                    end
                    // Ignore MWr (no response needed)
                end
                
                SEND_CPL: begin
                    if (tx_st_ready) begin
                        tx_st_hvalid <= 0;
                        tx_st_dvalid <= 0;
                        tx_st_sop <= 0;
                        tx_st_eop <= 0;
                        state <= IDLE;
                    end
                end
            endcase
        end
    end

    assign tx_st_hdr = tx_hdr_r;
    assign tx_st_data = {192'b0, tx_data_r};
    
    // Only accept RX when idle
    assign rx_st_ready = (state == IDLE);

endmodule

`default_nettype wire
