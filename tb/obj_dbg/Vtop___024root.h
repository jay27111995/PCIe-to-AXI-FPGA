// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtop.h for the primary calling header

#ifndef VERILATED_VTOP___024ROOT_H_
#define VERILATED_VTOP___024ROOT_H_  // guard

#include "verilated.h"


class Vtop__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtop___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        VL_IN8(clk,0,0);
        VL_IN8(rst_n,0,0);
        VL_IN8(rx_st_sop,0,0);
        VL_IN8(rx_st_eop,0,0);
        VL_IN8(rx_st_hvalid,0,0);
        VL_IN8(rx_st_dvalid,0,0);
        VL_IN8(rx_st_bar,2,0);
        VL_OUT8(rx_st_ready,0,0);
        VL_OUT8(tx_st_sop,0,0);
        VL_OUT8(tx_st_eop,0,0);
        VL_OUT8(tx_st_hvalid,0,0);
        VL_OUT8(tx_st_dvalid,0,0);
        VL_IN8(tx_st_ready,0,0);
        VL_OUT8(rx_hcrdt_init,2,0);
        VL_OUT8(rx_hcrdt_update,2,0);
        VL_OUT8(rx_hcrdt_update_cnt,5,0);
        VL_OUT8(rx_dcrdt_init,2,0);
        VL_OUT8(rx_dcrdt_update,2,0);
        VL_IN8(tx_hcrdt_init,2,0);
        VL_OUT8(tx_hcrdt_init_ack,2,0);
        VL_IN8(tx_hcrdt_update,2,0);
        VL_IN8(tx_hcrdt_update_cnt,5,0);
        VL_IN8(tx_dcrdt_init,2,0);
        VL_OUT8(tx_dcrdt_init_ack,2,0);
        VL_IN8(tx_dcrdt_update,2,0);
        VL_IN8(link_up,0,0);
        VL_IN8(ltssm_state,5,0);
        CData/*7:0*/ top__DOT__brg_wstrb;
        CData/*0:0*/ top__DOT__brg_awvalid;
        CData/*0:0*/ top__DOT__brg_awready;
        CData/*0:0*/ top__DOT__brg_wvalid;
        CData/*0:0*/ top__DOT__brg_wready;
        CData/*0:0*/ top__DOT__brg_bvalid;
        CData/*0:0*/ top__DOT__brg_bready;
        CData/*0:0*/ top__DOT__brg_arvalid;
        CData/*0:0*/ top__DOT__brg_arready;
        CData/*1:0*/ top__DOT__brg_rresp_mux;
        CData/*0:0*/ top__DOT__brg_rvalid_mux;
        CData/*0:0*/ top__DOT__brg_rready;
        CData/*0:0*/ top__DOT__dma_host_awready;
        CData/*0:0*/ top__DOT__dma_host_wready;
        CData/*0:0*/ top__DOT__dma_host_bvalid;
        CData/*0:0*/ top__DOT__dma_host_arready;
        CData/*0:0*/ top__DOT__dma_host_rvalid;
        CData/*1:0*/ top__DOT__dma_s_bresp;
        CData/*1:0*/ top__DOT__dma_s_rresp;
        CData/*0:0*/ top__DOT__dma_s_awready;
        CData/*0:0*/ top__DOT__dma_s_wready;
        CData/*0:0*/ top__DOT__dma_s_bvalid;
        CData/*0:0*/ top__DOT__dma_s_arready;
        CData/*0:0*/ top__DOT__dma_s_rvalid;
        CData/*0:0*/ top__DOT__ram_bar_awvalid;
        CData/*0:0*/ top__DOT__ram_bar_bvalid;
        CData/*0:0*/ top__DOT__ram_bar_arvalid;
        CData/*0:0*/ top__DOT__ram_bar_rvalid;
        CData/*0:0*/ top__DOT__dma_local_bvalid;
        CData/*0:0*/ top__DOT__dma_local_rvalid;
        CData/*7:0*/ top__DOT__ram_wstrb;
        CData/*1:0*/ top__DOT__ram_bresp;
        CData/*1:0*/ top__DOT__ram_rresp;
        CData/*0:0*/ top__DOT__ram_awready;
        CData/*0:0*/ top__DOT__ram_wready;
        CData/*0:0*/ top__DOT__ram_bvalid;
        CData/*0:0*/ top__DOT__ram_arready;
    };
    struct {
        CData/*0:0*/ top__DOT__ram_rvalid;
        CData/*0:0*/ top__DOT__msix_valid_i;
        CData/*0:0*/ top__DOT__msix_ready_i;
        CData/*0:0*/ top__DOT__dma_irq_req;
        CData/*0:0*/ top__DOT__pcie_dbg_wen;
        CData/*0:0*/ top__DOT__axi_dbg_wen;
        CData/*0:0*/ top__DOT__wr_to_ram;
        CData/*0:0*/ top__DOT__rd_to_ram;
        CData/*0:0*/ top__DOT__rd_to_axi_dbg;
        CData/*0:0*/ top__DOT__rd_to_dbg;
        CData/*0:0*/ top__DOT__dbg_rvalid;
        CData/*0:0*/ top__DOT__dbg_sel_axi_latched;
        CData/*1:0*/ top__DOT__dbg_rd_state;
        CData/*0:0*/ top__DOT__msix_pending;
        CData/*0:0*/ top__DOT__arb_busy;
        CData/*0:0*/ top__DOT__arb_owner;
        CData/*7:0*/ top__DOT__u_bridge__DOT__rx_tag;
        CData/*3:0*/ top__DOT__u_bridge__DOT__rx_fbe;
        CData/*3:0*/ top__DOT__u_bridge__DOT__rx_lbe;
        CData/*0:0*/ top__DOT__u_bridge__DOT__rx_is_mrd;
        CData/*0:0*/ top__DOT__u_bridge__DOT__rx_is_mwr;
        CData/*0:0*/ top__DOT__u_bridge__DOT__rx_is_cpld;
        CData/*0:0*/ top__DOT__u_bridge__DOT__completer_id_valid;
        CData/*7:0*/ top__DOT__u_bridge__DOT__host_mrd_tag;
        CData/*0:0*/ top__DOT__u_bridge__DOT__host_mrd_pending;
        CData/*0:0*/ top__DOT__u_bridge__DOT__host_mrd_inflight;
        CData/*0:0*/ top__DOT__u_bridge__DOT__host_mwr_pending;
        CData/*3:0*/ top__DOT__u_bridge__DOT__tx_state;
        CData/*0:0*/ top__DOT__u_bridge__DOT__host_mrd_ready_pulse;
        CData/*0:0*/ top__DOT__u_bridge__DOT__host_mwr_ready_pulse;
        CData/*7:0*/ top__DOT__u_bridge__DOT__bar_req_tag;
        CData/*6:0*/ top__DOT__u_bridge__DOT__bar_req_lower_addr;
        CData/*3:0*/ top__DOT__u_bridge__DOT__bar_dw_count;
        CData/*1:0*/ top__DOT__u_bridge__DOT__bar_cpl_status;
        CData/*1:0*/ top__DOT__u_bridge__DOT__u_crdt__DOT__state;
        CData/*3:0*/ top__DOT__u_bridge__DOT__u_crdt__DOT__cnt;
        CData/*7:0*/ top__DOT__u_sniffer__DOT__write_ptr;
        CData/*0:0*/ top__DOT__u_sniffer__DOT__running;
        CData/*0:0*/ top__DOT__u_sniffer__DOT__triggered;
        CData/*0:0*/ top__DOT__u_sniffer__DOT__full;
        CData/*1:0*/ top__DOT__u_sniffer__DOT__capture_mode;
        CData/*1:0*/ top__DOT__u_sniffer__DOT__filter_mode;
        CData/*7:0*/ top__DOT__u_sniffer__DOT__trigger_type;
        CData/*0:0*/ top__DOT__u_sniffer__DOT__trigger_type_en;
        CData/*0:0*/ top__DOT__u_sniffer__DOT__trigger_on_err;
        CData/*0:0*/ top__DOT__u_sniffer__DOT__armed;
        CData/*7:0*/ top__DOT__u_sniffer__DOT__read_ptr;
        CData/*0:0*/ top__DOT__u_sniffer__DOT__rx_seen;
        CData/*0:0*/ top__DOT__u_sniffer__DOT__tx_seen;
        CData/*7:0*/ top__DOT__u_sniffer__DOT__last_rx_type;
        CData/*0:0*/ top__DOT__u_sniffer__DOT__rx_valid;
        CData/*0:0*/ top__DOT__u_sniffer__DOT__tx_valid;
        CData/*0:0*/ top__DOT__u_sniffer__DOT__rx_is_cpl_err;
        CData/*0:0*/ top__DOT__u_sniffer__DOT__tx_is_cpl_err;
        CData/*0:0*/ top__DOT__u_sniffer__DOT__capture_rx;
        CData/*0:0*/ top__DOT__u_sniffer__DOT__capture_tx;
        CData/*0:0*/ top__DOT__u_sniffer__DOT__ctrl_clear;
        CData/*0:0*/ top__DOT__u_sniffer__DOT__unnamedblk1__DOT__should_capture;
        CData/*0:0*/ top__DOT__u_sniffer__DOT____VdfgRegularize_h54215f63_1_0;
        CData/*5:0*/ top__DOT__u_axi_sniffer__DOT__write_ptr;
        CData/*6:0*/ top__DOT__u_axi_sniffer__DOT__entry_count;
        CData/*0:0*/ top__DOT__u_axi_sniffer__DOT__running;
        CData/*0:0*/ top__DOT__u_axi_sniffer__DOT__full;
        CData/*5:0*/ top__DOT__u_axi_sniffer__DOT__read_ptr;
    };
    struct {
        CData/*0:0*/ top__DOT__u_axi_sniffer__DOT__aw_seen;
        CData/*0:0*/ top__DOT__u_axi_sniffer__DOT__w_seen;
        CData/*0:0*/ top__DOT__u_axi_sniffer__DOT__b_seen;
        CData/*0:0*/ top__DOT__u_axi_sniffer__DOT__ar_seen;
        CData/*0:0*/ top__DOT__u_axi_sniffer__DOT__r_seen;
        CData/*0:0*/ top__DOT__u_axi_sniffer__DOT__pending_awvalid;
        CData/*0:0*/ top__DOT__u_axi_sniffer__DOT__aw_handshake;
        CData/*0:0*/ top__DOT__u_axi_sniffer__DOT__ar_handshake;
        CData/*0:0*/ top__DOT__u_axi_sniffer__DOT__ctrl_clear;
        CData/*0:0*/ top__DOT__u_axi_sniffer__DOT____VdfgRegularize_h1732209f_5_0;
        CData/*0:0*/ top__DOT__u_dma__DOT__start;
        CData/*0:0*/ top__DOT__u_dma__DOT__busy;
        CData/*0:0*/ top__DOT__u_dma__DOT__done;
        CData/*0:0*/ top__DOT__u_dma__DOT__done_r;
        CData/*0:0*/ top__DOT__u_dma__DOT__h2c_host_arvalid;
        CData/*0:0*/ top__DOT__u_dma__DOT__h2c_host_rready;
        CData/*0:0*/ top__DOT__u_dma__DOT__h2c_local_awvalid;
        CData/*0:0*/ top__DOT__u_dma__DOT__h2c_local_wvalid;
        CData/*0:0*/ top__DOT__u_dma__DOT__h2c_local_bready;
        CData/*7:0*/ top__DOT__u_dma__DOT__h2c_local_wstrb;
        CData/*0:0*/ top__DOT__u_dma__DOT__c2h_local_arvalid;
        CData/*0:0*/ top__DOT__u_dma__DOT__c2h_local_rready;
        CData/*0:0*/ top__DOT__u_dma__DOT__c2h_host_awvalid;
        CData/*0:0*/ top__DOT__u_dma__DOT__c2h_host_wvalid;
        CData/*0:0*/ top__DOT__u_dma__DOT__c2h_host_bready;
        CData/*2:0*/ top__DOT__u_dma__DOT__u_h2c__DOT__state;
        CData/*2:0*/ top__DOT__u_dma__DOT__u_c2h__DOT__state;
        CData/*0:0*/ top__DOT__u_ram__DOT__read_pending;
        CData/*0:0*/ __Vfunc_is_4dw__7__Vfuncout;
        CData/*2:0*/ __Vfunc_is_4dw__7__fmt;
        CData/*0:0*/ __Vfunc_has_data__10__Vfuncout;
        CData/*2:0*/ __Vfunc_has_data__10__fmt;
        CData/*0:0*/ __Vfunc_has_data__11__Vfuncout;
        CData/*2:0*/ __Vfunc_has_data__11__fmt;
        CData/*0:0*/ __Vfunc_has_data__12__Vfuncout;
        CData/*2:0*/ __Vfunc_has_data__12__fmt;
        CData/*0:0*/ __VstlFirstIteration;
        CData/*0:0*/ __VicoFirstIteration;
        CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
        CData/*0:0*/ __Vtrigprevexpr___TOP__rst_n__0;
        CData/*0:0*/ __VactContinue;
        VL_OUT16(rx_dcrdt_update_cnt,11,0);
        VL_IN16(tx_dcrdt_update_cnt,11,0);
        SData/*11:0*/ top__DOT__dbg_addr_latched;
        SData/*11:0*/ top__DOT__dbg_addr_to_sniffer;
        SData/*9:0*/ top__DOT__u_bridge__DOT__rx_len;
        SData/*15:0*/ top__DOT__u_bridge__DOT__rx_rid;
        SData/*15:0*/ top__DOT__u_bridge__DOT__completer_id;
        SData/*15:0*/ top__DOT__u_bridge__DOT__bar_req_rid;
        SData/*9:0*/ top__DOT__u_bridge__DOT__bar_dw_remaining;
        SData/*8:0*/ top__DOT__u_sniffer__DOT__entry_count;
        SData/*8:0*/ top__DOT__u_ram__DOT__rd_addr_latched;
        VL_INW(rx_st_hdr,127,0,4);
        VL_INW(rx_st_data,255,0,8);
        VL_OUTW(tx_st_hdr,127,0,4);
        VL_OUTW(tx_st_data,255,0,8);
        IData/*31:0*/ top__DOT__brg_awaddr;
        IData/*31:0*/ top__DOT__brg_araddr;
        IData/*31:0*/ top__DOT__pcie_dbg_rdata;
        IData/*31:0*/ top__DOT__axi_dbg_rdata;
        IData/*31:0*/ top__DOT__dbg_rdata_latched;
        IData/*31:0*/ top__DOT__dbg_rdata;
        IData/*31:0*/ top__DOT__msix_data_reg;
        IData/*31:0*/ top__DOT__u_bridge__DOT__bar_req_addr;
    };
    struct {
        VlWide<8>/*255:0*/ top__DOT__u_bridge__DOT__bar_cpl_buffer;
        VlWide<4>/*127:0*/ top__DOT__u_bridge__DOT__tx_hdr_r;
        VlWide<8>/*255:0*/ top__DOT__u_bridge__DOT__tx_data_r;
        VlWide<8>/*255:0*/ top__DOT__u_sniffer__DOT__read_entry;
        IData/*31:0*/ top__DOT__u_sniffer__DOT__rx_count;
        IData/*31:0*/ top__DOT__u_sniffer__DOT__tx_count;
        VlWide<4>/*127:0*/ top__DOT__u_sniffer__DOT__last_rx_hdr;
        VlWide<4>/*127:0*/ top__DOT__u_sniffer__DOT__last_tx_hdr;
        VlWide<8>/*255:0*/ top__DOT__u_sniffer__DOT__unnamedblk1__DOT__unnamedblk2__DOT__entry;
        VlWide<4>/*127:0*/ top__DOT__u_axi_sniffer__DOT__read_entry;
        IData/*31:0*/ top__DOT__u_axi_sniffer__DOT__aw_count;
        IData/*31:0*/ top__DOT__u_axi_sniffer__DOT__ar_count;
        IData/*21:0*/ top__DOT__u_axi_sniffer__DOT__timestamp;
        IData/*31:0*/ top__DOT__u_axi_sniffer__DOT__pending_awaddr;
        VlWide<4>/*127:0*/ top__DOT__u_axi_sniffer__DOT__unnamedblk1__DOT__entry;
        VlWide<4>/*127:0*/ top__DOT__u_axi_sniffer__DOT__unnamedblk2__DOT__entry;
        VlWide<4>/*127:0*/ top__DOT__u_axi_sniffer__DOT__unnamedblk3__DOT__entry;
        VlWide<4>/*127:0*/ top__DOT__u_axi_sniffer__DOT__unnamedblk4__DOT__entry;
        IData/*31:0*/ top__DOT__u_dma__DOT__ctrl_reg;
        IData/*31:0*/ top__DOT__u_dma__DOT__local_addr;
        IData/*31:0*/ top__DOT__u_dma__DOT__length_reg;
        IData/*31:0*/ top__DOT__u_dma__DOT__h2c_local_awaddr;
        IData/*31:0*/ top__DOT__u_dma__DOT__c2h_local_araddr;
        IData/*31:0*/ top__DOT__u_dma__DOT__u_h2c__DOT__cur_local;
        IData/*31:0*/ top__DOT__u_dma__DOT__u_h2c__DOT__bytes_left;
        IData/*31:0*/ top__DOT__u_dma__DOT__u_c2h__DOT__cur_local;
        IData/*31:0*/ top__DOT__u_dma__DOT__u_c2h__DOT__bytes_left;
        VlWide<4>/*127:0*/ __Vfunc_hdr_addr64__8__h;
        IData/*31:0*/ __Vfunc_hdr_addr32__9__Vfuncout;
        VlWide<4>/*127:0*/ __Vfunc_hdr_addr32__9__h;
        IData/*31:0*/ __VactIterCount;
        QData/*63:0*/ top__DOT__brg_wdata;
        QData/*63:0*/ top__DOT__brg_rdata_mux;
        QData/*63:0*/ top__DOT__dma_host_rdata;
        QData/*63:0*/ top__DOT__dma_s_rdata;
        QData/*63:0*/ top__DOT__ram_wdata;
        QData/*63:0*/ top__DOT__ram_rdata;
        QData/*63:0*/ top__DOT__msix_addr_reg;
        QData/*63:0*/ top__DOT__u_bridge__DOT__rx_addr;
        QData/*63:0*/ top__DOT__u_bridge__DOT__host_mrd_addr;
        QData/*63:0*/ top__DOT__u_bridge__DOT__host_mwr_addr;
        QData/*63:0*/ top__DOT__u_bridge__DOT__host_mwr_data;
        QData/*63:0*/ top__DOT__u_sniffer__DOT__cycle_count;
        QData/*63:0*/ top__DOT__u_sniffer__DOT__last_rx_data;
        QData/*63:0*/ top__DOT__u_sniffer__DOT__last_tx_data;
        QData/*63:0*/ top__DOT__u_dma__DOT__host_addr;
        QData/*63:0*/ top__DOT__u_dma__DOT__h2c_host_araddr;
        QData/*63:0*/ top__DOT__u_dma__DOT__h2c_local_wdata;
        QData/*63:0*/ top__DOT__u_dma__DOT__c2h_host_awaddr;
        QData/*63:0*/ top__DOT__u_dma__DOT__c2h_host_wdata;
        QData/*63:0*/ top__DOT__u_dma__DOT__u_h2c__DOT__cur_host;
        QData/*63:0*/ top__DOT__u_dma__DOT__u_c2h__DOT__cur_host;
        QData/*63:0*/ __Vfunc_hdr_addr64__8__Vfuncout;
        VlUnpacked<VlWide<8>/*255:0*/, 256> top__DOT__u_sniffer__DOT__trace_ram;
        VlUnpacked<VlWide<4>/*127:0*/, 64> top__DOT__u_axi_sniffer__DOT__trace_ram;
        VlUnpacked<QData/*63:0*/, 512> top__DOT__u_ram__DOT__mem;
    };
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<1> __VactTriggered;
    VlTriggerVec<1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vtop__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vtop___024root(Vtop__Syms* symsp, const char* v__name);
    ~Vtop___024root();
    VL_UNCOPYABLE(Vtop___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
