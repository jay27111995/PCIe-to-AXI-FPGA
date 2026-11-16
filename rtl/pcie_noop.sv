//-----------------------------------------------------------------------------
// pcie_noop.sv - Minimal PCIe endpoint that doesn't respond to anything
//
// This design accepts TLPs but never responds. Use this to test if the
// crash is caused by our completion response or something else.
//
// Expected behavior: Host reads will timeout, but system should NOT crash.
//-----------------------------------------------------------------------------
`timescale 1ps/1ps
`default_nettype none

module pcie_noop (
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

    // Status (unused)
    input  logic         link_up,
    input  logic [5:0]   ltssm_state
);

    //=========================================================================
    // Credit initialization - advertise infinite credits to receive TLPs
    //=========================================================================
    logic [7:0] init_cnt;
    logic init_done;
    
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            init_cnt <= 0;
            init_done <= 0;
            rx_hcrdt_init <= 0;
            rx_dcrdt_init <= 0;
            rx_hcrdt_update <= 0;
            rx_dcrdt_update <= 0;
            tx_hcrdt_init_ack <= 0;
            tx_dcrdt_init_ack <= 0;
        end else begin
            // Ack any TX credit init from host
            tx_hcrdt_init_ack <= tx_hcrdt_init;
            tx_dcrdt_init_ack <= tx_dcrdt_init;
            
            if (!init_done) begin
                init_cnt <= init_cnt + 1;
                
                // Start credit init after a few cycles
                if (init_cnt >= 10 && init_cnt < 20) begin
                    rx_hcrdt_init <= 3'b111;  // All types
                    rx_dcrdt_init <= 3'b111;
                    rx_hcrdt_update <= 3'b111;
                    rx_dcrdt_update <= 3'b111;
                end else if (init_cnt >= 20) begin
                    rx_hcrdt_init <= 0;
                    rx_dcrdt_init <= 0;
                    rx_hcrdt_update <= 0;
                    rx_dcrdt_update <= 0;
                    init_done <= 1;
                end
            end else begin
                // After init, occasionally return credits
                rx_hcrdt_update <= 0;
                rx_dcrdt_update <= 0;
                
                // Return credits when we consume a TLP
                if (rx_st_hvalid && rx_st_sop) begin
                    if (rx_st_hdr[127:125] == 3'b000 || rx_st_hdr[127:125] == 3'b001) begin
                        // MRd (non-posted) - return NP credit
                        rx_hcrdt_update <= 3'b010;
                    end else begin
                        // Posted (MWr) - return Posted credit
                        rx_hcrdt_update <= 3'b001;
                        if (rx_st_dvalid)
                            rx_dcrdt_update <= 3'b001;
                    end
                end
            end
        end
    end
    
    // Advertise max credits
    assign rx_hcrdt_update_cnt = 6'h3F;
    assign rx_dcrdt_update_cnt = 12'hFFF;

    //=========================================================================
    // Accept all TLPs but never respond
    //=========================================================================
    assign rx_st_ready = init_done;  // Ready after credit init
    
    // Never send anything
    assign tx_st_hdr = '0;
    assign tx_st_data = '0;
    assign tx_st_sop = 0;
    assign tx_st_eop = 0;
    assign tx_st_hvalid = 0;
    assign tx_st_dvalid = 0;

endmodule

`default_nettype wire
