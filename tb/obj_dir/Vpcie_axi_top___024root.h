// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vpcie_axi_top.h for the primary calling header

#ifndef VERILATED_VPCIE_AXI_TOP___024ROOT_H_
#define VERILATED_VPCIE_AXI_TOP___024ROOT_H_  // guard

#include "verilated.h"


class Vpcie_axi_top__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vpcie_axi_top___024root final : public VerilatedModule {
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
        VL_OUT8(dma_irq,0,0);
        CData/*7:0*/ pcie_axi_top__DOT__brg_wstrb;
        CData/*0:0*/ pcie_axi_top__DOT__brg_awvalid;
        CData/*0:0*/ pcie_axi_top__DOT__brg_awready;
        CData/*0:0*/ pcie_axi_top__DOT__brg_wvalid;
        CData/*0:0*/ pcie_axi_top__DOT__brg_wready;
        CData/*0:0*/ pcie_axi_top__DOT__brg_bready;
        CData/*0:0*/ pcie_axi_top__DOT__brg_arvalid;
        CData/*0:0*/ pcie_axi_top__DOT__brg_arready;
        CData/*0:0*/ pcie_axi_top__DOT__brg_rready;
        CData/*0:0*/ pcie_axi_top__DOT__dma_mrd_valid;
        CData/*0:0*/ pcie_axi_top__DOT__dma_mrd_ready;
        CData/*7:0*/ pcie_axi_top__DOT__dma_mrd_tag;
        CData/*0:0*/ pcie_axi_top__DOT__dma_mwr_valid;
        CData/*0:0*/ pcie_axi_top__DOT__dma_mwr_ready;
        CData/*0:0*/ pcie_axi_top__DOT__dma_cpl_valid;
        CData/*7:0*/ pcie_axi_top__DOT__dma_cpl_tag;
        CData/*1:0*/ pcie_axi_top__DOT__reg_bresp;
        CData/*1:0*/ pcie_axi_top__DOT__reg_rresp;
        CData/*0:0*/ pcie_axi_top__DOT__reg_awvalid;
        CData/*0:0*/ pcie_axi_top__DOT__reg_awready;
        CData/*0:0*/ pcie_axi_top__DOT__reg_wvalid;
        CData/*0:0*/ pcie_axi_top__DOT__reg_wready;
        CData/*0:0*/ pcie_axi_top__DOT__reg_bvalid;
        CData/*0:0*/ pcie_axi_top__DOT__reg_arready;
        CData/*0:0*/ pcie_axi_top__DOT__reg_rvalid;
        CData/*1:0*/ pcie_axi_top__DOT__dma_bresp;
        CData/*1:0*/ pcie_axi_top__DOT__dma_rresp;
        CData/*0:0*/ pcie_axi_top__DOT__dma_awready;
        CData/*0:0*/ pcie_axi_top__DOT__dma_wready;
        CData/*0:0*/ pcie_axi_top__DOT__dma_bvalid;
        CData/*0:0*/ pcie_axi_top__DOT__dma_arready;
        CData/*0:0*/ pcie_axi_top__DOT__dma_rvalid;
        CData/*0:0*/ pcie_axi_top__DOT__ram_awvalid;
        CData/*0:0*/ pcie_axi_top__DOT__ram_arvalid;
        CData/*7:0*/ pcie_axi_top__DOT__dma_ram_wstrb;
        CData/*0:0*/ pcie_axi_top__DOT__dma_ram_awvalid;
    };
    struct {
        CData/*0:0*/ pcie_axi_top__DOT__dma_ram_wvalid;
        CData/*0:0*/ pcie_axi_top__DOT__dma_ram_bready;
        CData/*0:0*/ pcie_axi_top__DOT__dma_ram_arvalid;
        CData/*0:0*/ pcie_axi_top__DOT__dma_ram_rready;
        CData/*0:0*/ pcie_axi_top__DOT__ram_busy;
        CData/*0:0*/ pcie_axi_top__DOT__ram_owner;
        CData/*7:0*/ pcie_axi_top__DOT__ram_real_wstrb;
        CData/*1:0*/ pcie_axi_top__DOT__ram_real_bresp;
        CData/*1:0*/ pcie_axi_top__DOT__ram_real_rresp;
        CData/*0:0*/ pcie_axi_top__DOT__ram_real_awready;
        CData/*0:0*/ pcie_axi_top__DOT__ram_real_wready;
        CData/*0:0*/ pcie_axi_top__DOT__ram_real_bvalid;
        CData/*0:0*/ pcie_axi_top__DOT__ram_real_bready;
        CData/*0:0*/ pcie_axi_top__DOT__ram_real_arready;
        CData/*0:0*/ pcie_axi_top__DOT__ram_real_rvalid;
        CData/*0:0*/ pcie_axi_top__DOT__ram_real_rready;
        CData/*0:0*/ pcie_axi_top__DOT__u_bridge__DOT__tx_cpl_hdr_dec;
        CData/*0:0*/ pcie_axi_top__DOT__u_bridge__DOT__tx_cpl_data_dec;
        CData/*2:0*/ pcie_axi_top__DOT__u_bridge__DOT__rx_fmt;
        CData/*4:0*/ pcie_axi_top__DOT__u_bridge__DOT__rx_type;
        CData/*7:0*/ pcie_axi_top__DOT__u_bridge__DOT__rx_tag;
        CData/*3:0*/ pcie_axi_top__DOT__u_bridge__DOT__rx_fbe;
        CData/*3:0*/ pcie_axi_top__DOT__u_bridge__DOT__rx_lbe;
        CData/*0:0*/ pcie_axi_top__DOT__u_bridge__DOT__rx_is_mrd;
        CData/*0:0*/ pcie_axi_top__DOT__u_bridge__DOT__rx_is_mwr;
        CData/*0:0*/ pcie_axi_top__DOT__u_bridge__DOT__rx_is_cpld;
        CData/*3:0*/ pcie_axi_top__DOT__u_bridge__DOT__state;
        CData/*7:0*/ pcie_axi_top__DOT__u_bridge__DOT__bar_req_tag;
        CData/*6:0*/ pcie_axi_top__DOT__u_bridge__DOT__bar_req_lower_addr;
        CData/*1:0*/ pcie_axi_top__DOT__u_bridge__DOT__bar_cpl_status;
        CData/*1:0*/ pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__state;
        CData/*3:0*/ pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__cnt;
        CData/*1:0*/ pcie_axi_top__DOT__u_regs__DOT__wr_state;
        CData/*1:0*/ pcie_axi_top__DOT__u_regs__DOT__rd_state;
        CData/*0:0*/ pcie_axi_top__DOT__u_dma__DOT__start;
        CData/*3:0*/ pcie_axi_top__DOT__u_dma__DOT__dma_state;
        CData/*7:0*/ pcie_axi_top__DOT__u_dma__DOT__cur_tag;
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
        SData/*9:0*/ pcie_axi_top__DOT__dma_mrd_len;
        SData/*9:0*/ pcie_axi_top__DOT__dma_mwr_len;
        SData/*9:0*/ pcie_axi_top__DOT__u_bridge__DOT__rx_len;
        SData/*15:0*/ pcie_axi_top__DOT__u_bridge__DOT__rx_rid;
        SData/*15:0*/ pcie_axi_top__DOT__u_bridge__DOT__bar_req_rid;
        SData/*15:0*/ pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__tx_cpl_hdr_cnt;
        VL_INW(rx_st_hdr,127,0,4);
        VL_INW(rx_st_data,255,0,8);
        VL_OUTW(tx_st_hdr,127,0,4);
        VL_OUTW(tx_st_data,255,0,8);
        VL_OUT(write_count,31,0);
        IData/*31:0*/ pcie_axi_top__DOT__brg_awaddr;
    };
    struct {
        IData/*31:0*/ pcie_axi_top__DOT__brg_araddr;
        IData/*31:0*/ pcie_axi_top__DOT__dma_ram_awaddr;
        IData/*31:0*/ pcie_axi_top__DOT__dma_ram_araddr;
        VlWide<4>/*127:0*/ pcie_axi_top__DOT__u_bridge__DOT__tx_hdr_r;
        IData/*19:0*/ pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__tx_cpl_data_cnt;
        IData/*31:0*/ pcie_axi_top__DOT__u_regs__DOT__write_cnt;
        IData/*31:0*/ pcie_axi_top__DOT__u_regs__DOT__wr_addr;
        IData/*31:0*/ pcie_axi_top__DOT__u_dma__DOT__ctrl_reg;
        IData/*31:0*/ pcie_axi_top__DOT__u_dma__DOT__status_reg;
        IData/*31:0*/ pcie_axi_top__DOT__u_dma__DOT__host_addr_lo;
        IData/*31:0*/ pcie_axi_top__DOT__u_dma__DOT__host_addr_hi;
        IData/*31:0*/ pcie_axi_top__DOT__u_dma__DOT__local_addr;
        IData/*31:0*/ pcie_axi_top__DOT__u_dma__DOT__length_reg;
        IData/*31:0*/ pcie_axi_top__DOT__u_dma__DOT__bytes_remaining;
        IData/*31:0*/ pcie_axi_top__DOT__u_dma__DOT__cur_local_addr;
        IData/*31:0*/ pcie_axi_top__DOT__u_ram__DOT__unnamedblk1__DOT__i;
        VlWide<4>/*127:0*/ __Vfunc_hdr_addr64__8__h;
        IData/*31:0*/ __Vfunc_hdr_addr32__9__Vfuncout;
        VlWide<4>/*127:0*/ __Vfunc_hdr_addr32__9__h;
        IData/*31:0*/ __VactIterCount;
        VL_OUT64(scratch_reg,63,0);
        QData/*63:0*/ pcie_axi_top__DOT__brg_wdata;
        QData/*63:0*/ pcie_axi_top__DOT__dma_mrd_addr;
        QData/*63:0*/ pcie_axi_top__DOT__dma_mwr_addr;
        QData/*63:0*/ pcie_axi_top__DOT__dma_mwr_data;
        QData/*63:0*/ pcie_axi_top__DOT__dma_cpl_data;
        QData/*63:0*/ pcie_axi_top__DOT__reg_rdata;
        QData/*63:0*/ pcie_axi_top__DOT__dma_rdata;
        QData/*63:0*/ pcie_axi_top__DOT__dma_ram_wdata;
        QData/*63:0*/ pcie_axi_top__DOT__ram_real_wdata;
        QData/*63:0*/ pcie_axi_top__DOT__ram_real_rdata;
        QData/*63:0*/ pcie_axi_top__DOT__u_bridge__DOT__rx_addr;
        QData/*63:0*/ pcie_axi_top__DOT__u_bridge__DOT__bar_cpl_data;
        QData/*63:0*/ pcie_axi_top__DOT__u_bridge__DOT__tx_data_r;
        QData/*63:0*/ pcie_axi_top__DOT__u_regs__DOT__scratch_reg;
        QData/*63:0*/ pcie_axi_top__DOT__u_dma__DOT__cur_host_addr;
        QData/*63:0*/ pcie_axi_top__DOT__u_dma__DOT__dma_data_buf;
        QData/*63:0*/ __Vfunc_hdr_addr64__8__Vfuncout;
        VlUnpacked<QData/*63:0*/, 512> pcie_axi_top__DOT__u_ram__DOT__mem;
        VlUnpacked<CData/*0:0*/, 3> __Vm_traceActivity;
    };
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<1> __VactTriggered;
    VlTriggerVec<1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vpcie_axi_top__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vpcie_axi_top___024root(Vpcie_axi_top__Syms* symsp, const char* v__name);
    ~Vpcie_axi_top___024root();
    VL_UNCOPYABLE(Vpcie_axi_top___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
