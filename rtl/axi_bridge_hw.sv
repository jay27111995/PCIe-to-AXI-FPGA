`timescale 1 ps / 1 ps

`default_nettype none


package pcie_tlp_pkg;

  typedef enum logic [7:0] {
    FMT_TYPE_MRd_32 = 8'b000_00000,
    FMT_TYPE_MRd_64 = 8'b001_00000,
    FMT_TYPE_MWr_32 = 8'b010_00000,
    FMT_TYPE_MWr_64 = 8'b011_00000,
    FMT_TYPE_Cpl    = 8'b000_01010,
    FMT_TYPE_CplD   = 8'b010_01010
  } tlp_fmt_type_e;

  typedef struct packed {
    tlp_fmt_type_e fmt_type;  // [31:29] - Fmt
                              // [28:24] - Type
    logic       t9;           // [23]    - Tag[9]
    logic [2:0] tc;           // [22:20] - Traffic Class
    logic       t8;           // [19]    - Tag[8]
    logic       attr2;        // [18]    - Attr[2]
    logic       ln;           // [17]    - TLP Processing Hints present
    logic       th;           // [16]    - TLP Processing Hints present
    logic       td;           // [15]    - TLP Digest (ECRC) present
    logic       ep;           // [14]    - Poisoned TLP
    logic [1:0] attr;         // [13:12] - {RO, NS}
    logic [1:0] at;           // [11:10] - Address Translation
    logic [9:0] length;       // [9:0]   - Data length in DWs
  } tlp_dw0_t;

  // 3-DW Request header (32-bit address)
  typedef struct packed {
    // DW0
    tlp_dw0_t    dw0;
    // DW1
    logic [15:0] requester_id; // [31:16] - Requester ID
    logic [7:0]  tag;          // [15:8]  - Tag[7:0]
    logic [3:0]  last_dw_be;   // [7:4]   - Last DW BE
    logic [3:0]  first_dw_be;  // [3:0]   - First DW BE
    // DW2
    logic [29:0] addr;         // [31:2]  - Address[31:2]
    logic [1:0]  ph;           // [1:0]   - Processing Hints
  } tlp_req_hdr_3dw_t;

  // 4-DW Request header (64-bit address)
  typedef struct packed {
    // DW0
    tlp_dw0_t    dw0;
    // DW1
    logic [15:0] requester_id; // [31:16] - Requester ID
    logic [7:0]  tag;          // [15:8]  - Tag[7:0]
    logic [3:0]  last_dw_be;   // [7:4]   - Last DW BE
    logic [3:0]  first_dw_be;  // [3:0]   - First DW BE
    // DW2
    logic [31:0] addr_hi;      // [31:0]  - Address[63:32]
    // DW3
    logic [29:0] addr_lo;      // [31:2]  - Address[31:2]
    logic [1:0]  ph;           // [1:0]   - Processing Hints
  } tlp_req_hdr_4dw_t;

  // 3-DW Completion header
  typedef struct packed {
    // DW0
    tlp_dw0_t    dw0;
    // DW1
    logic [15:0] completer_id; // [31:16] - Completer ID
    logic [2:0]  cpl_status;   // [15:13] - Completion Status
    logic        bcm;          // [12]    -
    logic [11:0] byte_count;   // [11:0]  - Byte Count
    // DW2
    logic [15:0] requester_id; // [31:16] - Requester ID
    logic [7:0]  tag;          // [15:8]  - Tag[7:0]
    logic        rsrvd;        // [7]     - Reserved
    logic [6:0]  lower_addr;   // [6:0]   - Lower Address bits
  } tlp_cpl_hdr_t;

endpackage : pcie_tlp_pkg

import pcie_tlp_pkg::*;

module axi_bridge_hw (
    input  wire          Clk_i,                    //         clk.clk
    input  wire          Rstn_i,                   //       reset.reset_n
    input  wire  [255:0] rx_st0_payload_i,         //      rx_st0.data
    input  wire          rx_st0_sop_i,             //            .startofpacket
    input  wire          rx_st0_eop_i,             //            .endofpacket
    input  wire          rx_st0_dvalid_i,          //            .valid
    input  wire  [2:0]   rx_st0_empty_i,           //            .empty
    output logic         rx_st_ready_o,            //            .ready
    input  wire  [255:0] rx_st1_payload_i,         //      rx_st1.data
    input  wire          rx_st1_sop_i,             //            .startofpacket
    input  wire          rx_st1_eop_i,             //            .endofpacket
    input  wire          rx_st1_dvalid_i,          //            .valid
    input  wire  [2:0]   rx_st1_empty_i,           //            .empty
    input  wire  [255:0] rx_st2_payload_i,         //      rx_st2.data
    input  wire          rx_st2_sop_i,             //            .startofpacket
    input  wire          rx_st2_eop_i,             //            .endofpacket
    input  wire          rx_st2_dvalid_i,          //            .valid
    input  wire  [2:0]   rx_st2_empty_i,           //            .empty
    input  wire  [255:0] rx_st3_payload_i,         //      rx_st3.data
    input  wire          rx_st3_sop_i,             //            .startofpacket
    input  wire          rx_st3_eop_i,             //            .endofpacket
    input  wire          rx_st3_dvalid_i,          //            .valid
    input  wire  [2:0]   rx_st3_empty_i,           //            .empty
    output logic [2:0]   rx_st_hcrdt_init_o,       // rx_st0_misc.rx_st_Hcrdt_init
    output logic [2:0]   rx_st_hcrdt_update_o,     //            .rx_st_Hcrdt_update
    output logic [5:0]   rx_st_hcrdt_update_cnt_o, //            .rx_st_Hcrdt_update_cnt
    input  wire  [2:0]   rx_st_hcrdt_init_ack_i,   //            .rx_st_Hcrdt_init_ack
    output logic [2:0]   rx_st_dcrdt_init_o,       //            .rx_st_Dcrdt_init
    output logic [2:0]   rx_st_dcrdt_update_o,     //            .rx_st_Dcrdt_update
    output logic [11:0]  rx_st_dcrdt_update_cnt_o, //            .rx_st_Dcrdt_update_cnt
    input  wire  [2:0]   rx_st_dcrdt_init_ack_i,   //            .rx_st_Dcrdt_init_ack
    input  wire  [127:0] rx_st0_header_i,          //            .rx_st0_hdr
    input  wire  [31:0]  rx_st0_tlp_prfx_i,        //            .rx_st0_prefix
    input  wire          rx_st0_hvalid_i,          //            .rx_st0_hvalid
    input  wire          rx_st0_pvalid_i,          //            .rx_st0_pvalid
    input  wire  [2:0]   rx_st0_bar_i,             //            .rx_st0_bar
    input  wire  [127:0] rx_st1_header_i,          //            .rx_st1_hdr
    input  wire  [31:0]  rx_st1_tlp_prfx_i,        //            .rx_st1_prefix
    input  wire          rx_st1_hvalid_i,          //            .rx_st1_hvalid
    input  wire          rx_st1_pvalid_i,          //            .rx_st1_pvalid
    input  wire  [2:0]   rx_st1_bar_i,             //            .rx_st1_bar
    input  wire  [127:0] rx_st2_header_i,          //            .rx_st2_hdr
    input  wire  [31:0]  rx_st2_tlp_prfx_i,        //            .rx_st2_prefix
    input  wire          rx_st2_hvalid_i,          //            .rx_st2_hvalid
    input  wire          rx_st2_pvalid_i,          //            .rx_st2_pvalid
    input  wire  [2:0]   rx_st2_bar_i,             //            .rx_st2_bar
    input  wire  [127:0] rx_st3_header_i,          //            .rx_st3_hdr
    input  wire  [31:0]  rx_st3_tlp_prfx_i,        //            .rx_st3_prefix
    input  wire          rx_st3_hvalid_i,          //            .rx_st3_hvalid
    input  wire          rx_st3_pvalid_i,          //            .rx_st3_pvalid
    input  wire  [2:0]   rx_st3_bar_i,             //            .rx_st3_bar
    output logic [255:0] tx_st0_payload_o,         //      tx_st0.data
    output logic         tx_st0_sop_o,             //            .startofpacket
    output logic         tx_st0_eop_o,             //            .endofpacket
    output logic         tx_st0_dvalid_o,          //            .valid
    input  wire          tx_st_ready_i,            //            .ready
    output logic [255:0] tx_st1_payload_o,         //      tx_st1.data
    output logic         tx_st1_sop_o,             //            .startofpacket
    output logic         tx_st1_eop_o,             //            .endofpacket
    output logic         tx_st1_dvalid_o,          //            .valid
    output logic [255:0] tx_st2_payload_o,         //      tx_st2.data
    output logic         tx_st2_sop_o,             //            .startofpacket
    output logic         tx_st2_eop_o,             //            .endofpacket
    output logic         tx_st2_dvalid_o,          //            .valid
    output logic [255:0] tx_st3_payload_o,         //      tx_st3.data
    output logic         tx_st3_sop_o,             //            .startofpacket
    output logic         tx_st3_eop_o,             //            .endofpacket
    output logic         tx_st3_dvalid_o,          //            .valid
    output logic [127:0] tx_st0_header_o,          // tx_st0_misc.tx_st0_hdr
    output logic [127:0] tx_st1_header_o,          //            .tx_st1_hdr
    output logic [127:0] tx_st2_header_o,          //            .tx_st2_hdr
    output logic [127:0] tx_st3_header_o,          //            .tx_st3_hdr
    input  wire  [2:0]   tx_st_hcrdt_init_i,       //            .tx_st_Hcrdt_init
    input  wire  [2:0]   tx_st_hcrdt_update_i,     //            .tx_st_Hcrdt_update
    input  wire  [5:0]   tx_st_hcrdt_update_cnt_i, //            .tx_st_Hcrdt_update_cnt
    output logic [2:0]   tx_st_hcrdt_init_ack_o,   //            .tx_st_Hcrdtt_init_ack
    input  wire  [2:0]   tx_st_dcrdt_init_i,       //            .tx_st_Dcrdt_init
    input  wire  [2:0]   tx_st_dcrdt_update_i,     //            .tx_st_Dcrdt_update
    input  wire  [11:0]  tx_st_dcrdt_update_cnt_i, //            .tx_st_Dcrdt_update_cnt
    output logic [2:0]   tx_st_dcrdt_init_ack_o,   //            .tx_st_Dcrdt_init_ack
    output logic [31:0]  tx_st0_prefix_o,          //            .tx_st0_prefix
    output logic         tx_st0_hvalid_o,          //            .tx_st0_hvalid
    output logic         tx_st0_pvalid_o,          //            .tx_st0_pvalid
    output logic [31:0]  tx_st1_prefix_o,          //            .tx_st1_prefix
    output logic         tx_st1_hvalid_o,          //            .tx_st1_hvalid
    output logic         tx_st1_pvalid_o,          //            .tx_st1_pvalid
    output logic [31:0]  tx_st2_prefix_o,          //            .tx_st2_prefix
    output logic         tx_st2_hvalid_o,          //            .tx_st2_hvalid
    output logic         tx_st2_pvalid_o,          //            .tx_st2_pvalid
    output logic [31:0]  tx_st3_prefix_o,          //            .tx_st3_prefix
    output logic         tx_st3_hvalid_o,          //            .tx_st3_hvalid
    output logic         tx_st3_pvalid_o           //            .tx_st3_pvalid
  );

  wire clk, rst;
  assign clk = Clk_i;
  assign rst = ~Rstn_i;

  assign rx_st_ready_o = 1'b1; // Always ready - RX flow control handled by credits

  assign tx_st0_pvalid_o = 1'b0;
  assign tx_st1_pvalid_o = 1'b0;
  assign tx_st2_pvalid_o = 1'b0;
  assign tx_st3_pvalid_o = 1'b0;

  assign tx_st0_prefix_o = 32'h0;
  assign tx_st1_prefix_o = 32'h0;
  assign tx_st2_prefix_o = 32'h0;
  assign tx_st3_prefix_o = 32'h0;

  assign tx_st1_hvalid_o = 1'b0;
  assign tx_st2_hvalid_o = 1'b0;
  assign tx_st3_hvalid_o = 1'b0;

  assign tx_st1_header_o = 128'h0;
  assign tx_st2_header_o = 128'h0;
  assign tx_st3_header_o = 128'h0;

  //
  // Announce infinite RX credits (header and data) to the controller
  //

  typedef enum int {CRDT_P = 0, CRDT_NP = 1, CRDT_CPL = 2} crdt_type_t;
  typedef enum {RX_CRDT_S0, RX_CRDT_S1, RX_CRDT_S2, RX_CRDT_S3, RX_CRDT_S4, RX_CRDT_S5} rx_crdt_state_t;


  //
  // RX header credits (hcrdt)
  //
  assign rx_st_hcrdt_update_cnt_o = 6'b000000;
  rx_crdt_state_t next_rx_hcrdt_state[3], rx_hcrdt_state[3];

  always_ff @(posedge clk) begin
    for (int unsigned i = 0; i < 3; i++) begin
      if (rst) rx_hcrdt_state[i] <= RX_CRDT_S0;
      else rx_hcrdt_state[i] <= next_rx_hcrdt_state[i];
    end
  end

  always_comb begin
    for (int unsigned i = 0; i < 3; i++) begin
      next_rx_hcrdt_state[i] = rx_hcrdt_state[i];
      rx_st_hcrdt_init_o[i] = 1'b0;
      rx_st_hcrdt_update_o[i] = 1'b0;
      case (rx_hcrdt_state[i])
        RX_CRDT_S0: begin
          next_rx_hcrdt_state[i] = RX_CRDT_S1;
        end
        RX_CRDT_S1: begin
          rx_st_hcrdt_init_o[i] = 1'b1;
          if (rx_st_hcrdt_init_ack_i[i]) next_rx_hcrdt_state[i] = RX_CRDT_S2;
        end
        RX_CRDT_S2: begin
          rx_st_hcrdt_init_o[i] = 1'b1;
          rx_st_hcrdt_update_o[i] = 1'b1;
          next_rx_hcrdt_state[i] = RX_CRDT_S3;
        end
        RX_CRDT_S3: begin
          // 2 cc delay before de-assert of rx_st_hcrdt_init_o
          rx_st_hcrdt_init_o[i] = 1'b1;
          next_rx_hcrdt_state[i] = RX_CRDT_S4;
        end
        RX_CRDT_S4: begin
          rx_st_hcrdt_init_o[i] = 1'b1;
          next_rx_hcrdt_state[i] = RX_CRDT_S5;
        end
        RX_CRDT_S5: begin
          // Infinite credit initialization done
        end
      endcase
    end
  end

  //
  // RX data credits (dcrdt)
  //
  assign rx_st_dcrdt_update_cnt_o = 12'b000000000000;
  rx_crdt_state_t next_rx_dcrdt_state[3], rx_dcrdt_state[3];

  always_ff @(posedge clk) begin
    for (int unsigned i = 0; i < 3; i++) begin
      if (rst) rx_dcrdt_state[i] <= RX_CRDT_S0;
      else rx_dcrdt_state[i] <= next_rx_dcrdt_state[i];
    end
  end

  always_comb begin
    for (int unsigned i = 0; i < 3; i++) begin
      next_rx_dcrdt_state[i] = rx_dcrdt_state[i];
      rx_st_dcrdt_init_o[i] = 1'b0;
      rx_st_dcrdt_update_o[i] = 1'b0;
      case (rx_dcrdt_state[i])
        RX_CRDT_S0: begin
          next_rx_dcrdt_state[i] = RX_CRDT_S1;
        end
        RX_CRDT_S1: begin
          rx_st_dcrdt_init_o[i] = 1'b1;
          if (rx_st_dcrdt_init_ack_i[i]) next_rx_dcrdt_state[i] = RX_CRDT_S2;
        end
        RX_CRDT_S2: begin
          rx_st_dcrdt_init_o[i] = 1'b1;
          rx_st_dcrdt_update_o[i] = 1'b1;
          next_rx_dcrdt_state[i] = RX_CRDT_S3;
        end
        RX_CRDT_S3: begin
          // 2 cc delay before de-assert of rx_st_dcrdt_init_o
          rx_st_dcrdt_init_o[i] = 1'b1;
          next_rx_dcrdt_state[i] = RX_CRDT_S4;
        end
        RX_CRDT_S4: begin
          rx_st_dcrdt_init_o[i] = 1'b1;
          next_rx_dcrdt_state[i] = RX_CRDT_S5;
        end
        RX_CRDT_S5: begin
          // Infinite credit initialization done
        end
      endcase
    end
  end

  //
  // Collect TX credits (header and data) from the controller
  //

  typedef enum {TX_CRDT_S0, TX_CRDT_S1, TX_CRDT_S2, TX_CRDT_S3, TX_CRDT_S4} tx_crdt_state_t;

  //
  // TX header credits (hcrdt)
  //
  tx_crdt_state_t next_tx_hcrdt_state[3], tx_hcrdt_state[3];

  always_ff @(posedge clk) begin
    for (int unsigned i = 0; i < 3; i++) begin
      if (rst) tx_hcrdt_state[i] <= TX_CRDT_S0;
      else tx_hcrdt_state[i] <= next_tx_hcrdt_state[i];
    end
  end

  always_comb begin
    for (int unsigned i = 0; i < 3; i++) begin
      next_tx_hcrdt_state[i] = tx_hcrdt_state[i];
      tx_st_hcrdt_init_ack_o[i] = 1'b0;
      case (tx_hcrdt_state[i])
        TX_CRDT_S0: begin
          if (tx_st_hcrdt_init_i[i]) next_tx_hcrdt_state[i] = TX_CRDT_S1;
        end
        TX_CRDT_S1: begin
          // Pulse ACK
          tx_st_hcrdt_init_ack_o[i] = 1'b1;
          next_tx_hcrdt_state[i] = TX_CRDT_S2;
        end
        TX_CRDT_S2: begin
          // Collect credits
          if (~tx_st_hcrdt_init_i[i]) next_tx_hcrdt_state[i] = TX_CRDT_S3;
        end
        TX_CRDT_S3: begin
          // Handle post-init credit updates
        end
      endcase
    end
  end

  logic [2:0] tx_hcrdt_consume;
  logic [11:0] tx_hcrdt_cnt[2:0];

  always_ff @(posedge clk) begin
    for (int unsigned i = 0; i < 3; i++) begin
      if (rst) begin
        tx_hcrdt_cnt[i] <= 0;
      end else begin
        case (tx_hcrdt_state[i])
          TX_CRDT_S2: begin
            if (tx_st_hcrdt_update_i[i])
              tx_hcrdt_cnt[i] <= tx_hcrdt_cnt[i] + tx_st_hcrdt_update_cnt_i[i*2+:2];
          end
          TX_CRDT_S3: begin
            tx_hcrdt_cnt[i] <= tx_hcrdt_cnt[i] + (tx_st_hcrdt_update_i[i] ? tx_st_hcrdt_update_cnt_i[i*2+:2] : 4'h0)
                                               - (tx_hcrdt_consume[i] ? 4'h1 : 4'h0);
          end
        endcase
      end
    end
  end

  logic [2:0] tx_hcrdt_inf;

  always_ff @(posedge clk) begin
    for (int unsigned i = 0; i < 3; i++) begin
      if (rst) begin
        tx_hcrdt_inf[i] <= 0;
      end else if (next_tx_hcrdt_state[i] == TX_CRDT_S3 && next_tx_hcrdt_state[i] != tx_hcrdt_state[i]) begin
        tx_hcrdt_inf[i] <= (tx_hcrdt_cnt[i] == 0) ? 1'b1 : 1'b0;
      end
    end
  end

  //
  // TX data credits (dcrdt) - one dcrdt corresponds to 16 bytes
  //
  tx_crdt_state_t next_tx_dcrdt_state[3], tx_dcrdt_state[3];

  always_ff @(posedge clk) begin
    for (int unsigned i = 0; i < 3; i++) begin
      if (rst) tx_dcrdt_state[i] <= TX_CRDT_S0;
      else tx_dcrdt_state[i] <= next_tx_dcrdt_state[i];
    end
  end

  always_comb begin
    for (int unsigned i = 0; i < 3; i++) begin
      next_tx_dcrdt_state[i] = tx_dcrdt_state[i];
      tx_st_dcrdt_init_ack_o[i] = 1'b0;
      case (tx_dcrdt_state[i])
        TX_CRDT_S0: begin
          if (tx_st_dcrdt_init_i[i]) next_tx_dcrdt_state[i] = TX_CRDT_S1;
        end
        TX_CRDT_S1: begin
          // Pulse ACK
          tx_st_dcrdt_init_ack_o[i] = 1'b1;
          next_tx_dcrdt_state[i] = TX_CRDT_S2;
        end
        TX_CRDT_S2: begin
          // Collect credits
          if (~tx_st_dcrdt_init_i[i]) next_tx_dcrdt_state[i] = TX_CRDT_S3;
        end
        TX_CRDT_S3: begin
          // Handle post-init credit updates
        end
      endcase
    end
  end

  logic [3:0] tx_dcrdt_consume[2:0];
  logic [11:0] tx_dcrdt_cnt[2:0];

  always_ff @(posedge clk) begin
    for (int unsigned i = 0; i < 3; i++) begin
      if (rst) begin
        tx_dcrdt_cnt[i] <= 0;
      end else begin
        case (tx_dcrdt_state[i])
          TX_CRDT_S2: begin
            if (tx_st_dcrdt_update_i[i])
              tx_dcrdt_cnt[i] <= tx_dcrdt_cnt[i] + tx_st_dcrdt_update_cnt_i[i*4+:4];
          end
          TX_CRDT_S3: begin
            tx_dcrdt_cnt[i] <= tx_dcrdt_cnt[i] + (tx_st_dcrdt_update_i[i] ? tx_st_dcrdt_update_cnt_i[i*4+:4] : 4'h0)
                                               - tx_dcrdt_consume[i];
          end
        endcase
      end
    end
  end

  logic [2:0] tx_dcrdt_inf;

  always_ff @(posedge clk) begin
    for (int unsigned i = 0; i < 3; i++) begin
      if (rst) begin
        tx_dcrdt_inf[i] <= 0;
      end else if (next_tx_dcrdt_state[i] == TX_CRDT_S3 && next_tx_dcrdt_state[i] != tx_dcrdt_state[i]) begin
        tx_dcrdt_inf[i] <= (tx_dcrdt_cnt[i] == 0) ? 1'b1 : 1'b0;
      end
    end
  end

  //
  //
  // Scratch follows
  //
  //

  logic [127:0] rx_header;
  logic [63:0] rx_data;
  logic rx_sop;
  always_ff @(posedge clk) begin
    rx_header <= 0;
    rx_data <= 0;
    rx_sop <= 0;
    if (rx_st0_sop_i && rx_st0_hvalid_i) begin
      rx_header <= rx_st0_header_i;
      rx_data <= rx_st0_payload_i[63:0];
      rx_sop <= 1;
    end else if (rx_st1_sop_i && rx_st1_hvalid_i) begin
      rx_header <= rx_st1_header_i;
      rx_data <= rx_st1_payload_i[63:0];
      rx_sop <= 1;
    end else if (rx_st2_sop_i && rx_st2_hvalid_i) begin
      rx_header <= rx_st2_header_i;
      rx_data <= rx_st2_payload_i[63:0];
      rx_sop <= 1;
    end else if (rx_st3_sop_i && rx_st3_hvalid_i) begin
      rx_header <= rx_st3_header_i;
      rx_data <= rx_st3_payload_i[63:0];
      rx_sop <= 1;
    end
  end

  tlp_req_hdr_3dw_t tlp_rx_3dw;
  assign tlp_rx_3dw = rx_header[127:32];
  tlp_req_hdr_4dw_t tlp_rx_4dw;
  assign tlp_rx_4dw = rx_header[127:0];
  tlp_cpl_hdr_t tlp_rx_cpl;
  assign tlp_rx_cpl = rx_header[127:32];

  tlp_cpl_hdr_t bar_read_cpl_hdr;
  logic bar_rreq, bar_rreq_prev, bar_wreq;
  logic [21:0] bar_raddr, bar_waddr;
  logic [63:0] bar_rdata, bar_wdata;


  //
  // Handle RX
  //
  always_ff @(posedge clk) begin
    bar_rreq_prev <= bar_rreq;
    bar_rreq <= 0;
    bar_wreq <= 0;
    if (rx_sop) begin
      if (tlp_rx_4dw.dw0.fmt_type == FMT_TYPE_MWr_64 && tlp_rx_4dw.dw0.length == 2 &&
          tlp_rx_4dw.last_dw_be == 4'hf && tlp_rx_4dw.first_dw_be == 4'hf) begin
        bar_wreq <= 1;
        bar_waddr <= {tlp_rx_4dw.addr_lo[19:0], 2'b00};
        bar_wdata <= rx_data;
      end
      if (tlp_rx_4dw.dw0.fmt_type == FMT_TYPE_MRd_64 && tlp_rx_4dw.dw0.length == 2) begin
        bar_rreq <= 1;
        bar_raddr <= {tlp_rx_4dw.addr_lo[19:0], 2'b00};
        // XXX: Prepare bar_read_cpl_hdr
        bar_read_cpl_hdr <= 0;
        bar_read_cpl_hdr.dw0 <= tlp_rx_4dw.dw0;
        bar_read_cpl_hdr.dw0.fmt_type <= FMT_TYPE_CplD;
        bar_read_cpl_hdr.requester_id <= tlp_rx_4dw.requester_id;
        bar_read_cpl_hdr.cpl_status <= 3'b000; // Successful Completion (SC)
        bar_read_cpl_hdr.byte_count <= 8;
        bar_read_cpl_hdr.tag <= tlp_rx_4dw.tag;
        bar_read_cpl_hdr.lower_addr <= {tlp_rx_4dw.addr_lo[4:0], 2'b00};

      end
    end
  end

  //
  // Handle TX
  //

  logic has_tx_crdt_np;
  assign has_tx_crdt_np = (tx_hcrdt_inf[CRDT_NP] || tx_hcrdt_cnt[CRDT_NP] > 0);
  logic has_tx_crdt_p;
  assign has_tx_crdt_p = (tx_hcrdt_inf[CRDT_P] || tx_hcrdt_cnt[CRDT_P] > 0) && (tx_dcrdt_inf[CRDT_P] || tx_dcrdt_cnt[CRDT_P] > 32);

  always_ff @(posedge clk) begin
    tx_hcrdt_consume[CRDT_P] <= 1'b0;
    tx_hcrdt_consume[CRDT_NP] <= 1'b0;
    tx_hcrdt_consume[CRDT_CPL] <= 1'b0;
    tx_dcrdt_consume[CRDT_P] <= 4'h0;
    tx_dcrdt_consume[CRDT_NP] <= 4'h0;
    tx_dcrdt_consume[CRDT_CPL] <= 4'h0;
    tx_st0_sop_o <= 0;
    tx_st0_eop_o <= 0;
    tx_st0_hvalid_o <= 0;
    tx_st0_dvalid_o <= 0;
    tx_st1_sop_o <= 0;
    tx_st1_eop_o <= 0;
    tx_st1_dvalid_o <= 0;
    tx_st2_sop_o <= 0;
    tx_st2_eop_o <= 0;
    tx_st2_dvalid_o <= 0;
    tx_st3_sop_o <= 0;
    tx_st3_eop_o <= 0;
    tx_st3_dvalid_o <= 0;
    if (tx_st_ready_i) begin
      if (bar_rreq_prev && (tx_hcrdt_inf[CRDT_CPL] || tx_hcrdt_cnt[CRDT_CPL] > 0)) begin // BAR access XXX: Need to try again if not enough credits to send
        tx_hcrdt_consume[CRDT_CPL] <= 1;
        tx_st0_sop_o <= 1;
        tx_st0_eop_o <= 1;
        tx_st0_hvalid_o <= 1;
        tx_st0_dvalid_o <= 1;
        tx_st0_header_o <= {bar_read_cpl_hdr, 32'h0};
        tx_st0_payload_o[63:0] <= bar_rdata;
      end else if (mem_req_mrd_valid && has_tx_crdt_np) begin // MRd64 access from core
        tx_hcrdt_consume[CRDT_NP] <= 1;
        tx_st0_sop_o <= 1;
        tx_st0_hvalid_o <= 1;
        tx_st0_header_o <= tlp_tx_mrd64;
        tx_st0_eop_o <= 1;
      end else if (mem_req_mwr_valid && has_tx_crdt_p) begin // MWr64 access from core
        tx_hcrdt_consume[CRDT_P] <= 1;
        tx_dcrdt_consume[CRDT_P] <= 8;
        tx_st0_sop_o <= 1;
        tx_st0_hvalid_o <= 1;
        tx_st0_header_o <= tlp_tx_mwr64;
        tx_st0_dvalid_o <= 1;
        tx_st0_payload_o <= {4{mem_req_data}};
        tx_st1_dvalid_o <= 1;
        tx_st1_payload_o <= {4{mem_req_data}};
        tx_st2_dvalid_o <= 1;
        tx_st2_payload_o <= {4{mem_req_data}};
        tx_st3_dvalid_o <= 1;
        tx_st3_payload_o <= {4{mem_req_data}};
        tx_st3_eop_o <= 1;
      end
    end
  end

  logic core_rst_ctrl_reg;
  always_ff @(posedge clk) begin
    if (rst) begin
      core_rst_ctrl_reg <= 1'b1;
    end else if (bar_wreq && bar_waddr == 22'h10_0000) begin
      core_rst_ctrl_reg <= bar_wdata[0];
    end
  end

  logic        mem_req_ready;
  logic        mem_req_mrd_valid;
  logic        mem_req_mwr_valid;
  logic [9:0]  mem_req_tag;
  logic [63:0] mem_req_addr;
  logic [63:0] mem_req_data;
  logic [7:0]  mem_req_len;
  logic [2:0]  mem_req_attr;
  logic        mem_req_th;
  logic [1:0]  mem_req_ph;


  tlp_req_hdr_4dw_t tlp_tx_mrd64;
  assign tlp_tx_mrd64.dw0.fmt_type = FMT_TYPE_MRd_64;
  assign tlp_tx_mrd64.dw0.length = 32;
  assign tlp_tx_mrd64.dw0.t9 = mem_req_tag[9];
  assign tlp_tx_mrd64.dw0.t8 = mem_req_tag[8];
  assign tlp_tx_mrd64.dw0.attr2 = mem_req_attr[2];
  assign tlp_tx_mrd64.dw0.attr = mem_req_attr[1:0];
  assign tlp_tx_mrd64.dw0.th = mem_req_th;
  assign tlp_tx_mrd64.tag = mem_req_tag[7:0];
  assign tlp_tx_mrd64.last_dw_be = 4'hf;
  assign tlp_tx_mrd64.first_dw_be = 4'hf;
  assign tlp_tx_mrd64.addr_hi = mem_req_addr[63:32];
  assign tlp_tx_mrd64.addr_lo = mem_req_addr[31:2];
  assign tlp_tx_mrd64.ph = mem_req_th ? mem_req_ph : 2'b00;

  tlp_req_hdr_4dw_t tlp_tx_mwr64;
  assign tlp_tx_mwr64.dw0.fmt_type = FMT_TYPE_MWr_64;
  assign tlp_tx_mwr64.dw0.attr2 = mem_req_attr[2];
  assign tlp_tx_mwr64.dw0.attr = mem_req_attr[1:0];
  assign tlp_tx_mwr64.dw0.th = mem_req_th;
  assign tlp_tx_mwr64.dw0.length = 32;
  assign tlp_tx_mwr64.last_dw_be = 4'hf;
  assign tlp_tx_mwr64.first_dw_be = 4'hf;
  assign tlp_tx_mwr64.addr_hi = mem_req_addr[63:32];
  assign tlp_tx_mwr64.addr_lo = mem_req_addr[31:2];
  assign tlp_tx_mwr64.ph = mem_req_th ? mem_req_ph : 2'b00;

  core u_core(
    .clk(clk),
    .rst(core_rst_ctrl_reg),
    // BAR access
    .bar_raddr(bar_raddr),
    .bar_waddr(bar_waddr),
    .bar_rdata(bar_rdata),
    .bar_wdata(bar_wdata),
    .bar_wen(bar_wreq && bar_waddr[21:20] == 2'h0),
    // MRd/MWr
    .mem_req_mrd_ready(~bar_rreq_prev && has_tx_crdt_np),
    .mem_req_mrd_valid(mem_req_mrd_valid),
    .mem_req_mwr_ready(~bar_rreq_prev && has_tx_crdt_p),
    .mem_req_mwr_valid(mem_req_mwr_valid),
    .mem_req_tag(mem_req_tag),
    .mem_req_data(mem_req_data),
    .mem_req_addr(mem_req_addr),
    .mem_req_len(),
    .mem_req_attr(mem_req_attr),
    .mem_req_th(mem_req_th),
    .mem_req_ph(mem_req_ph),
    // CplD
    .mem_cpl_valid(rx_sop && (tlp_rx_cpl.dw0.fmt_type == FMT_TYPE_CplD)),
    .mem_cpl_tag({tlp_rx_cpl.dw0.t9, tlp_rx_cpl.dw0.t8, tlp_rx_cpl.tag}),
    .mem_cpl_data(rx_data)
  );

endmodule
