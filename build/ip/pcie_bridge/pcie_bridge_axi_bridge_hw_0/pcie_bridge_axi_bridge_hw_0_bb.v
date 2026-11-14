module pcie_bridge_axi_bridge_hw_0 (
		input  wire         Clk_i,                    //         clk.clk
		input  wire         Rstn_i,                   //       reset.reset_n
		input  wire [255:0] rx_st0_payload_i,         //      rx_st0.data
		input  wire         rx_st0_sop_i,             //            .startofpacket
		input  wire         rx_st0_eop_i,             //            .endofpacket
		input  wire         rx_st0_dvalid_i,          //            .valid
		input  wire [2:0]   rx_st0_empty_i,           //            .empty
		output wire         rx_st_ready_o,            //            .ready
		input  wire [255:0] rx_st1_payload_i,         //      rx_st1.data
		input  wire         rx_st1_sop_i,             //            .startofpacket
		input  wire         rx_st1_eop_i,             //            .endofpacket
		input  wire         rx_st1_dvalid_i,          //            .valid
		input  wire [2:0]   rx_st1_empty_i,           //            .empty
		input  wire [255:0] rx_st2_payload_i,         //      rx_st2.data
		input  wire         rx_st2_sop_i,             //            .startofpacket
		input  wire         rx_st2_eop_i,             //            .endofpacket
		input  wire         rx_st2_dvalid_i,          //            .valid
		input  wire [2:0]   rx_st2_empty_i,           //            .empty
		input  wire [255:0] rx_st3_payload_i,         //      rx_st3.data
		input  wire         rx_st3_sop_i,             //            .startofpacket
		input  wire         rx_st3_eop_i,             //            .endofpacket
		input  wire         rx_st3_dvalid_i,          //            .valid
		input  wire [2:0]   rx_st3_empty_i,           //            .empty
		output wire [2:0]   rx_st_hcrdt_init_o,       // rx_st0_misc.rx_st_Hcrdt_init
		output wire [2:0]   rx_st_hcrdt_update_o,     //            .rx_st_Hcrdt_update
		output wire [5:0]   rx_st_hcrdt_update_cnt_o, //            .rx_st_Hcrdt_update_cnt
		input  wire [2:0]   rx_st_hcrdt_init_ack_i,   //            .rx_st_Hcrdt_init_ack
		output wire [2:0]   rx_st_dcrdt_init_o,       //            .rx_st_Dcrdt_init
		output wire [2:0]   rx_st_dcrdt_update_o,     //            .rx_st_Dcrdt_update
		output wire [11:0]  rx_st_dcrdt_update_cnt_o, //            .rx_st_Dcrdt_update_cnt
		input  wire [2:0]   rx_st_dcrdt_init_ack_i,   //            .rx_st_Dcrdt_init_ack
		input  wire [127:0] rx_st0_header_i,          //            .rx_st0_hdr
		input  wire [31:0]  rx_st0_tlp_prfx_i,        //            .rx_st0_prefix
		input  wire         rx_st0_hvalid_i,          //            .rx_st0_hvalid
		input  wire         rx_st0_pvalid_i,          //            .rx_st0_pvalid
		input  wire [2:0]   rx_st0_bar_i,             //            .rx_st0_bar
		input  wire [127:0] rx_st1_header_i,          //            .rx_st1_hdr
		input  wire [31:0]  rx_st1_tlp_prfx_i,        //            .rx_st1_prefix
		input  wire         rx_st1_hvalid_i,          //            .rx_st1_hvalid
		input  wire         rx_st1_pvalid_i,          //            .rx_st1_pvalid
		input  wire [2:0]   rx_st1_bar_i,             //            .rx_st1_bar
		input  wire [127:0] rx_st2_header_i,          //            .rx_st2_hdr
		input  wire [31:0]  rx_st2_tlp_prfx_i,        //            .rx_st2_prefix
		input  wire         rx_st2_hvalid_i,          //            .rx_st2_hvalid
		input  wire         rx_st2_pvalid_i,          //            .rx_st2_pvalid
		input  wire [2:0]   rx_st2_bar_i,             //            .rx_st2_bar
		input  wire [127:0] rx_st3_header_i,          //            .rx_st3_hdr
		input  wire [31:0]  rx_st3_tlp_prfx_i,        //            .rx_st3_prefix
		input  wire         rx_st3_hvalid_i,          //            .rx_st3_hvalid
		input  wire         rx_st3_pvalid_i,          //            .rx_st3_pvalid
		input  wire [2:0]   rx_st3_bar_i,             //            .rx_st3_bar
		output wire [255:0] tx_st0_payload_o,         //      tx_st0.data
		output wire         tx_st0_sop_o,             //            .startofpacket
		output wire         tx_st0_eop_o,             //            .endofpacket
		output wire         tx_st0_dvalid_o,          //            .valid
		input  wire         tx_st_ready_i,            //            .ready
		output wire [255:0] tx_st1_payload_o,         //      tx_st1.data
		output wire         tx_st1_sop_o,             //            .startofpacket
		output wire         tx_st1_eop_o,             //            .endofpacket
		output wire         tx_st1_dvalid_o,          //            .valid
		output wire [255:0] tx_st2_payload_o,         //      tx_st2.data
		output wire         tx_st2_sop_o,             //            .startofpacket
		output wire         tx_st2_eop_o,             //            .endofpacket
		output wire         tx_st2_dvalid_o,          //            .valid
		output wire [255:0] tx_st3_payload_o,         //      tx_st3.data
		output wire         tx_st3_sop_o,             //            .startofpacket
		output wire         tx_st3_eop_o,             //            .endofpacket
		output wire         tx_st3_dvalid_o,          //            .valid
		output wire [127:0] tx_st0_header_o,          // tx_st0_misc.tx_st0_hdr
		output wire [127:0] tx_st1_header_o,          //            .tx_st1_hdr
		output wire [127:0] tx_st2_header_o,          //            .tx_st2_hdr
		output wire [127:0] tx_st3_header_o,          //            .tx_st3_hdr
		input  wire [2:0]   tx_st_hcrdt_init_i,       //            .tx_st_Hcrdt_init
		input  wire [2:0]   tx_st_hcrdt_update_i,     //            .tx_st_Hcrdt_update
		input  wire [5:0]   tx_st_hcrdt_update_cnt_i, //            .tx_st_Hcrdt_update_cnt
		output wire [2:0]   tx_st_hcrdt_init_ack_o,   //            .tx_st_Hcrdtt_init_ack
		input  wire [2:0]   tx_st_dcrdt_init_i,       //            .tx_st_Dcrdt_init
		input  wire [2:0]   tx_st_dcrdt_update_i,     //            .tx_st_Dcrdt_update
		input  wire [11:0]  tx_st_dcrdt_update_cnt_i, //            .tx_st_Dcrdt_update_cnt
		output wire [2:0]   tx_st_dcrdt_init_ack_o,   //            .tx_st_Dcrdt_init_ack
		output wire [31:0]  tx_st0_prefix_o,          //            .tx_st0_prefix
		output wire         tx_st0_hvalid_o,          //            .tx_st0_hvalid
		output wire         tx_st0_pvalid_o,          //            .tx_st0_pvalid
		output wire [31:0]  tx_st1_prefix_o,          //            .tx_st1_prefix
		output wire         tx_st1_hvalid_o,          //            .tx_st1_hvalid
		output wire         tx_st1_pvalid_o,          //            .tx_st1_pvalid
		output wire [31:0]  tx_st2_prefix_o,          //            .tx_st2_prefix
		output wire         tx_st2_hvalid_o,          //            .tx_st2_hvalid
		output wire         tx_st2_pvalid_o,          //            .tx_st2_pvalid
		output wire [31:0]  tx_st3_prefix_o,          //            .tx_st3_prefix
		output wire         tx_st3_hvalid_o,          //            .tx_st3_hvalid
		output wire         tx_st3_pvalid_o           //            .tx_st3_pvalid
	);
endmodule

