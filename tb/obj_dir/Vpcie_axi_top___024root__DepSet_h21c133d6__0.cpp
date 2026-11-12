// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vpcie_axi_top.h for the primary calling header

#include "Vpcie_axi_top__pch.h"
#include "Vpcie_axi_top___024root.h"

void Vpcie_axi_top___024root___ico_sequent__TOP__0(Vpcie_axi_top___024root* vlSelf);

void Vpcie_axi_top___024root___eval_ico(Vpcie_axi_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vpcie_axi_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpcie_axi_top___024root___eval_ico\n"); );
    // Body
    if ((1ULL & vlSelf->__VicoTriggered.word(0U))) {
        Vpcie_axi_top___024root___ico_sequent__TOP__0(vlSelf);
        vlSelf->__Vm_traceActivity[1U] = 1U;
    }
}

VL_INLINE_OPT void Vpcie_axi_top___024root___ico_sequent__TOP__0(Vpcie_axi_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vpcie_axi_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpcie_axi_top___024root___ico_sequent__TOP__0\n"); );
    // Init
    CData/*2:0*/ __Vfunc_hdr_fmt__0__Vfuncout;
    __Vfunc_hdr_fmt__0__Vfuncout = 0;
    VlWide<4>/*127:0*/ __Vfunc_hdr_fmt__0__h;
    VL_ZERO_W(128, __Vfunc_hdr_fmt__0__h);
    CData/*4:0*/ __Vfunc_hdr_type__1__Vfuncout;
    __Vfunc_hdr_type__1__Vfuncout = 0;
    VlWide<4>/*127:0*/ __Vfunc_hdr_type__1__h;
    VL_ZERO_W(128, __Vfunc_hdr_type__1__h);
    SData/*9:0*/ __Vfunc_hdr_len__2__Vfuncout;
    __Vfunc_hdr_len__2__Vfuncout = 0;
    VlWide<4>/*127:0*/ __Vfunc_hdr_len__2__h;
    VL_ZERO_W(128, __Vfunc_hdr_len__2__h);
    SData/*15:0*/ __Vfunc_hdr_rid__3__Vfuncout;
    __Vfunc_hdr_rid__3__Vfuncout = 0;
    VlWide<4>/*127:0*/ __Vfunc_hdr_rid__3__h;
    VL_ZERO_W(128, __Vfunc_hdr_rid__3__h);
    CData/*7:0*/ __Vfunc_hdr_tag__4__Vfuncout;
    __Vfunc_hdr_tag__4__Vfuncout = 0;
    VlWide<4>/*127:0*/ __Vfunc_hdr_tag__4__h;
    VL_ZERO_W(128, __Vfunc_hdr_tag__4__h);
    CData/*3:0*/ __Vfunc_hdr_fbe__5__Vfuncout;
    __Vfunc_hdr_fbe__5__Vfuncout = 0;
    VlWide<4>/*127:0*/ __Vfunc_hdr_fbe__5__h;
    VL_ZERO_W(128, __Vfunc_hdr_fbe__5__h);
    CData/*3:0*/ __Vfunc_hdr_lbe__6__Vfuncout;
    __Vfunc_hdr_lbe__6__Vfuncout = 0;
    VlWide<4>/*127:0*/ __Vfunc_hdr_lbe__6__h;
    VL_ZERO_W(128, __Vfunc_hdr_lbe__6__h);
    // Body
    __Vfunc_hdr_len__2__h[0U] = vlSelf->rx_st_hdr[0U];
    __Vfunc_hdr_len__2__h[1U] = vlSelf->rx_st_hdr[1U];
    __Vfunc_hdr_len__2__h[2U] = vlSelf->rx_st_hdr[2U];
    __Vfunc_hdr_len__2__h[3U] = vlSelf->rx_st_hdr[3U];
    __Vfunc_hdr_len__2__Vfuncout = (0x3ffU & __Vfunc_hdr_len__2__h[3U]);
    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_len 
        = __Vfunc_hdr_len__2__Vfuncout;
    __Vfunc_hdr_rid__3__h[0U] = vlSelf->rx_st_hdr[0U];
    __Vfunc_hdr_rid__3__h[1U] = vlSelf->rx_st_hdr[1U];
    __Vfunc_hdr_rid__3__h[2U] = vlSelf->rx_st_hdr[2U];
    __Vfunc_hdr_rid__3__h[3U] = vlSelf->rx_st_hdr[3U];
    __Vfunc_hdr_rid__3__Vfuncout = (__Vfunc_hdr_rid__3__h[2U] 
                                    >> 0x10U);
    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_rid 
        = __Vfunc_hdr_rid__3__Vfuncout;
    __Vfunc_hdr_tag__4__h[0U] = vlSelf->rx_st_hdr[0U];
    __Vfunc_hdr_tag__4__h[1U] = vlSelf->rx_st_hdr[1U];
    __Vfunc_hdr_tag__4__h[2U] = vlSelf->rx_st_hdr[2U];
    __Vfunc_hdr_tag__4__h[3U] = vlSelf->rx_st_hdr[3U];
    __Vfunc_hdr_tag__4__Vfuncout = (0xffU & (__Vfunc_hdr_tag__4__h[2U] 
                                             >> 8U));
    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_tag 
        = __Vfunc_hdr_tag__4__Vfuncout;
    __Vfunc_hdr_fbe__5__h[0U] = vlSelf->rx_st_hdr[0U];
    __Vfunc_hdr_fbe__5__h[1U] = vlSelf->rx_st_hdr[1U];
    __Vfunc_hdr_fbe__5__h[2U] = vlSelf->rx_st_hdr[2U];
    __Vfunc_hdr_fbe__5__h[3U] = vlSelf->rx_st_hdr[3U];
    __Vfunc_hdr_fbe__5__Vfuncout = (0xfU & __Vfunc_hdr_fbe__5__h[2U]);
    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_fbe 
        = __Vfunc_hdr_fbe__5__Vfuncout;
    __Vfunc_hdr_lbe__6__h[0U] = vlSelf->rx_st_hdr[0U];
    __Vfunc_hdr_lbe__6__h[1U] = vlSelf->rx_st_hdr[1U];
    __Vfunc_hdr_lbe__6__h[2U] = vlSelf->rx_st_hdr[2U];
    __Vfunc_hdr_lbe__6__h[3U] = vlSelf->rx_st_hdr[3U];
    __Vfunc_hdr_lbe__6__Vfuncout = (0xfU & (__Vfunc_hdr_lbe__6__h[2U] 
                                            >> 4U));
    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_lbe 
        = __Vfunc_hdr_lbe__6__Vfuncout;
    __Vfunc_hdr_fmt__0__h[0U] = vlSelf->rx_st_hdr[0U];
    __Vfunc_hdr_fmt__0__h[1U] = vlSelf->rx_st_hdr[1U];
    __Vfunc_hdr_fmt__0__h[2U] = vlSelf->rx_st_hdr[2U];
    __Vfunc_hdr_fmt__0__h[3U] = vlSelf->rx_st_hdr[3U];
    __Vfunc_hdr_fmt__0__Vfuncout = (__Vfunc_hdr_fmt__0__h[3U] 
                                    >> 0x1dU);
    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_fmt 
        = __Vfunc_hdr_fmt__0__Vfuncout;
    __Vfunc_hdr_type__1__h[0U] = vlSelf->rx_st_hdr[0U];
    __Vfunc_hdr_type__1__h[1U] = vlSelf->rx_st_hdr[1U];
    __Vfunc_hdr_type__1__h[2U] = vlSelf->rx_st_hdr[2U];
    __Vfunc_hdr_type__1__h[3U] = vlSelf->rx_st_hdr[3U];
    __Vfunc_hdr_type__1__Vfuncout = (0x1fU & (__Vfunc_hdr_type__1__h[3U] 
                                              >> 0x18U));
    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_type 
        = __Vfunc_hdr_type__1__Vfuncout;
    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_addr 
        = (([&]() {
                vlSelf->__Vfunc_is_4dw__7__fmt = vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_fmt;
                vlSelf->__Vfunc_is_4dw__7__Vfuncout 
                    = (1U & (IData)(vlSelf->__Vfunc_is_4dw__7__fmt));
            }(), (IData)(vlSelf->__Vfunc_is_4dw__7__Vfuncout))
            ? ([&]() {
                vlSelf->__Vfunc_hdr_addr64__8__h[0U] 
                    = vlSelf->rx_st_hdr[0U];
                vlSelf->__Vfunc_hdr_addr64__8__h[1U] 
                    = vlSelf->rx_st_hdr[1U];
                vlSelf->__Vfunc_hdr_addr64__8__h[2U] 
                    = vlSelf->rx_st_hdr[2U];
                vlSelf->__Vfunc_hdr_addr64__8__h[3U] 
                    = vlSelf->rx_st_hdr[3U];
                vlSelf->__Vfunc_hdr_addr64__8__Vfuncout 
                    = (((QData)((IData)(vlSelf->__Vfunc_hdr_addr64__8__h[1U])) 
                        << 0x20U) | (QData)((IData)(
                                                    vlSelf->__Vfunc_hdr_addr64__8__h[0U])));
            }(), vlSelf->__Vfunc_hdr_addr64__8__Vfuncout)
            : VL_EXTEND_QI(64,32, ([&]() {
                    vlSelf->__Vfunc_hdr_addr32__9__h[0U] 
                        = vlSelf->rx_st_hdr[0U];
                    vlSelf->__Vfunc_hdr_addr32__9__h[1U] 
                        = vlSelf->rx_st_hdr[1U];
                    vlSelf->__Vfunc_hdr_addr32__9__h[2U] 
                        = vlSelf->rx_st_hdr[2U];
                    vlSelf->__Vfunc_hdr_addr32__9__h[3U] 
                        = vlSelf->rx_st_hdr[3U];
                    vlSelf->__Vfunc_hdr_addr32__9__Vfuncout 
                        = vlSelf->__Vfunc_hdr_addr32__9__h[1U];
                }(), vlSelf->__Vfunc_hdr_addr32__9__Vfuncout)));
    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_is_mrd 
        = ((((IData)(vlSelf->rx_st_hvalid) & (IData)(vlSelf->rx_st_sop)) 
            & (0U == (IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_type))) 
           & (~ ([&]() {
                    vlSelf->__Vfunc_has_data__10__fmt 
                        = vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_fmt;
                    vlSelf->__Vfunc_has_data__10__Vfuncout 
                        = (1U & ((IData)(vlSelf->__Vfunc_has_data__10__fmt) 
                                 >> 1U));
                }(), (IData)(vlSelf->__Vfunc_has_data__10__Vfuncout))));
    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_is_mwr 
        = ((((IData)(vlSelf->rx_st_hvalid) & (IData)(vlSelf->rx_st_sop)) 
            & (0U == (IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_type))) 
           & ([&]() {
                vlSelf->__Vfunc_has_data__11__fmt = vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_fmt;
                vlSelf->__Vfunc_has_data__11__Vfuncout 
                    = (1U & ((IData)(vlSelf->__Vfunc_has_data__11__fmt) 
                             >> 1U));
            }(), (IData)(vlSelf->__Vfunc_has_data__11__Vfuncout)));
    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_is_cpld 
        = ((((IData)(vlSelf->rx_st_hvalid) & (IData)(vlSelf->rx_st_sop)) 
            & (0xaU == (IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_type))) 
           & ([&]() {
                vlSelf->__Vfunc_has_data__12__fmt = vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_fmt;
                vlSelf->__Vfunc_has_data__12__Vfuncout 
                    = (1U & ((IData)(vlSelf->__Vfunc_has_data__12__fmt) 
                             >> 1U));
            }(), (IData)(vlSelf->__Vfunc_has_data__12__Vfuncout)));
}

void Vpcie_axi_top___024root___eval_triggers__ico(Vpcie_axi_top___024root* vlSelf);

bool Vpcie_axi_top___024root___eval_phase__ico(Vpcie_axi_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vpcie_axi_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpcie_axi_top___024root___eval_phase__ico\n"); );
    // Init
    CData/*0:0*/ __VicoExecute;
    // Body
    Vpcie_axi_top___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = vlSelf->__VicoTriggered.any();
    if (__VicoExecute) {
        Vpcie_axi_top___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void Vpcie_axi_top___024root___eval_act(Vpcie_axi_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vpcie_axi_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpcie_axi_top___024root___eval_act\n"); );
}

void Vpcie_axi_top___024root___nba_sequent__TOP__0(Vpcie_axi_top___024root* vlSelf);

void Vpcie_axi_top___024root___eval_nba(Vpcie_axi_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vpcie_axi_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpcie_axi_top___024root___eval_nba\n"); );
    // Body
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vpcie_axi_top___024root___nba_sequent__TOP__0(vlSelf);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
}

extern const VlUnpacked<CData/*2:0*/, 128> Vpcie_axi_top__ConstPool__TABLE_hf3a84768_0;
extern const VlUnpacked<CData/*5:0*/, 128> Vpcie_axi_top__ConstPool__TABLE_h92b69fc4_0;
extern const VlUnpacked<CData/*2:0*/, 128> Vpcie_axi_top__ConstPool__TABLE_h3a3a7adf_0;
extern const VlUnpacked<CData/*3:0*/, 128> Vpcie_axi_top__ConstPool__TABLE_h1588c7a3_0;
extern const VlUnpacked<CData/*1:0*/, 128> Vpcie_axi_top__ConstPool__TABLE_h643f69a8_0;

VL_INLINE_OPT void Vpcie_axi_top___024root___nba_sequent__TOP__0(Vpcie_axi_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vpcie_axi_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpcie_axi_top___024root___nba_sequent__TOP__0\n"); );
    // Init
    CData/*6:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    CData/*0:0*/ __Vdly__pcie_axi_top__DOT__ram_owner;
    __Vdly__pcie_axi_top__DOT__ram_owner = 0;
    CData/*0:0*/ __Vdly__pcie_axi_top__DOT__dma_mrd_ready;
    __Vdly__pcie_axi_top__DOT__dma_mrd_ready = 0;
    CData/*0:0*/ __Vdly__pcie_axi_top__DOT__dma_mwr_ready;
    __Vdly__pcie_axi_top__DOT__dma_mwr_ready = 0;
    CData/*0:0*/ __Vdly__tx_st_hvalid;
    __Vdly__tx_st_hvalid = 0;
    CData/*0:0*/ __Vdly__pcie_axi_top__DOT__brg_awvalid;
    __Vdly__pcie_axi_top__DOT__brg_awvalid = 0;
    CData/*0:0*/ __Vdly__pcie_axi_top__DOT__brg_wvalid;
    __Vdly__pcie_axi_top__DOT__brg_wvalid = 0;
    CData/*3:0*/ __Vdly__pcie_axi_top__DOT__u_bridge__DOT__state;
    __Vdly__pcie_axi_top__DOT__u_bridge__DOT__state = 0;
    SData/*15:0*/ __Vdly__pcie_axi_top__DOT__u_bridge__DOT__bar_req_rid;
    __Vdly__pcie_axi_top__DOT__u_bridge__DOT__bar_req_rid = 0;
    CData/*7:0*/ __Vdly__pcie_axi_top__DOT__u_bridge__DOT__bar_req_tag;
    __Vdly__pcie_axi_top__DOT__u_bridge__DOT__bar_req_tag = 0;
    CData/*6:0*/ __Vdly__pcie_axi_top__DOT__u_bridge__DOT__bar_req_lower_addr;
    __Vdly__pcie_axi_top__DOT__u_bridge__DOT__bar_req_lower_addr = 0;
    QData/*63:0*/ __Vdly__pcie_axi_top__DOT__u_bridge__DOT__bar_cpl_data;
    __Vdly__pcie_axi_top__DOT__u_bridge__DOT__bar_cpl_data = 0;
    CData/*1:0*/ __Vdly__pcie_axi_top__DOT__u_bridge__DOT__bar_cpl_status;
    __Vdly__pcie_axi_top__DOT__u_bridge__DOT__bar_cpl_status = 0;
    SData/*15:0*/ __Vdly__pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__tx_cpl_hdr_cnt;
    __Vdly__pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__tx_cpl_hdr_cnt = 0;
    IData/*19:0*/ __Vdly__pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__tx_cpl_data_cnt;
    __Vdly__pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__tx_cpl_data_cnt = 0;
    IData/*31:0*/ __Vdly__pcie_axi_top__DOT__u_dma__DOT__ctrl_reg;
    __Vdly__pcie_axi_top__DOT__u_dma__DOT__ctrl_reg = 0;
    IData/*31:0*/ __Vdly__pcie_axi_top__DOT__u_dma__DOT__host_addr_lo;
    __Vdly__pcie_axi_top__DOT__u_dma__DOT__host_addr_lo = 0;
    IData/*31:0*/ __Vdly__pcie_axi_top__DOT__u_dma__DOT__host_addr_hi;
    __Vdly__pcie_axi_top__DOT__u_dma__DOT__host_addr_hi = 0;
    IData/*31:0*/ __Vdly__pcie_axi_top__DOT__u_dma__DOT__local_addr;
    __Vdly__pcie_axi_top__DOT__u_dma__DOT__local_addr = 0;
    IData/*31:0*/ __Vdly__pcie_axi_top__DOT__u_dma__DOT__length_reg;
    __Vdly__pcie_axi_top__DOT__u_dma__DOT__length_reg = 0;
    CData/*0:0*/ __Vdly__pcie_axi_top__DOT__dma_bvalid;
    __Vdly__pcie_axi_top__DOT__dma_bvalid = 0;
    QData/*63:0*/ __Vdly__pcie_axi_top__DOT__dma_rdata;
    __Vdly__pcie_axi_top__DOT__dma_rdata = 0;
    CData/*0:0*/ __Vdly__pcie_axi_top__DOT__dma_rvalid;
    __Vdly__pcie_axi_top__DOT__dma_rvalid = 0;
    IData/*31:0*/ __Vdly__pcie_axi_top__DOT__u_dma__DOT__bytes_remaining;
    __Vdly__pcie_axi_top__DOT__u_dma__DOT__bytes_remaining = 0;
    QData/*63:0*/ __Vdly__pcie_axi_top__DOT__u_dma__DOT__cur_host_addr;
    __Vdly__pcie_axi_top__DOT__u_dma__DOT__cur_host_addr = 0;
    IData/*31:0*/ __Vdly__pcie_axi_top__DOT__u_dma__DOT__cur_local_addr;
    __Vdly__pcie_axi_top__DOT__u_dma__DOT__cur_local_addr = 0;
    CData/*7:0*/ __Vdly__pcie_axi_top__DOT__u_dma__DOT__cur_tag;
    __Vdly__pcie_axi_top__DOT__u_dma__DOT__cur_tag = 0;
    CData/*3:0*/ __Vdly__pcie_axi_top__DOT__u_dma__DOT__dma_state;
    __Vdly__pcie_axi_top__DOT__u_dma__DOT__dma_state = 0;
    QData/*63:0*/ __Vdly__pcie_axi_top__DOT__u_dma__DOT__dma_data_buf;
    __Vdly__pcie_axi_top__DOT__u_dma__DOT__dma_data_buf = 0;
    SData/*8:0*/ __Vdlyvdim0__pcie_axi_top__DOT__u_ram__DOT__mem__v0;
    __Vdlyvdim0__pcie_axi_top__DOT__u_ram__DOT__mem__v0 = 0;
    CData/*5:0*/ __Vdlyvlsb__pcie_axi_top__DOT__u_ram__DOT__mem__v0;
    __Vdlyvlsb__pcie_axi_top__DOT__u_ram__DOT__mem__v0 = 0;
    CData/*7:0*/ __Vdlyvval__pcie_axi_top__DOT__u_ram__DOT__mem__v0;
    __Vdlyvval__pcie_axi_top__DOT__u_ram__DOT__mem__v0 = 0;
    CData/*0:0*/ __Vdlyvset__pcie_axi_top__DOT__u_ram__DOT__mem__v0;
    __Vdlyvset__pcie_axi_top__DOT__u_ram__DOT__mem__v0 = 0;
    CData/*0:0*/ __Vdly__pcie_axi_top__DOT__ram_real_awready;
    __Vdly__pcie_axi_top__DOT__ram_real_awready = 0;
    CData/*0:0*/ __Vdly__pcie_axi_top__DOT__ram_real_wready;
    __Vdly__pcie_axi_top__DOT__ram_real_wready = 0;
    CData/*0:0*/ __Vdly__pcie_axi_top__DOT__ram_real_bvalid;
    __Vdly__pcie_axi_top__DOT__ram_real_bvalid = 0;
    SData/*8:0*/ __Vdlyvdim0__pcie_axi_top__DOT__u_ram__DOT__mem__v1;
    __Vdlyvdim0__pcie_axi_top__DOT__u_ram__DOT__mem__v1 = 0;
    CData/*5:0*/ __Vdlyvlsb__pcie_axi_top__DOT__u_ram__DOT__mem__v1;
    __Vdlyvlsb__pcie_axi_top__DOT__u_ram__DOT__mem__v1 = 0;
    CData/*7:0*/ __Vdlyvval__pcie_axi_top__DOT__u_ram__DOT__mem__v1;
    __Vdlyvval__pcie_axi_top__DOT__u_ram__DOT__mem__v1 = 0;
    CData/*0:0*/ __Vdlyvset__pcie_axi_top__DOT__u_ram__DOT__mem__v1;
    __Vdlyvset__pcie_axi_top__DOT__u_ram__DOT__mem__v1 = 0;
    SData/*8:0*/ __Vdlyvdim0__pcie_axi_top__DOT__u_ram__DOT__mem__v2;
    __Vdlyvdim0__pcie_axi_top__DOT__u_ram__DOT__mem__v2 = 0;
    CData/*5:0*/ __Vdlyvlsb__pcie_axi_top__DOT__u_ram__DOT__mem__v2;
    __Vdlyvlsb__pcie_axi_top__DOT__u_ram__DOT__mem__v2 = 0;
    CData/*7:0*/ __Vdlyvval__pcie_axi_top__DOT__u_ram__DOT__mem__v2;
    __Vdlyvval__pcie_axi_top__DOT__u_ram__DOT__mem__v2 = 0;
    CData/*0:0*/ __Vdlyvset__pcie_axi_top__DOT__u_ram__DOT__mem__v2;
    __Vdlyvset__pcie_axi_top__DOT__u_ram__DOT__mem__v2 = 0;
    SData/*8:0*/ __Vdlyvdim0__pcie_axi_top__DOT__u_ram__DOT__mem__v3;
    __Vdlyvdim0__pcie_axi_top__DOT__u_ram__DOT__mem__v3 = 0;
    CData/*5:0*/ __Vdlyvlsb__pcie_axi_top__DOT__u_ram__DOT__mem__v3;
    __Vdlyvlsb__pcie_axi_top__DOT__u_ram__DOT__mem__v3 = 0;
    CData/*7:0*/ __Vdlyvval__pcie_axi_top__DOT__u_ram__DOT__mem__v3;
    __Vdlyvval__pcie_axi_top__DOT__u_ram__DOT__mem__v3 = 0;
    CData/*0:0*/ __Vdlyvset__pcie_axi_top__DOT__u_ram__DOT__mem__v3;
    __Vdlyvset__pcie_axi_top__DOT__u_ram__DOT__mem__v3 = 0;
    SData/*8:0*/ __Vdlyvdim0__pcie_axi_top__DOT__u_ram__DOT__mem__v4;
    __Vdlyvdim0__pcie_axi_top__DOT__u_ram__DOT__mem__v4 = 0;
    CData/*5:0*/ __Vdlyvlsb__pcie_axi_top__DOT__u_ram__DOT__mem__v4;
    __Vdlyvlsb__pcie_axi_top__DOT__u_ram__DOT__mem__v4 = 0;
    CData/*7:0*/ __Vdlyvval__pcie_axi_top__DOT__u_ram__DOT__mem__v4;
    __Vdlyvval__pcie_axi_top__DOT__u_ram__DOT__mem__v4 = 0;
    CData/*0:0*/ __Vdlyvset__pcie_axi_top__DOT__u_ram__DOT__mem__v4;
    __Vdlyvset__pcie_axi_top__DOT__u_ram__DOT__mem__v4 = 0;
    SData/*8:0*/ __Vdlyvdim0__pcie_axi_top__DOT__u_ram__DOT__mem__v5;
    __Vdlyvdim0__pcie_axi_top__DOT__u_ram__DOT__mem__v5 = 0;
    CData/*5:0*/ __Vdlyvlsb__pcie_axi_top__DOT__u_ram__DOT__mem__v5;
    __Vdlyvlsb__pcie_axi_top__DOT__u_ram__DOT__mem__v5 = 0;
    CData/*7:0*/ __Vdlyvval__pcie_axi_top__DOT__u_ram__DOT__mem__v5;
    __Vdlyvval__pcie_axi_top__DOT__u_ram__DOT__mem__v5 = 0;
    CData/*0:0*/ __Vdlyvset__pcie_axi_top__DOT__u_ram__DOT__mem__v5;
    __Vdlyvset__pcie_axi_top__DOT__u_ram__DOT__mem__v5 = 0;
    SData/*8:0*/ __Vdlyvdim0__pcie_axi_top__DOT__u_ram__DOT__mem__v6;
    __Vdlyvdim0__pcie_axi_top__DOT__u_ram__DOT__mem__v6 = 0;
    CData/*5:0*/ __Vdlyvlsb__pcie_axi_top__DOT__u_ram__DOT__mem__v6;
    __Vdlyvlsb__pcie_axi_top__DOT__u_ram__DOT__mem__v6 = 0;
    CData/*7:0*/ __Vdlyvval__pcie_axi_top__DOT__u_ram__DOT__mem__v6;
    __Vdlyvval__pcie_axi_top__DOT__u_ram__DOT__mem__v6 = 0;
    CData/*0:0*/ __Vdlyvset__pcie_axi_top__DOT__u_ram__DOT__mem__v6;
    __Vdlyvset__pcie_axi_top__DOT__u_ram__DOT__mem__v6 = 0;
    SData/*8:0*/ __Vdlyvdim0__pcie_axi_top__DOT__u_ram__DOT__mem__v7;
    __Vdlyvdim0__pcie_axi_top__DOT__u_ram__DOT__mem__v7 = 0;
    CData/*5:0*/ __Vdlyvlsb__pcie_axi_top__DOT__u_ram__DOT__mem__v7;
    __Vdlyvlsb__pcie_axi_top__DOT__u_ram__DOT__mem__v7 = 0;
    CData/*7:0*/ __Vdlyvval__pcie_axi_top__DOT__u_ram__DOT__mem__v7;
    __Vdlyvval__pcie_axi_top__DOT__u_ram__DOT__mem__v7 = 0;
    CData/*0:0*/ __Vdlyvset__pcie_axi_top__DOT__u_ram__DOT__mem__v7;
    __Vdlyvset__pcie_axi_top__DOT__u_ram__DOT__mem__v7 = 0;
    SData/*8:0*/ __Vdly__pcie_axi_top__DOT__u_ram__DOT__rd_addr_latched;
    __Vdly__pcie_axi_top__DOT__u_ram__DOT__rd_addr_latched = 0;
    CData/*0:0*/ __Vdly__pcie_axi_top__DOT__ram_real_arready;
    __Vdly__pcie_axi_top__DOT__ram_real_arready = 0;
    CData/*0:0*/ __Vdly__pcie_axi_top__DOT__u_ram__DOT__read_pending;
    __Vdly__pcie_axi_top__DOT__u_ram__DOT__read_pending = 0;
    QData/*63:0*/ __Vdly__pcie_axi_top__DOT__ram_real_rdata;
    __Vdly__pcie_axi_top__DOT__ram_real_rdata = 0;
    CData/*0:0*/ __Vdly__pcie_axi_top__DOT__ram_real_rvalid;
    __Vdly__pcie_axi_top__DOT__ram_real_rvalid = 0;
    // Body
    __Vdly__pcie_axi_top__DOT__u_dma__DOT__dma_data_buf 
        = vlSelf->pcie_axi_top__DOT__u_dma__DOT__dma_data_buf;
    __Vdly__pcie_axi_top__DOT__u_dma__DOT__dma_state 
        = vlSelf->pcie_axi_top__DOT__u_dma__DOT__dma_state;
    __Vdly__pcie_axi_top__DOT__u_dma__DOT__cur_tag 
        = vlSelf->pcie_axi_top__DOT__u_dma__DOT__cur_tag;
    __Vdly__pcie_axi_top__DOT__u_dma__DOT__cur_local_addr 
        = vlSelf->pcie_axi_top__DOT__u_dma__DOT__cur_local_addr;
    __Vdly__pcie_axi_top__DOT__u_dma__DOT__cur_host_addr 
        = vlSelf->pcie_axi_top__DOT__u_dma__DOT__cur_host_addr;
    __Vdly__pcie_axi_top__DOT__u_dma__DOT__bytes_remaining 
        = vlSelf->pcie_axi_top__DOT__u_dma__DOT__bytes_remaining;
    __Vdly__pcie_axi_top__DOT__ram_owner = vlSelf->pcie_axi_top__DOT__ram_owner;
    __Vdly__pcie_axi_top__DOT__u_bridge__DOT__bar_cpl_status 
        = vlSelf->pcie_axi_top__DOT__u_bridge__DOT__bar_cpl_status;
    __Vdly__pcie_axi_top__DOT__u_bridge__DOT__bar_cpl_data 
        = vlSelf->pcie_axi_top__DOT__u_bridge__DOT__bar_cpl_data;
    __Vdly__pcie_axi_top__DOT__u_bridge__DOT__bar_req_lower_addr 
        = vlSelf->pcie_axi_top__DOT__u_bridge__DOT__bar_req_lower_addr;
    __Vdly__pcie_axi_top__DOT__u_bridge__DOT__bar_req_tag 
        = vlSelf->pcie_axi_top__DOT__u_bridge__DOT__bar_req_tag;
    __Vdly__pcie_axi_top__DOT__u_bridge__DOT__bar_req_rid 
        = vlSelf->pcie_axi_top__DOT__u_bridge__DOT__bar_req_rid;
    __Vdly__pcie_axi_top__DOT__u_bridge__DOT__state 
        = vlSelf->pcie_axi_top__DOT__u_bridge__DOT__state;
    __Vdly__pcie_axi_top__DOT__brg_wvalid = vlSelf->pcie_axi_top__DOT__brg_wvalid;
    __Vdly__tx_st_hvalid = vlSelf->tx_st_hvalid;
    __Vdly__pcie_axi_top__DOT__dma_mwr_ready = vlSelf->pcie_axi_top__DOT__dma_mwr_ready;
    __Vdly__pcie_axi_top__DOT__dma_mrd_ready = vlSelf->pcie_axi_top__DOT__dma_mrd_ready;
    __Vdly__pcie_axi_top__DOT__brg_awvalid = vlSelf->pcie_axi_top__DOT__brg_awvalid;
    __Vdly__pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__tx_cpl_data_cnt 
        = vlSelf->pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__tx_cpl_data_cnt;
    __Vdly__pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__tx_cpl_hdr_cnt 
        = vlSelf->pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__tx_cpl_hdr_cnt;
    __Vdly__pcie_axi_top__DOT__ram_real_rvalid = vlSelf->pcie_axi_top__DOT__ram_real_rvalid;
    __Vdly__pcie_axi_top__DOT__ram_real_rdata = vlSelf->pcie_axi_top__DOT__ram_real_rdata;
    __Vdly__pcie_axi_top__DOT__u_ram__DOT__read_pending 
        = vlSelf->pcie_axi_top__DOT__u_ram__DOT__read_pending;
    __Vdly__pcie_axi_top__DOT__u_ram__DOT__rd_addr_latched 
        = vlSelf->pcie_axi_top__DOT__u_ram__DOT__rd_addr_latched;
    __Vdly__pcie_axi_top__DOT__ram_real_arready = vlSelf->pcie_axi_top__DOT__ram_real_arready;
    __Vdly__pcie_axi_top__DOT__ram_real_bvalid = vlSelf->pcie_axi_top__DOT__ram_real_bvalid;
    __Vdly__pcie_axi_top__DOT__ram_real_wready = vlSelf->pcie_axi_top__DOT__ram_real_wready;
    __Vdly__pcie_axi_top__DOT__ram_real_awready = vlSelf->pcie_axi_top__DOT__ram_real_awready;
    __Vdlyvset__pcie_axi_top__DOT__u_ram__DOT__mem__v0 = 0U;
    __Vdlyvset__pcie_axi_top__DOT__u_ram__DOT__mem__v1 = 0U;
    __Vdlyvset__pcie_axi_top__DOT__u_ram__DOT__mem__v2 = 0U;
    __Vdlyvset__pcie_axi_top__DOT__u_ram__DOT__mem__v3 = 0U;
    __Vdlyvset__pcie_axi_top__DOT__u_ram__DOT__mem__v4 = 0U;
    __Vdlyvset__pcie_axi_top__DOT__u_ram__DOT__mem__v5 = 0U;
    __Vdlyvset__pcie_axi_top__DOT__u_ram__DOT__mem__v6 = 0U;
    __Vdlyvset__pcie_axi_top__DOT__u_ram__DOT__mem__v7 = 0U;
    __Vdly__pcie_axi_top__DOT__dma_rvalid = vlSelf->pcie_axi_top__DOT__dma_rvalid;
    __Vdly__pcie_axi_top__DOT__dma_rdata = vlSelf->pcie_axi_top__DOT__dma_rdata;
    __Vdly__pcie_axi_top__DOT__dma_bvalid = vlSelf->pcie_axi_top__DOT__dma_bvalid;
    __Vdly__pcie_axi_top__DOT__u_dma__DOT__length_reg 
        = vlSelf->pcie_axi_top__DOT__u_dma__DOT__length_reg;
    __Vdly__pcie_axi_top__DOT__u_dma__DOT__local_addr 
        = vlSelf->pcie_axi_top__DOT__u_dma__DOT__local_addr;
    __Vdly__pcie_axi_top__DOT__u_dma__DOT__host_addr_hi 
        = vlSelf->pcie_axi_top__DOT__u_dma__DOT__host_addr_hi;
    __Vdly__pcie_axi_top__DOT__u_dma__DOT__host_addr_lo 
        = vlSelf->pcie_axi_top__DOT__u_dma__DOT__host_addr_lo;
    __Vdly__pcie_axi_top__DOT__u_dma__DOT__ctrl_reg 
        = vlSelf->pcie_axi_top__DOT__u_dma__DOT__ctrl_reg;
    if (vlSelf->rst_n) {
        if (vlSelf->pcie_axi_top__DOT__ram_busy) {
            if ((((IData)(vlSelf->pcie_axi_top__DOT__ram_real_bvalid) 
                  & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_bready)) 
                 | ((IData)(vlSelf->pcie_axi_top__DOT__ram_real_rvalid) 
                    & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_rready)))) {
                vlSelf->pcie_axi_top__DOT__ram_busy = 0U;
            }
        } else if (((IData)(vlSelf->pcie_axi_top__DOT__ram_awvalid) 
                    | (IData)(vlSelf->pcie_axi_top__DOT__ram_arvalid))) {
            vlSelf->pcie_axi_top__DOT__ram_busy = 1U;
            __Vdly__pcie_axi_top__DOT__ram_owner = 0U;
        } else if (((IData)(vlSelf->pcie_axi_top__DOT__dma_ram_awvalid) 
                    | (IData)(vlSelf->pcie_axi_top__DOT__dma_ram_arvalid))) {
            vlSelf->pcie_axi_top__DOT__ram_busy = 1U;
            __Vdly__pcie_axi_top__DOT__ram_owner = 1U;
        }
        if ((4U & (IData)(vlSelf->tx_dcrdt_update))) {
            __Vdly__pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__tx_cpl_data_cnt 
                = (0xfffffU & (vlSelf->pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__tx_cpl_data_cnt 
                               + (IData)(vlSelf->tx_dcrdt_update_cnt)));
        }
        if (((IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_cpl_data_dec) 
             & (1U <= vlSelf->pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__tx_cpl_data_cnt))) {
            __Vdly__pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__tx_cpl_data_cnt 
                = (0xfffffU & (vlSelf->pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__tx_cpl_data_cnt 
                               - (IData)(1U)));
        }
        if ((4U & (IData)(vlSelf->tx_hcrdt_update))) {
            __Vdly__pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__tx_cpl_hdr_cnt 
                = (0xffffU & ((IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__tx_cpl_hdr_cnt) 
                              + (IData)(vlSelf->tx_hcrdt_update_cnt)));
        }
        if (((IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_cpl_hdr_dec) 
             & (0U < (IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__tx_cpl_hdr_cnt)))) {
            __Vdly__pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__tx_cpl_hdr_cnt 
                = (0xffffU & ((IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__tx_cpl_hdr_cnt) 
                              - (IData)(1U)));
        }
        if ((((IData)(vlSelf->pcie_axi_top__DOT__ram_owner)
               ? (IData)(vlSelf->pcie_axi_top__DOT__dma_ram_arvalid)
               : (IData)(vlSelf->pcie_axi_top__DOT__ram_arvalid)) 
             & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_arready))) {
            __Vdly__pcie_axi_top__DOT__u_ram__DOT__rd_addr_latched 
                = (0x1ffU & (((IData)(vlSelf->pcie_axi_top__DOT__ram_owner)
                               ? vlSelf->pcie_axi_top__DOT__dma_ram_araddr
                               : vlSelf->pcie_axi_top__DOT__brg_araddr) 
                             >> 3U));
            __Vdly__pcie_axi_top__DOT__ram_real_arready = 0U;
            __Vdly__pcie_axi_top__DOT__u_ram__DOT__read_pending = 1U;
        }
        if (vlSelf->pcie_axi_top__DOT__u_ram__DOT__read_pending) {
            __Vdly__pcie_axi_top__DOT__ram_real_rdata 
                = vlSelf->pcie_axi_top__DOT__u_ram__DOT__mem
                [vlSelf->pcie_axi_top__DOT__u_ram__DOT__rd_addr_latched];
            __Vdly__pcie_axi_top__DOT__ram_real_rvalid = 1U;
            __Vdly__pcie_axi_top__DOT__u_ram__DOT__read_pending = 0U;
        }
        if (((IData)(vlSelf->pcie_axi_top__DOT__ram_real_rvalid) 
             & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_rready))) {
            __Vdly__pcie_axi_top__DOT__ram_real_rvalid = 0U;
            __Vdly__pcie_axi_top__DOT__ram_real_arready = 1U;
        }
        if (((((IData)(vlSelf->pcie_axi_top__DOT__ram_owner)
                ? (IData)(vlSelf->pcie_axi_top__DOT__dma_ram_awvalid)
                : (IData)(vlSelf->pcie_axi_top__DOT__ram_awvalid)) 
              & ((IData)(vlSelf->pcie_axi_top__DOT__ram_owner)
                  ? (IData)(vlSelf->pcie_axi_top__DOT__dma_ram_wvalid)
                  : ((IData)(vlSelf->pcie_axi_top__DOT__brg_wvalid) 
                     & (vlSelf->pcie_axi_top__DOT__brg_awaddr 
                        >> 0xcU)))) & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_awready))) {
            vlSelf->pcie_axi_top__DOT__u_ram__DOT__unnamedblk1__DOT__i = 8U;
            if ((1U & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_wstrb))) {
                __Vdlyvval__pcie_axi_top__DOT__u_ram__DOT__mem__v0 
                    = (0xffU & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_wdata));
                __Vdlyvset__pcie_axi_top__DOT__u_ram__DOT__mem__v0 = 1U;
                __Vdlyvlsb__pcie_axi_top__DOT__u_ram__DOT__mem__v0 = 0U;
                __Vdlyvdim0__pcie_axi_top__DOT__u_ram__DOT__mem__v0 
                    = (0x1ffU & (((IData)(vlSelf->pcie_axi_top__DOT__ram_owner)
                                   ? vlSelf->pcie_axi_top__DOT__dma_ram_awaddr
                                   : vlSelf->pcie_axi_top__DOT__brg_awaddr) 
                                 >> 3U));
            }
            __Vdly__pcie_axi_top__DOT__ram_real_awready = 0U;
            __Vdly__pcie_axi_top__DOT__ram_real_wready = 0U;
            __Vdly__pcie_axi_top__DOT__ram_real_bvalid = 1U;
            if ((2U & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_wstrb))) {
                __Vdlyvval__pcie_axi_top__DOT__u_ram__DOT__mem__v1 
                    = (0xffU & (IData)((vlSelf->pcie_axi_top__DOT__ram_real_wdata 
                                        >> 8U)));
                __Vdlyvset__pcie_axi_top__DOT__u_ram__DOT__mem__v1 = 1U;
                __Vdlyvlsb__pcie_axi_top__DOT__u_ram__DOT__mem__v1 = 8U;
                __Vdlyvdim0__pcie_axi_top__DOT__u_ram__DOT__mem__v1 
                    = (0x1ffU & (((IData)(vlSelf->pcie_axi_top__DOT__ram_owner)
                                   ? vlSelf->pcie_axi_top__DOT__dma_ram_awaddr
                                   : vlSelf->pcie_axi_top__DOT__brg_awaddr) 
                                 >> 3U));
            }
            if ((4U & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_wstrb))) {
                __Vdlyvval__pcie_axi_top__DOT__u_ram__DOT__mem__v2 
                    = (0xffU & (IData)((vlSelf->pcie_axi_top__DOT__ram_real_wdata 
                                        >> 0x10U)));
                __Vdlyvset__pcie_axi_top__DOT__u_ram__DOT__mem__v2 = 1U;
                __Vdlyvlsb__pcie_axi_top__DOT__u_ram__DOT__mem__v2 = 0x10U;
                __Vdlyvdim0__pcie_axi_top__DOT__u_ram__DOT__mem__v2 
                    = (0x1ffU & (((IData)(vlSelf->pcie_axi_top__DOT__ram_owner)
                                   ? vlSelf->pcie_axi_top__DOT__dma_ram_awaddr
                                   : vlSelf->pcie_axi_top__DOT__brg_awaddr) 
                                 >> 3U));
            }
            if ((8U & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_wstrb))) {
                __Vdlyvval__pcie_axi_top__DOT__u_ram__DOT__mem__v3 
                    = (0xffU & (IData)((vlSelf->pcie_axi_top__DOT__ram_real_wdata 
                                        >> 0x18U)));
                __Vdlyvset__pcie_axi_top__DOT__u_ram__DOT__mem__v3 = 1U;
                __Vdlyvlsb__pcie_axi_top__DOT__u_ram__DOT__mem__v3 = 0x18U;
                __Vdlyvdim0__pcie_axi_top__DOT__u_ram__DOT__mem__v3 
                    = (0x1ffU & (((IData)(vlSelf->pcie_axi_top__DOT__ram_owner)
                                   ? vlSelf->pcie_axi_top__DOT__dma_ram_awaddr
                                   : vlSelf->pcie_axi_top__DOT__brg_awaddr) 
                                 >> 3U));
            }
            if ((0x10U & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_wstrb))) {
                __Vdlyvval__pcie_axi_top__DOT__u_ram__DOT__mem__v4 
                    = (0xffU & (IData)((vlSelf->pcie_axi_top__DOT__ram_real_wdata 
                                        >> 0x20U)));
                __Vdlyvset__pcie_axi_top__DOT__u_ram__DOT__mem__v4 = 1U;
                __Vdlyvlsb__pcie_axi_top__DOT__u_ram__DOT__mem__v4 = 0x20U;
                __Vdlyvdim0__pcie_axi_top__DOT__u_ram__DOT__mem__v4 
                    = (0x1ffU & (((IData)(vlSelf->pcie_axi_top__DOT__ram_owner)
                                   ? vlSelf->pcie_axi_top__DOT__dma_ram_awaddr
                                   : vlSelf->pcie_axi_top__DOT__brg_awaddr) 
                                 >> 3U));
            }
            if ((0x20U & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_wstrb))) {
                __Vdlyvval__pcie_axi_top__DOT__u_ram__DOT__mem__v5 
                    = (0xffU & (IData)((vlSelf->pcie_axi_top__DOT__ram_real_wdata 
                                        >> 0x28U)));
                __Vdlyvset__pcie_axi_top__DOT__u_ram__DOT__mem__v5 = 1U;
                __Vdlyvlsb__pcie_axi_top__DOT__u_ram__DOT__mem__v5 = 0x28U;
                __Vdlyvdim0__pcie_axi_top__DOT__u_ram__DOT__mem__v5 
                    = (0x1ffU & (((IData)(vlSelf->pcie_axi_top__DOT__ram_owner)
                                   ? vlSelf->pcie_axi_top__DOT__dma_ram_awaddr
                                   : vlSelf->pcie_axi_top__DOT__brg_awaddr) 
                                 >> 3U));
            }
            if ((0x40U & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_wstrb))) {
                __Vdlyvval__pcie_axi_top__DOT__u_ram__DOT__mem__v6 
                    = (0xffU & (IData)((vlSelf->pcie_axi_top__DOT__ram_real_wdata 
                                        >> 0x30U)));
                __Vdlyvset__pcie_axi_top__DOT__u_ram__DOT__mem__v6 = 1U;
                __Vdlyvlsb__pcie_axi_top__DOT__u_ram__DOT__mem__v6 = 0x30U;
                __Vdlyvdim0__pcie_axi_top__DOT__u_ram__DOT__mem__v6 
                    = (0x1ffU & (((IData)(vlSelf->pcie_axi_top__DOT__ram_owner)
                                   ? vlSelf->pcie_axi_top__DOT__dma_ram_awaddr
                                   : vlSelf->pcie_axi_top__DOT__brg_awaddr) 
                                 >> 3U));
            }
            if ((0x80U & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_wstrb))) {
                __Vdlyvval__pcie_axi_top__DOT__u_ram__DOT__mem__v7 
                    = (0xffU & (IData)((vlSelf->pcie_axi_top__DOT__ram_real_wdata 
                                        >> 0x38U)));
                __Vdlyvset__pcie_axi_top__DOT__u_ram__DOT__mem__v7 = 1U;
                __Vdlyvlsb__pcie_axi_top__DOT__u_ram__DOT__mem__v7 = 0x38U;
                __Vdlyvdim0__pcie_axi_top__DOT__u_ram__DOT__mem__v7 
                    = (0x1ffU & (((IData)(vlSelf->pcie_axi_top__DOT__ram_owner)
                                   ? vlSelf->pcie_axi_top__DOT__dma_ram_awaddr
                                   : vlSelf->pcie_axi_top__DOT__brg_awaddr) 
                                 >> 3U));
            }
        }
        if (((IData)(vlSelf->pcie_axi_top__DOT__ram_real_bvalid) 
             & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_bready))) {
            __Vdly__pcie_axi_top__DOT__ram_real_bvalid = 0U;
            __Vdly__pcie_axi_top__DOT__ram_real_awready = 1U;
            __Vdly__pcie_axi_top__DOT__ram_real_wready = 1U;
        }
        if ((((~ (vlSelf->pcie_axi_top__DOT__brg_araddr 
                  >> 0xcU)) & (IData)(vlSelf->pcie_axi_top__DOT__brg_arvalid)) 
             & (IData)(vlSelf->pcie_axi_top__DOT__dma_arready))) {
            __Vdly__pcie_axi_top__DOT__dma_rdata = 
                ((0U == (0xffU & vlSelf->pcie_axi_top__DOT__brg_araddr))
                  ? (QData)((IData)(vlSelf->pcie_axi_top__DOT__u_dma__DOT__ctrl_reg))
                  : ((8U == (0xffU & vlSelf->pcie_axi_top__DOT__brg_araddr))
                      ? (QData)((IData)(vlSelf->pcie_axi_top__DOT__u_dma__DOT__status_reg))
                      : ((0x10U == (0xffU & vlSelf->pcie_axi_top__DOT__brg_araddr))
                          ? (QData)((IData)(vlSelf->pcie_axi_top__DOT__u_dma__DOT__host_addr_lo))
                          : ((0x18U == (0xffU & vlSelf->pcie_axi_top__DOT__brg_araddr))
                              ? (QData)((IData)(vlSelf->pcie_axi_top__DOT__u_dma__DOT__host_addr_hi))
                              : ((0x20U == (0xffU & vlSelf->pcie_axi_top__DOT__brg_araddr))
                                  ? (QData)((IData)(vlSelf->pcie_axi_top__DOT__u_dma__DOT__local_addr))
                                  : ((0x28U == (0xffU 
                                                & vlSelf->pcie_axi_top__DOT__brg_araddr))
                                      ? (QData)((IData)(vlSelf->pcie_axi_top__DOT__u_dma__DOT__length_reg))
                                      : 0xdeaddeadULL))))));
            vlSelf->pcie_axi_top__DOT__dma_arready = 0U;
            __Vdly__pcie_axi_top__DOT__dma_rvalid = 1U;
        }
        if (((IData)(vlSelf->pcie_axi_top__DOT__dma_rvalid) 
             & (IData)(vlSelf->pcie_axi_top__DOT__brg_rready))) {
            __Vdly__pcie_axi_top__DOT__dma_rvalid = 0U;
            vlSelf->pcie_axi_top__DOT__dma_arready = 1U;
        }
        vlSelf->tx_hcrdt_init_ack = vlSelf->tx_hcrdt_init;
        vlSelf->tx_dcrdt_init_ack = vlSelf->tx_dcrdt_init;
        if (((IData)(vlSelf->pcie_axi_top__DOT__u_dma__DOT__start) 
             & (~ vlSelf->pcie_axi_top__DOT__u_dma__DOT__status_reg))) {
            __Vdly__pcie_axi_top__DOT__u_dma__DOT__ctrl_reg 
                = (0xfffffffeU & __Vdly__pcie_axi_top__DOT__u_dma__DOT__ctrl_reg);
        }
        if (((((~ (vlSelf->pcie_axi_top__DOT__brg_awaddr 
                   >> 0xcU)) & (IData)(vlSelf->pcie_axi_top__DOT__brg_awvalid)) 
              & (IData)(vlSelf->pcie_axi_top__DOT__brg_wvalid)) 
             & (IData)(vlSelf->pcie_axi_top__DOT__dma_awready))) {
            if ((0U == (0xffU & vlSelf->pcie_axi_top__DOT__brg_awaddr))) {
                __Vdly__pcie_axi_top__DOT__u_dma__DOT__ctrl_reg 
                    = (IData)(vlSelf->pcie_axi_top__DOT__brg_wdata);
            } else if ((0x10U == (0xffU & vlSelf->pcie_axi_top__DOT__brg_awaddr))) {
                __Vdly__pcie_axi_top__DOT__u_dma__DOT__host_addr_lo 
                    = (IData)(vlSelf->pcie_axi_top__DOT__brg_wdata);
            } else if ((0x18U == (0xffU & vlSelf->pcie_axi_top__DOT__brg_awaddr))) {
                __Vdly__pcie_axi_top__DOT__u_dma__DOT__host_addr_hi 
                    = (IData)(vlSelf->pcie_axi_top__DOT__brg_wdata);
            } else if ((0x20U == (0xffU & vlSelf->pcie_axi_top__DOT__brg_awaddr))) {
                __Vdly__pcie_axi_top__DOT__u_dma__DOT__local_addr 
                    = (IData)(vlSelf->pcie_axi_top__DOT__brg_wdata);
            } else if ((0x28U == (0xffU & vlSelf->pcie_axi_top__DOT__brg_awaddr))) {
                __Vdly__pcie_axi_top__DOT__u_dma__DOT__length_reg 
                    = (IData)(vlSelf->pcie_axi_top__DOT__brg_wdata);
            }
            vlSelf->pcie_axi_top__DOT__dma_awready = 0U;
            vlSelf->pcie_axi_top__DOT__dma_wready = 0U;
            __Vdly__pcie_axi_top__DOT__dma_bvalid = 1U;
        }
        if (((IData)(vlSelf->pcie_axi_top__DOT__dma_bvalid) 
             & (IData)(vlSelf->pcie_axi_top__DOT__brg_bready))) {
            __Vdly__pcie_axi_top__DOT__dma_bvalid = 0U;
            vlSelf->pcie_axi_top__DOT__dma_awready = 1U;
            vlSelf->pcie_axi_top__DOT__dma_wready = 1U;
        }
        vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_cpl_hdr_dec = 0U;
        vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_cpl_data_dec = 0U;
        __Vdly__pcie_axi_top__DOT__dma_mrd_ready = 0U;
        __Vdly__pcie_axi_top__DOT__dma_mwr_ready = 0U;
        if (((((((((0U == (IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__state)) 
                   | (1U == (IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__state))) 
                  | (2U == (IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__state))) 
                 | (3U == (IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__state))) 
                | (4U == (IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__state))) 
               | (5U == (IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__state))) 
              | (6U == (IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__state))) 
             | (7U == (IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__state)))) {
            if ((0U == (IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__state))) {
                __Vdly__tx_st_hvalid = 0U;
                vlSelf->tx_st_dvalid = 0U;
                vlSelf->tx_st_sop = 0U;
                vlSelf->tx_st_eop = 0U;
                if (((IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_is_mwr) 
                     & (0U == (IData)(vlSelf->rx_st_bar)))) {
                    vlSelf->pcie_axi_top__DOT__brg_awaddr 
                        = (IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_addr);
                    __Vdly__pcie_axi_top__DOT__brg_awvalid = 1U;
                    vlSelf->pcie_axi_top__DOT__brg_wdata 
                        = (((QData)((IData)(vlSelf->rx_st_data[1U])) 
                            << 0x20U) | (QData)((IData)(
                                                        vlSelf->rx_st_data[0U])));
                    vlSelf->pcie_axi_top__DOT__brg_wstrb 
                        = (((IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_lbe) 
                            << 4U) | (IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_fbe));
                    __Vdly__pcie_axi_top__DOT__brg_wvalid = 1U;
                    __Vdly__pcie_axi_top__DOT__u_bridge__DOT__state = 1U;
                } else if (((IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_is_mrd) 
                            & (0U == (IData)(vlSelf->rx_st_bar)))) {
                    __Vdly__pcie_axi_top__DOT__u_bridge__DOT__bar_req_rid 
                        = vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_rid;
                    __Vdly__pcie_axi_top__DOT__u_bridge__DOT__bar_req_tag 
                        = vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_tag;
                    __Vdly__pcie_axi_top__DOT__u_bridge__DOT__bar_req_lower_addr 
                        = (0x7fU & (IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_addr));
                    vlSelf->pcie_axi_top__DOT__brg_araddr 
                        = (IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_addr);
                    vlSelf->pcie_axi_top__DOT__brg_arvalid = 1U;
                    __Vdly__pcie_axi_top__DOT__u_bridge__DOT__state = 3U;
                } else if (vlSelf->pcie_axi_top__DOT__dma_mrd_valid) {
                    __Vdly__pcie_axi_top__DOT__u_bridge__DOT__state = 6U;
                } else if (vlSelf->pcie_axi_top__DOT__dma_mwr_valid) {
                    __Vdly__pcie_axi_top__DOT__u_bridge__DOT__state = 7U;
                }
            } else if ((1U == (IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__state))) {
                if ((1U & (((IData)(vlSelf->pcie_axi_top__DOT__brg_awready) 
                            | (~ (IData)(vlSelf->pcie_axi_top__DOT__brg_awvalid))) 
                           & ((IData)(vlSelf->pcie_axi_top__DOT__brg_wready) 
                              | (~ (IData)(vlSelf->pcie_axi_top__DOT__brg_wvalid)))))) {
                    vlSelf->pcie_axi_top__DOT__brg_bready = 1U;
                    __Vdly__pcie_axi_top__DOT__u_bridge__DOT__state = 2U;
                }
                if (vlSelf->pcie_axi_top__DOT__brg_awready) {
                    __Vdly__pcie_axi_top__DOT__brg_awvalid = 0U;
                }
                if (vlSelf->pcie_axi_top__DOT__brg_wready) {
                    __Vdly__pcie_axi_top__DOT__brg_wvalid = 0U;
                }
            } else if ((2U == (IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__state))) {
                if (((IData)(vlSelf->pcie_axi_top__DOT__dma_bvalid) 
                     | ((~ (IData)(vlSelf->pcie_axi_top__DOT__ram_owner)) 
                        & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_bvalid)))) {
                    vlSelf->pcie_axi_top__DOT__brg_bready = 0U;
                    __Vdly__pcie_axi_top__DOT__u_bridge__DOT__state = 0U;
                }
            } else if ((3U == (IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__state))) {
                if (vlSelf->pcie_axi_top__DOT__brg_arready) {
                    vlSelf->pcie_axi_top__DOT__brg_arvalid = 0U;
                    vlSelf->pcie_axi_top__DOT__brg_rready = 1U;
                    __Vdly__pcie_axi_top__DOT__u_bridge__DOT__state = 4U;
                }
            } else if ((4U == (IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__state))) {
                if (((IData)(vlSelf->pcie_axi_top__DOT__dma_rvalid) 
                     | ((~ (IData)(vlSelf->pcie_axi_top__DOT__ram_owner)) 
                        & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_rvalid)))) {
                    vlSelf->pcie_axi_top__DOT__brg_rready = 0U;
                    if (vlSelf->pcie_axi_top__DOT__dma_rvalid) {
                        __Vdly__pcie_axi_top__DOT__u_bridge__DOT__bar_cpl_data 
                            = vlSelf->pcie_axi_top__DOT__dma_rdata;
                        __Vdly__pcie_axi_top__DOT__u_bridge__DOT__bar_cpl_status 
                            = vlSelf->pcie_axi_top__DOT__dma_rresp;
                    } else {
                        __Vdly__pcie_axi_top__DOT__u_bridge__DOT__bar_cpl_data 
                            = vlSelf->pcie_axi_top__DOT__ram_real_rdata;
                        __Vdly__pcie_axi_top__DOT__u_bridge__DOT__bar_cpl_status 
                            = vlSelf->pcie_axi_top__DOT__ram_real_rresp;
                    }
                    __Vdly__pcie_axi_top__DOT__u_bridge__DOT__state = 5U;
                }
            } else if ((5U == (IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__state))) {
                if (((IData)(vlSelf->tx_st_ready) & 
                     (~ (IData)(vlSelf->tx_st_hvalid)))) {
                    vlSelf->tx_st_sop = 1U;
                    vlSelf->tx_st_eop = 1U;
                    __Vdly__tx_st_hvalid = 1U;
                    vlSelf->tx_st_dvalid = 1U;
                    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_cpl_hdr_dec = 1U;
                    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_cpl_data_dec = 1U;
                    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_hdr_r[0U] = 0U;
                    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_hdr_r[1U] 
                        = (((IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__bar_req_rid) 
                            << 0x10U) | (((IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__bar_req_tag) 
                                          << 8U) | (IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__bar_req_lower_addr)));
                    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_hdr_r[2U] 
                        = (IData)((0x4a00000200000000ULL 
                                   | (QData)((IData)(
                                                     (0x1000008U 
                                                      | (((0U 
                                                           == (IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__bar_cpl_status))
                                                           ? 0U
                                                           : 1U) 
                                                         << 0xdU))))));
                    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_hdr_r[3U] 
                        = (IData)(((0x4a00000200000000ULL 
                                    | (QData)((IData)(
                                                      (0x1000008U 
                                                       | (((0U 
                                                            == (IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__bar_cpl_status))
                                                            ? 0U
                                                            : 1U) 
                                                          << 0xdU))))) 
                                   >> 0x20U));
                    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_data_r 
                        = vlSelf->pcie_axi_top__DOT__u_bridge__DOT__bar_cpl_data;
                    __Vdly__pcie_axi_top__DOT__u_bridge__DOT__state = 0U;
                }
            } else if ((6U == (IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__state))) {
                if (((IData)(vlSelf->tx_st_ready) & 
                     (~ (IData)(vlSelf->tx_st_hvalid)))) {
                    vlSelf->tx_st_sop = 1U;
                    vlSelf->tx_st_eop = 1U;
                    __Vdly__tx_st_hvalid = 1U;
                    vlSelf->tx_st_dvalid = 0U;
                    __Vdly__pcie_axi_top__DOT__dma_mrd_ready = 1U;
                    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_hdr_r[0U] 
                        = ((IData)((vlSelf->pcie_axi_top__DOT__dma_mrd_addr 
                                    >> 2U)) << 2U);
                    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_hdr_r[1U] 
                        = (IData)((vlSelf->pcie_axi_top__DOT__dma_mrd_addr 
                                   >> 0x20U));
                    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_hdr_r[2U] 
                        = (IData)((((QData)((IData)(
                                                    (0x20000000U 
                                                     | (IData)(vlSelf->pcie_axi_top__DOT__dma_mrd_len)))) 
                                    << 0x20U) | (QData)((IData)(
                                                                (0x10000ffU 
                                                                 | ((IData)(vlSelf->pcie_axi_top__DOT__dma_mrd_tag) 
                                                                    << 8U))))));
                    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_hdr_r[3U] 
                        = (IData)(((((QData)((IData)(
                                                     (0x20000000U 
                                                      | (IData)(vlSelf->pcie_axi_top__DOT__dma_mrd_len)))) 
                                     << 0x20U) | (QData)((IData)(
                                                                 (0x10000ffU 
                                                                  | ((IData)(vlSelf->pcie_axi_top__DOT__dma_mrd_tag) 
                                                                     << 8U))))) 
                                   >> 0x20U));
                    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_data_r = 0ULL;
                    __Vdly__pcie_axi_top__DOT__u_bridge__DOT__state = 0U;
                }
            } else if (((IData)(vlSelf->tx_st_ready) 
                        & (~ (IData)(vlSelf->tx_st_hvalid)))) {
                vlSelf->tx_st_sop = 1U;
                vlSelf->tx_st_eop = 1U;
                __Vdly__tx_st_hvalid = 1U;
                vlSelf->tx_st_dvalid = 1U;
                __Vdly__pcie_axi_top__DOT__dma_mwr_ready = 1U;
                vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_hdr_r[0U] 
                    = ((IData)((vlSelf->pcie_axi_top__DOT__dma_mwr_addr 
                                >> 2U)) << 2U);
                vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_hdr_r[1U] 
                    = (IData)((vlSelf->pcie_axi_top__DOT__dma_mwr_addr 
                               >> 0x20U));
                vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_hdr_r[2U] 
                    = (IData)((0x10000ffULL | ((QData)((IData)(
                                                               (0x60000000U 
                                                                | (IData)(vlSelf->pcie_axi_top__DOT__dma_mwr_len)))) 
                                               << 0x20U)));
                vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_hdr_r[3U] 
                    = (IData)(((0x10000ffULL | ((QData)((IData)(
                                                                (0x60000000U 
                                                                 | (IData)(vlSelf->pcie_axi_top__DOT__dma_mwr_len)))) 
                                                << 0x20U)) 
                               >> 0x20U));
                vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_data_r 
                    = vlSelf->pcie_axi_top__DOT__dma_mwr_data;
                __Vdly__pcie_axi_top__DOT__u_bridge__DOT__state = 0U;
            }
        }
        vlSelf->dma_irq = 0U;
        if (((((((((0U == (IData)(vlSelf->pcie_axi_top__DOT__u_dma__DOT__dma_state)) 
                   | (1U == (IData)(vlSelf->pcie_axi_top__DOT__u_dma__DOT__dma_state))) 
                  | (2U == (IData)(vlSelf->pcie_axi_top__DOT__u_dma__DOT__dma_state))) 
                 | (3U == (IData)(vlSelf->pcie_axi_top__DOT__u_dma__DOT__dma_state))) 
                | (4U == (IData)(vlSelf->pcie_axi_top__DOT__u_dma__DOT__dma_state))) 
               | (5U == (IData)(vlSelf->pcie_axi_top__DOT__u_dma__DOT__dma_state))) 
              | (6U == (IData)(vlSelf->pcie_axi_top__DOT__u_dma__DOT__dma_state))) 
             | (7U == (IData)(vlSelf->pcie_axi_top__DOT__u_dma__DOT__dma_state)))) {
            if ((0U == (IData)(vlSelf->pcie_axi_top__DOT__u_dma__DOT__dma_state))) {
                vlSelf->pcie_axi_top__DOT__u_dma__DOT__status_reg 
                    = (0xfffffffeU & vlSelf->pcie_axi_top__DOT__u_dma__DOT__status_reg);
                if ((vlSelf->pcie_axi_top__DOT__u_dma__DOT__ctrl_reg 
                     & (0U < vlSelf->pcie_axi_top__DOT__u_dma__DOT__length_reg))) {
                    vlSelf->pcie_axi_top__DOT__u_dma__DOT__status_reg = 1U;
                    __Vdly__pcie_axi_top__DOT__u_dma__DOT__bytes_remaining 
                        = vlSelf->pcie_axi_top__DOT__u_dma__DOT__length_reg;
                    __Vdly__pcie_axi_top__DOT__u_dma__DOT__cur_host_addr 
                        = (((QData)((IData)(vlSelf->pcie_axi_top__DOT__u_dma__DOT__host_addr_hi)) 
                            << 0x20U) | (QData)((IData)(vlSelf->pcie_axi_top__DOT__u_dma__DOT__host_addr_lo)));
                    __Vdly__pcie_axi_top__DOT__u_dma__DOT__cur_local_addr 
                        = vlSelf->pcie_axi_top__DOT__u_dma__DOT__local_addr;
                    __Vdly__pcie_axi_top__DOT__u_dma__DOT__cur_tag = 0xa0U;
                    __Vdly__pcie_axi_top__DOT__u_dma__DOT__dma_state 
                        = ((2U & vlSelf->pcie_axi_top__DOT__u_dma__DOT__ctrl_reg)
                            ? 5U : 1U);
                }
            } else if ((1U == (IData)(vlSelf->pcie_axi_top__DOT__u_dma__DOT__dma_state))) {
                vlSelf->pcie_axi_top__DOT__dma_mrd_valid = 1U;
                vlSelf->pcie_axi_top__DOT__dma_mrd_addr 
                    = vlSelf->pcie_axi_top__DOT__u_dma__DOT__cur_host_addr;
                vlSelf->pcie_axi_top__DOT__dma_mrd_len = 2U;
                vlSelf->pcie_axi_top__DOT__dma_mrd_tag 
                    = vlSelf->pcie_axi_top__DOT__u_dma__DOT__cur_tag;
                if (vlSelf->pcie_axi_top__DOT__dma_mrd_ready) {
                    vlSelf->pcie_axi_top__DOT__dma_mrd_valid = 0U;
                    __Vdly__pcie_axi_top__DOT__u_dma__DOT__dma_state = 2U;
                }
            } else if ((2U == (IData)(vlSelf->pcie_axi_top__DOT__u_dma__DOT__dma_state))) {
                if (((IData)(vlSelf->pcie_axi_top__DOT__dma_cpl_valid) 
                     & ((IData)(vlSelf->pcie_axi_top__DOT__dma_cpl_tag) 
                        == (IData)(vlSelf->pcie_axi_top__DOT__u_dma__DOT__cur_tag)))) {
                    __Vdly__pcie_axi_top__DOT__u_dma__DOT__dma_data_buf 
                        = vlSelf->pcie_axi_top__DOT__dma_cpl_data;
                    __Vdly__pcie_axi_top__DOT__u_dma__DOT__dma_state = 3U;
                }
            } else if ((3U == (IData)(vlSelf->pcie_axi_top__DOT__u_dma__DOT__dma_state))) {
                vlSelf->pcie_axi_top__DOT__dma_ram_awaddr 
                    = vlSelf->pcie_axi_top__DOT__u_dma__DOT__cur_local_addr;
                vlSelf->pcie_axi_top__DOT__dma_ram_awvalid = 1U;
                vlSelf->pcie_axi_top__DOT__dma_ram_wdata 
                    = vlSelf->pcie_axi_top__DOT__u_dma__DOT__dma_data_buf;
                vlSelf->pcie_axi_top__DOT__dma_ram_wstrb = 0xffU;
                vlSelf->pcie_axi_top__DOT__dma_ram_wvalid = 1U;
                vlSelf->pcie_axi_top__DOT__dma_ram_bready = 1U;
                __Vdly__pcie_axi_top__DOT__u_dma__DOT__dma_state = 4U;
            } else if ((4U == (IData)(vlSelf->pcie_axi_top__DOT__u_dma__DOT__dma_state))) {
                if (((IData)(vlSelf->pcie_axi_top__DOT__ram_owner) 
                     & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_awready))) {
                    vlSelf->pcie_axi_top__DOT__dma_ram_awvalid = 0U;
                }
                if (((IData)(vlSelf->pcie_axi_top__DOT__ram_owner) 
                     & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_wready))) {
                    vlSelf->pcie_axi_top__DOT__dma_ram_wvalid = 0U;
                }
                if (((IData)(vlSelf->pcie_axi_top__DOT__ram_owner) 
                     & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_bvalid))) {
                    __Vdly__pcie_axi_top__DOT__u_dma__DOT__cur_host_addr 
                        = (8ULL + vlSelf->pcie_axi_top__DOT__u_dma__DOT__cur_host_addr);
                    __Vdly__pcie_axi_top__DOT__u_dma__DOT__cur_local_addr 
                        = ((IData)(8U) + vlSelf->pcie_axi_top__DOT__u_dma__DOT__cur_local_addr);
                    __Vdly__pcie_axi_top__DOT__u_dma__DOT__cur_tag 
                        = (0xffU & ((IData)(1U) + (IData)(vlSelf->pcie_axi_top__DOT__u_dma__DOT__cur_tag)));
                    vlSelf->pcie_axi_top__DOT__dma_ram_bready = 0U;
                    if ((8U >= vlSelf->pcie_axi_top__DOT__u_dma__DOT__bytes_remaining)) {
                        __Vdly__pcie_axi_top__DOT__u_dma__DOT__bytes_remaining = 0U;
                        __Vdly__pcie_axi_top__DOT__u_dma__DOT__dma_state = 9U;
                    } else {
                        __Vdly__pcie_axi_top__DOT__u_dma__DOT__bytes_remaining 
                            = (vlSelf->pcie_axi_top__DOT__u_dma__DOT__bytes_remaining 
                               - (IData)(8U));
                        __Vdly__pcie_axi_top__DOT__u_dma__DOT__dma_state = 1U;
                    }
                }
            } else if ((5U == (IData)(vlSelf->pcie_axi_top__DOT__u_dma__DOT__dma_state))) {
                vlSelf->pcie_axi_top__DOT__dma_ram_araddr 
                    = vlSelf->pcie_axi_top__DOT__u_dma__DOT__cur_local_addr;
                vlSelf->pcie_axi_top__DOT__dma_ram_arvalid = 1U;
                vlSelf->pcie_axi_top__DOT__dma_ram_rready = 1U;
                __Vdly__pcie_axi_top__DOT__u_dma__DOT__dma_state = 6U;
            } else if ((6U == (IData)(vlSelf->pcie_axi_top__DOT__u_dma__DOT__dma_state))) {
                if (((IData)(vlSelf->pcie_axi_top__DOT__ram_owner) 
                     & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_arready))) {
                    vlSelf->pcie_axi_top__DOT__dma_ram_arvalid = 0U;
                }
                if (((IData)(vlSelf->pcie_axi_top__DOT__ram_owner) 
                     & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_rvalid))) {
                    vlSelf->pcie_axi_top__DOT__dma_ram_rready = 0U;
                    __Vdly__pcie_axi_top__DOT__u_dma__DOT__dma_data_buf 
                        = vlSelf->pcie_axi_top__DOT__ram_real_rdata;
                    __Vdly__pcie_axi_top__DOT__u_dma__DOT__dma_state = 7U;
                }
            } else {
                vlSelf->pcie_axi_top__DOT__dma_mwr_valid = 1U;
                vlSelf->pcie_axi_top__DOT__dma_mwr_addr 
                    = vlSelf->pcie_axi_top__DOT__u_dma__DOT__cur_host_addr;
                vlSelf->pcie_axi_top__DOT__dma_mwr_data 
                    = vlSelf->pcie_axi_top__DOT__u_dma__DOT__dma_data_buf;
                vlSelf->pcie_axi_top__DOT__dma_mwr_len = 2U;
                __Vdly__pcie_axi_top__DOT__u_dma__DOT__dma_state = 8U;
            }
        } else if ((8U == (IData)(vlSelf->pcie_axi_top__DOT__u_dma__DOT__dma_state))) {
            if (vlSelf->pcie_axi_top__DOT__dma_mwr_ready) {
                __Vdly__pcie_axi_top__DOT__u_dma__DOT__cur_host_addr 
                    = (8ULL + vlSelf->pcie_axi_top__DOT__u_dma__DOT__cur_host_addr);
                __Vdly__pcie_axi_top__DOT__u_dma__DOT__cur_local_addr 
                    = ((IData)(8U) + vlSelf->pcie_axi_top__DOT__u_dma__DOT__cur_local_addr);
                vlSelf->pcie_axi_top__DOT__dma_mwr_valid = 0U;
                if ((8U >= vlSelf->pcie_axi_top__DOT__u_dma__DOT__bytes_remaining)) {
                    __Vdly__pcie_axi_top__DOT__u_dma__DOT__bytes_remaining = 0U;
                    __Vdly__pcie_axi_top__DOT__u_dma__DOT__dma_state = 9U;
                } else {
                    __Vdly__pcie_axi_top__DOT__u_dma__DOT__bytes_remaining 
                        = (vlSelf->pcie_axi_top__DOT__u_dma__DOT__bytes_remaining 
                           - (IData)(8U));
                    __Vdly__pcie_axi_top__DOT__u_dma__DOT__dma_state = 5U;
                }
            }
        } else if ((9U == (IData)(vlSelf->pcie_axi_top__DOT__u_dma__DOT__dma_state))) {
            vlSelf->pcie_axi_top__DOT__u_dma__DOT__status_reg = 2U;
            if ((4U & vlSelf->pcie_axi_top__DOT__u_dma__DOT__ctrl_reg)) {
                vlSelf->dma_irq = 1U;
            }
            __Vdly__pcie_axi_top__DOT__u_dma__DOT__dma_state = 0U;
        }
        vlSelf->pcie_axi_top__DOT__dma_cpl_valid = 0U;
        if (vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_is_cpld) {
            vlSelf->pcie_axi_top__DOT__dma_cpl_valid = 1U;
            vlSelf->pcie_axi_top__DOT__dma_cpl_tag 
                = (0xffU & (vlSelf->rx_st_hdr[1U] >> 8U));
            vlSelf->pcie_axi_top__DOT__dma_cpl_data 
                = (((QData)((IData)(vlSelf->rx_st_data[1U])) 
                    << 0x20U) | (QData)((IData)(vlSelf->rx_st_data[0U])));
        }
    } else {
        vlSelf->pcie_axi_top__DOT__ram_busy = 0U;
        __Vdly__pcie_axi_top__DOT__ram_owner = 0U;
        __Vdly__pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__tx_cpl_data_cnt = 0U;
        __Vdly__pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__tx_cpl_hdr_cnt = 0U;
        __Vdly__pcie_axi_top__DOT__ram_real_rvalid = 0U;
        __Vdly__pcie_axi_top__DOT__u_ram__DOT__read_pending = 0U;
        __Vdly__pcie_axi_top__DOT__ram_real_arready = 1U;
        __Vdly__pcie_axi_top__DOT__ram_real_rdata = 0ULL;
        __Vdly__pcie_axi_top__DOT__u_ram__DOT__rd_addr_latched = 0U;
        __Vdly__pcie_axi_top__DOT__ram_real_bvalid = 0U;
        __Vdly__pcie_axi_top__DOT__ram_real_awready = 1U;
        __Vdly__pcie_axi_top__DOT__ram_real_wready = 1U;
        __Vdly__pcie_axi_top__DOT__dma_rvalid = 0U;
        vlSelf->pcie_axi_top__DOT__dma_arready = 1U;
        __Vdly__pcie_axi_top__DOT__dma_rdata = 0ULL;
        vlSelf->tx_hcrdt_init_ack = 0U;
        vlSelf->tx_dcrdt_init_ack = 0U;
        __Vdly__pcie_axi_top__DOT__dma_bvalid = 0U;
        __Vdly__pcie_axi_top__DOT__u_dma__DOT__ctrl_reg = 0U;
        __Vdly__pcie_axi_top__DOT__u_dma__DOT__host_addr_lo = 0U;
        __Vdly__pcie_axi_top__DOT__u_dma__DOT__host_addr_hi = 0U;
        __Vdly__pcie_axi_top__DOT__u_dma__DOT__local_addr = 0U;
        __Vdly__pcie_axi_top__DOT__u_dma__DOT__length_reg = 0U;
        vlSelf->pcie_axi_top__DOT__dma_awready = 1U;
        vlSelf->pcie_axi_top__DOT__dma_wready = 1U;
        __Vdly__pcie_axi_top__DOT__u_bridge__DOT__state = 0U;
        __Vdly__pcie_axi_top__DOT__brg_awvalid = 0U;
        __Vdly__pcie_axi_top__DOT__brg_wvalid = 0U;
        vlSelf->pcie_axi_top__DOT__brg_bready = 0U;
        vlSelf->pcie_axi_top__DOT__brg_arvalid = 0U;
        vlSelf->pcie_axi_top__DOT__brg_rready = 0U;
        __Vdly__tx_st_hvalid = 0U;
        vlSelf->tx_st_dvalid = 0U;
        vlSelf->tx_st_sop = 0U;
        vlSelf->tx_st_eop = 0U;
        vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_cpl_hdr_dec = 0U;
        vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_cpl_data_dec = 0U;
        __Vdly__pcie_axi_top__DOT__dma_mrd_ready = 0U;
        __Vdly__pcie_axi_top__DOT__dma_mwr_ready = 0U;
        __Vdly__pcie_axi_top__DOT__u_dma__DOT__dma_state = 0U;
        vlSelf->pcie_axi_top__DOT__u_dma__DOT__status_reg = 0U;
        __Vdly__pcie_axi_top__DOT__u_dma__DOT__bytes_remaining = 0U;
        __Vdly__pcie_axi_top__DOT__u_dma__DOT__cur_host_addr = 0ULL;
        __Vdly__pcie_axi_top__DOT__u_dma__DOT__cur_local_addr = 0U;
        __Vdly__pcie_axi_top__DOT__u_dma__DOT__cur_tag = 0U;
        __Vdly__pcie_axi_top__DOT__u_dma__DOT__dma_data_buf = 0ULL;
        vlSelf->pcie_axi_top__DOT__dma_mrd_valid = 0U;
        vlSelf->pcie_axi_top__DOT__dma_mwr_valid = 0U;
        vlSelf->pcie_axi_top__DOT__dma_ram_arvalid = 0U;
        vlSelf->pcie_axi_top__DOT__dma_ram_awvalid = 0U;
        vlSelf->pcie_axi_top__DOT__dma_ram_wvalid = 0U;
        vlSelf->pcie_axi_top__DOT__dma_ram_rready = 0U;
        vlSelf->pcie_axi_top__DOT__dma_ram_bready = 0U;
        vlSelf->dma_irq = 0U;
        vlSelf->pcie_axi_top__DOT__dma_cpl_valid = 0U;
        vlSelf->pcie_axi_top__DOT__dma_cpl_tag = 0U;
        vlSelf->pcie_axi_top__DOT__dma_cpl_data = 0ULL;
    }
    if ((1U & (~ (IData)(vlSelf->rst_n)))) {
        vlSelf->pcie_axi_top__DOT__ram_real_bresp = 0U;
        vlSelf->pcie_axi_top__DOT__dma_bresp = 0U;
        vlSelf->pcie_axi_top__DOT__dma_rresp = 0U;
        vlSelf->pcie_axi_top__DOT__ram_real_rresp = 0U;
    }
    __Vtableidx1 = (((IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__cnt) 
                     << 3U) | (((IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__state) 
                                << 1U) | (IData)(vlSelf->rst_n)));
    vlSelf->rx_hcrdt_update = Vpcie_axi_top__ConstPool__TABLE_hf3a84768_0
        [__Vtableidx1];
    vlSelf->rx_dcrdt_update = Vpcie_axi_top__ConstPool__TABLE_hf3a84768_0
        [__Vtableidx1];
    if ((4U & Vpcie_axi_top__ConstPool__TABLE_h92b69fc4_0
         [__Vtableidx1])) {
        vlSelf->rx_hcrdt_init = Vpcie_axi_top__ConstPool__TABLE_h3a3a7adf_0
            [__Vtableidx1];
    }
    if ((8U & Vpcie_axi_top__ConstPool__TABLE_h92b69fc4_0
         [__Vtableidx1])) {
        vlSelf->rx_dcrdt_init = Vpcie_axi_top__ConstPool__TABLE_h3a3a7adf_0
            [__Vtableidx1];
    }
    if ((0x10U & Vpcie_axi_top__ConstPool__TABLE_h92b69fc4_0
         [__Vtableidx1])) {
        vlSelf->pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__cnt 
            = Vpcie_axi_top__ConstPool__TABLE_h1588c7a3_0
            [__Vtableidx1];
    }
    if ((0x20U & Vpcie_axi_top__ConstPool__TABLE_h92b69fc4_0
         [__Vtableidx1])) {
        vlSelf->pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__state 
            = Vpcie_axi_top__ConstPool__TABLE_h643f69a8_0
            [__Vtableidx1];
    }
    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__tx_cpl_data_cnt 
        = __Vdly__pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__tx_cpl_data_cnt;
    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__tx_cpl_hdr_cnt 
        = __Vdly__pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__tx_cpl_hdr_cnt;
    vlSelf->pcie_axi_top__DOT__u_ram__DOT__rd_addr_latched 
        = __Vdly__pcie_axi_top__DOT__u_ram__DOT__rd_addr_latched;
    vlSelf->pcie_axi_top__DOT__u_ram__DOT__read_pending 
        = __Vdly__pcie_axi_top__DOT__u_ram__DOT__read_pending;
    if (__Vdlyvset__pcie_axi_top__DOT__u_ram__DOT__mem__v0) {
        vlSelf->pcie_axi_top__DOT__u_ram__DOT__mem[__Vdlyvdim0__pcie_axi_top__DOT__u_ram__DOT__mem__v0] 
            = (((~ (0xffULL << (IData)(__Vdlyvlsb__pcie_axi_top__DOT__u_ram__DOT__mem__v0))) 
                & vlSelf->pcie_axi_top__DOT__u_ram__DOT__mem
                [__Vdlyvdim0__pcie_axi_top__DOT__u_ram__DOT__mem__v0]) 
               | ((QData)((IData)(__Vdlyvval__pcie_axi_top__DOT__u_ram__DOT__mem__v0)) 
                  << (IData)(__Vdlyvlsb__pcie_axi_top__DOT__u_ram__DOT__mem__v0)));
    }
    if (__Vdlyvset__pcie_axi_top__DOT__u_ram__DOT__mem__v1) {
        vlSelf->pcie_axi_top__DOT__u_ram__DOT__mem[__Vdlyvdim0__pcie_axi_top__DOT__u_ram__DOT__mem__v1] 
            = (((~ (0xffULL << (IData)(__Vdlyvlsb__pcie_axi_top__DOT__u_ram__DOT__mem__v1))) 
                & vlSelf->pcie_axi_top__DOT__u_ram__DOT__mem
                [__Vdlyvdim0__pcie_axi_top__DOT__u_ram__DOT__mem__v1]) 
               | ((QData)((IData)(__Vdlyvval__pcie_axi_top__DOT__u_ram__DOT__mem__v1)) 
                  << (IData)(__Vdlyvlsb__pcie_axi_top__DOT__u_ram__DOT__mem__v1)));
    }
    if (__Vdlyvset__pcie_axi_top__DOT__u_ram__DOT__mem__v2) {
        vlSelf->pcie_axi_top__DOT__u_ram__DOT__mem[__Vdlyvdim0__pcie_axi_top__DOT__u_ram__DOT__mem__v2] 
            = (((~ (0xffULL << (IData)(__Vdlyvlsb__pcie_axi_top__DOT__u_ram__DOT__mem__v2))) 
                & vlSelf->pcie_axi_top__DOT__u_ram__DOT__mem
                [__Vdlyvdim0__pcie_axi_top__DOT__u_ram__DOT__mem__v2]) 
               | ((QData)((IData)(__Vdlyvval__pcie_axi_top__DOT__u_ram__DOT__mem__v2)) 
                  << (IData)(__Vdlyvlsb__pcie_axi_top__DOT__u_ram__DOT__mem__v2)));
    }
    if (__Vdlyvset__pcie_axi_top__DOT__u_ram__DOT__mem__v3) {
        vlSelf->pcie_axi_top__DOT__u_ram__DOT__mem[__Vdlyvdim0__pcie_axi_top__DOT__u_ram__DOT__mem__v3] 
            = (((~ (0xffULL << (IData)(__Vdlyvlsb__pcie_axi_top__DOT__u_ram__DOT__mem__v3))) 
                & vlSelf->pcie_axi_top__DOT__u_ram__DOT__mem
                [__Vdlyvdim0__pcie_axi_top__DOT__u_ram__DOT__mem__v3]) 
               | ((QData)((IData)(__Vdlyvval__pcie_axi_top__DOT__u_ram__DOT__mem__v3)) 
                  << (IData)(__Vdlyvlsb__pcie_axi_top__DOT__u_ram__DOT__mem__v3)));
    }
    if (__Vdlyvset__pcie_axi_top__DOT__u_ram__DOT__mem__v4) {
        vlSelf->pcie_axi_top__DOT__u_ram__DOT__mem[__Vdlyvdim0__pcie_axi_top__DOT__u_ram__DOT__mem__v4] 
            = (((~ (0xffULL << (IData)(__Vdlyvlsb__pcie_axi_top__DOT__u_ram__DOT__mem__v4))) 
                & vlSelf->pcie_axi_top__DOT__u_ram__DOT__mem
                [__Vdlyvdim0__pcie_axi_top__DOT__u_ram__DOT__mem__v4]) 
               | ((QData)((IData)(__Vdlyvval__pcie_axi_top__DOT__u_ram__DOT__mem__v4)) 
                  << (IData)(__Vdlyvlsb__pcie_axi_top__DOT__u_ram__DOT__mem__v4)));
    }
    if (__Vdlyvset__pcie_axi_top__DOT__u_ram__DOT__mem__v5) {
        vlSelf->pcie_axi_top__DOT__u_ram__DOT__mem[__Vdlyvdim0__pcie_axi_top__DOT__u_ram__DOT__mem__v5] 
            = (((~ (0xffULL << (IData)(__Vdlyvlsb__pcie_axi_top__DOT__u_ram__DOT__mem__v5))) 
                & vlSelf->pcie_axi_top__DOT__u_ram__DOT__mem
                [__Vdlyvdim0__pcie_axi_top__DOT__u_ram__DOT__mem__v5]) 
               | ((QData)((IData)(__Vdlyvval__pcie_axi_top__DOT__u_ram__DOT__mem__v5)) 
                  << (IData)(__Vdlyvlsb__pcie_axi_top__DOT__u_ram__DOT__mem__v5)));
    }
    if (__Vdlyvset__pcie_axi_top__DOT__u_ram__DOT__mem__v6) {
        vlSelf->pcie_axi_top__DOT__u_ram__DOT__mem[__Vdlyvdim0__pcie_axi_top__DOT__u_ram__DOT__mem__v6] 
            = (((~ (0xffULL << (IData)(__Vdlyvlsb__pcie_axi_top__DOT__u_ram__DOT__mem__v6))) 
                & vlSelf->pcie_axi_top__DOT__u_ram__DOT__mem
                [__Vdlyvdim0__pcie_axi_top__DOT__u_ram__DOT__mem__v6]) 
               | ((QData)((IData)(__Vdlyvval__pcie_axi_top__DOT__u_ram__DOT__mem__v6)) 
                  << (IData)(__Vdlyvlsb__pcie_axi_top__DOT__u_ram__DOT__mem__v6)));
    }
    if (__Vdlyvset__pcie_axi_top__DOT__u_ram__DOT__mem__v7) {
        vlSelf->pcie_axi_top__DOT__u_ram__DOT__mem[__Vdlyvdim0__pcie_axi_top__DOT__u_ram__DOT__mem__v7] 
            = (((~ (0xffULL << (IData)(__Vdlyvlsb__pcie_axi_top__DOT__u_ram__DOT__mem__v7))) 
                & vlSelf->pcie_axi_top__DOT__u_ram__DOT__mem
                [__Vdlyvdim0__pcie_axi_top__DOT__u_ram__DOT__mem__v7]) 
               | ((QData)((IData)(__Vdlyvval__pcie_axi_top__DOT__u_ram__DOT__mem__v7)) 
                  << (IData)(__Vdlyvlsb__pcie_axi_top__DOT__u_ram__DOT__mem__v7)));
    }
    vlSelf->rx_dcrdt_update_cnt = ((3U == (IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__state))
                                    ? 0U : 0xfffU);
    vlSelf->pcie_axi_top__DOT__dma_rdata = __Vdly__pcie_axi_top__DOT__dma_rdata;
    vlSelf->tx_st_hvalid = __Vdly__tx_st_hvalid;
    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__state 
        = __Vdly__pcie_axi_top__DOT__u_bridge__DOT__state;
    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__bar_req_rid 
        = __Vdly__pcie_axi_top__DOT__u_bridge__DOT__bar_req_rid;
    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__bar_req_tag 
        = __Vdly__pcie_axi_top__DOT__u_bridge__DOT__bar_req_tag;
    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__bar_req_lower_addr 
        = __Vdly__pcie_axi_top__DOT__u_bridge__DOT__bar_req_lower_addr;
    vlSelf->pcie_axi_top__DOT__dma_bvalid = __Vdly__pcie_axi_top__DOT__dma_bvalid;
    vlSelf->pcie_axi_top__DOT__dma_rvalid = __Vdly__pcie_axi_top__DOT__dma_rvalid;
    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__bar_cpl_data 
        = __Vdly__pcie_axi_top__DOT__u_bridge__DOT__bar_cpl_data;
    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__bar_cpl_status 
        = __Vdly__pcie_axi_top__DOT__u_bridge__DOT__bar_cpl_status;
    vlSelf->pcie_axi_top__DOT__brg_wvalid = __Vdly__pcie_axi_top__DOT__brg_wvalid;
    vlSelf->pcie_axi_top__DOT__brg_awvalid = __Vdly__pcie_axi_top__DOT__brg_awvalid;
    vlSelf->tx_st_hdr[0U] = vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_hdr_r[0U];
    vlSelf->tx_st_hdr[1U] = vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_hdr_r[1U];
    vlSelf->tx_st_hdr[2U] = vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_hdr_r[2U];
    vlSelf->tx_st_hdr[3U] = vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_hdr_r[3U];
    vlSelf->tx_st_data[0U] = (IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_data_r);
    vlSelf->tx_st_data[1U] = (IData)((vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_data_r 
                                      >> 0x20U));
    vlSelf->tx_st_data[2U] = 0U;
    vlSelf->tx_st_data[3U] = 0U;
    vlSelf->tx_st_data[4U] = 0U;
    vlSelf->tx_st_data[5U] = 0U;
    vlSelf->tx_st_data[6U] = 0U;
    vlSelf->tx_st_data[7U] = 0U;
    vlSelf->pcie_axi_top__DOT__ram_arvalid = ((IData)(vlSelf->pcie_axi_top__DOT__brg_arvalid) 
                                              & (vlSelf->pcie_axi_top__DOT__brg_araddr 
                                                 >> 0xcU));
    vlSelf->pcie_axi_top__DOT__ram_awvalid = ((IData)(vlSelf->pcie_axi_top__DOT__brg_awvalid) 
                                              & (vlSelf->pcie_axi_top__DOT__brg_awaddr 
                                                 >> 0xcU));
    vlSelf->pcie_axi_top__DOT__dma_mrd_ready = __Vdly__pcie_axi_top__DOT__dma_mrd_ready;
    vlSelf->pcie_axi_top__DOT__dma_mwr_ready = __Vdly__pcie_axi_top__DOT__dma_mwr_ready;
    vlSelf->pcie_axi_top__DOT__u_dma__DOT__length_reg 
        = __Vdly__pcie_axi_top__DOT__u_dma__DOT__length_reg;
    vlSelf->pcie_axi_top__DOT__u_dma__DOT__bytes_remaining 
        = __Vdly__pcie_axi_top__DOT__u_dma__DOT__bytes_remaining;
    vlSelf->pcie_axi_top__DOT__u_dma__DOT__host_addr_hi 
        = __Vdly__pcie_axi_top__DOT__u_dma__DOT__host_addr_hi;
    vlSelf->pcie_axi_top__DOT__u_dma__DOT__host_addr_lo 
        = __Vdly__pcie_axi_top__DOT__u_dma__DOT__host_addr_lo;
    vlSelf->pcie_axi_top__DOT__u_dma__DOT__cur_host_addr 
        = __Vdly__pcie_axi_top__DOT__u_dma__DOT__cur_host_addr;
    vlSelf->pcie_axi_top__DOT__u_dma__DOT__local_addr 
        = __Vdly__pcie_axi_top__DOT__u_dma__DOT__local_addr;
    vlSelf->pcie_axi_top__DOT__u_dma__DOT__cur_local_addr 
        = __Vdly__pcie_axi_top__DOT__u_dma__DOT__cur_local_addr;
    vlSelf->pcie_axi_top__DOT__u_dma__DOT__cur_tag 
        = __Vdly__pcie_axi_top__DOT__u_dma__DOT__cur_tag;
    vlSelf->pcie_axi_top__DOT__u_dma__DOT__dma_state 
        = __Vdly__pcie_axi_top__DOT__u_dma__DOT__dma_state;
    vlSelf->pcie_axi_top__DOT__u_dma__DOT__dma_data_buf 
        = __Vdly__pcie_axi_top__DOT__u_dma__DOT__dma_data_buf;
    vlSelf->pcie_axi_top__DOT__ram_real_rdata = __Vdly__pcie_axi_top__DOT__ram_real_rdata;
    vlSelf->pcie_axi_top__DOT__ram_real_bvalid = __Vdly__pcie_axi_top__DOT__ram_real_bvalid;
    vlSelf->pcie_axi_top__DOT__ram_real_rvalid = __Vdly__pcie_axi_top__DOT__ram_real_rvalid;
    vlSelf->pcie_axi_top__DOT__u_dma__DOT__ctrl_reg 
        = __Vdly__pcie_axi_top__DOT__u_dma__DOT__ctrl_reg;
    vlSelf->pcie_axi_top__DOT__ram_real_wready = __Vdly__pcie_axi_top__DOT__ram_real_wready;
    vlSelf->pcie_axi_top__DOT__ram_real_awready = __Vdly__pcie_axi_top__DOT__ram_real_awready;
    vlSelf->pcie_axi_top__DOT__ram_real_arready = __Vdly__pcie_axi_top__DOT__ram_real_arready;
    vlSelf->pcie_axi_top__DOT__ram_owner = __Vdly__pcie_axi_top__DOT__ram_owner;
    vlSelf->pcie_axi_top__DOT__u_dma__DOT__start = 
        (1U & vlSelf->pcie_axi_top__DOT__u_dma__DOT__ctrl_reg);
    if (vlSelf->pcie_axi_top__DOT__ram_owner) {
        vlSelf->pcie_axi_top__DOT__ram_real_bready 
            = vlSelf->pcie_axi_top__DOT__dma_ram_bready;
        vlSelf->pcie_axi_top__DOT__ram_real_rready 
            = vlSelf->pcie_axi_top__DOT__dma_ram_rready;
        vlSelf->pcie_axi_top__DOT__ram_real_wdata = vlSelf->pcie_axi_top__DOT__dma_ram_wdata;
        vlSelf->pcie_axi_top__DOT__ram_real_wstrb = vlSelf->pcie_axi_top__DOT__dma_ram_wstrb;
    } else {
        vlSelf->pcie_axi_top__DOT__ram_real_bready 
            = vlSelf->pcie_axi_top__DOT__brg_bready;
        vlSelf->pcie_axi_top__DOT__ram_real_rready 
            = vlSelf->pcie_axi_top__DOT__brg_rready;
        vlSelf->pcie_axi_top__DOT__ram_real_wdata = vlSelf->pcie_axi_top__DOT__brg_wdata;
        vlSelf->pcie_axi_top__DOT__ram_real_wstrb = vlSelf->pcie_axi_top__DOT__brg_wstrb;
    }
    if ((0x1000U & vlSelf->pcie_axi_top__DOT__brg_awaddr)) {
        vlSelf->pcie_axi_top__DOT__brg_awready = ((~ (IData)(vlSelf->pcie_axi_top__DOT__ram_owner)) 
                                                  & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_awready));
        vlSelf->pcie_axi_top__DOT__brg_wready = ((~ (IData)(vlSelf->pcie_axi_top__DOT__ram_owner)) 
                                                 & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_wready));
    } else {
        vlSelf->pcie_axi_top__DOT__brg_awready = vlSelf->pcie_axi_top__DOT__dma_awready;
        vlSelf->pcie_axi_top__DOT__brg_wready = vlSelf->pcie_axi_top__DOT__dma_wready;
    }
    vlSelf->pcie_axi_top__DOT__brg_arready = ((0x1000U 
                                               & vlSelf->pcie_axi_top__DOT__brg_araddr)
                                               ? ((~ (IData)(vlSelf->pcie_axi_top__DOT__ram_owner)) 
                                                  & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_arready))
                                               : (IData)(vlSelf->pcie_axi_top__DOT__dma_arready));
}

void Vpcie_axi_top___024root___eval_triggers__act(Vpcie_axi_top___024root* vlSelf);

bool Vpcie_axi_top___024root___eval_phase__act(Vpcie_axi_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vpcie_axi_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpcie_axi_top___024root___eval_phase__act\n"); );
    // Init
    VlTriggerVec<1> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vpcie_axi_top___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelf->__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
        vlSelf->__VnbaTriggered.thisOr(vlSelf->__VactTriggered);
        Vpcie_axi_top___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vpcie_axi_top___024root___eval_phase__nba(Vpcie_axi_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vpcie_axi_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpcie_axi_top___024root___eval_phase__nba\n"); );
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelf->__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vpcie_axi_top___024root___eval_nba(vlSelf);
        vlSelf->__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vpcie_axi_top___024root___dump_triggers__ico(Vpcie_axi_top___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vpcie_axi_top___024root___dump_triggers__nba(Vpcie_axi_top___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vpcie_axi_top___024root___dump_triggers__act(Vpcie_axi_top___024root* vlSelf);
#endif  // VL_DEBUG

void Vpcie_axi_top___024root___eval(Vpcie_axi_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vpcie_axi_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpcie_axi_top___024root___eval\n"); );
    // Init
    IData/*31:0*/ __VicoIterCount;
    CData/*0:0*/ __VicoContinue;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VicoIterCount = 0U;
    vlSelf->__VicoFirstIteration = 1U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        if (VL_UNLIKELY((0x64U < __VicoIterCount))) {
#ifdef VL_DEBUG
            Vpcie_axi_top___024root___dump_triggers__ico(vlSelf);
#endif
            VL_FATAL_MT("../rtl/../rtl/pcie_axi_top.sv", 8, "", "Input combinational region did not converge.");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        __VicoContinue = 0U;
        if (Vpcie_axi_top___024root___eval_phase__ico(vlSelf)) {
            __VicoContinue = 1U;
        }
        vlSelf->__VicoFirstIteration = 0U;
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            Vpcie_axi_top___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("../rtl/../rtl/pcie_axi_top.sv", 8, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                Vpcie_axi_top___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("../rtl/../rtl/pcie_axi_top.sv", 8, "", "Active region did not converge.");
            }
            vlSelf->__VactIterCount = ((IData)(1U) 
                                       + vlSelf->__VactIterCount);
            vlSelf->__VactContinue = 0U;
            if (Vpcie_axi_top___024root___eval_phase__act(vlSelf)) {
                vlSelf->__VactContinue = 1U;
            }
        }
        if (Vpcie_axi_top___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vpcie_axi_top___024root___eval_debug_assertions(Vpcie_axi_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vpcie_axi_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpcie_axi_top___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((vlSelf->rst_n & 0xfeU))) {
        Verilated::overWidthError("rst_n");}
    if (VL_UNLIKELY((vlSelf->rx_st_sop & 0xfeU))) {
        Verilated::overWidthError("rx_st_sop");}
    if (VL_UNLIKELY((vlSelf->rx_st_eop & 0xfeU))) {
        Verilated::overWidthError("rx_st_eop");}
    if (VL_UNLIKELY((vlSelf->rx_st_hvalid & 0xfeU))) {
        Verilated::overWidthError("rx_st_hvalid");}
    if (VL_UNLIKELY((vlSelf->rx_st_dvalid & 0xfeU))) {
        Verilated::overWidthError("rx_st_dvalid");}
    if (VL_UNLIKELY((vlSelf->rx_st_bar & 0xf8U))) {
        Verilated::overWidthError("rx_st_bar");}
    if (VL_UNLIKELY((vlSelf->tx_st_ready & 0xfeU))) {
        Verilated::overWidthError("tx_st_ready");}
    if (VL_UNLIKELY((vlSelf->tx_hcrdt_init & 0xf8U))) {
        Verilated::overWidthError("tx_hcrdt_init");}
    if (VL_UNLIKELY((vlSelf->tx_hcrdt_update & 0xf8U))) {
        Verilated::overWidthError("tx_hcrdt_update");}
    if (VL_UNLIKELY((vlSelf->tx_hcrdt_update_cnt & 0xc0U))) {
        Verilated::overWidthError("tx_hcrdt_update_cnt");}
    if (VL_UNLIKELY((vlSelf->tx_dcrdt_init & 0xf8U))) {
        Verilated::overWidthError("tx_dcrdt_init");}
    if (VL_UNLIKELY((vlSelf->tx_dcrdt_update & 0xf8U))) {
        Verilated::overWidthError("tx_dcrdt_update");}
    if (VL_UNLIKELY((vlSelf->tx_dcrdt_update_cnt & 0xf000U))) {
        Verilated::overWidthError("tx_dcrdt_update_cnt");}
    if (VL_UNLIKELY((vlSelf->link_up & 0xfeU))) {
        Verilated::overWidthError("link_up");}
    if (VL_UNLIKELY((vlSelf->ltssm_state & 0xc0U))) {
        Verilated::overWidthError("ltssm_state");}
}
#endif  // VL_DEBUG
