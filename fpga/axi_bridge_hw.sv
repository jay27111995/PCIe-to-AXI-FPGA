//-----------------------------------------------------------------------------
// axi_bridge_hw.sv - Qsys wrapper for top
//
// Adapts R-Tile 4-segment Avalon-ST interface to our single-segment design.
// We only process one TLP at a time (segment 0 priority).
//-----------------------------------------------------------------------------
`timescale 1ps/1ps
`default_nettype none

module axi_bridge_hw (
    input  wire          Clk_i,
    input  wire          Rstn_i,

    //-------------------------------------------------------------------------
    // RX Avalon-ST (4 segments, from R-Tile)
    //-------------------------------------------------------------------------
    input  wire [255:0]  rx_st0_payload_i,
    input  wire          rx_st0_sop_i,
    input  wire          rx_st0_eop_i,
    input  wire          rx_st0_dvalid_i,
    input  wire [2:0]    rx_st0_empty_i,
    output logic         rx_st_ready_o,

    input  wire [255:0]  rx_st1_payload_i,
    input  wire          rx_st1_sop_i,
    input  wire          rx_st1_eop_i,
    input  wire          rx_st1_dvalid_i,
    input  wire [2:0]    rx_st1_empty_i,

    input  wire [255:0]  rx_st2_payload_i,
    input  wire          rx_st2_sop_i,
    input  wire          rx_st2_eop_i,
    input  wire          rx_st2_dvalid_i,
    input  wire [2:0]    rx_st2_empty_i,

    input  wire [255:0]  rx_st3_payload_i,
    input  wire          rx_st3_sop_i,
    input  wire          rx_st3_eop_i,
    input  wire          rx_st3_dvalid_i,
    input  wire [2:0]    rx_st3_empty_i,

    //-------------------------------------------------------------------------
    // RX sideband (headers, BAR, credits)
    //-------------------------------------------------------------------------
    input  wire [127:0]  rx_st0_header_i,
    input  wire [31:0]   rx_st0_tlp_prfx_i,
    input  wire          rx_st0_hvalid_i,
    input  wire          rx_st0_pvalid_i,
    input  wire [2:0]    rx_st0_bar_i,

    input  wire [127:0]  rx_st1_header_i,
    input  wire [31:0]   rx_st1_tlp_prfx_i,
    input  wire          rx_st1_hvalid_i,
    input  wire          rx_st1_pvalid_i,
    input  wire [2:0]    rx_st1_bar_i,

    input  wire [127:0]  rx_st2_header_i,
    input  wire [31:0]   rx_st2_tlp_prfx_i,
    input  wire          rx_st2_hvalid_i,
    input  wire          rx_st2_pvalid_i,
    input  wire [2:0]    rx_st2_bar_i,

    input  wire [127:0]  rx_st3_header_i,
    input  wire [31:0]   rx_st3_tlp_prfx_i,
    input  wire          rx_st3_hvalid_i,
    input  wire          rx_st3_pvalid_i,
    input  wire [2:0]    rx_st3_bar_i,

    // RX credits
    output logic [2:0]   rx_st_hcrdt_init_o,
    output logic [2:0]   rx_st_hcrdt_update_o,
    output logic [5:0]   rx_st_hcrdt_update_cnt_o,
    input  wire  [2:0]   rx_st_hcrdt_init_ack_i,
    output logic [2:0]   rx_st_dcrdt_init_o,
    output logic [2:0]   rx_st_dcrdt_update_o,
    output logic [11:0]  rx_st_dcrdt_update_cnt_o,
    input  wire  [2:0]   rx_st_dcrdt_init_ack_i,

    //-------------------------------------------------------------------------
    // TX Avalon-ST (4 segments, to R-Tile)
    //-------------------------------------------------------------------------
    output logic [255:0] tx_st0_payload_o,
    output logic         tx_st0_sop_o,
    output logic         tx_st0_eop_o,
    output logic         tx_st0_dvalid_o,
    input  wire          tx_st_ready_i,

    output logic [255:0] tx_st1_payload_o,
    output logic         tx_st1_sop_o,
    output logic         tx_st1_eop_o,
    output logic         tx_st1_dvalid_o,

    output logic [255:0] tx_st2_payload_o,
    output logic         tx_st2_sop_o,
    output logic         tx_st2_eop_o,
    output logic         tx_st2_dvalid_o,

    output logic [255:0] tx_st3_payload_o,
    output logic         tx_st3_sop_o,
    output logic         tx_st3_eop_o,
    output logic         tx_st3_dvalid_o,

    //-------------------------------------------------------------------------
    // TX sideband (headers, prefix, credits)
    //-------------------------------------------------------------------------
    output logic [127:0] tx_st0_header_o,
    output logic [31:0]  tx_st0_prefix_o,
    output logic         tx_st0_hvalid_o,
    output logic         tx_st0_pvalid_o,

    output logic [127:0] tx_st1_header_o,
    output logic [31:0]  tx_st1_prefix_o,
    output logic         tx_st1_hvalid_o,
    output logic         tx_st1_pvalid_o,

    output logic [127:0] tx_st2_header_o,
    output logic [31:0]  tx_st2_prefix_o,
    output logic         tx_st2_hvalid_o,
    output logic         tx_st2_pvalid_o,

    output logic [127:0] tx_st3_header_o,
    output logic [31:0]  tx_st3_prefix_o,
    output logic         tx_st3_hvalid_o,
    output logic         tx_st3_pvalid_o,

    // TX credits
    input  wire  [2:0]   tx_st_hcrdt_init_i,
    input  wire  [2:0]   tx_st_hcrdt_update_i,
    input  wire  [5:0]   tx_st_hcrdt_update_cnt_i,
    output logic [2:0]   tx_st_hcrdt_init_ack_o,
    input  wire  [2:0]   tx_st_dcrdt_init_i,
    input  wire  [2:0]   tx_st_dcrdt_update_i,
    input  wire  [11:0]  tx_st_dcrdt_update_cnt_i,
    output logic [2:0]   tx_st_dcrdt_init_ack_o
);

    //=========================================================================
    // RX: Select first valid segment (priority 0 > 1 > 2 > 3)
    //=========================================================================
    logic [127:0] rx_hdr;
    logic [255:0] rx_data;
    logic         rx_sop, rx_eop, rx_hvalid, rx_dvalid;
    logic [2:0]   rx_bar;

    always_comb begin
        if (rx_st0_hvalid_i) begin
            rx_hdr    = rx_st0_header_i;
            rx_data   = rx_st0_payload_i;
            rx_sop    = rx_st0_sop_i;
            rx_eop    = rx_st0_eop_i;
            rx_hvalid = 1'b1;
            rx_dvalid = rx_st0_dvalid_i;
            rx_bar    = rx_st0_bar_i;
        end else if (rx_st1_hvalid_i) begin
            rx_hdr    = rx_st1_header_i;
            rx_data   = rx_st1_payload_i;
            rx_sop    = rx_st1_sop_i;
            rx_eop    = rx_st1_eop_i;
            rx_hvalid = 1'b1;
            rx_dvalid = rx_st1_dvalid_i;
            rx_bar    = rx_st1_bar_i;
        end else if (rx_st2_hvalid_i) begin
            rx_hdr    = rx_st2_header_i;
            rx_data   = rx_st2_payload_i;
            rx_sop    = rx_st2_sop_i;
            rx_eop    = rx_st2_eop_i;
            rx_hvalid = 1'b1;
            rx_dvalid = rx_st2_dvalid_i;
            rx_bar    = rx_st2_bar_i;
        end else if (rx_st3_hvalid_i) begin
            rx_hdr    = rx_st3_header_i;
            rx_data   = rx_st3_payload_i;
            rx_sop    = rx_st3_sop_i;
            rx_eop    = rx_st3_eop_i;
            rx_hvalid = 1'b1;
            rx_dvalid = rx_st3_dvalid_i;
            rx_bar    = rx_st3_bar_i;
        end else begin
            rx_hdr    = '0;
            rx_data   = '0;
            rx_sop    = 1'b0;
            rx_eop    = 1'b0;
            rx_hvalid = 1'b0;
            rx_dvalid = 1'b0;
            rx_bar    = '0;
        end
    end

    //=========================================================================
    // TX: Only use segment 0, tie off 1-3
    //=========================================================================
    logic [127:0] tx_hdr;
    logic [255:0] tx_data;
    logic         tx_sop, tx_eop, tx_hvalid, tx_dvalid;

    // Segment 0 - active
    assign tx_st0_header_o  = tx_hdr;
    assign tx_st0_payload_o = tx_data;
    assign tx_st0_sop_o     = tx_sop;
    assign tx_st0_eop_o     = tx_eop;
    assign tx_st0_hvalid_o  = tx_hvalid;
    assign tx_st0_dvalid_o  = tx_dvalid;
    assign tx_st0_pvalid_o  = 1'b0;
    assign tx_st0_prefix_o  = '0;

    // Segments 1-3 - unused
    assign tx_st1_header_o  = '0;  assign tx_st1_payload_o = '0;
    assign tx_st1_sop_o     = '0;  assign tx_st1_eop_o     = '0;
    assign tx_st1_hvalid_o  = '0;  assign tx_st1_dvalid_o  = '0;
    assign tx_st1_pvalid_o  = '0;  assign tx_st1_prefix_o  = '0;

    assign tx_st2_header_o  = '0;  assign tx_st2_payload_o = '0;
    assign tx_st2_sop_o     = '0;  assign tx_st2_eop_o     = '0;
    assign tx_st2_hvalid_o  = '0;  assign tx_st2_dvalid_o  = '0;
    assign tx_st2_pvalid_o  = '0;  assign tx_st2_prefix_o  = '0;

    assign tx_st3_header_o  = '0;  assign tx_st3_payload_o = '0;
    assign tx_st3_sop_o     = '0;  assign tx_st3_eop_o     = '0;
    assign tx_st3_hvalid_o  = '0;  assign tx_st3_dvalid_o  = '0;
    assign tx_st3_pvalid_o  = '0;  assign tx_st3_prefix_o  = '0;

    //=========================================================================
    // Core: PCIe-to-AXI bridge with RAM and DMA
    //=========================================================================
    top u_core (
        .clk                  (Clk_i),
        .rst_n                (Rstn_i),

        // RX TLP
        .rx_st_hdr            (rx_hdr),
        .rx_st_data           (rx_data),
        .rx_st_sop            (rx_sop),
        .rx_st_eop            (rx_eop),
        .rx_st_hvalid         (rx_hvalid),
        .rx_st_dvalid         (rx_dvalid),
        .rx_st_bar            (rx_bar),
        .rx_st_ready          (rx_st_ready_o),

        // TX TLP
        .tx_st_hdr            (tx_hdr),
        .tx_st_data           (tx_data),
        .tx_st_sop            (tx_sop),
        .tx_st_eop            (tx_eop),
        .tx_st_hvalid         (tx_hvalid),
        .tx_st_dvalid         (tx_dvalid),
        .tx_st_ready          (tx_st_ready_i),

        // RX credits (we advertise to host)
        .rx_hcrdt_init        (rx_st_hcrdt_init_o),
        .rx_hcrdt_update      (rx_st_hcrdt_update_o),
        .rx_hcrdt_update_cnt  (rx_st_hcrdt_update_cnt_o),
        .rx_dcrdt_init        (rx_st_dcrdt_init_o),
        .rx_dcrdt_update      (rx_st_dcrdt_update_o),
        .rx_dcrdt_update_cnt  (rx_st_dcrdt_update_cnt_o),

        // TX credits (host advertises to us)
        .tx_hcrdt_init        (tx_st_hcrdt_init_i),
        .tx_hcrdt_init_ack    (tx_st_hcrdt_init_ack_o),
        .tx_hcrdt_update      (tx_st_hcrdt_update_i),
        .tx_hcrdt_update_cnt  (tx_st_hcrdt_update_cnt_i),
        .tx_dcrdt_init        (tx_st_dcrdt_init_i),
        .tx_dcrdt_init_ack    (tx_st_dcrdt_init_ack_o),
        .tx_dcrdt_update      (tx_st_dcrdt_update_i),
        .tx_dcrdt_update_cnt  (tx_st_dcrdt_update_cnt_i),

        // Status
        .link_up              (1'b1),
        .ltssm_state          (6'h11)   // L0
    );

endmodule

`default_nettype wire
