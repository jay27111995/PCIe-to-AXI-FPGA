//-----------------------------------------------------------------------------
// rtile_crdt.sv - Credit manager for R-Tile
//
// RX: Advertise infinite credits during init, return credits as consumed
// TX: Track available credits from link partner
//-----------------------------------------------------------------------------
module rtile_crdt
    import rtile_pkg::*;
(
    input  logic       clk,
    input  logic       rst_n,

    // RX credits (we → HIP)
    output logic [2:0] rx_hcrdt_init,
    output logic [2:0] rx_hcrdt_update,
    output logic [5:0] rx_hcrdt_update_cnt,
    output logic [2:0] rx_dcrdt_init,
    output logic [2:0] rx_dcrdt_update,
    output logic [11:0] rx_dcrdt_update_cnt,

    // TX credits (HIP → us)
    input  logic [2:0] tx_hcrdt_init,
    output logic [2:0] tx_hcrdt_init_ack,
    input  logic [2:0] tx_hcrdt_update,
    input  logic [5:0] tx_hcrdt_update_cnt,
    input  logic [2:0] tx_dcrdt_init,
    output logic [2:0] tx_dcrdt_init_ack,
    input  logic [2:0] tx_dcrdt_update,
    input  logic [11:0] tx_dcrdt_update_cnt,

    // Credit return (from RX consumer)
    input  logic       rx_cpl_hdr_ret,      // Return 1 CPL header credit
    input  logic       rx_cpl_data_ret,     // Return CPL data credits
    input  logic [11:0] rx_cpl_data_cnt,    // How many data credits

    // TX credit check (to TX arbiter)
    output logic       tx_cpl_hdr_ok,       // Have CPL header credit
    output logic       tx_cpl_data_ok,      // Have CPL data credits
    input  logic       tx_cpl_hdr_dec,      // Decrement header
    input  logic       tx_cpl_data_dec,     // Decrement data
    input  logic [11:0] tx_cpl_data_amt,    // Data credits to decrement

    output logic       init_done
);

    //-------------------------------------------------------------------------
    // RX Credit Init FSM - advertise large credits then done
    //-------------------------------------------------------------------------
    typedef enum logic [1:0] { IDLE, INIT, UPDATE, DONE } state_e;
    state_e state;
    logic [3:0] cnt;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            state <= IDLE;
            cnt <= 0;
            rx_hcrdt_init <= 0;
            rx_dcrdt_init <= 0;
            rx_hcrdt_update <= 0;
            rx_dcrdt_update <= 0;
        end else begin
            rx_hcrdt_update <= 0;
            rx_dcrdt_update <= 0;

            case (state)
                IDLE: begin
                    cnt <= cnt + 1;
                    if (cnt == 4'd10) state <= INIT;
                end
                INIT: begin
                    rx_hcrdt_init <= 3'b111;  // P, NP, CPL
                    rx_dcrdt_init <= 3'b111;
                    state <= UPDATE;
                    cnt <= 0;
                end
                UPDATE: begin
                    rx_hcrdt_update <= 3'b111;
                    rx_dcrdt_update <= 3'b111;
                    cnt <= cnt + 1;
                    if (cnt == 4'd15) state <= DONE;
                end
                DONE: begin
                    rx_hcrdt_init <= 0;
                    rx_dcrdt_init <= 0;
                    // Runtime credit returns for completions
                    if (rx_cpl_hdr_ret) begin
                        rx_hcrdt_update[CRDT_CPL] <= 1;
                    end
                    if (rx_cpl_data_ret) begin
                        rx_dcrdt_update[CRDT_CPL] <= 1;
                    end
                end
            endcase
        end
    end

    // Credit counts - max during init, actual during runtime
    assign rx_hcrdt_update_cnt = 6'd63;
    assign rx_dcrdt_update_cnt = (state == DONE) ? rx_cpl_data_cnt : 12'd4095;
    assign init_done = (state == DONE);

    //-------------------------------------------------------------------------
    // TX Credit Tracking
    //-------------------------------------------------------------------------
    logic [15:0] tx_cpl_hdr_cnt;
    logic [19:0] tx_cpl_data_cnt;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            tx_hcrdt_init_ack <= 0;
            tx_dcrdt_init_ack <= 0;
            tx_cpl_hdr_cnt <= 0;
            tx_cpl_data_cnt <= 0;
        end else begin
            tx_hcrdt_init_ack <= tx_hcrdt_init;
            tx_dcrdt_init_ack <= tx_dcrdt_init;

            // Accumulate from updates
            if (tx_hcrdt_update[CRDT_CPL])
                tx_cpl_hdr_cnt <= tx_cpl_hdr_cnt + {10'b0, tx_hcrdt_update_cnt};
            if (tx_dcrdt_update[CRDT_CPL])
                tx_cpl_data_cnt <= tx_cpl_data_cnt + {8'b0, tx_dcrdt_update_cnt};

            // Decrement when TX uses credits
            if (tx_cpl_hdr_dec && tx_cpl_hdr_cnt > 0)
                tx_cpl_hdr_cnt <= tx_cpl_hdr_cnt - 1;
            if (tx_cpl_data_dec && tx_cpl_data_cnt >= {8'b0, tx_cpl_data_amt})
                tx_cpl_data_cnt <= tx_cpl_data_cnt - {8'b0, tx_cpl_data_amt};
        end
    end

    assign tx_cpl_hdr_ok = (tx_cpl_hdr_cnt > 0);
    assign tx_cpl_data_ok = (tx_cpl_data_cnt > 0);

endmodule
