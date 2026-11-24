// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop__pch.h"
#include "Vtop___024root.h"

void Vtop___024root___ico_sequent__TOP__0(Vtop___024root* vlSelf);

void Vtop___024root___eval_ico(Vtop___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_ico\n"); );
    // Body
    if ((1ULL & vlSelf->__VicoTriggered.word(0U))) {
        Vtop___024root___ico_sequent__TOP__0(vlSelf);
    }
}

VL_INLINE_OPT void Vtop___024root___ico_sequent__TOP__0(Vtop___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___ico_sequent__TOP__0\n"); );
    // Init
    CData/*2:0*/ top__DOT__u_bridge__DOT__rx_fmt;
    top__DOT__u_bridge__DOT__rx_fmt = 0;
    CData/*4:0*/ top__DOT__u_bridge__DOT__rx_type;
    top__DOT__u_bridge__DOT__rx_type = 0;
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
    vlSelf->top__DOT__u_bridge__DOT__rx_len = __Vfunc_hdr_len__2__Vfuncout;
    __Vfunc_hdr_rid__3__h[0U] = vlSelf->rx_st_hdr[0U];
    __Vfunc_hdr_rid__3__h[1U] = vlSelf->rx_st_hdr[1U];
    __Vfunc_hdr_rid__3__h[2U] = vlSelf->rx_st_hdr[2U];
    __Vfunc_hdr_rid__3__h[3U] = vlSelf->rx_st_hdr[3U];
    __Vfunc_hdr_rid__3__Vfuncout = (__Vfunc_hdr_rid__3__h[2U] 
                                    >> 0x10U);
    vlSelf->top__DOT__u_bridge__DOT__rx_rid = __Vfunc_hdr_rid__3__Vfuncout;
    __Vfunc_hdr_tag__4__h[0U] = vlSelf->rx_st_hdr[0U];
    __Vfunc_hdr_tag__4__h[1U] = vlSelf->rx_st_hdr[1U];
    __Vfunc_hdr_tag__4__h[2U] = vlSelf->rx_st_hdr[2U];
    __Vfunc_hdr_tag__4__h[3U] = vlSelf->rx_st_hdr[3U];
    __Vfunc_hdr_tag__4__Vfuncout = (0xffU & (__Vfunc_hdr_tag__4__h[2U] 
                                             >> 8U));
    vlSelf->top__DOT__u_bridge__DOT__rx_tag = __Vfunc_hdr_tag__4__Vfuncout;
    __Vfunc_hdr_fbe__5__h[0U] = vlSelf->rx_st_hdr[0U];
    __Vfunc_hdr_fbe__5__h[1U] = vlSelf->rx_st_hdr[1U];
    __Vfunc_hdr_fbe__5__h[2U] = vlSelf->rx_st_hdr[2U];
    __Vfunc_hdr_fbe__5__h[3U] = vlSelf->rx_st_hdr[3U];
    __Vfunc_hdr_fbe__5__Vfuncout = (0xfU & __Vfunc_hdr_fbe__5__h[2U]);
    vlSelf->top__DOT__u_bridge__DOT__rx_fbe = __Vfunc_hdr_fbe__5__Vfuncout;
    __Vfunc_hdr_lbe__6__h[0U] = vlSelf->rx_st_hdr[0U];
    __Vfunc_hdr_lbe__6__h[1U] = vlSelf->rx_st_hdr[1U];
    __Vfunc_hdr_lbe__6__h[2U] = vlSelf->rx_st_hdr[2U];
    __Vfunc_hdr_lbe__6__h[3U] = vlSelf->rx_st_hdr[3U];
    __Vfunc_hdr_lbe__6__Vfuncout = (0xfU & (__Vfunc_hdr_lbe__6__h[2U] 
                                            >> 4U));
    vlSelf->top__DOT__u_bridge__DOT__rx_lbe = __Vfunc_hdr_lbe__6__Vfuncout;
    vlSelf->top__DOT__u_sniffer__DOT__rx_valid = ((IData)(vlSelf->rx_st_hvalid) 
                                                  & ((IData)(vlSelf->rx_st_ready) 
                                                     & (IData)(vlSelf->rx_st_sop)));
    __Vfunc_hdr_type__1__h[0U] = vlSelf->rx_st_hdr[0U];
    __Vfunc_hdr_type__1__h[1U] = vlSelf->rx_st_hdr[1U];
    __Vfunc_hdr_type__1__h[2U] = vlSelf->rx_st_hdr[2U];
    __Vfunc_hdr_type__1__h[3U] = vlSelf->rx_st_hdr[3U];
    __Vfunc_hdr_type__1__Vfuncout = (0x1fU & (__Vfunc_hdr_type__1__h[3U] 
                                              >> 0x18U));
    top__DOT__u_bridge__DOT__rx_type = __Vfunc_hdr_type__1__Vfuncout;
    __Vfunc_hdr_fmt__0__h[0U] = vlSelf->rx_st_hdr[0U];
    __Vfunc_hdr_fmt__0__h[1U] = vlSelf->rx_st_hdr[1U];
    __Vfunc_hdr_fmt__0__h[2U] = vlSelf->rx_st_hdr[2U];
    __Vfunc_hdr_fmt__0__h[3U] = vlSelf->rx_st_hdr[3U];
    __Vfunc_hdr_fmt__0__Vfuncout = (__Vfunc_hdr_fmt__0__h[3U] 
                                    >> 0x1dU);
    top__DOT__u_bridge__DOT__rx_fmt = __Vfunc_hdr_fmt__0__Vfuncout;
    vlSelf->top__DOT__u_sniffer__DOT__rx_is_cpl_err 
        = ((IData)(vlSelf->top__DOT__u_sniffer__DOT__rx_valid) 
           & (IData)(((0xa000000U == (0x1f000000U & 
                                      vlSelf->rx_st_hdr[3U])) 
                      & (0U != (7U & (vlSelf->rx_st_hdr[1U] 
                                      >> 0xdU))))));
    vlSelf->top__DOT__u_bridge__DOT__rx_is_mrd = ((
                                                   ((IData)(vlSelf->rx_st_hvalid) 
                                                    & (IData)(vlSelf->rx_st_sop)) 
                                                   & (0U 
                                                      == (IData)(top__DOT__u_bridge__DOT__rx_type))) 
                                                  & (~ 
                                                     ([&]() {
                    vlSelf->__Vfunc_has_data__10__fmt 
                        = top__DOT__u_bridge__DOT__rx_fmt;
                    vlSelf->__Vfunc_has_data__10__Vfuncout 
                        = (1U & ((IData)(vlSelf->__Vfunc_has_data__10__fmt) 
                                 >> 1U));
                }(), (IData)(vlSelf->__Vfunc_has_data__10__Vfuncout))));
    vlSelf->top__DOT__u_bridge__DOT__rx_is_mwr = ((
                                                   ((IData)(vlSelf->rx_st_hvalid) 
                                                    & (IData)(vlSelf->rx_st_sop)) 
                                                   & (0U 
                                                      == (IData)(top__DOT__u_bridge__DOT__rx_type))) 
                                                  & ([&]() {
                vlSelf->__Vfunc_has_data__11__fmt = top__DOT__u_bridge__DOT__rx_fmt;
                vlSelf->__Vfunc_has_data__11__Vfuncout 
                    = (1U & ((IData)(vlSelf->__Vfunc_has_data__11__fmt) 
                             >> 1U));
            }(), (IData)(vlSelf->__Vfunc_has_data__11__Vfuncout)));
    vlSelf->top__DOT__u_bridge__DOT__rx_is_cpld = (
                                                   (((IData)(vlSelf->rx_st_hvalid) 
                                                     & (IData)(vlSelf->rx_st_sop)) 
                                                    & (0xaU 
                                                       == (IData)(top__DOT__u_bridge__DOT__rx_type))) 
                                                   & ([&]() {
                vlSelf->__Vfunc_has_data__12__fmt = top__DOT__u_bridge__DOT__rx_fmt;
                vlSelf->__Vfunc_has_data__12__Vfuncout 
                    = (1U & ((IData)(vlSelf->__Vfunc_has_data__12__fmt) 
                             >> 1U));
            }(), (IData)(vlSelf->__Vfunc_has_data__12__Vfuncout)));
    vlSelf->top__DOT__u_bridge__DOT__rx_addr = (([&]() {
                vlSelf->__Vfunc_is_4dw__7__fmt = top__DOT__u_bridge__DOT__rx_fmt;
                vlSelf->__Vfunc_is_4dw__7__Vfuncout 
                    = (1U & (IData)(vlSelf->__Vfunc_is_4dw__7__fmt));
            }(), (IData)(vlSelf->__Vfunc_is_4dw__7__Vfuncout))
                                                 ? 
                                                ([&]() {
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
                                                 : 
                                                VL_EXTEND_QI(64,32, 
                                                             ([&]() {
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
    vlSelf->top__DOT__u_sniffer__DOT__capture_rx = 
        ((IData)(vlSelf->top__DOT__u_sniffer__DOT__rx_valid) 
         & ((0U == (IData)(vlSelf->top__DOT__u_sniffer__DOT__filter_mode)) 
            | ((1U == (IData)(vlSelf->top__DOT__u_sniffer__DOT__filter_mode)) 
               | ((3U == (IData)(vlSelf->top__DOT__u_sniffer__DOT__filter_mode)) 
                  & (IData)(vlSelf->top__DOT__u_sniffer__DOT__rx_is_cpl_err)))));
}

void Vtop___024root___eval_triggers__ico(Vtop___024root* vlSelf);

bool Vtop___024root___eval_phase__ico(Vtop___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__ico\n"); );
    // Init
    CData/*0:0*/ __VicoExecute;
    // Body
    Vtop___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = vlSelf->__VicoTriggered.any();
    if (__VicoExecute) {
        Vtop___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void Vtop___024root___eval_act(Vtop___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_act\n"); );
}

void Vtop___024root___nba_sequent__TOP__0(Vtop___024root* vlSelf);

void Vtop___024root___eval_nba(Vtop___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_nba\n"); );
    // Body
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        Vtop___024root___nba_sequent__TOP__0(vlSelf);
    }
}

extern const VlWide<8>/*255:0*/ Vtop__ConstPool__CONST_h9e67c271_0;
extern const VlUnpacked<CData/*2:0*/, 128> Vtop__ConstPool__TABLE_hf3a84768_0;
extern const VlUnpacked<CData/*5:0*/, 128> Vtop__ConstPool__TABLE_h92b69fc4_0;
extern const VlUnpacked<CData/*2:0*/, 128> Vtop__ConstPool__TABLE_h3a3a7adf_0;
extern const VlUnpacked<CData/*3:0*/, 128> Vtop__ConstPool__TABLE_h1588c7a3_0;
extern const VlUnpacked<CData/*1:0*/, 128> Vtop__ConstPool__TABLE_h643f69a8_0;

VL_INLINE_OPT void Vtop___024root___nba_sequent__TOP__0(Vtop___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__0\n"); );
    // Init
    CData/*0:0*/ top__DOT____VdfgRegularize_h245778ca_0_2;
    top__DOT____VdfgRegularize_h245778ca_0_2 = 0;
    CData/*6:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    CData/*1:0*/ __Vdly__top__DOT__dbg_rd_state;
    __Vdly__top__DOT__dbg_rd_state = 0;
    CData/*0:0*/ __Vdly__top__DOT__msix_valid_i;
    __Vdly__top__DOT__msix_valid_i = 0;
    CData/*0:0*/ __Vdly__top__DOT__arb_owner;
    __Vdly__top__DOT__arb_owner = 0;
    CData/*7:0*/ __Vdly__top__DOT__u_bridge__DOT__host_mrd_tag;
    __Vdly__top__DOT__u_bridge__DOT__host_mrd_tag = 0;
    QData/*63:0*/ __Vdly__top__DOT__u_bridge__DOT__host_mrd_addr;
    __Vdly__top__DOT__u_bridge__DOT__host_mrd_addr = 0;
    CData/*0:0*/ __Vdly__top__DOT__u_bridge__DOT__host_mrd_pending;
    __Vdly__top__DOT__u_bridge__DOT__host_mrd_pending = 0;
    CData/*0:0*/ __Vdly__top__DOT__dma_host_arready;
    __Vdly__top__DOT__dma_host_arready = 0;
    CData/*0:0*/ __Vdly__top__DOT__u_bridge__DOT__host_mrd_inflight;
    __Vdly__top__DOT__u_bridge__DOT__host_mrd_inflight = 0;
    QData/*63:0*/ __Vdly__top__DOT__dma_host_rdata;
    __Vdly__top__DOT__dma_host_rdata = 0;
    CData/*0:0*/ __Vdly__top__DOT__dma_host_rvalid;
    __Vdly__top__DOT__dma_host_rvalid = 0;
    CData/*0:0*/ __Vdly__top__DOT__u_bridge__DOT__host_mwr_pending;
    __Vdly__top__DOT__u_bridge__DOT__host_mwr_pending = 0;
    CData/*0:0*/ __Vdly__top__DOT__dma_host_awready;
    __Vdly__top__DOT__dma_host_awready = 0;
    CData/*0:0*/ __Vdly__top__DOT__dma_host_wready;
    __Vdly__top__DOT__dma_host_wready = 0;
    CData/*0:0*/ __Vdly__top__DOT__dma_host_bvalid;
    __Vdly__top__DOT__dma_host_bvalid = 0;
    CData/*0:0*/ __Vdly__top__DOT__u_bridge__DOT__host_mwr_ready_pulse;
    __Vdly__top__DOT__u_bridge__DOT__host_mwr_ready_pulse = 0;
    CData/*0:0*/ __Vdly__top__DOT__brg_awvalid;
    __Vdly__top__DOT__brg_awvalid = 0;
    CData/*0:0*/ __Vdly__top__DOT__brg_wvalid;
    __Vdly__top__DOT__brg_wvalid = 0;
    CData/*3:0*/ __Vdly__top__DOT__u_bridge__DOT__tx_state;
    __Vdly__top__DOT__u_bridge__DOT__tx_state = 0;
    SData/*15:0*/ __Vdly__top__DOT__u_bridge__DOT__bar_req_rid;
    __Vdly__top__DOT__u_bridge__DOT__bar_req_rid = 0;
    CData/*7:0*/ __Vdly__top__DOT__u_bridge__DOT__bar_req_tag;
    __Vdly__top__DOT__u_bridge__DOT__bar_req_tag = 0;
    CData/*6:0*/ __Vdly__top__DOT__u_bridge__DOT__bar_req_lower_addr;
    __Vdly__top__DOT__u_bridge__DOT__bar_req_lower_addr = 0;
    IData/*31:0*/ __Vdly__top__DOT__u_bridge__DOT__bar_req_addr;
    __Vdly__top__DOT__u_bridge__DOT__bar_req_addr = 0;
    SData/*9:0*/ __Vdly__top__DOT__u_bridge__DOT__bar_dw_remaining;
    __Vdly__top__DOT__u_bridge__DOT__bar_dw_remaining = 0;
    CData/*3:0*/ __Vdly__top__DOT__u_bridge__DOT__bar_dw_count;
    __Vdly__top__DOT__u_bridge__DOT__bar_dw_count = 0;
    VlWide<8>/*255:0*/ __Vdly__top__DOT__u_bridge__DOT__bar_cpl_buffer;
    VL_ZERO_W(256, __Vdly__top__DOT__u_bridge__DOT__bar_cpl_buffer);
    CData/*1:0*/ __Vdly__top__DOT__u_bridge__DOT__bar_cpl_status;
    __Vdly__top__DOT__u_bridge__DOT__bar_cpl_status = 0;
    QData/*63:0*/ __Vdly__top__DOT__u_sniffer__DOT__cycle_count;
    __Vdly__top__DOT__u_sniffer__DOT__cycle_count = 0;
    CData/*7:0*/ __Vdly__top__DOT__u_sniffer__DOT__write_ptr;
    __Vdly__top__DOT__u_sniffer__DOT__write_ptr = 0;
    SData/*8:0*/ __Vdly__top__DOT__u_sniffer__DOT__entry_count;
    __Vdly__top__DOT__u_sniffer__DOT__entry_count = 0;
    CData/*0:0*/ __Vdly__top__DOT__u_sniffer__DOT__triggered;
    __Vdly__top__DOT__u_sniffer__DOT__triggered = 0;
    CData/*0:0*/ __Vdly__top__DOT__u_sniffer__DOT__full;
    __Vdly__top__DOT__u_sniffer__DOT__full = 0;
    CData/*0:0*/ __Vdly__top__DOT__u_sniffer__DOT__running;
    __Vdly__top__DOT__u_sniffer__DOT__running = 0;
    CData/*0:0*/ __Vdly__top__DOT__u_sniffer__DOT__armed;
    __Vdly__top__DOT__u_sniffer__DOT__armed = 0;
    CData/*7:0*/ __Vdlyvdim0__top__DOT__u_sniffer__DOT__trace_ram__v0;
    __Vdlyvdim0__top__DOT__u_sniffer__DOT__trace_ram__v0 = 0;
    VlWide<8>/*255:0*/ __Vdlyvval__top__DOT__u_sniffer__DOT__trace_ram__v0;
    VL_ZERO_W(256, __Vdlyvval__top__DOT__u_sniffer__DOT__trace_ram__v0);
    CData/*0:0*/ __Vdlyvset__top__DOT__u_sniffer__DOT__trace_ram__v0;
    __Vdlyvset__top__DOT__u_sniffer__DOT__trace_ram__v0 = 0;
    IData/*31:0*/ __Vdly__top__DOT__u_sniffer__DOT__rx_count;
    __Vdly__top__DOT__u_sniffer__DOT__rx_count = 0;
    IData/*31:0*/ __Vdly__top__DOT__u_sniffer__DOT__tx_count;
    __Vdly__top__DOT__u_sniffer__DOT__tx_count = 0;
    IData/*31:0*/ __Vdly__top__DOT__u_axi_sniffer__DOT__ar_count;
    __Vdly__top__DOT__u_axi_sniffer__DOT__ar_count = 0;
    IData/*21:0*/ __Vdly__top__DOT__u_axi_sniffer__DOT__timestamp;
    __Vdly__top__DOT__u_axi_sniffer__DOT__timestamp = 0;
    CData/*5:0*/ __Vdly__top__DOT__u_axi_sniffer__DOT__write_ptr;
    __Vdly__top__DOT__u_axi_sniffer__DOT__write_ptr = 0;
    CData/*6:0*/ __Vdly__top__DOT__u_axi_sniffer__DOT__entry_count;
    __Vdly__top__DOT__u_axi_sniffer__DOT__entry_count = 0;
    CData/*0:0*/ __Vdly__top__DOT__u_axi_sniffer__DOT__full;
    __Vdly__top__DOT__u_axi_sniffer__DOT__full = 0;
    CData/*0:0*/ __Vdly__top__DOT__u_axi_sniffer__DOT__pending_awvalid;
    __Vdly__top__DOT__u_axi_sniffer__DOT__pending_awvalid = 0;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__u_axi_sniffer__DOT__trace_ram__v0;
    __Vdlyvdim0__top__DOT__u_axi_sniffer__DOT__trace_ram__v0 = 0;
    VlWide<4>/*127:0*/ __Vdlyvval__top__DOT__u_axi_sniffer__DOT__trace_ram__v0;
    VL_ZERO_W(128, __Vdlyvval__top__DOT__u_axi_sniffer__DOT__trace_ram__v0);
    CData/*0:0*/ __Vdlyvset__top__DOT__u_axi_sniffer__DOT__trace_ram__v0;
    __Vdlyvset__top__DOT__u_axi_sniffer__DOT__trace_ram__v0 = 0;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__u_axi_sniffer__DOT__trace_ram__v1;
    __Vdlyvdim0__top__DOT__u_axi_sniffer__DOT__trace_ram__v1 = 0;
    VlWide<4>/*127:0*/ __Vdlyvval__top__DOT__u_axi_sniffer__DOT__trace_ram__v1;
    VL_ZERO_W(128, __Vdlyvval__top__DOT__u_axi_sniffer__DOT__trace_ram__v1);
    CData/*0:0*/ __Vdlyvset__top__DOT__u_axi_sniffer__DOT__trace_ram__v1;
    __Vdlyvset__top__DOT__u_axi_sniffer__DOT__trace_ram__v1 = 0;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__u_axi_sniffer__DOT__trace_ram__v2;
    __Vdlyvdim0__top__DOT__u_axi_sniffer__DOT__trace_ram__v2 = 0;
    VlWide<4>/*127:0*/ __Vdlyvval__top__DOT__u_axi_sniffer__DOT__trace_ram__v2;
    VL_ZERO_W(128, __Vdlyvval__top__DOT__u_axi_sniffer__DOT__trace_ram__v2);
    CData/*0:0*/ __Vdlyvset__top__DOT__u_axi_sniffer__DOT__trace_ram__v2;
    __Vdlyvset__top__DOT__u_axi_sniffer__DOT__trace_ram__v2 = 0;
    CData/*5:0*/ __Vdlyvdim0__top__DOT__u_axi_sniffer__DOT__trace_ram__v3;
    __Vdlyvdim0__top__DOT__u_axi_sniffer__DOT__trace_ram__v3 = 0;
    VlWide<4>/*127:0*/ __Vdlyvval__top__DOT__u_axi_sniffer__DOT__trace_ram__v3;
    VL_ZERO_W(128, __Vdlyvval__top__DOT__u_axi_sniffer__DOT__trace_ram__v3);
    CData/*0:0*/ __Vdlyvset__top__DOT__u_axi_sniffer__DOT__trace_ram__v3;
    __Vdlyvset__top__DOT__u_axi_sniffer__DOT__trace_ram__v3 = 0;
    IData/*31:0*/ __Vdly__top__DOT__u_axi_sniffer__DOT__aw_count;
    __Vdly__top__DOT__u_axi_sniffer__DOT__aw_count = 0;
    IData/*31:0*/ __Vdly__top__DOT__u_dma__DOT__ctrl_reg;
    __Vdly__top__DOT__u_dma__DOT__ctrl_reg = 0;
    QData/*63:0*/ __Vdly__top__DOT__u_dma__DOT__host_addr;
    __Vdly__top__DOT__u_dma__DOT__host_addr = 0;
    IData/*31:0*/ __Vdly__top__DOT__u_dma__DOT__local_addr;
    __Vdly__top__DOT__u_dma__DOT__local_addr = 0;
    IData/*31:0*/ __Vdly__top__DOT__u_dma__DOT__length_reg;
    __Vdly__top__DOT__u_dma__DOT__length_reg = 0;
    CData/*0:0*/ __Vdly__top__DOT__dma_s_bvalid;
    __Vdly__top__DOT__dma_s_bvalid = 0;
    CData/*0:0*/ __Vdly__top__DOT__dma_s_rvalid;
    __Vdly__top__DOT__dma_s_rvalid = 0;
    QData/*63:0*/ __Vdly__top__DOT__u_dma__DOT__u_h2c__DOT__cur_host;
    __Vdly__top__DOT__u_dma__DOT__u_h2c__DOT__cur_host = 0;
    IData/*31:0*/ __Vdly__top__DOT__u_dma__DOT__u_h2c__DOT__cur_local;
    __Vdly__top__DOT__u_dma__DOT__u_h2c__DOT__cur_local = 0;
    IData/*31:0*/ __Vdly__top__DOT__u_dma__DOT__u_h2c__DOT__bytes_left;
    __Vdly__top__DOT__u_dma__DOT__u_h2c__DOT__bytes_left = 0;
    CData/*2:0*/ __Vdly__top__DOT__u_dma__DOT__u_h2c__DOT__state;
    __Vdly__top__DOT__u_dma__DOT__u_h2c__DOT__state = 0;
    CData/*0:0*/ __Vdly__top__DOT__u_dma__DOT__h2c_host_arvalid;
    __Vdly__top__DOT__u_dma__DOT__h2c_host_arvalid = 0;
    CData/*0:0*/ __Vdly__top__DOT__u_dma__DOT__h2c_local_awvalid;
    __Vdly__top__DOT__u_dma__DOT__h2c_local_awvalid = 0;
    CData/*0:0*/ __Vdly__top__DOT__u_dma__DOT__h2c_local_wvalid;
    __Vdly__top__DOT__u_dma__DOT__h2c_local_wvalid = 0;
    QData/*63:0*/ __Vdly__top__DOT__u_dma__DOT__u_c2h__DOT__cur_host;
    __Vdly__top__DOT__u_dma__DOT__u_c2h__DOT__cur_host = 0;
    IData/*31:0*/ __Vdly__top__DOT__u_dma__DOT__u_c2h__DOT__cur_local;
    __Vdly__top__DOT__u_dma__DOT__u_c2h__DOT__cur_local = 0;
    IData/*31:0*/ __Vdly__top__DOT__u_dma__DOT__u_c2h__DOT__bytes_left;
    __Vdly__top__DOT__u_dma__DOT__u_c2h__DOT__bytes_left = 0;
    CData/*2:0*/ __Vdly__top__DOT__u_dma__DOT__u_c2h__DOT__state;
    __Vdly__top__DOT__u_dma__DOT__u_c2h__DOT__state = 0;
    CData/*0:0*/ __Vdly__top__DOT__u_dma__DOT__c2h_local_arvalid;
    __Vdly__top__DOT__u_dma__DOT__c2h_local_arvalid = 0;
    CData/*0:0*/ __Vdly__top__DOT__u_dma__DOT__c2h_host_awvalid;
    __Vdly__top__DOT__u_dma__DOT__c2h_host_awvalid = 0;
    CData/*0:0*/ __Vdly__top__DOT__u_dma__DOT__c2h_host_wvalid;
    __Vdly__top__DOT__u_dma__DOT__c2h_host_wvalid = 0;
    SData/*8:0*/ __Vdlyvdim0__top__DOT__u_ram__DOT__mem__v0;
    __Vdlyvdim0__top__DOT__u_ram__DOT__mem__v0 = 0;
    CData/*5:0*/ __Vdlyvlsb__top__DOT__u_ram__DOT__mem__v0;
    __Vdlyvlsb__top__DOT__u_ram__DOT__mem__v0 = 0;
    CData/*7:0*/ __Vdlyvval__top__DOT__u_ram__DOT__mem__v0;
    __Vdlyvval__top__DOT__u_ram__DOT__mem__v0 = 0;
    CData/*0:0*/ __Vdlyvset__top__DOT__u_ram__DOT__mem__v0;
    __Vdlyvset__top__DOT__u_ram__DOT__mem__v0 = 0;
    CData/*0:0*/ __Vdly__top__DOT__ram_awready;
    __Vdly__top__DOT__ram_awready = 0;
    CData/*0:0*/ __Vdly__top__DOT__ram_wready;
    __Vdly__top__DOT__ram_wready = 0;
    CData/*0:0*/ __Vdly__top__DOT__ram_bvalid;
    __Vdly__top__DOT__ram_bvalid = 0;
    SData/*8:0*/ __Vdlyvdim0__top__DOT__u_ram__DOT__mem__v1;
    __Vdlyvdim0__top__DOT__u_ram__DOT__mem__v1 = 0;
    CData/*5:0*/ __Vdlyvlsb__top__DOT__u_ram__DOT__mem__v1;
    __Vdlyvlsb__top__DOT__u_ram__DOT__mem__v1 = 0;
    CData/*7:0*/ __Vdlyvval__top__DOT__u_ram__DOT__mem__v1;
    __Vdlyvval__top__DOT__u_ram__DOT__mem__v1 = 0;
    CData/*0:0*/ __Vdlyvset__top__DOT__u_ram__DOT__mem__v1;
    __Vdlyvset__top__DOT__u_ram__DOT__mem__v1 = 0;
    SData/*8:0*/ __Vdlyvdim0__top__DOT__u_ram__DOT__mem__v2;
    __Vdlyvdim0__top__DOT__u_ram__DOT__mem__v2 = 0;
    CData/*5:0*/ __Vdlyvlsb__top__DOT__u_ram__DOT__mem__v2;
    __Vdlyvlsb__top__DOT__u_ram__DOT__mem__v2 = 0;
    CData/*7:0*/ __Vdlyvval__top__DOT__u_ram__DOT__mem__v2;
    __Vdlyvval__top__DOT__u_ram__DOT__mem__v2 = 0;
    CData/*0:0*/ __Vdlyvset__top__DOT__u_ram__DOT__mem__v2;
    __Vdlyvset__top__DOT__u_ram__DOT__mem__v2 = 0;
    SData/*8:0*/ __Vdlyvdim0__top__DOT__u_ram__DOT__mem__v3;
    __Vdlyvdim0__top__DOT__u_ram__DOT__mem__v3 = 0;
    CData/*5:0*/ __Vdlyvlsb__top__DOT__u_ram__DOT__mem__v3;
    __Vdlyvlsb__top__DOT__u_ram__DOT__mem__v3 = 0;
    CData/*7:0*/ __Vdlyvval__top__DOT__u_ram__DOT__mem__v3;
    __Vdlyvval__top__DOT__u_ram__DOT__mem__v3 = 0;
    CData/*0:0*/ __Vdlyvset__top__DOT__u_ram__DOT__mem__v3;
    __Vdlyvset__top__DOT__u_ram__DOT__mem__v3 = 0;
    SData/*8:0*/ __Vdlyvdim0__top__DOT__u_ram__DOT__mem__v4;
    __Vdlyvdim0__top__DOT__u_ram__DOT__mem__v4 = 0;
    CData/*5:0*/ __Vdlyvlsb__top__DOT__u_ram__DOT__mem__v4;
    __Vdlyvlsb__top__DOT__u_ram__DOT__mem__v4 = 0;
    CData/*7:0*/ __Vdlyvval__top__DOT__u_ram__DOT__mem__v4;
    __Vdlyvval__top__DOT__u_ram__DOT__mem__v4 = 0;
    CData/*0:0*/ __Vdlyvset__top__DOT__u_ram__DOT__mem__v4;
    __Vdlyvset__top__DOT__u_ram__DOT__mem__v4 = 0;
    SData/*8:0*/ __Vdlyvdim0__top__DOT__u_ram__DOT__mem__v5;
    __Vdlyvdim0__top__DOT__u_ram__DOT__mem__v5 = 0;
    CData/*5:0*/ __Vdlyvlsb__top__DOT__u_ram__DOT__mem__v5;
    __Vdlyvlsb__top__DOT__u_ram__DOT__mem__v5 = 0;
    CData/*7:0*/ __Vdlyvval__top__DOT__u_ram__DOT__mem__v5;
    __Vdlyvval__top__DOT__u_ram__DOT__mem__v5 = 0;
    CData/*0:0*/ __Vdlyvset__top__DOT__u_ram__DOT__mem__v5;
    __Vdlyvset__top__DOT__u_ram__DOT__mem__v5 = 0;
    SData/*8:0*/ __Vdlyvdim0__top__DOT__u_ram__DOT__mem__v6;
    __Vdlyvdim0__top__DOT__u_ram__DOT__mem__v6 = 0;
    CData/*5:0*/ __Vdlyvlsb__top__DOT__u_ram__DOT__mem__v6;
    __Vdlyvlsb__top__DOT__u_ram__DOT__mem__v6 = 0;
    CData/*7:0*/ __Vdlyvval__top__DOT__u_ram__DOT__mem__v6;
    __Vdlyvval__top__DOT__u_ram__DOT__mem__v6 = 0;
    CData/*0:0*/ __Vdlyvset__top__DOT__u_ram__DOT__mem__v6;
    __Vdlyvset__top__DOT__u_ram__DOT__mem__v6 = 0;
    SData/*8:0*/ __Vdlyvdim0__top__DOT__u_ram__DOT__mem__v7;
    __Vdlyvdim0__top__DOT__u_ram__DOT__mem__v7 = 0;
    CData/*5:0*/ __Vdlyvlsb__top__DOT__u_ram__DOT__mem__v7;
    __Vdlyvlsb__top__DOT__u_ram__DOT__mem__v7 = 0;
    CData/*7:0*/ __Vdlyvval__top__DOT__u_ram__DOT__mem__v7;
    __Vdlyvval__top__DOT__u_ram__DOT__mem__v7 = 0;
    CData/*0:0*/ __Vdlyvset__top__DOT__u_ram__DOT__mem__v7;
    __Vdlyvset__top__DOT__u_ram__DOT__mem__v7 = 0;
    SData/*8:0*/ __Vdly__top__DOT__u_ram__DOT__rd_addr_latched;
    __Vdly__top__DOT__u_ram__DOT__rd_addr_latched = 0;
    CData/*0:0*/ __Vdly__top__DOT__ram_arready;
    __Vdly__top__DOT__ram_arready = 0;
    CData/*0:0*/ __Vdly__top__DOT__u_ram__DOT__read_pending;
    __Vdly__top__DOT__u_ram__DOT__read_pending = 0;
    QData/*63:0*/ __Vdly__top__DOT__ram_rdata;
    __Vdly__top__DOT__ram_rdata = 0;
    CData/*0:0*/ __Vdly__top__DOT__ram_rvalid;
    __Vdly__top__DOT__ram_rvalid = 0;
    // Body
    __Vdly__top__DOT__u_axi_sniffer__DOT__ar_count 
        = vlSelf->top__DOT__u_axi_sniffer__DOT__ar_count;
    __Vdly__top__DOT__u_axi_sniffer__DOT__aw_count 
        = vlSelf->top__DOT__u_axi_sniffer__DOT__aw_count;
    __Vdly__top__DOT__u_sniffer__DOT__tx_count = vlSelf->top__DOT__u_sniffer__DOT__tx_count;
    __Vdly__top__DOT__u_sniffer__DOT__rx_count = vlSelf->top__DOT__u_sniffer__DOT__rx_count;
    __Vdly__top__DOT__u_dma__DOT__c2h_host_wvalid = vlSelf->top__DOT__u_dma__DOT__c2h_host_wvalid;
    __Vdly__top__DOT__u_dma__DOT__c2h_host_awvalid 
        = vlSelf->top__DOT__u_dma__DOT__c2h_host_awvalid;
    __Vdly__top__DOT__u_dma__DOT__c2h_local_arvalid 
        = vlSelf->top__DOT__u_dma__DOT__c2h_local_arvalid;
    __Vdly__top__DOT__u_dma__DOT__u_c2h__DOT__bytes_left 
        = vlSelf->top__DOT__u_dma__DOT__u_c2h__DOT__bytes_left;
    __Vdly__top__DOT__u_dma__DOT__u_c2h__DOT__cur_local 
        = vlSelf->top__DOT__u_dma__DOT__u_c2h__DOT__cur_local;
    __Vdly__top__DOT__u_dma__DOT__u_c2h__DOT__cur_host 
        = vlSelf->top__DOT__u_dma__DOT__u_c2h__DOT__cur_host;
    __Vdly__top__DOT__u_dma__DOT__u_c2h__DOT__state 
        = vlSelf->top__DOT__u_dma__DOT__u_c2h__DOT__state;
    __Vdly__top__DOT__u_dma__DOT__h2c_local_wvalid 
        = vlSelf->top__DOT__u_dma__DOT__h2c_local_wvalid;
    __Vdly__top__DOT__u_dma__DOT__h2c_local_awvalid 
        = vlSelf->top__DOT__u_dma__DOT__h2c_local_awvalid;
    __Vdly__top__DOT__u_dma__DOT__h2c_host_arvalid 
        = vlSelf->top__DOT__u_dma__DOT__h2c_host_arvalid;
    __Vdly__top__DOT__u_dma__DOT__u_h2c__DOT__bytes_left 
        = vlSelf->top__DOT__u_dma__DOT__u_h2c__DOT__bytes_left;
    __Vdly__top__DOT__u_dma__DOT__u_h2c__DOT__cur_local 
        = vlSelf->top__DOT__u_dma__DOT__u_h2c__DOT__cur_local;
    __Vdly__top__DOT__u_dma__DOT__u_h2c__DOT__cur_host 
        = vlSelf->top__DOT__u_dma__DOT__u_h2c__DOT__cur_host;
    __Vdly__top__DOT__u_dma__DOT__u_h2c__DOT__state 
        = vlSelf->top__DOT__u_dma__DOT__u_h2c__DOT__state;
    __Vdly__top__DOT__dma_host_bvalid = vlSelf->top__DOT__dma_host_bvalid;
    __Vdly__top__DOT__dma_host_wready = vlSelf->top__DOT__dma_host_wready;
    __Vdly__top__DOT__dma_host_awready = vlSelf->top__DOT__dma_host_awready;
    __Vdly__top__DOT__u_bridge__DOT__host_mwr_pending 
        = vlSelf->top__DOT__u_bridge__DOT__host_mwr_pending;
    __Vdly__top__DOT__u_bridge__DOT__bar_cpl_status 
        = vlSelf->top__DOT__u_bridge__DOT__bar_cpl_status;
    __Vdly__top__DOT__u_bridge__DOT__bar_cpl_buffer[0U] 
        = vlSelf->top__DOT__u_bridge__DOT__bar_cpl_buffer[0U];
    __Vdly__top__DOT__u_bridge__DOT__bar_cpl_buffer[1U] 
        = vlSelf->top__DOT__u_bridge__DOT__bar_cpl_buffer[1U];
    __Vdly__top__DOT__u_bridge__DOT__bar_cpl_buffer[2U] 
        = vlSelf->top__DOT__u_bridge__DOT__bar_cpl_buffer[2U];
    __Vdly__top__DOT__u_bridge__DOT__bar_cpl_buffer[3U] 
        = vlSelf->top__DOT__u_bridge__DOT__bar_cpl_buffer[3U];
    __Vdly__top__DOT__u_bridge__DOT__bar_cpl_buffer[4U] 
        = vlSelf->top__DOT__u_bridge__DOT__bar_cpl_buffer[4U];
    __Vdly__top__DOT__u_bridge__DOT__bar_cpl_buffer[5U] 
        = vlSelf->top__DOT__u_bridge__DOT__bar_cpl_buffer[5U];
    __Vdly__top__DOT__u_bridge__DOT__bar_cpl_buffer[6U] 
        = vlSelf->top__DOT__u_bridge__DOT__bar_cpl_buffer[6U];
    __Vdly__top__DOT__u_bridge__DOT__bar_cpl_buffer[7U] 
        = vlSelf->top__DOT__u_bridge__DOT__bar_cpl_buffer[7U];
    __Vdly__top__DOT__u_bridge__DOT__bar_dw_count = vlSelf->top__DOT__u_bridge__DOT__bar_dw_count;
    __Vdly__top__DOT__u_bridge__DOT__bar_dw_remaining 
        = vlSelf->top__DOT__u_bridge__DOT__bar_dw_remaining;
    __Vdly__top__DOT__u_bridge__DOT__bar_req_addr = vlSelf->top__DOT__u_bridge__DOT__bar_req_addr;
    __Vdly__top__DOT__u_bridge__DOT__bar_req_lower_addr 
        = vlSelf->top__DOT__u_bridge__DOT__bar_req_lower_addr;
    __Vdly__top__DOT__u_bridge__DOT__bar_req_tag = vlSelf->top__DOT__u_bridge__DOT__bar_req_tag;
    __Vdly__top__DOT__u_bridge__DOT__bar_req_rid = vlSelf->top__DOT__u_bridge__DOT__bar_req_rid;
    __Vdly__top__DOT__u_bridge__DOT__host_mwr_ready_pulse 
        = vlSelf->top__DOT__u_bridge__DOT__host_mwr_ready_pulse;
    __Vdly__top__DOT__u_bridge__DOT__tx_state = vlSelf->top__DOT__u_bridge__DOT__tx_state;
    __Vdly__top__DOT__brg_wvalid = vlSelf->top__DOT__brg_wvalid;
    __Vdly__top__DOT__brg_awvalid = vlSelf->top__DOT__brg_awvalid;
    __Vdly__top__DOT__msix_valid_i = vlSelf->top__DOT__msix_valid_i;
    __Vdly__top__DOT__dma_host_rvalid = vlSelf->top__DOT__dma_host_rvalid;
    __Vdly__top__DOT__dma_host_rdata = vlSelf->top__DOT__dma_host_rdata;
    __Vdly__top__DOT__u_bridge__DOT__host_mrd_inflight 
        = vlSelf->top__DOT__u_bridge__DOT__host_mrd_inflight;
    __Vdly__top__DOT__dma_host_arready = vlSelf->top__DOT__dma_host_arready;
    __Vdly__top__DOT__u_bridge__DOT__host_mrd_pending 
        = vlSelf->top__DOT__u_bridge__DOT__host_mrd_pending;
    __Vdly__top__DOT__u_bridge__DOT__host_mrd_addr 
        = vlSelf->top__DOT__u_bridge__DOT__host_mrd_addr;
    __Vdly__top__DOT__u_bridge__DOT__host_mrd_tag = vlSelf->top__DOT__u_bridge__DOT__host_mrd_tag;
    __Vdly__top__DOT__arb_owner = vlSelf->top__DOT__arb_owner;
    __Vdly__top__DOT__u_ram__DOT__read_pending = vlSelf->top__DOT__u_ram__DOT__read_pending;
    __Vdly__top__DOT__u_ram__DOT__rd_addr_latched = vlSelf->top__DOT__u_ram__DOT__rd_addr_latched;
    __Vdly__top__DOT__ram_rdata = vlSelf->top__DOT__ram_rdata;
    __Vdly__top__DOT__ram_arready = vlSelf->top__DOT__ram_arready;
    __Vdly__top__DOT__ram_rvalid = vlSelf->top__DOT__ram_rvalid;
    __Vdly__top__DOT__ram_wready = vlSelf->top__DOT__ram_wready;
    __Vdly__top__DOT__ram_awready = vlSelf->top__DOT__ram_awready;
    __Vdly__top__DOT__ram_bvalid = vlSelf->top__DOT__ram_bvalid;
    __Vdlyvset__top__DOT__u_ram__DOT__mem__v0 = 0U;
    __Vdlyvset__top__DOT__u_ram__DOT__mem__v1 = 0U;
    __Vdlyvset__top__DOT__u_ram__DOT__mem__v2 = 0U;
    __Vdlyvset__top__DOT__u_ram__DOT__mem__v3 = 0U;
    __Vdlyvset__top__DOT__u_ram__DOT__mem__v4 = 0U;
    __Vdlyvset__top__DOT__u_ram__DOT__mem__v5 = 0U;
    __Vdlyvset__top__DOT__u_ram__DOT__mem__v6 = 0U;
    __Vdlyvset__top__DOT__u_ram__DOT__mem__v7 = 0U;
    __Vdly__top__DOT__u_dma__DOT__length_reg = vlSelf->top__DOT__u_dma__DOT__length_reg;
    __Vdly__top__DOT__u_dma__DOT__local_addr = vlSelf->top__DOT__u_dma__DOT__local_addr;
    __Vdly__top__DOT__u_dma__DOT__host_addr = vlSelf->top__DOT__u_dma__DOT__host_addr;
    __Vdly__top__DOT__u_dma__DOT__ctrl_reg = vlSelf->top__DOT__u_dma__DOT__ctrl_reg;
    __Vdly__top__DOT__dma_s_bvalid = vlSelf->top__DOT__dma_s_bvalid;
    __Vdly__top__DOT__dma_s_rvalid = vlSelf->top__DOT__dma_s_rvalid;
    __Vdly__top__DOT__dbg_rd_state = vlSelf->top__DOT__dbg_rd_state;
    __Vdly__top__DOT__u_sniffer__DOT__armed = vlSelf->top__DOT__u_sniffer__DOT__armed;
    __Vdly__top__DOT__u_sniffer__DOT__running = vlSelf->top__DOT__u_sniffer__DOT__running;
    __Vdly__top__DOT__u_sniffer__DOT__full = vlSelf->top__DOT__u_sniffer__DOT__full;
    __Vdly__top__DOT__u_sniffer__DOT__triggered = vlSelf->top__DOT__u_sniffer__DOT__triggered;
    __Vdly__top__DOT__u_sniffer__DOT__entry_count = vlSelf->top__DOT__u_sniffer__DOT__entry_count;
    __Vdly__top__DOT__u_sniffer__DOT__write_ptr = vlSelf->top__DOT__u_sniffer__DOT__write_ptr;
    __Vdly__top__DOT__u_sniffer__DOT__cycle_count = vlSelf->top__DOT__u_sniffer__DOT__cycle_count;
    __Vdlyvset__top__DOT__u_sniffer__DOT__trace_ram__v0 = 0U;
    __Vdly__top__DOT__u_axi_sniffer__DOT__pending_awvalid 
        = vlSelf->top__DOT__u_axi_sniffer__DOT__pending_awvalid;
    __Vdly__top__DOT__u_axi_sniffer__DOT__full = vlSelf->top__DOT__u_axi_sniffer__DOT__full;
    __Vdly__top__DOT__u_axi_sniffer__DOT__entry_count 
        = vlSelf->top__DOT__u_axi_sniffer__DOT__entry_count;
    __Vdly__top__DOT__u_axi_sniffer__DOT__write_ptr 
        = vlSelf->top__DOT__u_axi_sniffer__DOT__write_ptr;
    __Vdly__top__DOT__u_axi_sniffer__DOT__timestamp 
        = vlSelf->top__DOT__u_axi_sniffer__DOT__timestamp;
    __Vdlyvset__top__DOT__u_axi_sniffer__DOT__trace_ram__v0 = 0U;
    __Vdlyvset__top__DOT__u_axi_sniffer__DOT__trace_ram__v1 = 0U;
    __Vdlyvset__top__DOT__u_axi_sniffer__DOT__trace_ram__v2 = 0U;
    __Vdlyvset__top__DOT__u_axi_sniffer__DOT__trace_ram__v3 = 0U;
    if (vlSelf->rst_n) {
        if (vlSelf->top__DOT__u_axi_sniffer__DOT__ctrl_clear) {
            __Vdly__top__DOT__u_axi_sniffer__DOT__ar_count = 0U;
            __Vdly__top__DOT__u_axi_sniffer__DOT__aw_count = 0U;
        }
        if (((IData)(vlSelf->top__DOT__dma_irq_req) 
             & (~ (IData)(vlSelf->top__DOT__msix_pending)))) {
            __Vdly__top__DOT__msix_valid_i = 1U;
            vlSelf->top__DOT__msix_pending = 1U;
        }
        if (((IData)(vlSelf->top__DOT__msix_valid_i) 
             & (IData)(vlSelf->top__DOT__msix_ready_i))) {
            __Vdly__top__DOT__msix_valid_i = 0U;
            vlSelf->top__DOT__msix_pending = 0U;
        }
        if ((((IData)(vlSelf->top__DOT__u_dma__DOT__h2c_host_arvalid) 
              & (IData)(vlSelf->top__DOT__dma_host_arready)) 
             & (~ (IData)(vlSelf->top__DOT__u_bridge__DOT__host_mrd_pending)))) {
            __Vdly__top__DOT__u_bridge__DOT__host_mrd_tag 
                = (0xffU & ((IData)(1U) + (IData)(vlSelf->top__DOT__u_bridge__DOT__host_mrd_tag)));
            __Vdly__top__DOT__u_bridge__DOT__host_mrd_addr 
                = vlSelf->top__DOT__u_dma__DOT__h2c_host_araddr;
            __Vdly__top__DOT__u_bridge__DOT__host_mrd_pending = 1U;
            __Vdly__top__DOT__dma_host_arready = 0U;
        }
        if (((IData)(vlSelf->top__DOT__u_bridge__DOT__host_mrd_pending) 
             & (IData)(vlSelf->top__DOT__u_bridge__DOT__host_mrd_ready_pulse))) {
            __Vdly__top__DOT__u_bridge__DOT__host_mrd_pending = 0U;
            __Vdly__top__DOT__u_bridge__DOT__host_mrd_inflight = 1U;
        }
        if ((((IData)(vlSelf->top__DOT__u_bridge__DOT__host_mrd_inflight) 
              & (IData)(vlSelf->top__DOT__u_bridge__DOT__rx_is_cpld)) 
             & ((0xffU & (vlSelf->rx_st_hdr[1U] >> 8U)) 
                == (IData)(vlSelf->top__DOT__u_bridge__DOT__host_mrd_tag)))) {
            __Vdly__top__DOT__dma_host_rdata = (((QData)((IData)(
                                                                 vlSelf->rx_st_data[1U])) 
                                                 << 0x20U) 
                                                | (QData)((IData)(
                                                                  vlSelf->rx_st_data[0U])));
            __Vdly__top__DOT__dma_host_rvalid = 1U;
            __Vdly__top__DOT__u_bridge__DOT__host_mrd_inflight = 0U;
            __Vdly__top__DOT__dma_host_arready = 1U;
        }
        if (((IData)(vlSelf->top__DOT__dma_host_rvalid) 
             & (IData)(vlSelf->top__DOT__u_dma__DOT__h2c_host_rready))) {
            __Vdly__top__DOT__dma_host_rvalid = 0U;
        }
        if (vlSelf->top__DOT__arb_busy) {
            if (((~ (IData)(vlSelf->top__DOT__arb_owner)) 
                 & (((IData)(vlSelf->top__DOT__ram_bar_bvalid) 
                     & (IData)(vlSelf->top__DOT__brg_bready)) 
                    | ((IData)(vlSelf->top__DOT__ram_bar_rvalid) 
                       & (IData)(vlSelf->top__DOT__brg_rready))))) {
                vlSelf->top__DOT__arb_busy = 0U;
            }
            if (((IData)(vlSelf->top__DOT__arb_owner) 
                 & (((IData)(vlSelf->top__DOT__dma_local_bvalid) 
                     & (IData)(vlSelf->top__DOT__u_dma__DOT__h2c_local_bready)) 
                    | ((IData)(vlSelf->top__DOT__dma_local_rvalid) 
                       & (IData)(vlSelf->top__DOT__u_dma__DOT__c2h_local_rready))))) {
                vlSelf->top__DOT__arb_busy = 0U;
            }
        } else if (((IData)(vlSelf->top__DOT__ram_bar_awvalid) 
                    | (IData)(vlSelf->top__DOT__ram_bar_arvalid))) {
            vlSelf->top__DOT__arb_busy = 1U;
            __Vdly__top__DOT__arb_owner = 0U;
        } else if (((IData)(vlSelf->top__DOT__u_dma__DOT__h2c_local_awvalid) 
                    | (IData)(vlSelf->top__DOT__u_dma__DOT__c2h_local_arvalid))) {
            vlSelf->top__DOT__arb_busy = 1U;
            __Vdly__top__DOT__arb_owner = 1U;
        }
        if ((((IData)(vlSelf->top__DOT__arb_owner) ? (IData)(vlSelf->top__DOT__u_dma__DOT__c2h_local_arvalid)
               : (IData)(vlSelf->top__DOT__ram_bar_arvalid)) 
             & (IData)(vlSelf->top__DOT__ram_arready))) {
            __Vdly__top__DOT__u_ram__DOT__rd_addr_latched 
                = (0x1ffU & (((IData)(vlSelf->top__DOT__arb_owner)
                               ? vlSelf->top__DOT__u_dma__DOT__c2h_local_araddr
                               : vlSelf->top__DOT__brg_araddr) 
                             >> 3U));
            __Vdly__top__DOT__ram_arready = 0U;
            __Vdly__top__DOT__u_ram__DOT__read_pending = 1U;
        }
        if (vlSelf->top__DOT__u_ram__DOT__read_pending) {
            __Vdly__top__DOT__ram_rdata = vlSelf->top__DOT__u_ram__DOT__mem
                [vlSelf->top__DOT__u_ram__DOT__rd_addr_latched];
            __Vdly__top__DOT__ram_rvalid = 1U;
            __Vdly__top__DOT__u_ram__DOT__read_pending = 0U;
        }
        if (((IData)(vlSelf->top__DOT__ram_rvalid) 
             & ((IData)(vlSelf->top__DOT__arb_owner)
                 ? (IData)(vlSelf->top__DOT__u_dma__DOT__c2h_local_rready)
                 : (IData)(vlSelf->top__DOT__brg_rready)))) {
            __Vdly__top__DOT__ram_rvalid = 0U;
            __Vdly__top__DOT__ram_arready = 1U;
        }
        if (((((IData)(vlSelf->top__DOT__arb_owner)
                ? (IData)(vlSelf->top__DOT__u_dma__DOT__h2c_local_awvalid)
                : (IData)(vlSelf->top__DOT__ram_bar_awvalid)) 
              & ((IData)(vlSelf->top__DOT__arb_owner)
                  ? (IData)(vlSelf->top__DOT__u_dma__DOT__h2c_local_wvalid)
                  : ((IData)(vlSelf->top__DOT__brg_wvalid) 
                     & (IData)(vlSelf->top__DOT__wr_to_ram)))) 
             & (IData)(vlSelf->top__DOT__ram_awready))) {
            if ((1U & (IData)(vlSelf->top__DOT__ram_wstrb))) {
                __Vdlyvval__top__DOT__u_ram__DOT__mem__v0 
                    = (0xffU & (IData)(vlSelf->top__DOT__ram_wdata));
                __Vdlyvset__top__DOT__u_ram__DOT__mem__v0 = 1U;
                __Vdlyvlsb__top__DOT__u_ram__DOT__mem__v0 = 0U;
                __Vdlyvdim0__top__DOT__u_ram__DOT__mem__v0 
                    = (0x1ffU & (((IData)(vlSelf->top__DOT__arb_owner)
                                   ? vlSelf->top__DOT__u_dma__DOT__h2c_local_awaddr
                                   : vlSelf->top__DOT__brg_awaddr) 
                                 >> 3U));
            }
            __Vdly__top__DOT__ram_awready = 0U;
            __Vdly__top__DOT__ram_wready = 0U;
            __Vdly__top__DOT__ram_bvalid = 1U;
            if ((2U & (IData)(vlSelf->top__DOT__ram_wstrb))) {
                __Vdlyvval__top__DOT__u_ram__DOT__mem__v1 
                    = (0xffU & (IData)((vlSelf->top__DOT__ram_wdata 
                                        >> 8U)));
                __Vdlyvset__top__DOT__u_ram__DOT__mem__v1 = 1U;
                __Vdlyvlsb__top__DOT__u_ram__DOT__mem__v1 = 8U;
                __Vdlyvdim0__top__DOT__u_ram__DOT__mem__v1 
                    = (0x1ffU & (((IData)(vlSelf->top__DOT__arb_owner)
                                   ? vlSelf->top__DOT__u_dma__DOT__h2c_local_awaddr
                                   : vlSelf->top__DOT__brg_awaddr) 
                                 >> 3U));
            }
            if ((4U & (IData)(vlSelf->top__DOT__ram_wstrb))) {
                __Vdlyvval__top__DOT__u_ram__DOT__mem__v2 
                    = (0xffU & (IData)((vlSelf->top__DOT__ram_wdata 
                                        >> 0x10U)));
                __Vdlyvset__top__DOT__u_ram__DOT__mem__v2 = 1U;
                __Vdlyvlsb__top__DOT__u_ram__DOT__mem__v2 = 0x10U;
                __Vdlyvdim0__top__DOT__u_ram__DOT__mem__v2 
                    = (0x1ffU & (((IData)(vlSelf->top__DOT__arb_owner)
                                   ? vlSelf->top__DOT__u_dma__DOT__h2c_local_awaddr
                                   : vlSelf->top__DOT__brg_awaddr) 
                                 >> 3U));
            }
            if ((8U & (IData)(vlSelf->top__DOT__ram_wstrb))) {
                __Vdlyvval__top__DOT__u_ram__DOT__mem__v3 
                    = (0xffU & (IData)((vlSelf->top__DOT__ram_wdata 
                                        >> 0x18U)));
                __Vdlyvset__top__DOT__u_ram__DOT__mem__v3 = 1U;
                __Vdlyvlsb__top__DOT__u_ram__DOT__mem__v3 = 0x18U;
                __Vdlyvdim0__top__DOT__u_ram__DOT__mem__v3 
                    = (0x1ffU & (((IData)(vlSelf->top__DOT__arb_owner)
                                   ? vlSelf->top__DOT__u_dma__DOT__h2c_local_awaddr
                                   : vlSelf->top__DOT__brg_awaddr) 
                                 >> 3U));
            }
            if ((0x10U & (IData)(vlSelf->top__DOT__ram_wstrb))) {
                __Vdlyvval__top__DOT__u_ram__DOT__mem__v4 
                    = (0xffU & (IData)((vlSelf->top__DOT__ram_wdata 
                                        >> 0x20U)));
                __Vdlyvset__top__DOT__u_ram__DOT__mem__v4 = 1U;
                __Vdlyvlsb__top__DOT__u_ram__DOT__mem__v4 = 0x20U;
                __Vdlyvdim0__top__DOT__u_ram__DOT__mem__v4 
                    = (0x1ffU & (((IData)(vlSelf->top__DOT__arb_owner)
                                   ? vlSelf->top__DOT__u_dma__DOT__h2c_local_awaddr
                                   : vlSelf->top__DOT__brg_awaddr) 
                                 >> 3U));
            }
            if ((0x20U & (IData)(vlSelf->top__DOT__ram_wstrb))) {
                __Vdlyvval__top__DOT__u_ram__DOT__mem__v5 
                    = (0xffU & (IData)((vlSelf->top__DOT__ram_wdata 
                                        >> 0x28U)));
                __Vdlyvset__top__DOT__u_ram__DOT__mem__v5 = 1U;
                __Vdlyvlsb__top__DOT__u_ram__DOT__mem__v5 = 0x28U;
                __Vdlyvdim0__top__DOT__u_ram__DOT__mem__v5 
                    = (0x1ffU & (((IData)(vlSelf->top__DOT__arb_owner)
                                   ? vlSelf->top__DOT__u_dma__DOT__h2c_local_awaddr
                                   : vlSelf->top__DOT__brg_awaddr) 
                                 >> 3U));
            }
            if ((0x40U & (IData)(vlSelf->top__DOT__ram_wstrb))) {
                __Vdlyvval__top__DOT__u_ram__DOT__mem__v6 
                    = (0xffU & (IData)((vlSelf->top__DOT__ram_wdata 
                                        >> 0x30U)));
                __Vdlyvset__top__DOT__u_ram__DOT__mem__v6 = 1U;
                __Vdlyvlsb__top__DOT__u_ram__DOT__mem__v6 = 0x30U;
                __Vdlyvdim0__top__DOT__u_ram__DOT__mem__v6 
                    = (0x1ffU & (((IData)(vlSelf->top__DOT__arb_owner)
                                   ? vlSelf->top__DOT__u_dma__DOT__h2c_local_awaddr
                                   : vlSelf->top__DOT__brg_awaddr) 
                                 >> 3U));
            }
            if ((0x80U & (IData)(vlSelf->top__DOT__ram_wstrb))) {
                __Vdlyvval__top__DOT__u_ram__DOT__mem__v7 
                    = (0xffU & (IData)((vlSelf->top__DOT__ram_wdata 
                                        >> 0x38U)));
                __Vdlyvset__top__DOT__u_ram__DOT__mem__v7 = 1U;
                __Vdlyvlsb__top__DOT__u_ram__DOT__mem__v7 = 0x38U;
                __Vdlyvdim0__top__DOT__u_ram__DOT__mem__v7 
                    = (0x1ffU & (((IData)(vlSelf->top__DOT__arb_owner)
                                   ? vlSelf->top__DOT__u_dma__DOT__h2c_local_awaddr
                                   : vlSelf->top__DOT__brg_awaddr) 
                                 >> 3U));
            }
        }
        if (((IData)(vlSelf->top__DOT__ram_bvalid) 
             & ((IData)(vlSelf->top__DOT__arb_owner)
                 ? (IData)(vlSelf->top__DOT__u_dma__DOT__h2c_local_bready)
                 : (IData)(vlSelf->top__DOT__brg_bready)))) {
            __Vdly__top__DOT__ram_bvalid = 0U;
            __Vdly__top__DOT__ram_awready = 1U;
            __Vdly__top__DOT__ram_wready = 1U;
        }
        __Vdly__top__DOT__u_sniffer__DOT__cycle_count 
            = (1ULL + vlSelf->top__DOT__u_sniffer__DOT__cycle_count);
        if (((IData)(vlSelf->top__DOT__u_sniffer__DOT____VdfgRegularize_h54215f63_1_0) 
             & (IData)(vlSelf->top__DOT__brg_wdata))) {
            __Vdly__top__DOT__u_sniffer__DOT__running = 1U;
            if ((3U == (IData)(vlSelf->top__DOT__u_sniffer__DOT__capture_mode))) {
                __Vdly__top__DOT__u_sniffer__DOT__armed = 1U;
            }
        }
        if (((IData)(vlSelf->top__DOT__u_sniffer__DOT____VdfgRegularize_h54215f63_1_0) 
             & (IData)((vlSelf->top__DOT__brg_wdata 
                        >> 1U)))) {
            __Vdly__top__DOT__u_sniffer__DOT__running = 0U;
            __Vdly__top__DOT__u_sniffer__DOT__armed = 0U;
        }
        if (((IData)(vlSelf->top__DOT__u_sniffer__DOT____VdfgRegularize_h54215f63_1_0) 
             & (IData)((vlSelf->top__DOT__brg_wdata 
                        >> 3U)))) {
            __Vdly__top__DOT__u_sniffer__DOT__armed = 1U;
        }
        if (vlSelf->top__DOT__u_sniffer__DOT__ctrl_clear) {
            __Vdly__top__DOT__u_sniffer__DOT__tx_count = 0U;
            __Vdly__top__DOT__u_sniffer__DOT__rx_count = 0U;
            __Vdly__top__DOT__u_sniffer__DOT__write_ptr = 0U;
            __Vdly__top__DOT__u_sniffer__DOT__entry_count = 0U;
            __Vdly__top__DOT__u_sniffer__DOT__triggered = 0U;
            __Vdly__top__DOT__u_sniffer__DOT__full = 0U;
        }
        if (((IData)(vlSelf->top__DOT__u_sniffer__DOT__running) 
             & (((IData)(vlSelf->top__DOT__u_sniffer__DOT__capture_rx) 
                 & ((IData)(vlSelf->top__DOT__u_sniffer__DOT__trigger_type_en) 
                    & ((vlSelf->rx_st_hdr[3U] >> 0x18U) 
                       == (IData)(vlSelf->top__DOT__u_sniffer__DOT__trigger_type)))) 
                | (((IData)(vlSelf->top__DOT__u_sniffer__DOT__capture_tx) 
                    & ((IData)(vlSelf->top__DOT__u_sniffer__DOT__trigger_type_en) 
                       & ((vlSelf->top__DOT__u_bridge__DOT__tx_hdr_r[3U] 
                           >> 0x18U) == (IData)(vlSelf->top__DOT__u_sniffer__DOT__trigger_type)))) 
                   | ((IData)(vlSelf->top__DOT__u_sniffer__DOT__trigger_on_err) 
                      & ((IData)(vlSelf->top__DOT__u_sniffer__DOT__rx_is_cpl_err) 
                         | (IData)(vlSelf->top__DOT__u_sniffer__DOT__tx_is_cpl_err))))))) {
            if (((3U == (IData)(vlSelf->top__DOT__u_sniffer__DOT__capture_mode)) 
                 & (IData)(vlSelf->top__DOT__u_sniffer__DOT__armed))) {
                __Vdly__top__DOT__u_sniffer__DOT__armed = 0U;
            }
            __Vdly__top__DOT__u_sniffer__DOT__triggered = 1U;
            if ((2U == (IData)(vlSelf->top__DOT__u_sniffer__DOT__capture_mode))) {
                __Vdly__top__DOT__u_sniffer__DOT__running = 0U;
            }
        }
        if (((IData)(vlSelf->top__DOT__u_sniffer__DOT__running) 
             & (~ (IData)(vlSelf->top__DOT__u_sniffer__DOT__full)))) {
            vlSelf->top__DOT__u_sniffer__DOT__unnamedblk1__DOT__should_capture 
                = ((3U != (IData)(vlSelf->top__DOT__u_sniffer__DOT__capture_mode)) 
                   | (IData)(vlSelf->top__DOT__u_sniffer__DOT__triggered));
            if (((IData)(vlSelf->top__DOT__u_sniffer__DOT__unnamedblk1__DOT__should_capture) 
                 & ((IData)(vlSelf->top__DOT__u_sniffer__DOT__capture_rx) 
                    | (IData)(vlSelf->top__DOT__u_sniffer__DOT__capture_tx)))) {
                if ((0x100U > (IData)(vlSelf->top__DOT__u_sniffer__DOT__entry_count))) {
                    __Vdly__top__DOT__u_sniffer__DOT__entry_count 
                        = (0x1ffU & ((IData)(1U) + (IData)(vlSelf->top__DOT__u_sniffer__DOT__entry_count)));
                }
                if (vlSelf->top__DOT__u_sniffer__DOT__capture_rx) {
                    vlSelf->top__DOT__u_sniffer__DOT__unnamedblk1__DOT__unnamedblk2__DOT__entry[0U] 
                        = vlSelf->rx_st_hdr[0U];
                    vlSelf->top__DOT__u_sniffer__DOT__unnamedblk1__DOT__unnamedblk2__DOT__entry[1U] 
                        = vlSelf->rx_st_hdr[1U];
                    vlSelf->top__DOT__u_sniffer__DOT__unnamedblk1__DOT__unnamedblk2__DOT__entry[2U] 
                        = vlSelf->rx_st_hdr[2U];
                    vlSelf->top__DOT__u_sniffer__DOT__unnamedblk1__DOT__unnamedblk2__DOT__entry[3U] 
                        = vlSelf->rx_st_hdr[3U];
                    vlSelf->top__DOT__u_sniffer__DOT__unnamedblk1__DOT__unnamedblk2__DOT__entry[4U] 
                        = (IData)((((QData)((IData)(
                                                    vlSelf->rx_st_data[1U])) 
                                    << 0x20U) | (QData)((IData)(
                                                                vlSelf->rx_st_data[0U]))));
                    vlSelf->top__DOT__u_sniffer__DOT__unnamedblk1__DOT__unnamedblk2__DOT__entry[5U] 
                        = (IData)(((((QData)((IData)(
                                                     vlSelf->rx_st_data[1U])) 
                                     << 0x20U) | (QData)((IData)(
                                                                 vlSelf->rx_st_data[0U]))) 
                                   >> 0x20U));
                } else {
                    vlSelf->top__DOT__u_sniffer__DOT__unnamedblk1__DOT__unnamedblk2__DOT__entry[0U] 
                        = vlSelf->tx_st_hdr[0U];
                    vlSelf->top__DOT__u_sniffer__DOT__unnamedblk1__DOT__unnamedblk2__DOT__entry[1U] 
                        = vlSelf->tx_st_hdr[1U];
                    vlSelf->top__DOT__u_sniffer__DOT__unnamedblk1__DOT__unnamedblk2__DOT__entry[2U] 
                        = vlSelf->tx_st_hdr[2U];
                    vlSelf->top__DOT__u_sniffer__DOT__unnamedblk1__DOT__unnamedblk2__DOT__entry[3U] 
                        = vlSelf->tx_st_hdr[3U];
                    vlSelf->top__DOT__u_sniffer__DOT__unnamedblk1__DOT__unnamedblk2__DOT__entry[4U] 
                        = (IData)((((QData)((IData)(
                                                    vlSelf->tx_st_data[1U])) 
                                    << 0x20U) | (QData)((IData)(
                                                                vlSelf->tx_st_data[0U]))));
                    vlSelf->top__DOT__u_sniffer__DOT__unnamedblk1__DOT__unnamedblk2__DOT__entry[5U] 
                        = (IData)(((((QData)((IData)(
                                                     vlSelf->tx_st_data[1U])) 
                                     << 0x20U) | (QData)((IData)(
                                                                 vlSelf->tx_st_data[0U]))) 
                                   >> 0x20U));
                }
                vlSelf->top__DOT__u_sniffer__DOT__unnamedblk1__DOT__unnamedblk2__DOT__entry[6U] 
                    = ((0xfffffffeU & vlSelf->top__DOT__u_sniffer__DOT__unnamedblk1__DOT__unnamedblk2__DOT__entry[6U]) 
                       | ((IData)(vlSelf->top__DOT__u_sniffer__DOT__capture_rx)
                           ? 0U : 1U));
                vlSelf->top__DOT__u_sniffer__DOT__unnamedblk1__DOT__unnamedblk2__DOT__entry[6U] 
                    = ((1U & vlSelf->top__DOT__u_sniffer__DOT__unnamedblk1__DOT__unnamedblk2__DOT__entry[6U]) 
                       | ((IData)(((0x7ffffffffffffff0ULL 
                                    & (vlSelf->top__DOT__u_sniffer__DOT__cycle_count 
                                       << 4U)) | (QData)((IData)(vlSelf->top__DOT__u_bridge__DOT__tx_state)))) 
                          << 1U));
                vlSelf->top__DOT__u_sniffer__DOT__unnamedblk1__DOT__unnamedblk2__DOT__entry[7U] 
                    = (((IData)(((0x7ffffffffffffff0ULL 
                                  & (vlSelf->top__DOT__u_sniffer__DOT__cycle_count 
                                     << 4U)) | (QData)((IData)(vlSelf->top__DOT__u_bridge__DOT__tx_state)))) 
                        >> 0x1fU) | ((IData)((((0x7ffffffffffffff0ULL 
                                                & (vlSelf->top__DOT__u_sniffer__DOT__cycle_count 
                                                   << 4U)) 
                                               | (QData)((IData)(vlSelf->top__DOT__u_bridge__DOT__tx_state))) 
                                              >> 0x20U)) 
                                     << 1U));
                __Vdlyvval__top__DOT__u_sniffer__DOT__trace_ram__v0[0U] 
                    = vlSelf->top__DOT__u_sniffer__DOT__unnamedblk1__DOT__unnamedblk2__DOT__entry[0U];
                __Vdlyvval__top__DOT__u_sniffer__DOT__trace_ram__v0[1U] 
                    = vlSelf->top__DOT__u_sniffer__DOT__unnamedblk1__DOT__unnamedblk2__DOT__entry[1U];
                __Vdlyvval__top__DOT__u_sniffer__DOT__trace_ram__v0[2U] 
                    = vlSelf->top__DOT__u_sniffer__DOT__unnamedblk1__DOT__unnamedblk2__DOT__entry[2U];
                __Vdlyvval__top__DOT__u_sniffer__DOT__trace_ram__v0[3U] 
                    = vlSelf->top__DOT__u_sniffer__DOT__unnamedblk1__DOT__unnamedblk2__DOT__entry[3U];
                __Vdlyvval__top__DOT__u_sniffer__DOT__trace_ram__v0[4U] 
                    = vlSelf->top__DOT__u_sniffer__DOT__unnamedblk1__DOT__unnamedblk2__DOT__entry[4U];
                __Vdlyvval__top__DOT__u_sniffer__DOT__trace_ram__v0[5U] 
                    = vlSelf->top__DOT__u_sniffer__DOT__unnamedblk1__DOT__unnamedblk2__DOT__entry[5U];
                __Vdlyvval__top__DOT__u_sniffer__DOT__trace_ram__v0[6U] 
                    = vlSelf->top__DOT__u_sniffer__DOT__unnamedblk1__DOT__unnamedblk2__DOT__entry[6U];
                __Vdlyvval__top__DOT__u_sniffer__DOT__trace_ram__v0[7U] 
                    = vlSelf->top__DOT__u_sniffer__DOT__unnamedblk1__DOT__unnamedblk2__DOT__entry[7U];
                __Vdlyvset__top__DOT__u_sniffer__DOT__trace_ram__v0 = 1U;
                __Vdlyvdim0__top__DOT__u_sniffer__DOT__trace_ram__v0 
                    = vlSelf->top__DOT__u_sniffer__DOT__write_ptr;
                __Vdly__top__DOT__u_sniffer__DOT__write_ptr 
                    = (0xffU & ((IData)(1U) + (IData)(vlSelf->top__DOT__u_sniffer__DOT__write_ptr)));
                if ((0xffU == (IData)(vlSelf->top__DOT__u_sniffer__DOT__write_ptr))) {
                    if ((1U == (IData)(vlSelf->top__DOT__u_sniffer__DOT__capture_mode))) {
                        __Vdly__top__DOT__u_sniffer__DOT__full = 1U;
                        __Vdly__top__DOT__u_sniffer__DOT__running = 0U;
                    }
                }
            }
        }
        vlSelf->tx_hcrdt_init_ack = vlSelf->tx_hcrdt_init;
        vlSelf->tx_dcrdt_init_ack = vlSelf->tx_dcrdt_init;
        if (((IData)(vlSelf->top__DOT__u_dma__DOT__start) 
             & (~ (IData)(vlSelf->top__DOT__u_dma__DOT__busy)))) {
            __Vdly__top__DOT__u_dma__DOT__ctrl_reg 
                = (0xfffffffeU & __Vdly__top__DOT__u_dma__DOT__ctrl_reg);
        }
        if (((((~ (IData)(vlSelf->top__DOT__wr_to_ram)) 
               & (IData)(vlSelf->top__DOT__brg_awvalid)) 
              & (IData)(vlSelf->top__DOT__brg_wvalid)) 
             & (IData)(vlSelf->top__DOT__dma_s_awready))) {
            if ((0U == (0xffU & vlSelf->top__DOT__brg_awaddr))) {
                __Vdly__top__DOT__u_dma__DOT__ctrl_reg 
                    = (IData)(vlSelf->top__DOT__brg_wdata);
            } else if ((0x10U == (0xffU & vlSelf->top__DOT__brg_awaddr))) {
                __Vdly__top__DOT__u_dma__DOT__host_addr 
                    = vlSelf->top__DOT__brg_wdata;
            } else if ((0x18U == (0xffU & vlSelf->top__DOT__brg_awaddr))) {
                __Vdly__top__DOT__u_dma__DOT__local_addr 
                    = (IData)(vlSelf->top__DOT__brg_wdata);
            } else if ((0x20U == (0xffU & vlSelf->top__DOT__brg_awaddr))) {
                __Vdly__top__DOT__u_dma__DOT__length_reg 
                    = (IData)(vlSelf->top__DOT__brg_wdata);
            }
            vlSelf->top__DOT__dma_s_awready = 0U;
            vlSelf->top__DOT__dma_s_wready = 0U;
            __Vdly__top__DOT__dma_s_bvalid = 1U;
        }
        if (((IData)(vlSelf->top__DOT__dma_s_bvalid) 
             & (IData)(vlSelf->top__DOT__brg_bready))) {
            __Vdly__top__DOT__dma_s_bvalid = 0U;
            vlSelf->top__DOT__dma_s_awready = 1U;
            vlSelf->top__DOT__dma_s_wready = 1U;
        }
        if ((((~ ((IData)(vlSelf->top__DOT__rd_to_ram) 
                  | (IData)(vlSelf->top__DOT__rd_to_dbg))) 
              & (IData)(vlSelf->top__DOT__brg_arvalid)) 
             & (IData)(vlSelf->top__DOT__dma_s_arready))) {
            vlSelf->top__DOT__dma_s_rdata = ((0U == 
                                              (0xffU 
                                               & vlSelf->top__DOT__brg_araddr))
                                              ? (QData)((IData)(vlSelf->top__DOT__u_dma__DOT__ctrl_reg))
                                              : ((8U 
                                                  == 
                                                  (0xffU 
                                                   & vlSelf->top__DOT__brg_araddr))
                                                  ? (QData)((IData)(
                                                                    (((IData)(vlSelf->top__DOT__u_dma__DOT__done) 
                                                                      << 1U) 
                                                                     | (IData)(vlSelf->top__DOT__u_dma__DOT__busy))))
                                                  : 
                                                 ((0x10U 
                                                   == 
                                                   (0xffU 
                                                    & vlSelf->top__DOT__brg_araddr))
                                                   ? vlSelf->top__DOT__u_dma__DOT__host_addr
                                                   : 
                                                  ((0x18U 
                                                    == 
                                                    (0xffU 
                                                     & vlSelf->top__DOT__brg_araddr))
                                                    ? (QData)((IData)(vlSelf->top__DOT__u_dma__DOT__local_addr))
                                                    : 
                                                   ((0x20U 
                                                     == 
                                                     (0xffU 
                                                      & vlSelf->top__DOT__brg_araddr))
                                                     ? (QData)((IData)(vlSelf->top__DOT__u_dma__DOT__length_reg))
                                                     : 0xdeaddeadULL)))));
            vlSelf->top__DOT__dma_s_arready = 0U;
            __Vdly__top__DOT__dma_s_rvalid = 1U;
        }
        if (((IData)(vlSelf->top__DOT__dma_s_rvalid) 
             & (IData)(vlSelf->top__DOT__brg_rready))) {
            __Vdly__top__DOT__dma_s_rvalid = 0U;
            vlSelf->top__DOT__dma_s_arready = 1U;
        }
        if ((2U & (IData)(vlSelf->top__DOT__dbg_rd_state))) {
            if ((1U & (IData)(vlSelf->top__DOT__dbg_rd_state))) {
                if (vlSelf->top__DOT__brg_rready) {
                    vlSelf->top__DOT__dbg_rvalid = 0U;
                    __Vdly__top__DOT__dbg_rd_state = 0U;
                }
            } else {
                vlSelf->top__DOT__dbg_rdata_latched 
                    = vlSelf->top__DOT__dbg_rdata;
                vlSelf->top__DOT__dbg_rvalid = 1U;
                __Vdly__top__DOT__dbg_rd_state = 3U;
            }
        } else if ((1U & (IData)(vlSelf->top__DOT__dbg_rd_state))) {
            __Vdly__top__DOT__dbg_rd_state = 2U;
        } else if (((IData)(vlSelf->top__DOT__brg_arvalid) 
                    & ((IData)(vlSelf->top__DOT__brg_arready) 
                       & (IData)(vlSelf->top__DOT__rd_to_dbg)))) {
            vlSelf->top__DOT__dbg_addr_latched = (0xfffU 
                                                  & vlSelf->top__DOT__brg_araddr);
            vlSelf->top__DOT__dbg_sel_axi_latched = vlSelf->top__DOT__rd_to_axi_dbg;
            __Vdly__top__DOT__dbg_rd_state = 1U;
        }
        vlSelf->top__DOT__pcie_dbg_rdata = ((0x800U 
                                             & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                             ? (0x3ffU 
                                                & ((IData)(vlSelf->top__DOT__dbg_addr_to_sniffer) 
                                                   >> 2U))
                                             : ((0x400U 
                                                 & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                 ? 
                                                (0x3ffU 
                                                 & ((IData)(vlSelf->top__DOT__dbg_addr_to_sniffer) 
                                                    >> 2U))
                                                 : 
                                                ((0x200U 
                                                  & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                  ? 
                                                 (0x3ffU 
                                                  & ((IData)(vlSelf->top__DOT__dbg_addr_to_sniffer) 
                                                     >> 2U))
                                                  : 
                                                 ((0x100U 
                                                   & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                   ? 
                                                  (0x3ffU 
                                                   & ((IData)(vlSelf->top__DOT__dbg_addr_to_sniffer) 
                                                      >> 2U))
                                                   : 
                                                  ((0x80U 
                                                    & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                    ? 
                                                   (0x3ffU 
                                                    & ((IData)(vlSelf->top__DOT__dbg_addr_to_sniffer) 
                                                       >> 2U))
                                                    : 
                                                   ((0x40U 
                                                     & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                     ? 
                                                    ((0x20U 
                                                      & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                      ? 
                                                     ((0x10U 
                                                       & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                       ? 
                                                      ((8U 
                                                        & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                        ? 
                                                       ((4U 
                                                         & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                         ? (IData)(
                                                                   (vlSelf->top__DOT__u_sniffer__DOT__last_tx_data 
                                                                    >> 0x20U))
                                                         : (IData)(vlSelf->top__DOT__u_sniffer__DOT__last_tx_data))
                                                        : 
                                                       ((4U 
                                                         & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                         ? 
                                                        vlSelf->top__DOT__u_sniffer__DOT__last_tx_hdr[3U]
                                                         : 
                                                        vlSelf->top__DOT__u_sniffer__DOT__last_tx_hdr[2U]))
                                                       : 
                                                      ((8U 
                                                        & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                        ? 
                                                       ((4U 
                                                         & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                         ? 
                                                        vlSelf->top__DOT__u_sniffer__DOT__last_tx_hdr[1U]
                                                         : 
                                                        vlSelf->top__DOT__u_sniffer__DOT__last_tx_hdr[0U])
                                                        : 
                                                       ((4U 
                                                         & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                         ? (IData)(
                                                                   (vlSelf->top__DOT__u_sniffer__DOT__last_rx_data 
                                                                    >> 0x20U))
                                                         : (IData)(vlSelf->top__DOT__u_sniffer__DOT__last_rx_data))))
                                                      : 
                                                     ((0x10U 
                                                       & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                       ? 
                                                      ((8U 
                                                        & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                        ? 
                                                       ((4U 
                                                         & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                         ? 
                                                        vlSelf->top__DOT__u_sniffer__DOT__last_rx_hdr[3U]
                                                         : 
                                                        vlSelf->top__DOT__u_sniffer__DOT__last_rx_hdr[2U])
                                                        : 
                                                       ((4U 
                                                         & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                         ? 
                                                        vlSelf->top__DOT__u_sniffer__DOT__last_rx_hdr[1U]
                                                         : 
                                                        vlSelf->top__DOT__u_sniffer__DOT__last_rx_hdr[0U]))
                                                       : 
                                                      ((8U 
                                                        & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                        ? 
                                                       ((4U 
                                                         & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                         ? 
                                                        vlSelf->top__DOT__u_sniffer__DOT__read_entry[6U]
                                                         : 
                                                        vlSelf->top__DOT__u_sniffer__DOT__read_entry[5U])
                                                        : 
                                                       ((4U 
                                                         & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                         ? 
                                                        vlSelf->top__DOT__u_sniffer__DOT__read_entry[4U]
                                                         : 
                                                        vlSelf->top__DOT__u_sniffer__DOT__read_entry[3U]))))
                                                     : 
                                                    ((0x20U 
                                                      & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                      ? 
                                                     ((0x10U 
                                                       & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                       ? 
                                                      ((8U 
                                                        & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                        ? 
                                                       ((4U 
                                                         & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                         ? 
                                                        vlSelf->top__DOT__u_sniffer__DOT__read_entry[2U]
                                                         : 
                                                        vlSelf->top__DOT__u_sniffer__DOT__read_entry[1U])
                                                        : 
                                                       ((4U 
                                                         & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                         ? 
                                                        vlSelf->top__DOT__u_sniffer__DOT__read_entry[0U]
                                                         : (IData)(vlSelf->top__DOT__u_sniffer__DOT__read_ptr)))
                                                       : 
                                                      ((8U 
                                                        & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                        ? 
                                                       (0x3ffU 
                                                        & ((IData)(vlSelf->top__DOT__dbg_addr_to_sniffer) 
                                                           >> 2U))
                                                        : 
                                                       ((4U 
                                                         & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                         ? (IData)(
                                                                   (vlSelf->top__DOT__u_sniffer__DOT__cycle_count 
                                                                    >> 0x20U))
                                                         : (IData)(vlSelf->top__DOT__u_sniffer__DOT__cycle_count))))
                                                      : 
                                                     ((0x10U 
                                                       & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                       ? 
                                                      ((8U 
                                                        & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                        ? 
                                                       ((4U 
                                                         & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                         ? vlSelf->top__DOT__u_sniffer__DOT__tx_count
                                                         : vlSelf->top__DOT__u_sniffer__DOT__rx_count)
                                                        : 
                                                       ((4U 
                                                         & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                         ? (IData)(vlSelf->top__DOT__u_sniffer__DOT__entry_count)
                                                         : (IData)(vlSelf->top__DOT__u_sniffer__DOT__write_ptr)))
                                                       : 
                                                      ((8U 
                                                        & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                        ? 
                                                       ((4U 
                                                         & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                         ? 
                                                        (((IData)(vlSelf->top__DOT__u_sniffer__DOT__trigger_on_err) 
                                                          << 9U) 
                                                         | (((IData)(vlSelf->top__DOT__u_sniffer__DOT__trigger_type_en) 
                                                             << 8U) 
                                                            | (IData)(vlSelf->top__DOT__u_sniffer__DOT__trigger_type)))
                                                         : 
                                                        (((IData)(vlSelf->top__DOT__u_sniffer__DOT__filter_mode) 
                                                          << 4U) 
                                                         | (IData)(vlSelf->top__DOT__u_sniffer__DOT__capture_mode)))
                                                        : 
                                                       ((4U 
                                                         & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                         ? 0U
                                                         : 
                                                        (((IData)(vlSelf->top__DOT__u_sniffer__DOT__capture_mode) 
                                                          << 0x13U) 
                                                         | (((IData)(vlSelf->top__DOT__u_sniffer__DOT__full) 
                                                             << 0x12U) 
                                                            | (((IData)(vlSelf->top__DOT__u_sniffer__DOT__triggered) 
                                                                << 0x11U) 
                                                               | (((IData)(vlSelf->top__DOT__u_sniffer__DOT__running) 
                                                                   << 0x10U) 
                                                                  | (((IData)(vlSelf->top__DOT__u_sniffer__DOT__last_rx_type) 
                                                                      << 8U) 
                                                                     | (((IData)(vlSelf->top__DOT__u_bridge__DOT__tx_state) 
                                                                         << 4U) 
                                                                        | (((IData)(vlSelf->top__DOT__u_sniffer__DOT__tx_seen) 
                                                                            << 1U) 
                                                                           | (IData)(vlSelf->top__DOT__u_sniffer__DOT__rx_seen))))))))))))))))));
        if (vlSelf->top__DOT__u_sniffer__DOT__ctrl_clear) {
            vlSelf->top__DOT__u_sniffer__DOT__tx_seen = 0U;
            vlSelf->top__DOT__u_sniffer__DOT__rx_seen = 0U;
        }
        if (vlSelf->top__DOT__u_sniffer__DOT__rx_valid) {
            __Vdly__top__DOT__u_sniffer__DOT__rx_count 
                = ((IData)(1U) + vlSelf->top__DOT__u_sniffer__DOT__rx_count);
            vlSelf->top__DOT__u_sniffer__DOT__last_rx_data 
                = (((QData)((IData)(vlSelf->rx_st_data[1U])) 
                    << 0x20U) | (QData)((IData)(vlSelf->rx_st_data[0U])));
            vlSelf->top__DOT__u_sniffer__DOT__last_rx_hdr[0U] 
                = vlSelf->rx_st_hdr[0U];
            vlSelf->top__DOT__u_sniffer__DOT__last_rx_hdr[1U] 
                = vlSelf->rx_st_hdr[1U];
            vlSelf->top__DOT__u_sniffer__DOT__last_rx_hdr[2U] 
                = vlSelf->rx_st_hdr[2U];
            vlSelf->top__DOT__u_sniffer__DOT__last_rx_hdr[3U] 
                = vlSelf->rx_st_hdr[3U];
            vlSelf->top__DOT__u_sniffer__DOT__last_rx_type 
                = (vlSelf->rx_st_hdr[3U] >> 0x18U);
            vlSelf->top__DOT__u_sniffer__DOT__rx_seen = 1U;
        }
        if (vlSelf->top__DOT__u_sniffer__DOT__tx_valid) {
            __Vdly__top__DOT__u_sniffer__DOT__tx_count 
                = ((IData)(1U) + vlSelf->top__DOT__u_sniffer__DOT__tx_count);
            vlSelf->top__DOT__u_sniffer__DOT__last_tx_data 
                = (((QData)((IData)(vlSelf->tx_st_data[1U])) 
                    << 0x20U) | (QData)((IData)(vlSelf->tx_st_data[0U])));
            vlSelf->top__DOT__u_sniffer__DOT__last_tx_hdr[0U] 
                = vlSelf->tx_st_hdr[0U];
            vlSelf->top__DOT__u_sniffer__DOT__last_tx_hdr[1U] 
                = vlSelf->tx_st_hdr[1U];
            vlSelf->top__DOT__u_sniffer__DOT__last_tx_hdr[2U] 
                = vlSelf->tx_st_hdr[2U];
            vlSelf->top__DOT__u_sniffer__DOT__last_tx_hdr[3U] 
                = vlSelf->tx_st_hdr[3U];
            vlSelf->top__DOT__u_sniffer__DOT__tx_seen = 1U;
        }
        vlSelf->top__DOT__axi_dbg_rdata = ((0x80U & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                            ? 0xdeadbeefU
                                            : ((0x40U 
                                                & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                ? 0xdeadbeefU
                                                : (
                                                   (0x20U 
                                                    & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                    ? 
                                                   ((0x10U 
                                                     & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                     ? 
                                                    ((8U 
                                                      & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                      ? 0xdeadbeefU
                                                      : 
                                                     ((4U 
                                                       & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                       ? 0xdeadbeefU
                                                       : 
                                                      vlSelf->top__DOT__u_axi_sniffer__DOT__read_entry[3U]))
                                                     : 
                                                    ((8U 
                                                      & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                      ? 
                                                     ((4U 
                                                       & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                       ? 
                                                      vlSelf->top__DOT__u_axi_sniffer__DOT__read_entry[2U]
                                                       : 
                                                      vlSelf->top__DOT__u_axi_sniffer__DOT__read_entry[1U])
                                                      : 
                                                     ((4U 
                                                       & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                       ? 
                                                      vlSelf->top__DOT__u_axi_sniffer__DOT__read_entry[0U]
                                                       : (IData)(vlSelf->top__DOT__u_axi_sniffer__DOT__read_ptr))))
                                                    : 
                                                   ((0x10U 
                                                     & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                     ? 
                                                    ((8U 
                                                      & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                      ? 0xdeadbeefU
                                                      : 
                                                     ((4U 
                                                       & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                       ? vlSelf->top__DOT__u_axi_sniffer__DOT__ar_count
                                                       : vlSelf->top__DOT__u_axi_sniffer__DOT__aw_count))
                                                     : 
                                                    ((8U 
                                                      & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                      ? 
                                                     ((4U 
                                                       & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                       ? (IData)(vlSelf->top__DOT__u_axi_sniffer__DOT__entry_count)
                                                       : (IData)(vlSelf->top__DOT__u_axi_sniffer__DOT__write_ptr))
                                                      : 
                                                     ((4U 
                                                       & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))
                                                       ? 0U
                                                       : 
                                                      (((IData)(vlSelf->top__DOT__u_axi_sniffer__DOT__r_seen) 
                                                        << 0xcU) 
                                                       | (((IData)(vlSelf->top__DOT__u_axi_sniffer__DOT__ar_seen) 
                                                           << 0xbU) 
                                                          | (((IData)(vlSelf->top__DOT__u_axi_sniffer__DOT__b_seen) 
                                                              << 0xaU) 
                                                             | (((IData)(vlSelf->top__DOT__u_axi_sniffer__DOT__w_seen) 
                                                                 << 9U) 
                                                                | (((IData)(vlSelf->top__DOT__u_axi_sniffer__DOT__aw_seen) 
                                                                    << 8U) 
                                                                   | (((IData)(vlSelf->top__DOT__u_axi_sniffer__DOT__full) 
                                                                       << 1U) 
                                                                      | (IData)(vlSelf->top__DOT__u_axi_sniffer__DOT__running)))))))))))));
        if (vlSelf->top__DOT__u_axi_sniffer__DOT__ctrl_clear) {
            vlSelf->top__DOT__u_axi_sniffer__DOT__ar_seen = 0U;
            vlSelf->top__DOT__u_axi_sniffer__DOT__aw_seen = 0U;
            __Vdly__top__DOT__u_axi_sniffer__DOT__write_ptr = 0U;
            __Vdly__top__DOT__u_axi_sniffer__DOT__entry_count = 0U;
            __Vdly__top__DOT__u_axi_sniffer__DOT__full = 0U;
            vlSelf->top__DOT__u_axi_sniffer__DOT__w_seen = 0U;
            vlSelf->top__DOT__u_axi_sniffer__DOT__b_seen = 0U;
            vlSelf->top__DOT__u_axi_sniffer__DOT__r_seen = 0U;
        }
        if ((0U == (IData)(vlSelf->top__DOT__u_dma__DOT__u_h2c__DOT__state))) {
            if (((IData)(((1U == (3U & vlSelf->top__DOT__u_dma__DOT__ctrl_reg)) 
                          & (~ (IData)(vlSelf->top__DOT__u_dma__DOT__busy)))) 
                 & (0U < vlSelf->top__DOT__u_dma__DOT__length_reg))) {
                __Vdly__top__DOT__u_dma__DOT__u_h2c__DOT__cur_host 
                    = vlSelf->top__DOT__u_dma__DOT__host_addr;
                __Vdly__top__DOT__u_dma__DOT__u_h2c__DOT__cur_local 
                    = vlSelf->top__DOT__u_dma__DOT__local_addr;
                __Vdly__top__DOT__u_dma__DOT__u_h2c__DOT__bytes_left 
                    = vlSelf->top__DOT__u_dma__DOT__length_reg;
                __Vdly__top__DOT__u_dma__DOT__u_h2c__DOT__state = 1U;
            }
        } else if ((1U == (IData)(vlSelf->top__DOT__u_dma__DOT__u_h2c__DOT__state))) {
            __Vdly__top__DOT__u_dma__DOT__h2c_host_arvalid = 1U;
            vlSelf->top__DOT__u_dma__DOT__h2c_host_araddr 
                = vlSelf->top__DOT__u_dma__DOT__u_h2c__DOT__cur_host;
            if (((IData)(vlSelf->top__DOT__u_dma__DOT__h2c_host_arvalid) 
                 & (IData)(vlSelf->top__DOT__dma_host_arready))) {
                __Vdly__top__DOT__u_dma__DOT__h2c_host_arvalid = 0U;
                vlSelf->top__DOT__u_dma__DOT__h2c_host_rready = 1U;
                __Vdly__top__DOT__u_dma__DOT__u_h2c__DOT__state = 2U;
            }
        } else if ((2U == (IData)(vlSelf->top__DOT__u_dma__DOT__u_h2c__DOT__state))) {
            if (vlSelf->top__DOT__dma_host_rvalid) {
                vlSelf->top__DOT__u_dma__DOT__h2c_host_rready = 0U;
                vlSelf->top__DOT__u_dma__DOT__h2c_local_awaddr 
                    = vlSelf->top__DOT__u_dma__DOT__u_h2c__DOT__cur_local;
                vlSelf->top__DOT__u_dma__DOT__h2c_local_wdata 
                    = vlSelf->top__DOT__dma_host_rdata;
                vlSelf->top__DOT__u_dma__DOT__h2c_local_wstrb = 0xffU;
                __Vdly__top__DOT__u_dma__DOT__u_h2c__DOT__state = 3U;
            }
        } else if ((3U == (IData)(vlSelf->top__DOT__u_dma__DOT__u_h2c__DOT__state))) {
            __Vdly__top__DOT__u_dma__DOT__h2c_local_awvalid = 1U;
            __Vdly__top__DOT__u_dma__DOT__h2c_local_wvalid = 1U;
            if ((((((IData)(vlSelf->top__DOT__u_dma__DOT__h2c_local_awvalid) 
                    & (IData)(vlSelf->top__DOT__arb_owner)) 
                   & (IData)(vlSelf->top__DOT__ram_awready)) 
                  & (IData)(vlSelf->top__DOT__u_dma__DOT__h2c_local_wvalid)) 
                 & (IData)(vlSelf->top__DOT__ram_wready))) {
                __Vdly__top__DOT__u_dma__DOT__h2c_local_awvalid = 0U;
                __Vdly__top__DOT__u_dma__DOT__h2c_local_wvalid = 0U;
                vlSelf->top__DOT__u_dma__DOT__h2c_local_bready = 1U;
                __Vdly__top__DOT__u_dma__DOT__u_h2c__DOT__state = 4U;
            }
        } else if ((4U == (IData)(vlSelf->top__DOT__u_dma__DOT__u_h2c__DOT__state))) {
            if (vlSelf->top__DOT__dma_local_bvalid) {
                __Vdly__top__DOT__u_dma__DOT__u_h2c__DOT__cur_host 
                    = (8ULL + vlSelf->top__DOT__u_dma__DOT__u_h2c__DOT__cur_host);
                __Vdly__top__DOT__u_dma__DOT__u_h2c__DOT__cur_local 
                    = ((IData)(8U) + vlSelf->top__DOT__u_dma__DOT__u_h2c__DOT__cur_local);
                vlSelf->top__DOT__u_dma__DOT__h2c_local_bready = 0U;
                if ((8U >= vlSelf->top__DOT__u_dma__DOT__u_h2c__DOT__bytes_left)) {
                    __Vdly__top__DOT__u_dma__DOT__u_h2c__DOT__state = 5U;
                } else {
                    __Vdly__top__DOT__u_dma__DOT__u_h2c__DOT__bytes_left 
                        = (vlSelf->top__DOT__u_dma__DOT__u_h2c__DOT__bytes_left 
                           - (IData)(8U));
                    __Vdly__top__DOT__u_dma__DOT__u_h2c__DOT__state = 1U;
                }
            }
        } else if ((5U == (IData)(vlSelf->top__DOT__u_dma__DOT__u_h2c__DOT__state))) {
            __Vdly__top__DOT__u_dma__DOT__u_h2c__DOT__state = 0U;
        }
        if (((IData)(vlSelf->top__DOT__pcie_dbg_wen) 
             & (0xcU == (0xffcU & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))))) {
            vlSelf->top__DOT__u_sniffer__DOT__trigger_on_err 
                = (1U & (IData)((vlSelf->top__DOT__brg_wdata 
                                 >> 9U)));
            vlSelf->top__DOT__u_sniffer__DOT__trigger_type_en 
                = (1U & (IData)((vlSelf->top__DOT__brg_wdata 
                                 >> 8U)));
            vlSelf->top__DOT__u_sniffer__DOT__trigger_type 
                = (0xffU & (IData)(vlSelf->top__DOT__brg_wdata));
        }
        if (((IData)(vlSelf->top__DOT__pcie_dbg_wen) 
             & (8U == (0xffcU & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))))) {
            vlSelf->top__DOT__u_sniffer__DOT__capture_mode 
                = (3U & (IData)(vlSelf->top__DOT__brg_wdata));
            vlSelf->top__DOT__u_sniffer__DOT__filter_mode 
                = (3U & (IData)((vlSelf->top__DOT__brg_wdata 
                                 >> 4U)));
        }
        if (((IData)(vlSelf->top__DOT__pcie_dbg_wen) 
             & (0x30U == (0xffcU & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))))) {
            vlSelf->top__DOT__u_sniffer__DOT__read_ptr 
                = (0xffU & (IData)(vlSelf->top__DOT__brg_wdata));
        }
        if (((IData)(vlSelf->top__DOT__axi_dbg_wen) 
             & (0x20U == (0xfcU & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))))) {
            vlSelf->top__DOT__u_axi_sniffer__DOT__read_ptr 
                = (0x3fU & (IData)(vlSelf->top__DOT__brg_wdata));
        }
        __Vdly__top__DOT__u_axi_sniffer__DOT__timestamp 
            = (0x3fffffU & ((IData)(1U) + vlSelf->top__DOT__u_axi_sniffer__DOT__timestamp));
        if (vlSelf->top__DOT__u_axi_sniffer__DOT__aw_handshake) {
            __Vdly__top__DOT__u_axi_sniffer__DOT__aw_count 
                = ((IData)(1U) + vlSelf->top__DOT__u_axi_sniffer__DOT__aw_count);
            vlSelf->top__DOT__u_axi_sniffer__DOT__aw_seen = 1U;
            __Vdly__top__DOT__u_axi_sniffer__DOT__pending_awvalid = 1U;
        }
        if (((((IData)(vlSelf->top__DOT__u_axi_sniffer__DOT__running) 
               & (~ (IData)(vlSelf->top__DOT__u_axi_sniffer__DOT__full))) 
              & ((IData)(vlSelf->top__DOT__brg_wready) 
                 & (IData)(vlSelf->top__DOT__brg_wvalid))) 
             & (IData)(vlSelf->top__DOT__u_axi_sniffer__DOT__pending_awvalid))) {
            if ((0x40U > (IData)(vlSelf->top__DOT__u_axi_sniffer__DOT__entry_count))) {
                __Vdly__top__DOT__u_axi_sniffer__DOT__entry_count 
                    = (0x7fU & ((IData)(1U) + (IData)(vlSelf->top__DOT__u_axi_sniffer__DOT__entry_count)));
            }
            vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk1__DOT__entry[0U] 
                = vlSelf->top__DOT__u_axi_sniffer__DOT__pending_awaddr;
            vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk1__DOT__entry[1U] 
                = (IData)(vlSelf->top__DOT__brg_wdata);
            vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk1__DOT__entry[2U] 
                = (IData)((vlSelf->top__DOT__brg_wdata 
                           >> 0x20U));
            vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk1__DOT__entry[3U] 
                = ((0xfffffe00U & vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk1__DOT__entry[3U]) 
                   | (IData)(vlSelf->top__DOT__brg_wstrb));
            vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk1__DOT__entry[3U] 
                = ((0x1ffU & vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk1__DOT__entry[3U]) 
                   | (0xfffffe00U & (vlSelf->top__DOT__u_axi_sniffer__DOT__timestamp 
                                     << 0xaU)));
            __Vdly__top__DOT__u_axi_sniffer__DOT__pending_awvalid = 0U;
            vlSelf->top__DOT__u_axi_sniffer__DOT__w_seen = 1U;
            __Vdlyvval__top__DOT__u_axi_sniffer__DOT__trace_ram__v0[0U] 
                = vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk1__DOT__entry[0U];
            __Vdlyvval__top__DOT__u_axi_sniffer__DOT__trace_ram__v0[1U] 
                = vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk1__DOT__entry[1U];
            __Vdlyvval__top__DOT__u_axi_sniffer__DOT__trace_ram__v0[2U] 
                = vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk1__DOT__entry[2U];
            __Vdlyvval__top__DOT__u_axi_sniffer__DOT__trace_ram__v0[3U] 
                = vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk1__DOT__entry[3U];
            __Vdlyvset__top__DOT__u_axi_sniffer__DOT__trace_ram__v0 = 1U;
            __Vdlyvdim0__top__DOT__u_axi_sniffer__DOT__trace_ram__v0 
                = vlSelf->top__DOT__u_axi_sniffer__DOT__write_ptr;
            __Vdly__top__DOT__u_axi_sniffer__DOT__write_ptr 
                = (0x3fU & ((IData)(1U) + (IData)(vlSelf->top__DOT__u_axi_sniffer__DOT__write_ptr)));
            if ((0x3fU == (IData)(vlSelf->top__DOT__u_axi_sniffer__DOT__write_ptr))) {
                __Vdly__top__DOT__u_axi_sniffer__DOT__full = 1U;
            }
        }
        if (vlSelf->top__DOT__u_axi_sniffer__DOT__aw_handshake) {
            vlSelf->top__DOT__u_axi_sniffer__DOT__pending_awaddr 
                = vlSelf->top__DOT__brg_awaddr;
        }
        if ((((IData)(vlSelf->top__DOT__u_axi_sniffer__DOT__running) 
              & (~ (IData)(vlSelf->top__DOT__u_axi_sniffer__DOT__full))) 
             & ((IData)(vlSelf->top__DOT__brg_bready) 
                & (IData)(vlSelf->top__DOT__brg_bvalid)))) {
            if ((0x40U > (IData)(vlSelf->top__DOT__u_axi_sniffer__DOT__entry_count))) {
                __Vdly__top__DOT__u_axi_sniffer__DOT__entry_count 
                    = (0x7fU & ((IData)(1U) + (IData)(vlSelf->top__DOT__u_axi_sniffer__DOT__entry_count)));
            }
            vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk2__DOT__entry[0U] = 0U;
            vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk2__DOT__entry[1U] = 0U;
            vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk2__DOT__entry[2U] = 0U;
            vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk2__DOT__entry[3U] 
                = ((0xfffffe00U & vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk2__DOT__entry[3U]) 
                   | ((IData)(vlSelf->top__DOT__dma_s_bvalid)
                       ? (IData)(vlSelf->top__DOT__dma_s_bresp)
                       : (IData)(vlSelf->top__DOT__ram_bresp)));
            vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk2__DOT__entry[3U] 
                = ((0x1ffU & vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk2__DOT__entry[3U]) 
                   | (0xfffffe00U & (0x200U | (vlSelf->top__DOT__u_axi_sniffer__DOT__timestamp 
                                               << 0xaU))));
            vlSelf->top__DOT__u_axi_sniffer__DOT__b_seen = 1U;
            __Vdlyvval__top__DOT__u_axi_sniffer__DOT__trace_ram__v1[0U] 
                = vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk2__DOT__entry[0U];
            __Vdlyvval__top__DOT__u_axi_sniffer__DOT__trace_ram__v1[1U] 
                = vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk2__DOT__entry[1U];
            __Vdlyvval__top__DOT__u_axi_sniffer__DOT__trace_ram__v1[2U] 
                = vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk2__DOT__entry[2U];
            __Vdlyvval__top__DOT__u_axi_sniffer__DOT__trace_ram__v1[3U] 
                = vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk2__DOT__entry[3U];
            __Vdlyvset__top__DOT__u_axi_sniffer__DOT__trace_ram__v1 = 1U;
            __Vdlyvdim0__top__DOT__u_axi_sniffer__DOT__trace_ram__v1 
                = vlSelf->top__DOT__u_axi_sniffer__DOT__write_ptr;
            __Vdly__top__DOT__u_axi_sniffer__DOT__write_ptr 
                = (0x3fU & ((IData)(1U) + (IData)(vlSelf->top__DOT__u_axi_sniffer__DOT__write_ptr)));
            if ((0x3fU == (IData)(vlSelf->top__DOT__u_axi_sniffer__DOT__write_ptr))) {
                __Vdly__top__DOT__u_axi_sniffer__DOT__full = 1U;
            }
        }
        if (vlSelf->top__DOT__u_axi_sniffer__DOT__ar_handshake) {
            __Vdly__top__DOT__u_axi_sniffer__DOT__ar_count 
                = ((IData)(1U) + vlSelf->top__DOT__u_axi_sniffer__DOT__ar_count);
            vlSelf->top__DOT__u_axi_sniffer__DOT__ar_seen = 1U;
            if (((IData)(vlSelf->top__DOT__u_axi_sniffer__DOT__running) 
                 & (~ (IData)(vlSelf->top__DOT__u_axi_sniffer__DOT__full)))) {
                if ((0x40U > (IData)(vlSelf->top__DOT__u_axi_sniffer__DOT__entry_count))) {
                    __Vdly__top__DOT__u_axi_sniffer__DOT__entry_count 
                        = (0x7fU & ((IData)(1U) + (IData)(vlSelf->top__DOT__u_axi_sniffer__DOT__entry_count)));
                }
                vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk3__DOT__entry[0U] 
                    = vlSelf->top__DOT__brg_araddr;
                vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk3__DOT__entry[1U] = 0U;
                vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk3__DOT__entry[2U] = 0U;
                vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk3__DOT__entry[3U] 
                    = (0x100U | (0xfffffc00U & vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk3__DOT__entry[3U]));
                vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk3__DOT__entry[3U] 
                    = ((0x3ffU & vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk3__DOT__entry[3U]) 
                       | (vlSelf->top__DOT__u_axi_sniffer__DOT__timestamp 
                          << 0xaU));
                __Vdlyvval__top__DOT__u_axi_sniffer__DOT__trace_ram__v2[0U] 
                    = vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk3__DOT__entry[0U];
                __Vdlyvval__top__DOT__u_axi_sniffer__DOT__trace_ram__v2[1U] 
                    = vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk3__DOT__entry[1U];
                __Vdlyvval__top__DOT__u_axi_sniffer__DOT__trace_ram__v2[2U] 
                    = vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk3__DOT__entry[2U];
                __Vdlyvval__top__DOT__u_axi_sniffer__DOT__trace_ram__v2[3U] 
                    = vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk3__DOT__entry[3U];
                __Vdlyvset__top__DOT__u_axi_sniffer__DOT__trace_ram__v2 = 1U;
                __Vdlyvdim0__top__DOT__u_axi_sniffer__DOT__trace_ram__v2 
                    = vlSelf->top__DOT__u_axi_sniffer__DOT__write_ptr;
                __Vdly__top__DOT__u_axi_sniffer__DOT__write_ptr 
                    = (0x3fU & ((IData)(1U) + (IData)(vlSelf->top__DOT__u_axi_sniffer__DOT__write_ptr)));
                if ((0x3fU == (IData)(vlSelf->top__DOT__u_axi_sniffer__DOT__write_ptr))) {
                    __Vdly__top__DOT__u_axi_sniffer__DOT__full = 1U;
                }
            }
        }
        if ((((IData)(vlSelf->top__DOT__u_axi_sniffer__DOT__running) 
              & (~ (IData)(vlSelf->top__DOT__u_axi_sniffer__DOT__full))) 
             & ((IData)(vlSelf->top__DOT__brg_rready) 
                & (IData)(vlSelf->top__DOT__brg_rvalid_mux)))) {
            if ((0x40U > (IData)(vlSelf->top__DOT__u_axi_sniffer__DOT__entry_count))) {
                __Vdly__top__DOT__u_axi_sniffer__DOT__entry_count 
                    = (0x7fU & ((IData)(1U) + (IData)(vlSelf->top__DOT__u_axi_sniffer__DOT__entry_count)));
            }
            vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk4__DOT__entry[0U] = 0U;
            vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk4__DOT__entry[1U] 
                = (IData)(vlSelf->top__DOT__brg_rdata_mux);
            vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk4__DOT__entry[2U] 
                = (IData)((vlSelf->top__DOT__brg_rdata_mux 
                           >> 0x20U));
            vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk4__DOT__entry[3U] 
                = (0x100U | ((0xfffffe00U & vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk4__DOT__entry[3U]) 
                             | (IData)(vlSelf->top__DOT__brg_rresp_mux)));
            vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk4__DOT__entry[3U] 
                = ((0x1ffU & vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk4__DOT__entry[3U]) 
                   | (0xfffffe00U & (0x200U | (vlSelf->top__DOT__u_axi_sniffer__DOT__timestamp 
                                               << 0xaU))));
            vlSelf->top__DOT__u_axi_sniffer__DOT__r_seen = 1U;
            __Vdlyvval__top__DOT__u_axi_sniffer__DOT__trace_ram__v3[0U] 
                = vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk4__DOT__entry[0U];
            __Vdlyvval__top__DOT__u_axi_sniffer__DOT__trace_ram__v3[1U] 
                = vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk4__DOT__entry[1U];
            __Vdlyvval__top__DOT__u_axi_sniffer__DOT__trace_ram__v3[2U] 
                = vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk4__DOT__entry[2U];
            __Vdlyvval__top__DOT__u_axi_sniffer__DOT__trace_ram__v3[3U] 
                = vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk4__DOT__entry[3U];
            __Vdlyvset__top__DOT__u_axi_sniffer__DOT__trace_ram__v3 = 1U;
            __Vdlyvdim0__top__DOT__u_axi_sniffer__DOT__trace_ram__v3 
                = vlSelf->top__DOT__u_axi_sniffer__DOT__write_ptr;
            __Vdly__top__DOT__u_axi_sniffer__DOT__write_ptr 
                = (0x3fU & ((IData)(1U) + (IData)(vlSelf->top__DOT__u_axi_sniffer__DOT__write_ptr)));
            if ((0x3fU == (IData)(vlSelf->top__DOT__u_axi_sniffer__DOT__write_ptr))) {
                __Vdly__top__DOT__u_axi_sniffer__DOT__full = 1U;
            }
        }
        if (((IData)(vlSelf->top__DOT__u_axi_sniffer__DOT____VdfgRegularize_h1732209f_5_0) 
             & (IData)(vlSelf->top__DOT__brg_wdata))) {
            vlSelf->top__DOT__u_axi_sniffer__DOT__running = 1U;
        }
        if (((IData)(vlSelf->top__DOT__u_axi_sniffer__DOT____VdfgRegularize_h1732209f_5_0) 
             & (IData)((vlSelf->top__DOT__brg_wdata 
                        >> 1U)))) {
            vlSelf->top__DOT__u_axi_sniffer__DOT__running = 0U;
        }
        vlSelf->top__DOT__msix_ready_i = 0U;
        vlSelf->top__DOT__u_bridge__DOT__host_mrd_ready_pulse = 0U;
        __Vdly__top__DOT__u_bridge__DOT__host_mwr_ready_pulse = 0U;
        if (((((((((0U == (IData)(vlSelf->top__DOT__u_bridge__DOT__tx_state)) 
                   | (1U == (IData)(vlSelf->top__DOT__u_bridge__DOT__tx_state))) 
                  | (2U == (IData)(vlSelf->top__DOT__u_bridge__DOT__tx_state))) 
                 | (3U == (IData)(vlSelf->top__DOT__u_bridge__DOT__tx_state))) 
                | (4U == (IData)(vlSelf->top__DOT__u_bridge__DOT__tx_state))) 
               | (5U == (IData)(vlSelf->top__DOT__u_bridge__DOT__tx_state))) 
              | (6U == (IData)(vlSelf->top__DOT__u_bridge__DOT__tx_state))) 
             | (7U == (IData)(vlSelf->top__DOT__u_bridge__DOT__tx_state)))) {
            if ((0U == (IData)(vlSelf->top__DOT__u_bridge__DOT__tx_state))) {
                vlSelf->tx_st_hvalid = 0U;
                vlSelf->tx_st_dvalid = 0U;
                vlSelf->tx_st_sop = 0U;
                vlSelf->tx_st_eop = 0U;
                if (((IData)(vlSelf->top__DOT__u_bridge__DOT__rx_is_mwr) 
                     & (0U == (IData)(vlSelf->rx_st_bar)))) {
                    vlSelf->top__DOT__brg_awaddr = (IData)(vlSelf->top__DOT__u_bridge__DOT__rx_addr);
                    __Vdly__top__DOT__brg_awvalid = 1U;
                    vlSelf->top__DOT__brg_wdata = (
                                                   ((QData)((IData)(
                                                                    vlSelf->rx_st_data[1U])) 
                                                    << 0x20U) 
                                                   | (QData)((IData)(
                                                                     vlSelf->rx_st_data[0U])));
                    vlSelf->top__DOT__brg_wstrb = (
                                                   ((IData)(vlSelf->top__DOT__u_bridge__DOT__rx_lbe) 
                                                    << 4U) 
                                                   | (IData)(vlSelf->top__DOT__u_bridge__DOT__rx_fbe));
                    __Vdly__top__DOT__brg_wvalid = 1U;
                    __Vdly__top__DOT__u_bridge__DOT__tx_state = 1U;
                } else if (((IData)(vlSelf->top__DOT__u_bridge__DOT__rx_is_mrd) 
                            & (0U == (IData)(vlSelf->rx_st_bar)))) {
                    __Vdly__top__DOT__u_bridge__DOT__bar_req_rid 
                        = vlSelf->top__DOT__u_bridge__DOT__rx_rid;
                    __Vdly__top__DOT__u_bridge__DOT__bar_req_tag 
                        = vlSelf->top__DOT__u_bridge__DOT__rx_tag;
                    __Vdly__top__DOT__u_bridge__DOT__bar_req_lower_addr 
                        = (0x7fU & (IData)(vlSelf->top__DOT__u_bridge__DOT__rx_addr));
                    __Vdly__top__DOT__u_bridge__DOT__bar_req_addr 
                        = (IData)(vlSelf->top__DOT__u_bridge__DOT__rx_addr);
                    __Vdly__top__DOT__u_bridge__DOT__bar_dw_remaining 
                        = ((8U < (IData)(vlSelf->top__DOT__u_bridge__DOT__rx_len))
                            ? 8U : (IData)(vlSelf->top__DOT__u_bridge__DOT__rx_len));
                    __Vdly__top__DOT__u_bridge__DOT__bar_dw_count = 0U;
                    __Vdly__top__DOT__u_bridge__DOT__bar_cpl_buffer[0U] 
                        = Vtop__ConstPool__CONST_h9e67c271_0[0U];
                    __Vdly__top__DOT__u_bridge__DOT__bar_cpl_buffer[1U] 
                        = Vtop__ConstPool__CONST_h9e67c271_0[1U];
                    __Vdly__top__DOT__u_bridge__DOT__bar_cpl_buffer[2U] 
                        = Vtop__ConstPool__CONST_h9e67c271_0[2U];
                    __Vdly__top__DOT__u_bridge__DOT__bar_cpl_buffer[3U] 
                        = Vtop__ConstPool__CONST_h9e67c271_0[3U];
                    __Vdly__top__DOT__u_bridge__DOT__bar_cpl_buffer[4U] 
                        = Vtop__ConstPool__CONST_h9e67c271_0[4U];
                    __Vdly__top__DOT__u_bridge__DOT__bar_cpl_buffer[5U] 
                        = Vtop__ConstPool__CONST_h9e67c271_0[5U];
                    __Vdly__top__DOT__u_bridge__DOT__bar_cpl_buffer[6U] 
                        = Vtop__ConstPool__CONST_h9e67c271_0[6U];
                    __Vdly__top__DOT__u_bridge__DOT__bar_cpl_buffer[7U] 
                        = Vtop__ConstPool__CONST_h9e67c271_0[7U];
                    vlSelf->top__DOT__brg_araddr = (IData)(vlSelf->top__DOT__u_bridge__DOT__rx_addr);
                    vlSelf->top__DOT__brg_arvalid = 1U;
                    __Vdly__top__DOT__u_bridge__DOT__tx_state = 3U;
                } else if (vlSelf->top__DOT__u_bridge__DOT__host_mrd_pending) {
                    __Vdly__top__DOT__u_bridge__DOT__tx_state = 6U;
                } else if (vlSelf->top__DOT__u_bridge__DOT__host_mwr_pending) {
                    __Vdly__top__DOT__u_bridge__DOT__tx_state = 7U;
                } else if (vlSelf->top__DOT__msix_valid_i) {
                    __Vdly__top__DOT__u_bridge__DOT__tx_state = 8U;
                }
            } else if ((1U == (IData)(vlSelf->top__DOT__u_bridge__DOT__tx_state))) {
                if ((1U & (((IData)(vlSelf->top__DOT__brg_awready) 
                            | (~ (IData)(vlSelf->top__DOT__brg_awvalid))) 
                           & ((IData)(vlSelf->top__DOT__brg_wready) 
                              | (~ (IData)(vlSelf->top__DOT__brg_wvalid)))))) {
                    vlSelf->top__DOT__brg_bready = 1U;
                    __Vdly__top__DOT__u_bridge__DOT__tx_state = 2U;
                }
                if (vlSelf->top__DOT__brg_awready) {
                    __Vdly__top__DOT__brg_awvalid = 0U;
                }
                if (vlSelf->top__DOT__brg_wready) {
                    __Vdly__top__DOT__brg_wvalid = 0U;
                }
            } else if ((2U == (IData)(vlSelf->top__DOT__u_bridge__DOT__tx_state))) {
                if (vlSelf->top__DOT__brg_bvalid) {
                    vlSelf->top__DOT__brg_bready = 0U;
                    __Vdly__top__DOT__u_bridge__DOT__tx_state = 0U;
                }
            } else if ((3U == (IData)(vlSelf->top__DOT__u_bridge__DOT__tx_state))) {
                if (vlSelf->top__DOT__brg_arready) {
                    vlSelf->top__DOT__brg_arvalid = 0U;
                    vlSelf->top__DOT__brg_rready = 1U;
                    __Vdly__top__DOT__u_bridge__DOT__tx_state = 4U;
                }
            } else if ((4U == (IData)(vlSelf->top__DOT__u_bridge__DOT__tx_state))) {
                if (vlSelf->top__DOT__brg_rvalid_mux) {
                    vlSelf->top__DOT__brg_rready = 0U;
                    __Vdly__top__DOT__u_bridge__DOT__bar_cpl_status 
                        = vlSelf->top__DOT__brg_rresp_mux;
                    if ((4U & (IData)(vlSelf->top__DOT__u_bridge__DOT__bar_dw_count))) {
                        if ((2U & (IData)(vlSelf->top__DOT__u_bridge__DOT__bar_dw_count))) {
                            __Vdly__top__DOT__u_bridge__DOT__bar_cpl_buffer[6U] 
                                = (IData)(vlSelf->top__DOT__brg_rdata_mux);
                            __Vdly__top__DOT__u_bridge__DOT__bar_cpl_buffer[7U] 
                                = (IData)((vlSelf->top__DOT__brg_rdata_mux 
                                           >> 0x20U));
                        } else {
                            __Vdly__top__DOT__u_bridge__DOT__bar_cpl_buffer[4U] 
                                = (IData)(vlSelf->top__DOT__brg_rdata_mux);
                            __Vdly__top__DOT__u_bridge__DOT__bar_cpl_buffer[5U] 
                                = (IData)((vlSelf->top__DOT__brg_rdata_mux 
                                           >> 0x20U));
                        }
                    } else if ((2U & (IData)(vlSelf->top__DOT__u_bridge__DOT__bar_dw_count))) {
                        __Vdly__top__DOT__u_bridge__DOT__bar_cpl_buffer[2U] 
                            = (IData)(vlSelf->top__DOT__brg_rdata_mux);
                        __Vdly__top__DOT__u_bridge__DOT__bar_cpl_buffer[3U] 
                            = (IData)((vlSelf->top__DOT__brg_rdata_mux 
                                       >> 0x20U));
                    } else {
                        __Vdly__top__DOT__u_bridge__DOT__bar_cpl_buffer[0U] 
                            = (IData)(vlSelf->top__DOT__brg_rdata_mux);
                        __Vdly__top__DOT__u_bridge__DOT__bar_cpl_buffer[1U] 
                            = (IData)((vlSelf->top__DOT__brg_rdata_mux 
                                       >> 0x20U));
                    }
                    if ((2U < (IData)(vlSelf->top__DOT__u_bridge__DOT__bar_dw_remaining))) {
                        __Vdly__top__DOT__u_bridge__DOT__bar_dw_remaining 
                            = (0x3ffU & ((IData)(vlSelf->top__DOT__u_bridge__DOT__bar_dw_remaining) 
                                         - (IData)(2U)));
                        vlSelf->top__DOT__brg_araddr 
                            = ((IData)(8U) + vlSelf->top__DOT__u_bridge__DOT__bar_req_addr);
                        vlSelf->top__DOT__brg_arvalid = 1U;
                        __Vdly__top__DOT__u_bridge__DOT__tx_state = 3U;
                    } else {
                        __Vdly__top__DOT__u_bridge__DOT__bar_dw_remaining = 0U;
                        __Vdly__top__DOT__u_bridge__DOT__tx_state = 5U;
                    }
                    __Vdly__top__DOT__u_bridge__DOT__bar_dw_count 
                        = (0xfU & ((IData)(2U) + (IData)(vlSelf->top__DOT__u_bridge__DOT__bar_dw_count)));
                    __Vdly__top__DOT__u_bridge__DOT__bar_req_addr 
                        = ((IData)(8U) + vlSelf->top__DOT__u_bridge__DOT__bar_req_addr);
                }
            } else if ((5U == (IData)(vlSelf->top__DOT__u_bridge__DOT__tx_state))) {
                vlSelf->tx_st_sop = 1U;
                vlSelf->tx_st_eop = 1U;
                vlSelf->tx_st_hvalid = 1U;
                vlSelf->tx_st_dvalid = 1U;
                vlSelf->top__DOT__u_bridge__DOT__tx_hdr_r[0U] 
                    = (IData)(((QData)((IData)((((IData)(vlSelf->top__DOT__u_bridge__DOT__bar_req_rid) 
                                                 << 0x10U) 
                                                | (((IData)(vlSelf->top__DOT__u_bridge__DOT__bar_req_tag) 
                                                    << 8U) 
                                                   | (IData)(vlSelf->top__DOT__u_bridge__DOT__bar_req_lower_addr))))) 
                               << 0x20U));
                vlSelf->top__DOT__u_bridge__DOT__tx_hdr_r[1U] 
                    = (IData)((((QData)((IData)((((IData)(vlSelf->top__DOT__u_bridge__DOT__bar_req_rid) 
                                                  << 0x10U) 
                                                 | (((IData)(vlSelf->top__DOT__u_bridge__DOT__bar_req_tag) 
                                                     << 8U) 
                                                    | (IData)(vlSelf->top__DOT__u_bridge__DOT__bar_req_lower_addr))))) 
                                << 0x20U) >> 0x20U));
                vlSelf->top__DOT__u_bridge__DOT__tx_hdr_r[2U] 
                    = (IData)((((QData)((IData)((0x4a000000U 
                                                 | (IData)(vlSelf->top__DOT__u_bridge__DOT__bar_dw_count)))) 
                                << 0x1cU) | (QData)((IData)(
                                                            (((IData)(vlSelf->top__DOT__u_bridge__DOT__completer_id) 
                                                              << 0xcU) 
                                                             | ((((0U 
                                                                   == (IData)(vlSelf->top__DOT__u_bridge__DOT__bar_cpl_status))
                                                                   ? 0U
                                                                   : 1U) 
                                                                 << 9U) 
                                                                | ((IData)(vlSelf->top__DOT__u_bridge__DOT__bar_dw_count) 
                                                                   << 2U)))))));
                vlSelf->top__DOT__u_bridge__DOT__tx_hdr_r[3U] 
                    = (IData)(((((QData)((IData)((0x4a000000U 
                                                  | (IData)(vlSelf->top__DOT__u_bridge__DOT__bar_dw_count)))) 
                                 << 0x1cU) | (QData)((IData)(
                                                             (((IData)(vlSelf->top__DOT__u_bridge__DOT__completer_id) 
                                                               << 0xcU) 
                                                              | ((((0U 
                                                                    == (IData)(vlSelf->top__DOT__u_bridge__DOT__bar_cpl_status))
                                                                    ? 0U
                                                                    : 1U) 
                                                                  << 9U) 
                                                                 | ((IData)(vlSelf->top__DOT__u_bridge__DOT__bar_dw_count) 
                                                                    << 2U)))))) 
                               >> 0x20U));
                vlSelf->top__DOT__u_bridge__DOT__tx_data_r[0U] 
                    = vlSelf->top__DOT__u_bridge__DOT__bar_cpl_buffer[0U];
                vlSelf->top__DOT__u_bridge__DOT__tx_data_r[1U] 
                    = vlSelf->top__DOT__u_bridge__DOT__bar_cpl_buffer[1U];
                vlSelf->top__DOT__u_bridge__DOT__tx_data_r[2U] 
                    = vlSelf->top__DOT__u_bridge__DOT__bar_cpl_buffer[2U];
                vlSelf->top__DOT__u_bridge__DOT__tx_data_r[3U] 
                    = vlSelf->top__DOT__u_bridge__DOT__bar_cpl_buffer[3U];
                vlSelf->top__DOT__u_bridge__DOT__tx_data_r[4U] 
                    = vlSelf->top__DOT__u_bridge__DOT__bar_cpl_buffer[4U];
                vlSelf->top__DOT__u_bridge__DOT__tx_data_r[5U] 
                    = vlSelf->top__DOT__u_bridge__DOT__bar_cpl_buffer[5U];
                vlSelf->top__DOT__u_bridge__DOT__tx_data_r[6U] 
                    = vlSelf->top__DOT__u_bridge__DOT__bar_cpl_buffer[6U];
                vlSelf->top__DOT__u_bridge__DOT__tx_data_r[7U] 
                    = vlSelf->top__DOT__u_bridge__DOT__bar_cpl_buffer[7U];
                __Vdly__top__DOT__u_bridge__DOT__tx_state = 9U;
            } else if ((6U == (IData)(vlSelf->top__DOT__u_bridge__DOT__tx_state))) {
                vlSelf->tx_st_sop = 1U;
                vlSelf->tx_st_eop = 1U;
                vlSelf->tx_st_hvalid = 1U;
                vlSelf->tx_st_dvalid = 0U;
                vlSelf->top__DOT__u_bridge__DOT__host_mrd_ready_pulse = 1U;
                vlSelf->top__DOT__u_bridge__DOT__tx_hdr_r[0U] 
                    = ((IData)((vlSelf->top__DOT__u_bridge__DOT__host_mrd_addr 
                                >> 2U)) << 2U);
                vlSelf->top__DOT__u_bridge__DOT__tx_hdr_r[1U] 
                    = (IData)((vlSelf->top__DOT__u_bridge__DOT__host_mrd_addr 
                               >> 0x20U));
                vlSelf->top__DOT__u_bridge__DOT__tx_hdr_r[2U] 
                    = (IData)((0x2000000200000000ULL 
                               | (QData)((IData)((0xffU 
                                                  | (((IData)(vlSelf->top__DOT__u_bridge__DOT__completer_id) 
                                                      << 0x10U) 
                                                     | ((IData)(vlSelf->top__DOT__u_bridge__DOT__host_mrd_tag) 
                                                        << 8U)))))));
                vlSelf->top__DOT__u_bridge__DOT__tx_hdr_r[3U] 
                    = (IData)(((0x2000000200000000ULL 
                                | (QData)((IData)((0xffU 
                                                   | (((IData)(vlSelf->top__DOT__u_bridge__DOT__completer_id) 
                                                       << 0x10U) 
                                                      | ((IData)(vlSelf->top__DOT__u_bridge__DOT__host_mrd_tag) 
                                                         << 8U)))))) 
                               >> 0x20U));
                vlSelf->top__DOT__u_bridge__DOT__tx_data_r[0U] 
                    = Vtop__ConstPool__CONST_h9e67c271_0[0U];
                vlSelf->top__DOT__u_bridge__DOT__tx_data_r[1U] 
                    = Vtop__ConstPool__CONST_h9e67c271_0[1U];
                vlSelf->top__DOT__u_bridge__DOT__tx_data_r[2U] 
                    = Vtop__ConstPool__CONST_h9e67c271_0[2U];
                vlSelf->top__DOT__u_bridge__DOT__tx_data_r[3U] 
                    = Vtop__ConstPool__CONST_h9e67c271_0[3U];
                vlSelf->top__DOT__u_bridge__DOT__tx_data_r[4U] 
                    = Vtop__ConstPool__CONST_h9e67c271_0[4U];
                vlSelf->top__DOT__u_bridge__DOT__tx_data_r[5U] 
                    = Vtop__ConstPool__CONST_h9e67c271_0[5U];
                vlSelf->top__DOT__u_bridge__DOT__tx_data_r[6U] 
                    = Vtop__ConstPool__CONST_h9e67c271_0[6U];
                vlSelf->top__DOT__u_bridge__DOT__tx_data_r[7U] 
                    = Vtop__ConstPool__CONST_h9e67c271_0[7U];
                __Vdly__top__DOT__u_bridge__DOT__tx_state = 9U;
            } else {
                vlSelf->tx_st_sop = 1U;
                vlSelf->tx_st_eop = 1U;
                vlSelf->tx_st_hvalid = 1U;
                vlSelf->tx_st_dvalid = 1U;
                __Vdly__top__DOT__u_bridge__DOT__host_mwr_ready_pulse = 1U;
                vlSelf->top__DOT__u_bridge__DOT__tx_hdr_r[0U] 
                    = ((IData)((vlSelf->top__DOT__u_bridge__DOT__host_mwr_addr 
                                >> 2U)) << 2U);
                vlSelf->top__DOT__u_bridge__DOT__tx_hdr_r[1U] 
                    = (IData)((vlSelf->top__DOT__u_bridge__DOT__host_mwr_addr 
                               >> 0x20U));
                vlSelf->top__DOT__u_bridge__DOT__tx_hdr_r[2U] 
                    = (IData)((0x6000000200000000ULL 
                               | (QData)((IData)((0xffU 
                                                  | ((IData)(vlSelf->top__DOT__u_bridge__DOT__completer_id) 
                                                     << 0x10U))))));
                vlSelf->top__DOT__u_bridge__DOT__tx_hdr_r[3U] 
                    = (IData)(((0x6000000200000000ULL 
                                | (QData)((IData)((0xffU 
                                                   | ((IData)(vlSelf->top__DOT__u_bridge__DOT__completer_id) 
                                                      << 0x10U))))) 
                               >> 0x20U));
                vlSelf->top__DOT__u_bridge__DOT__tx_data_r[0U] 
                    = (IData)(vlSelf->top__DOT__u_bridge__DOT__host_mwr_data);
                vlSelf->top__DOT__u_bridge__DOT__tx_data_r[1U] 
                    = (IData)((vlSelf->top__DOT__u_bridge__DOT__host_mwr_data 
                               >> 0x20U));
                vlSelf->top__DOT__u_bridge__DOT__tx_data_r[2U] = 0U;
                vlSelf->top__DOT__u_bridge__DOT__tx_data_r[3U] = 0U;
                vlSelf->top__DOT__u_bridge__DOT__tx_data_r[4U] = 0U;
                vlSelf->top__DOT__u_bridge__DOT__tx_data_r[5U] = 0U;
                vlSelf->top__DOT__u_bridge__DOT__tx_data_r[6U] = 0U;
                vlSelf->top__DOT__u_bridge__DOT__tx_data_r[7U] = 0U;
                __Vdly__top__DOT__u_bridge__DOT__tx_state = 9U;
            }
        } else if ((8U == (IData)(vlSelf->top__DOT__u_bridge__DOT__tx_state))) {
            vlSelf->tx_st_sop = 1U;
            vlSelf->tx_st_eop = 1U;
            vlSelf->tx_st_hvalid = 1U;
            vlSelf->tx_st_dvalid = 1U;
            vlSelf->top__DOT__msix_ready_i = 1U;
            vlSelf->top__DOT__u_bridge__DOT__tx_hdr_r[0U] 
                = ((IData)((vlSelf->top__DOT__msix_addr_reg 
                            >> 2U)) << 2U);
            vlSelf->top__DOT__u_bridge__DOT__tx_hdr_r[1U] 
                = (IData)((vlSelf->top__DOT__msix_addr_reg 
                           >> 0x20U));
            vlSelf->top__DOT__u_bridge__DOT__tx_hdr_r[2U] 
                = (IData)((0x6000000100000000ULL | (QData)((IData)(
                                                                   (0xffU 
                                                                    | ((IData)(vlSelf->top__DOT__u_bridge__DOT__completer_id) 
                                                                       << 0x10U))))));
            vlSelf->top__DOT__u_bridge__DOT__tx_hdr_r[3U] 
                = (IData)(((0x6000000100000000ULL | (QData)((IData)(
                                                                    (0xffU 
                                                                     | ((IData)(vlSelf->top__DOT__u_bridge__DOT__completer_id) 
                                                                        << 0x10U))))) 
                           >> 0x20U));
            vlSelf->top__DOT__u_bridge__DOT__tx_data_r[0U] 
                = vlSelf->top__DOT__msix_data_reg;
            vlSelf->top__DOT__u_bridge__DOT__tx_data_r[1U] = 0U;
            vlSelf->top__DOT__u_bridge__DOT__tx_data_r[2U] = 0U;
            vlSelf->top__DOT__u_bridge__DOT__tx_data_r[3U] = 0U;
            vlSelf->top__DOT__u_bridge__DOT__tx_data_r[4U] = 0U;
            vlSelf->top__DOT__u_bridge__DOT__tx_data_r[5U] = 0U;
            vlSelf->top__DOT__u_bridge__DOT__tx_data_r[6U] = 0U;
            vlSelf->top__DOT__u_bridge__DOT__tx_data_r[7U] = 0U;
            __Vdly__top__DOT__u_bridge__DOT__tx_state = 9U;
        } else if ((9U == (IData)(vlSelf->top__DOT__u_bridge__DOT__tx_state))) {
            if (vlSelf->tx_st_ready) {
                vlSelf->tx_st_hvalid = 0U;
                vlSelf->tx_st_dvalid = 0U;
                vlSelf->tx_st_sop = 0U;
                vlSelf->tx_st_eop = 0U;
                __Vdly__top__DOT__u_bridge__DOT__tx_state = 0U;
            }
        }
        if (vlSelf->link_up) {
            if ((((~ (IData)(vlSelf->top__DOT__u_bridge__DOT__completer_id_valid)) 
                  & (IData)(vlSelf->rx_st_hvalid)) 
                 & (IData)(vlSelf->rx_st_sop))) {
                vlSelf->top__DOT__u_bridge__DOT__completer_id 
                    = (0xff00U & (((IData)(1U) + ((IData)(vlSelf->top__DOT__u_bridge__DOT__rx_rid) 
                                                  >> 8U)) 
                                  << 8U));
                vlSelf->top__DOT__u_bridge__DOT__completer_id_valid = 1U;
            }
        } else {
            vlSelf->top__DOT__u_bridge__DOT__completer_id_valid = 0U;
        }
        if (((((IData)(vlSelf->top__DOT__u_dma__DOT__c2h_host_awvalid) 
               & (IData)(vlSelf->top__DOT__u_dma__DOT__c2h_host_wvalid)) 
              & (IData)(vlSelf->top__DOT__dma_host_awready)) 
             & (~ (IData)(vlSelf->top__DOT__u_bridge__DOT__host_mwr_pending)))) {
            vlSelf->top__DOT__u_bridge__DOT__host_mwr_addr 
                = vlSelf->top__DOT__u_dma__DOT__c2h_host_awaddr;
            vlSelf->top__DOT__u_bridge__DOT__host_mwr_data 
                = vlSelf->top__DOT__u_dma__DOT__c2h_host_wdata;
            __Vdly__top__DOT__u_bridge__DOT__host_mwr_pending = 1U;
            __Vdly__top__DOT__dma_host_awready = 0U;
            __Vdly__top__DOT__dma_host_wready = 0U;
        }
        if (((IData)(vlSelf->top__DOT__u_bridge__DOT__host_mwr_pending) 
             & (IData)(vlSelf->top__DOT__u_bridge__DOT__host_mwr_ready_pulse))) {
            __Vdly__top__DOT__u_bridge__DOT__host_mwr_pending = 0U;
            __Vdly__top__DOT__dma_host_bvalid = 1U;
        }
        if (((IData)(vlSelf->top__DOT__dma_host_bvalid) 
             & (IData)(vlSelf->top__DOT__u_dma__DOT__c2h_host_bready))) {
            __Vdly__top__DOT__dma_host_bvalid = 0U;
            __Vdly__top__DOT__dma_host_awready = 1U;
            __Vdly__top__DOT__dma_host_wready = 1U;
        }
        if ((0U == (IData)(vlSelf->top__DOT__u_dma__DOT__u_c2h__DOT__state))) {
            if (((vlSelf->top__DOT__u_dma__DOT__ctrl_reg 
                  & ((~ (IData)(vlSelf->top__DOT__u_dma__DOT__busy)) 
                     & (vlSelf->top__DOT__u_dma__DOT__ctrl_reg 
                        >> 1U))) & (0U < vlSelf->top__DOT__u_dma__DOT__length_reg))) {
                __Vdly__top__DOT__u_dma__DOT__u_c2h__DOT__cur_host 
                    = vlSelf->top__DOT__u_dma__DOT__host_addr;
                __Vdly__top__DOT__u_dma__DOT__u_c2h__DOT__cur_local 
                    = vlSelf->top__DOT__u_dma__DOT__local_addr;
                __Vdly__top__DOT__u_dma__DOT__u_c2h__DOT__bytes_left 
                    = vlSelf->top__DOT__u_dma__DOT__length_reg;
                __Vdly__top__DOT__u_dma__DOT__u_c2h__DOT__state = 1U;
            }
        } else if ((1U == (IData)(vlSelf->top__DOT__u_dma__DOT__u_c2h__DOT__state))) {
            __Vdly__top__DOT__u_dma__DOT__c2h_local_arvalid = 1U;
            vlSelf->top__DOT__u_dma__DOT__c2h_local_araddr 
                = vlSelf->top__DOT__u_dma__DOT__u_c2h__DOT__cur_local;
            if (((IData)(vlSelf->top__DOT__u_dma__DOT__c2h_local_arvalid) 
                 & ((IData)(vlSelf->top__DOT__arb_owner) 
                    & (IData)(vlSelf->top__DOT__ram_arready)))) {
                __Vdly__top__DOT__u_dma__DOT__c2h_local_arvalid = 0U;
                vlSelf->top__DOT__u_dma__DOT__c2h_local_rready = 1U;
                __Vdly__top__DOT__u_dma__DOT__u_c2h__DOT__state = 2U;
            }
        } else if ((2U == (IData)(vlSelf->top__DOT__u_dma__DOT__u_c2h__DOT__state))) {
            if (vlSelf->top__DOT__dma_local_rvalid) {
                vlSelf->top__DOT__u_dma__DOT__c2h_local_rready = 0U;
                vlSelf->top__DOT__u_dma__DOT__c2h_host_awaddr 
                    = vlSelf->top__DOT__u_dma__DOT__u_c2h__DOT__cur_host;
                vlSelf->top__DOT__u_dma__DOT__c2h_host_wdata 
                    = vlSelf->top__DOT__ram_rdata;
                __Vdly__top__DOT__u_dma__DOT__u_c2h__DOT__state = 3U;
            }
        } else if ((3U == (IData)(vlSelf->top__DOT__u_dma__DOT__u_c2h__DOT__state))) {
            __Vdly__top__DOT__u_dma__DOT__c2h_host_awvalid = 1U;
            __Vdly__top__DOT__u_dma__DOT__c2h_host_wvalid = 1U;
            if (((((IData)(vlSelf->top__DOT__u_dma__DOT__c2h_host_awvalid) 
                   & (IData)(vlSelf->top__DOT__dma_host_awready)) 
                  & (IData)(vlSelf->top__DOT__u_dma__DOT__c2h_host_wvalid)) 
                 & (IData)(vlSelf->top__DOT__dma_host_wready))) {
                __Vdly__top__DOT__u_dma__DOT__c2h_host_awvalid = 0U;
                __Vdly__top__DOT__u_dma__DOT__c2h_host_wvalid = 0U;
                vlSelf->top__DOT__u_dma__DOT__c2h_host_bready = 1U;
                __Vdly__top__DOT__u_dma__DOT__u_c2h__DOT__state = 4U;
            }
        } else if ((4U == (IData)(vlSelf->top__DOT__u_dma__DOT__u_c2h__DOT__state))) {
            if (vlSelf->top__DOT__dma_host_bvalid) {
                __Vdly__top__DOT__u_dma__DOT__u_c2h__DOT__cur_host 
                    = (8ULL + vlSelf->top__DOT__u_dma__DOT__u_c2h__DOT__cur_host);
                __Vdly__top__DOT__u_dma__DOT__u_c2h__DOT__cur_local 
                    = ((IData)(8U) + vlSelf->top__DOT__u_dma__DOT__u_c2h__DOT__cur_local);
                vlSelf->top__DOT__u_dma__DOT__c2h_host_bready = 0U;
                if ((8U >= vlSelf->top__DOT__u_dma__DOT__u_c2h__DOT__bytes_left)) {
                    __Vdly__top__DOT__u_dma__DOT__u_c2h__DOT__state = 5U;
                } else {
                    __Vdly__top__DOT__u_dma__DOT__u_c2h__DOT__bytes_left 
                        = (vlSelf->top__DOT__u_dma__DOT__u_c2h__DOT__bytes_left 
                           - (IData)(8U));
                    __Vdly__top__DOT__u_dma__DOT__u_c2h__DOT__state = 1U;
                }
            }
        } else if ((5U == (IData)(vlSelf->top__DOT__u_dma__DOT__u_c2h__DOT__state))) {
            __Vdly__top__DOT__u_dma__DOT__u_c2h__DOT__state = 0U;
        }
    } else {
        __Vdly__top__DOT__u_axi_sniffer__DOT__ar_count = 0U;
        __Vdly__top__DOT__u_axi_sniffer__DOT__aw_count = 0U;
        __Vdly__top__DOT__u_sniffer__DOT__tx_count = 0U;
        __Vdly__top__DOT__u_sniffer__DOT__rx_count = 0U;
        __Vdly__top__DOT__msix_valid_i = 0U;
        vlSelf->top__DOT__msix_pending = 0U;
        __Vdly__top__DOT__dma_host_rvalid = 0U;
        __Vdly__top__DOT__u_bridge__DOT__host_mrd_inflight = 0U;
        __Vdly__top__DOT__u_bridge__DOT__host_mrd_tag = 0U;
        __Vdly__top__DOT__dma_host_arready = 1U;
        __Vdly__top__DOT__u_bridge__DOT__host_mrd_pending = 0U;
        vlSelf->top__DOT__arb_busy = 0U;
        __Vdly__top__DOT__arb_owner = 0U;
        __Vdly__top__DOT__ram_rvalid = 0U;
        __Vdly__top__DOT__u_ram__DOT__read_pending = 0U;
        __Vdly__top__DOT__ram_arready = 1U;
        __Vdly__top__DOT__ram_rdata = 0ULL;
        __Vdly__top__DOT__u_ram__DOT__rd_addr_latched = 0U;
        __Vdly__top__DOT__ram_bvalid = 0U;
        __Vdly__top__DOT__ram_awready = 1U;
        __Vdly__top__DOT__ram_wready = 1U;
        __Vdly__top__DOT__u_sniffer__DOT__write_ptr = 0U;
        __Vdly__top__DOT__u_sniffer__DOT__entry_count = 0U;
        __Vdly__top__DOT__u_sniffer__DOT__triggered = 0U;
        __Vdly__top__DOT__u_sniffer__DOT__full = 0U;
        __Vdly__top__DOT__u_sniffer__DOT__armed = 0U;
        __Vdly__top__DOT__u_sniffer__DOT__running = 0U;
        __Vdly__top__DOT__u_sniffer__DOT__cycle_count = 0ULL;
        vlSelf->tx_hcrdt_init_ack = 0U;
        vlSelf->tx_dcrdt_init_ack = 0U;
        __Vdly__top__DOT__dma_s_bvalid = 0U;
        __Vdly__top__DOT__u_dma__DOT__ctrl_reg = 0U;
        __Vdly__top__DOT__u_dma__DOT__host_addr = 0ULL;
        __Vdly__top__DOT__u_dma__DOT__local_addr = 0U;
        __Vdly__top__DOT__u_dma__DOT__length_reg = 0U;
        vlSelf->top__DOT__dma_s_awready = 1U;
        vlSelf->top__DOT__dma_s_wready = 1U;
        __Vdly__top__DOT__dma_s_rvalid = 0U;
        vlSelf->top__DOT__dma_s_arready = 1U;
        vlSelf->top__DOT__dma_s_rdata = 0ULL;
        vlSelf->top__DOT__dbg_rvalid = 0U;
        __Vdly__top__DOT__dbg_rd_state = 0U;
        vlSelf->top__DOT__dbg_rdata_latched = 0U;
        vlSelf->top__DOT__dbg_addr_latched = 0U;
        vlSelf->top__DOT__dbg_sel_axi_latched = 0U;
        vlSelf->top__DOT__pcie_dbg_rdata = 0U;
        vlSelf->top__DOT__axi_dbg_rdata = 0U;
        __Vdly__top__DOT__u_dma__DOT__h2c_host_arvalid = 0U;
        __Vdly__top__DOT__u_dma__DOT__h2c_local_awvalid = 0U;
        __Vdly__top__DOT__u_dma__DOT__h2c_local_wvalid = 0U;
        __Vdly__top__DOT__u_dma__DOT__u_h2c__DOT__state = 0U;
        __Vdly__top__DOT__u_dma__DOT__u_h2c__DOT__cur_host = 0ULL;
        __Vdly__top__DOT__u_dma__DOT__u_h2c__DOT__cur_local = 0U;
        __Vdly__top__DOT__u_dma__DOT__u_h2c__DOT__bytes_left = 0U;
        vlSelf->top__DOT__u_dma__DOT__h2c_host_araddr = 0ULL;
        vlSelf->top__DOT__u_dma__DOT__h2c_host_rready = 0U;
        vlSelf->top__DOT__u_dma__DOT__h2c_local_awaddr = 0U;
        vlSelf->top__DOT__u_dma__DOT__h2c_local_wdata = 0ULL;
        vlSelf->top__DOT__u_dma__DOT__h2c_local_wstrb = 0U;
        vlSelf->top__DOT__u_dma__DOT__h2c_local_bready = 0U;
        vlSelf->top__DOT__u_sniffer__DOT__last_tx_data = 0ULL;
        vlSelf->top__DOT__u_sniffer__DOT__last_tx_hdr[0U] = 0U;
        vlSelf->top__DOT__u_sniffer__DOT__last_tx_hdr[1U] = 0U;
        vlSelf->top__DOT__u_sniffer__DOT__last_tx_hdr[2U] = 0U;
        vlSelf->top__DOT__u_sniffer__DOT__last_tx_hdr[3U] = 0U;
        vlSelf->top__DOT__u_sniffer__DOT__last_rx_data = 0ULL;
        vlSelf->top__DOT__u_sniffer__DOT__last_rx_hdr[0U] = 0U;
        vlSelf->top__DOT__u_sniffer__DOT__last_rx_hdr[1U] = 0U;
        vlSelf->top__DOT__u_sniffer__DOT__last_rx_hdr[2U] = 0U;
        vlSelf->top__DOT__u_sniffer__DOT__last_rx_hdr[3U] = 0U;
        vlSelf->top__DOT__u_sniffer__DOT__last_rx_type = 0U;
        vlSelf->top__DOT__u_sniffer__DOT__tx_seen = 0U;
        vlSelf->top__DOT__u_sniffer__DOT__rx_seen = 0U;
        vlSelf->top__DOT__u_sniffer__DOT__trigger_on_err = 0U;
        vlSelf->top__DOT__u_sniffer__DOT__trigger_type_en = 0U;
        vlSelf->top__DOT__u_sniffer__DOT__trigger_type = 0U;
        vlSelf->top__DOT__u_sniffer__DOT__capture_mode = 0U;
        vlSelf->top__DOT__u_sniffer__DOT__read_ptr = 0U;
        vlSelf->top__DOT__u_sniffer__DOT__filter_mode = 0U;
        vlSelf->top__DOT__u_axi_sniffer__DOT__ar_seen = 0U;
        vlSelf->top__DOT__u_axi_sniffer__DOT__aw_seen = 0U;
        vlSelf->top__DOT__u_axi_sniffer__DOT__read_ptr = 0U;
        __Vdly__top__DOT__u_axi_sniffer__DOT__pending_awvalid = 0U;
        __Vdly__top__DOT__u_axi_sniffer__DOT__write_ptr = 0U;
        __Vdly__top__DOT__u_axi_sniffer__DOT__entry_count = 0U;
        __Vdly__top__DOT__u_axi_sniffer__DOT__full = 0U;
        __Vdly__top__DOT__u_axi_sniffer__DOT__timestamp = 0U;
        vlSelf->top__DOT__u_axi_sniffer__DOT__w_seen = 0U;
        vlSelf->top__DOT__u_axi_sniffer__DOT__b_seen = 0U;
        vlSelf->top__DOT__u_axi_sniffer__DOT__r_seen = 0U;
        vlSelf->top__DOT__u_axi_sniffer__DOT__running = 0U;
        vlSelf->top__DOT__u_axi_sniffer__DOT__pending_awaddr = 0U;
        __Vdly__top__DOT__u_bridge__DOT__tx_state = 0U;
        __Vdly__top__DOT__brg_awvalid = 0U;
        __Vdly__top__DOT__brg_wvalid = 0U;
        vlSelf->top__DOT__brg_bready = 0U;
        vlSelf->top__DOT__brg_arvalid = 0U;
        vlSelf->top__DOT__brg_rready = 0U;
        vlSelf->tx_st_hvalid = 0U;
        vlSelf->tx_st_dvalid = 0U;
        vlSelf->tx_st_sop = 0U;
        vlSelf->tx_st_eop = 0U;
        vlSelf->top__DOT__msix_ready_i = 0U;
        vlSelf->top__DOT__u_bridge__DOT__host_mrd_ready_pulse = 0U;
        __Vdly__top__DOT__u_bridge__DOT__host_mwr_ready_pulse = 0U;
        __Vdly__top__DOT__u_bridge__DOT__bar_req_rid = 0U;
        __Vdly__top__DOT__u_bridge__DOT__bar_req_tag = 0U;
        __Vdly__top__DOT__u_bridge__DOT__bar_req_lower_addr = 0U;
        __Vdly__top__DOT__u_bridge__DOT__bar_req_addr = 0U;
        __Vdly__top__DOT__u_bridge__DOT__bar_dw_remaining = 0U;
        __Vdly__top__DOT__u_bridge__DOT__bar_cpl_buffer[0U] 
            = Vtop__ConstPool__CONST_h9e67c271_0[0U];
        __Vdly__top__DOT__u_bridge__DOT__bar_cpl_buffer[1U] 
            = Vtop__ConstPool__CONST_h9e67c271_0[1U];
        __Vdly__top__DOT__u_bridge__DOT__bar_cpl_buffer[2U] 
            = Vtop__ConstPool__CONST_h9e67c271_0[2U];
        __Vdly__top__DOT__u_bridge__DOT__bar_cpl_buffer[3U] 
            = Vtop__ConstPool__CONST_h9e67c271_0[3U];
        __Vdly__top__DOT__u_bridge__DOT__bar_cpl_buffer[4U] 
            = Vtop__ConstPool__CONST_h9e67c271_0[4U];
        __Vdly__top__DOT__u_bridge__DOT__bar_cpl_buffer[5U] 
            = Vtop__ConstPool__CONST_h9e67c271_0[5U];
        __Vdly__top__DOT__u_bridge__DOT__bar_cpl_buffer[6U] 
            = Vtop__ConstPool__CONST_h9e67c271_0[6U];
        __Vdly__top__DOT__u_bridge__DOT__bar_cpl_buffer[7U] 
            = Vtop__ConstPool__CONST_h9e67c271_0[7U];
        __Vdly__top__DOT__u_bridge__DOT__bar_dw_count = 0U;
        __Vdly__top__DOT__u_bridge__DOT__bar_cpl_status = 0U;
        vlSelf->top__DOT__u_bridge__DOT__completer_id = 0U;
        vlSelf->top__DOT__u_bridge__DOT__completer_id_valid = 0U;
        __Vdly__top__DOT__dma_host_bvalid = 0U;
        __Vdly__top__DOT__dma_host_awready = 1U;
        __Vdly__top__DOT__dma_host_wready = 1U;
        __Vdly__top__DOT__u_bridge__DOT__host_mwr_pending = 0U;
        __Vdly__top__DOT__u_dma__DOT__c2h_local_arvalid = 0U;
        __Vdly__top__DOT__u_dma__DOT__c2h_host_awvalid = 0U;
        __Vdly__top__DOT__u_dma__DOT__c2h_host_wvalid = 0U;
        __Vdly__top__DOT__u_dma__DOT__u_c2h__DOT__state = 0U;
        __Vdly__top__DOT__u_dma__DOT__u_c2h__DOT__cur_host = 0ULL;
        __Vdly__top__DOT__u_dma__DOT__u_c2h__DOT__cur_local = 0U;
        __Vdly__top__DOT__u_dma__DOT__u_c2h__DOT__bytes_left = 0U;
        vlSelf->top__DOT__u_dma__DOT__c2h_local_araddr = 0U;
        vlSelf->top__DOT__u_dma__DOT__c2h_local_rready = 0U;
        vlSelf->top__DOT__u_dma__DOT__c2h_host_awaddr = 0ULL;
        vlSelf->top__DOT__u_dma__DOT__c2h_host_wdata = 0ULL;
        vlSelf->top__DOT__u_dma__DOT__c2h_host_bready = 0U;
    }
    if ((1U & (~ (IData)(vlSelf->rst_n)))) {
        vlSelf->top__DOT__ram_rresp = 0U;
        vlSelf->top__DOT__dma_s_rresp = 0U;
        vlSelf->top__DOT__dma_s_bresp = 0U;
        vlSelf->top__DOT__ram_bresp = 0U;
        vlSelf->top__DOT__msix_addr_reg = 0xfee00000ULL;
        vlSelf->top__DOT__msix_data_reg = 0U;
    }
    __Vtableidx1 = (((IData)(vlSelf->top__DOT__u_bridge__DOT__u_crdt__DOT__cnt) 
                     << 3U) | (((IData)(vlSelf->top__DOT__u_bridge__DOT__u_crdt__DOT__state) 
                                << 1U) | (IData)(vlSelf->rst_n)));
    vlSelf->rx_hcrdt_update = Vtop__ConstPool__TABLE_hf3a84768_0
        [__Vtableidx1];
    vlSelf->rx_dcrdt_update = Vtop__ConstPool__TABLE_hf3a84768_0
        [__Vtableidx1];
    if ((4U & Vtop__ConstPool__TABLE_h92b69fc4_0[__Vtableidx1])) {
        vlSelf->rx_hcrdt_init = Vtop__ConstPool__TABLE_h3a3a7adf_0
            [__Vtableidx1];
    }
    if ((8U & Vtop__ConstPool__TABLE_h92b69fc4_0[__Vtableidx1])) {
        vlSelf->rx_dcrdt_init = Vtop__ConstPool__TABLE_h3a3a7adf_0
            [__Vtableidx1];
    }
    if ((0x10U & Vtop__ConstPool__TABLE_h92b69fc4_0
         [__Vtableidx1])) {
        vlSelf->top__DOT__u_bridge__DOT__u_crdt__DOT__cnt 
            = Vtop__ConstPool__TABLE_h1588c7a3_0[__Vtableidx1];
    }
    if ((0x20U & Vtop__ConstPool__TABLE_h92b69fc4_0
         [__Vtableidx1])) {
        vlSelf->top__DOT__u_bridge__DOT__u_crdt__DOT__state 
            = Vtop__ConstPool__TABLE_h643f69a8_0[__Vtableidx1];
    }
    vlSelf->top__DOT__u_bridge__DOT__host_mrd_inflight 
        = __Vdly__top__DOT__u_bridge__DOT__host_mrd_inflight;
    vlSelf->top__DOT__u_ram__DOT__rd_addr_latched = __Vdly__top__DOT__u_ram__DOT__rd_addr_latched;
    vlSelf->top__DOT__u_ram__DOT__read_pending = __Vdly__top__DOT__u_ram__DOT__read_pending;
    vlSelf->top__DOT__ram_rvalid = __Vdly__top__DOT__ram_rvalid;
    vlSelf->top__DOT__ram_bvalid = __Vdly__top__DOT__ram_bvalid;
    if (__Vdlyvset__top__DOT__u_ram__DOT__mem__v0) {
        vlSelf->top__DOT__u_ram__DOT__mem[__Vdlyvdim0__top__DOT__u_ram__DOT__mem__v0] 
            = (((~ (0xffULL << (IData)(__Vdlyvlsb__top__DOT__u_ram__DOT__mem__v0))) 
                & vlSelf->top__DOT__u_ram__DOT__mem
                [__Vdlyvdim0__top__DOT__u_ram__DOT__mem__v0]) 
               | ((QData)((IData)(__Vdlyvval__top__DOT__u_ram__DOT__mem__v0)) 
                  << (IData)(__Vdlyvlsb__top__DOT__u_ram__DOT__mem__v0)));
    }
    if (__Vdlyvset__top__DOT__u_ram__DOT__mem__v1) {
        vlSelf->top__DOT__u_ram__DOT__mem[__Vdlyvdim0__top__DOT__u_ram__DOT__mem__v1] 
            = (((~ (0xffULL << (IData)(__Vdlyvlsb__top__DOT__u_ram__DOT__mem__v1))) 
                & vlSelf->top__DOT__u_ram__DOT__mem
                [__Vdlyvdim0__top__DOT__u_ram__DOT__mem__v1]) 
               | ((QData)((IData)(__Vdlyvval__top__DOT__u_ram__DOT__mem__v1)) 
                  << (IData)(__Vdlyvlsb__top__DOT__u_ram__DOT__mem__v1)));
    }
    if (__Vdlyvset__top__DOT__u_ram__DOT__mem__v2) {
        vlSelf->top__DOT__u_ram__DOT__mem[__Vdlyvdim0__top__DOT__u_ram__DOT__mem__v2] 
            = (((~ (0xffULL << (IData)(__Vdlyvlsb__top__DOT__u_ram__DOT__mem__v2))) 
                & vlSelf->top__DOT__u_ram__DOT__mem
                [__Vdlyvdim0__top__DOT__u_ram__DOT__mem__v2]) 
               | ((QData)((IData)(__Vdlyvval__top__DOT__u_ram__DOT__mem__v2)) 
                  << (IData)(__Vdlyvlsb__top__DOT__u_ram__DOT__mem__v2)));
    }
    if (__Vdlyvset__top__DOT__u_ram__DOT__mem__v3) {
        vlSelf->top__DOT__u_ram__DOT__mem[__Vdlyvdim0__top__DOT__u_ram__DOT__mem__v3] 
            = (((~ (0xffULL << (IData)(__Vdlyvlsb__top__DOT__u_ram__DOT__mem__v3))) 
                & vlSelf->top__DOT__u_ram__DOT__mem
                [__Vdlyvdim0__top__DOT__u_ram__DOT__mem__v3]) 
               | ((QData)((IData)(__Vdlyvval__top__DOT__u_ram__DOT__mem__v3)) 
                  << (IData)(__Vdlyvlsb__top__DOT__u_ram__DOT__mem__v3)));
    }
    if (__Vdlyvset__top__DOT__u_ram__DOT__mem__v4) {
        vlSelf->top__DOT__u_ram__DOT__mem[__Vdlyvdim0__top__DOT__u_ram__DOT__mem__v4] 
            = (((~ (0xffULL << (IData)(__Vdlyvlsb__top__DOT__u_ram__DOT__mem__v4))) 
                & vlSelf->top__DOT__u_ram__DOT__mem
                [__Vdlyvdim0__top__DOT__u_ram__DOT__mem__v4]) 
               | ((QData)((IData)(__Vdlyvval__top__DOT__u_ram__DOT__mem__v4)) 
                  << (IData)(__Vdlyvlsb__top__DOT__u_ram__DOT__mem__v4)));
    }
    if (__Vdlyvset__top__DOT__u_ram__DOT__mem__v5) {
        vlSelf->top__DOT__u_ram__DOT__mem[__Vdlyvdim0__top__DOT__u_ram__DOT__mem__v5] 
            = (((~ (0xffULL << (IData)(__Vdlyvlsb__top__DOT__u_ram__DOT__mem__v5))) 
                & vlSelf->top__DOT__u_ram__DOT__mem
                [__Vdlyvdim0__top__DOT__u_ram__DOT__mem__v5]) 
               | ((QData)((IData)(__Vdlyvval__top__DOT__u_ram__DOT__mem__v5)) 
                  << (IData)(__Vdlyvlsb__top__DOT__u_ram__DOT__mem__v5)));
    }
    if (__Vdlyvset__top__DOT__u_ram__DOT__mem__v6) {
        vlSelf->top__DOT__u_ram__DOT__mem[__Vdlyvdim0__top__DOT__u_ram__DOT__mem__v6] 
            = (((~ (0xffULL << (IData)(__Vdlyvlsb__top__DOT__u_ram__DOT__mem__v6))) 
                & vlSelf->top__DOT__u_ram__DOT__mem
                [__Vdlyvdim0__top__DOT__u_ram__DOT__mem__v6]) 
               | ((QData)((IData)(__Vdlyvval__top__DOT__u_ram__DOT__mem__v6)) 
                  << (IData)(__Vdlyvlsb__top__DOT__u_ram__DOT__mem__v6)));
    }
    if (__Vdlyvset__top__DOT__u_ram__DOT__mem__v7) {
        vlSelf->top__DOT__u_ram__DOT__mem[__Vdlyvdim0__top__DOT__u_ram__DOT__mem__v7] 
            = (((~ (0xffULL << (IData)(__Vdlyvlsb__top__DOT__u_ram__DOT__mem__v7))) 
                & vlSelf->top__DOT__u_ram__DOT__mem
                [__Vdlyvdim0__top__DOT__u_ram__DOT__mem__v7]) 
               | ((QData)((IData)(__Vdlyvval__top__DOT__u_ram__DOT__mem__v7)) 
                  << (IData)(__Vdlyvlsb__top__DOT__u_ram__DOT__mem__v7)));
    }
    vlSelf->top__DOT__u_sniffer__DOT__armed = __Vdly__top__DOT__u_sniffer__DOT__armed;
    if (__Vdlyvset__top__DOT__u_sniffer__DOT__trace_ram__v0) {
        vlSelf->top__DOT__u_sniffer__DOT__trace_ram[__Vdlyvdim0__top__DOT__u_sniffer__DOT__trace_ram__v0][0U] 
            = __Vdlyvval__top__DOT__u_sniffer__DOT__trace_ram__v0[0U];
        vlSelf->top__DOT__u_sniffer__DOT__trace_ram[__Vdlyvdim0__top__DOT__u_sniffer__DOT__trace_ram__v0][1U] 
            = __Vdlyvval__top__DOT__u_sniffer__DOT__trace_ram__v0[1U];
        vlSelf->top__DOT__u_sniffer__DOT__trace_ram[__Vdlyvdim0__top__DOT__u_sniffer__DOT__trace_ram__v0][2U] 
            = __Vdlyvval__top__DOT__u_sniffer__DOT__trace_ram__v0[2U];
        vlSelf->top__DOT__u_sniffer__DOT__trace_ram[__Vdlyvdim0__top__DOT__u_sniffer__DOT__trace_ram__v0][3U] 
            = __Vdlyvval__top__DOT__u_sniffer__DOT__trace_ram__v0[3U];
        vlSelf->top__DOT__u_sniffer__DOT__trace_ram[__Vdlyvdim0__top__DOT__u_sniffer__DOT__trace_ram__v0][4U] 
            = __Vdlyvval__top__DOT__u_sniffer__DOT__trace_ram__v0[4U];
        vlSelf->top__DOT__u_sniffer__DOT__trace_ram[__Vdlyvdim0__top__DOT__u_sniffer__DOT__trace_ram__v0][5U] 
            = __Vdlyvval__top__DOT__u_sniffer__DOT__trace_ram__v0[5U];
        vlSelf->top__DOT__u_sniffer__DOT__trace_ram[__Vdlyvdim0__top__DOT__u_sniffer__DOT__trace_ram__v0][6U] 
            = __Vdlyvval__top__DOT__u_sniffer__DOT__trace_ram__v0[6U];
        vlSelf->top__DOT__u_sniffer__DOT__trace_ram[__Vdlyvdim0__top__DOT__u_sniffer__DOT__trace_ram__v0][7U] 
            = __Vdlyvval__top__DOT__u_sniffer__DOT__trace_ram__v0[7U];
    }
    vlSelf->top__DOT__dma_s_rvalid = __Vdly__top__DOT__dma_s_rvalid;
    vlSelf->top__DOT__dbg_rd_state = __Vdly__top__DOT__dbg_rd_state;
    vlSelf->top__DOT__u_sniffer__DOT__cycle_count = __Vdly__top__DOT__u_sniffer__DOT__cycle_count;
    vlSelf->top__DOT__u_sniffer__DOT__tx_count = __Vdly__top__DOT__u_sniffer__DOT__tx_count;
    vlSelf->top__DOT__u_sniffer__DOT__rx_count = __Vdly__top__DOT__u_sniffer__DOT__rx_count;
    vlSelf->top__DOT__u_sniffer__DOT__entry_count = __Vdly__top__DOT__u_sniffer__DOT__entry_count;
    vlSelf->top__DOT__u_sniffer__DOT__write_ptr = __Vdly__top__DOT__u_sniffer__DOT__write_ptr;
    vlSelf->top__DOT__u_sniffer__DOT__full = __Vdly__top__DOT__u_sniffer__DOT__full;
    vlSelf->top__DOT__u_sniffer__DOT__triggered = __Vdly__top__DOT__u_sniffer__DOT__triggered;
    vlSelf->top__DOT__u_sniffer__DOT__running = __Vdly__top__DOT__u_sniffer__DOT__running;
    vlSelf->top__DOT__u_axi_sniffer__DOT__ar_count 
        = __Vdly__top__DOT__u_axi_sniffer__DOT__ar_count;
    vlSelf->top__DOT__u_axi_sniffer__DOT__aw_count 
        = __Vdly__top__DOT__u_axi_sniffer__DOT__aw_count;
    vlSelf->top__DOT__dma_irq_req = ((IData)(vlSelf->rst_n) 
                                     && (((IData)(vlSelf->top__DOT__u_dma__DOT__done) 
                                          & (~ (IData)(vlSelf->top__DOT__u_dma__DOT__done_r))) 
                                         & (vlSelf->top__DOT__u_dma__DOT__ctrl_reg 
                                            >> 2U)));
    vlSelf->rx_dcrdt_update_cnt = ((3U == (IData)(vlSelf->top__DOT__u_bridge__DOT__u_crdt__DOT__state))
                                    ? 0U : 0xfffU);
    vlSelf->top__DOT__dbg_rdata = ((IData)(vlSelf->top__DOT__dbg_sel_axi_latched)
                                    ? vlSelf->top__DOT__axi_dbg_rdata
                                    : vlSelf->top__DOT__pcie_dbg_rdata);
    vlSelf->top__DOT__dma_host_rdata = __Vdly__top__DOT__dma_host_rdata;
    vlSelf->top__DOT__u_dma__DOT__u_h2c__DOT__cur_host 
        = __Vdly__top__DOT__u_dma__DOT__u_h2c__DOT__cur_host;
    vlSelf->top__DOT__u_dma__DOT__u_h2c__DOT__cur_local 
        = __Vdly__top__DOT__u_dma__DOT__u_h2c__DOT__cur_local;
    vlSelf->top__DOT__u_dma__DOT__u_h2c__DOT__bytes_left 
        = __Vdly__top__DOT__u_dma__DOT__u_h2c__DOT__bytes_left;
    vlSelf->top__DOT__u_dma__DOT__h2c_host_arvalid 
        = __Vdly__top__DOT__u_dma__DOT__h2c_host_arvalid;
    vlSelf->top__DOT__dma_host_arready = __Vdly__top__DOT__dma_host_arready;
    vlSelf->top__DOT__dma_host_rvalid = __Vdly__top__DOT__dma_host_rvalid;
    vlSelf->top__DOT__u_dma__DOT__h2c_local_wvalid 
        = __Vdly__top__DOT__u_dma__DOT__h2c_local_wvalid;
    vlSelf->top__DOT__u_dma__DOT__h2c_local_awvalid 
        = __Vdly__top__DOT__u_dma__DOT__h2c_local_awvalid;
    vlSelf->top__DOT__ram_wready = __Vdly__top__DOT__ram_wready;
    vlSelf->top__DOT__u_dma__DOT__u_h2c__DOT__state 
        = __Vdly__top__DOT__u_dma__DOT__u_h2c__DOT__state;
    vlSelf->top__DOT__ram_awready = __Vdly__top__DOT__ram_awready;
    vlSelf->top__DOT__u_axi_sniffer__DOT__timestamp 
        = __Vdly__top__DOT__u_axi_sniffer__DOT__timestamp;
    vlSelf->top__DOT__u_axi_sniffer__DOT__pending_awvalid 
        = __Vdly__top__DOT__u_axi_sniffer__DOT__pending_awvalid;
    vlSelf->top__DOT__u_axi_sniffer__DOT__full = __Vdly__top__DOT__u_axi_sniffer__DOT__full;
    vlSelf->top__DOT__u_axi_sniffer__DOT__entry_count 
        = __Vdly__top__DOT__u_axi_sniffer__DOT__entry_count;
    vlSelf->top__DOT__u_axi_sniffer__DOT__write_ptr 
        = __Vdly__top__DOT__u_axi_sniffer__DOT__write_ptr;
    vlSelf->top__DOT__dma_s_bvalid = __Vdly__top__DOT__dma_s_bvalid;
    if (__Vdlyvset__top__DOT__u_axi_sniffer__DOT__trace_ram__v0) {
        vlSelf->top__DOT__u_axi_sniffer__DOT__trace_ram[__Vdlyvdim0__top__DOT__u_axi_sniffer__DOT__trace_ram__v0][0U] 
            = __Vdlyvval__top__DOT__u_axi_sniffer__DOT__trace_ram__v0[0U];
        vlSelf->top__DOT__u_axi_sniffer__DOT__trace_ram[__Vdlyvdim0__top__DOT__u_axi_sniffer__DOT__trace_ram__v0][1U] 
            = __Vdlyvval__top__DOT__u_axi_sniffer__DOT__trace_ram__v0[1U];
        vlSelf->top__DOT__u_axi_sniffer__DOT__trace_ram[__Vdlyvdim0__top__DOT__u_axi_sniffer__DOT__trace_ram__v0][2U] 
            = __Vdlyvval__top__DOT__u_axi_sniffer__DOT__trace_ram__v0[2U];
        vlSelf->top__DOT__u_axi_sniffer__DOT__trace_ram[__Vdlyvdim0__top__DOT__u_axi_sniffer__DOT__trace_ram__v0][3U] 
            = __Vdlyvval__top__DOT__u_axi_sniffer__DOT__trace_ram__v0[3U];
    }
    if (__Vdlyvset__top__DOT__u_axi_sniffer__DOT__trace_ram__v1) {
        vlSelf->top__DOT__u_axi_sniffer__DOT__trace_ram[__Vdlyvdim0__top__DOT__u_axi_sniffer__DOT__trace_ram__v1][0U] 
            = __Vdlyvval__top__DOT__u_axi_sniffer__DOT__trace_ram__v1[0U];
        vlSelf->top__DOT__u_axi_sniffer__DOT__trace_ram[__Vdlyvdim0__top__DOT__u_axi_sniffer__DOT__trace_ram__v1][1U] 
            = __Vdlyvval__top__DOT__u_axi_sniffer__DOT__trace_ram__v1[1U];
        vlSelf->top__DOT__u_axi_sniffer__DOT__trace_ram[__Vdlyvdim0__top__DOT__u_axi_sniffer__DOT__trace_ram__v1][2U] 
            = __Vdlyvval__top__DOT__u_axi_sniffer__DOT__trace_ram__v1[2U];
        vlSelf->top__DOT__u_axi_sniffer__DOT__trace_ram[__Vdlyvdim0__top__DOT__u_axi_sniffer__DOT__trace_ram__v1][3U] 
            = __Vdlyvval__top__DOT__u_axi_sniffer__DOT__trace_ram__v1[3U];
    }
    if (__Vdlyvset__top__DOT__u_axi_sniffer__DOT__trace_ram__v2) {
        vlSelf->top__DOT__u_axi_sniffer__DOT__trace_ram[__Vdlyvdim0__top__DOT__u_axi_sniffer__DOT__trace_ram__v2][0U] 
            = __Vdlyvval__top__DOT__u_axi_sniffer__DOT__trace_ram__v2[0U];
        vlSelf->top__DOT__u_axi_sniffer__DOT__trace_ram[__Vdlyvdim0__top__DOT__u_axi_sniffer__DOT__trace_ram__v2][1U] 
            = __Vdlyvval__top__DOT__u_axi_sniffer__DOT__trace_ram__v2[1U];
        vlSelf->top__DOT__u_axi_sniffer__DOT__trace_ram[__Vdlyvdim0__top__DOT__u_axi_sniffer__DOT__trace_ram__v2][2U] 
            = __Vdlyvval__top__DOT__u_axi_sniffer__DOT__trace_ram__v2[2U];
        vlSelf->top__DOT__u_axi_sniffer__DOT__trace_ram[__Vdlyvdim0__top__DOT__u_axi_sniffer__DOT__trace_ram__v2][3U] 
            = __Vdlyvval__top__DOT__u_axi_sniffer__DOT__trace_ram__v2[3U];
    }
    if (__Vdlyvset__top__DOT__u_axi_sniffer__DOT__trace_ram__v3) {
        vlSelf->top__DOT__u_axi_sniffer__DOT__trace_ram[__Vdlyvdim0__top__DOT__u_axi_sniffer__DOT__trace_ram__v3][0U] 
            = __Vdlyvval__top__DOT__u_axi_sniffer__DOT__trace_ram__v3[0U];
        vlSelf->top__DOT__u_axi_sniffer__DOT__trace_ram[__Vdlyvdim0__top__DOT__u_axi_sniffer__DOT__trace_ram__v3][1U] 
            = __Vdlyvval__top__DOT__u_axi_sniffer__DOT__trace_ram__v3[1U];
        vlSelf->top__DOT__u_axi_sniffer__DOT__trace_ram[__Vdlyvdim0__top__DOT__u_axi_sniffer__DOT__trace_ram__v3][2U] 
            = __Vdlyvval__top__DOT__u_axi_sniffer__DOT__trace_ram__v3[2U];
        vlSelf->top__DOT__u_axi_sniffer__DOT__trace_ram[__Vdlyvdim0__top__DOT__u_axi_sniffer__DOT__trace_ram__v3][3U] 
            = __Vdlyvval__top__DOT__u_axi_sniffer__DOT__trace_ram__v3[3U];
    }
    vlSelf->top__DOT__u_dma__DOT__done_r = ((IData)(vlSelf->rst_n) 
                                            && (IData)(vlSelf->top__DOT__u_dma__DOT__done));
    vlSelf->top__DOT__u_sniffer__DOT__read_entry[0U] 
        = vlSelf->top__DOT__u_sniffer__DOT__trace_ram
        [vlSelf->top__DOT__u_sniffer__DOT__read_ptr][0U];
    vlSelf->top__DOT__u_sniffer__DOT__read_entry[1U] 
        = vlSelf->top__DOT__u_sniffer__DOT__trace_ram
        [vlSelf->top__DOT__u_sniffer__DOT__read_ptr][1U];
    vlSelf->top__DOT__u_sniffer__DOT__read_entry[2U] 
        = vlSelf->top__DOT__u_sniffer__DOT__trace_ram
        [vlSelf->top__DOT__u_sniffer__DOT__read_ptr][2U];
    vlSelf->top__DOT__u_sniffer__DOT__read_entry[3U] 
        = vlSelf->top__DOT__u_sniffer__DOT__trace_ram
        [vlSelf->top__DOT__u_sniffer__DOT__read_ptr][3U];
    vlSelf->top__DOT__u_sniffer__DOT__read_entry[4U] 
        = vlSelf->top__DOT__u_sniffer__DOT__trace_ram
        [vlSelf->top__DOT__u_sniffer__DOT__read_ptr][4U];
    vlSelf->top__DOT__u_sniffer__DOT__read_entry[5U] 
        = vlSelf->top__DOT__u_sniffer__DOT__trace_ram
        [vlSelf->top__DOT__u_sniffer__DOT__read_ptr][5U];
    vlSelf->top__DOT__u_sniffer__DOT__read_entry[6U] 
        = vlSelf->top__DOT__u_sniffer__DOT__trace_ram
        [vlSelf->top__DOT__u_sniffer__DOT__read_ptr][6U];
    vlSelf->top__DOT__u_sniffer__DOT__read_entry[7U] 
        = vlSelf->top__DOT__u_sniffer__DOT__trace_ram
        [vlSelf->top__DOT__u_sniffer__DOT__read_ptr][7U];
    vlSelf->top__DOT__u_axi_sniffer__DOT__read_entry[0U] 
        = vlSelf->top__DOT__u_axi_sniffer__DOT__trace_ram
        [vlSelf->top__DOT__u_axi_sniffer__DOT__read_ptr][0U];
    vlSelf->top__DOT__u_axi_sniffer__DOT__read_entry[1U] 
        = vlSelf->top__DOT__u_axi_sniffer__DOT__trace_ram
        [vlSelf->top__DOT__u_axi_sniffer__DOT__read_ptr][1U];
    vlSelf->top__DOT__u_axi_sniffer__DOT__read_entry[2U] 
        = vlSelf->top__DOT__u_axi_sniffer__DOT__trace_ram
        [vlSelf->top__DOT__u_axi_sniffer__DOT__read_ptr][2U];
    vlSelf->top__DOT__u_axi_sniffer__DOT__read_entry[3U] 
        = vlSelf->top__DOT__u_axi_sniffer__DOT__trace_ram
        [vlSelf->top__DOT__u_axi_sniffer__DOT__read_ptr][3U];
    vlSelf->top__DOT__u_bridge__DOT__host_mrd_addr 
        = __Vdly__top__DOT__u_bridge__DOT__host_mrd_addr;
    vlSelf->top__DOT__u_bridge__DOT__bar_req_rid = __Vdly__top__DOT__u_bridge__DOT__bar_req_rid;
    vlSelf->top__DOT__u_bridge__DOT__bar_req_tag = __Vdly__top__DOT__u_bridge__DOT__bar_req_tag;
    vlSelf->top__DOT__u_bridge__DOT__bar_req_lower_addr 
        = __Vdly__top__DOT__u_bridge__DOT__bar_req_lower_addr;
    vlSelf->top__DOT__u_bridge__DOT__bar_req_addr = __Vdly__top__DOT__u_bridge__DOT__bar_req_addr;
    vlSelf->top__DOT__u_bridge__DOT__bar_dw_remaining 
        = __Vdly__top__DOT__u_bridge__DOT__bar_dw_remaining;
    vlSelf->top__DOT__u_bridge__DOT__bar_dw_count = __Vdly__top__DOT__u_bridge__DOT__bar_dw_count;
    vlSelf->top__DOT__u_bridge__DOT__bar_cpl_buffer[0U] 
        = __Vdly__top__DOT__u_bridge__DOT__bar_cpl_buffer[0U];
    vlSelf->top__DOT__u_bridge__DOT__bar_cpl_buffer[1U] 
        = __Vdly__top__DOT__u_bridge__DOT__bar_cpl_buffer[1U];
    vlSelf->top__DOT__u_bridge__DOT__bar_cpl_buffer[2U] 
        = __Vdly__top__DOT__u_bridge__DOT__bar_cpl_buffer[2U];
    vlSelf->top__DOT__u_bridge__DOT__bar_cpl_buffer[3U] 
        = __Vdly__top__DOT__u_bridge__DOT__bar_cpl_buffer[3U];
    vlSelf->top__DOT__u_bridge__DOT__bar_cpl_buffer[4U] 
        = __Vdly__top__DOT__u_bridge__DOT__bar_cpl_buffer[4U];
    vlSelf->top__DOT__u_bridge__DOT__bar_cpl_buffer[5U] 
        = __Vdly__top__DOT__u_bridge__DOT__bar_cpl_buffer[5U];
    vlSelf->top__DOT__u_bridge__DOT__bar_cpl_buffer[6U] 
        = __Vdly__top__DOT__u_bridge__DOT__bar_cpl_buffer[6U];
    vlSelf->top__DOT__u_bridge__DOT__bar_cpl_buffer[7U] 
        = __Vdly__top__DOT__u_bridge__DOT__bar_cpl_buffer[7U];
    vlSelf->top__DOT__u_bridge__DOT__host_mrd_pending 
        = __Vdly__top__DOT__u_bridge__DOT__host_mrd_pending;
    vlSelf->top__DOT__msix_valid_i = __Vdly__top__DOT__msix_valid_i;
    vlSelf->top__DOT__u_bridge__DOT__bar_cpl_status 
        = __Vdly__top__DOT__u_bridge__DOT__bar_cpl_status;
    vlSelf->top__DOT__u_bridge__DOT__host_mrd_tag = __Vdly__top__DOT__u_bridge__DOT__host_mrd_tag;
    vlSelf->top__DOT__u_bridge__DOT__tx_state = __Vdly__top__DOT__u_bridge__DOT__tx_state;
    vlSelf->top__DOT__brg_wvalid = __Vdly__top__DOT__brg_wvalid;
    vlSelf->top__DOT__brg_awvalid = __Vdly__top__DOT__brg_awvalid;
    vlSelf->tx_st_data[0U] = vlSelf->top__DOT__u_bridge__DOT__tx_data_r[0U];
    vlSelf->tx_st_data[1U] = vlSelf->top__DOT__u_bridge__DOT__tx_data_r[1U];
    vlSelf->tx_st_data[2U] = vlSelf->top__DOT__u_bridge__DOT__tx_data_r[2U];
    vlSelf->tx_st_data[3U] = vlSelf->top__DOT__u_bridge__DOT__tx_data_r[3U];
    vlSelf->tx_st_data[4U] = vlSelf->top__DOT__u_bridge__DOT__tx_data_r[4U];
    vlSelf->tx_st_data[5U] = vlSelf->top__DOT__u_bridge__DOT__tx_data_r[5U];
    vlSelf->tx_st_data[6U] = vlSelf->top__DOT__u_bridge__DOT__tx_data_r[6U];
    vlSelf->tx_st_data[7U] = vlSelf->top__DOT__u_bridge__DOT__tx_data_r[7U];
    vlSelf->tx_st_hdr[0U] = vlSelf->top__DOT__u_bridge__DOT__tx_hdr_r[0U];
    vlSelf->tx_st_hdr[1U] = vlSelf->top__DOT__u_bridge__DOT__tx_hdr_r[1U];
    vlSelf->tx_st_hdr[2U] = vlSelf->top__DOT__u_bridge__DOT__tx_hdr_r[2U];
    vlSelf->tx_st_hdr[3U] = vlSelf->top__DOT__u_bridge__DOT__tx_hdr_r[3U];
    vlSelf->top__DOT__u_sniffer__DOT__tx_valid = ((IData)(vlSelf->tx_st_hvalid) 
                                                  & (IData)(vlSelf->tx_st_sop));
    vlSelf->rx_st_ready = (0U == (IData)(vlSelf->top__DOT__u_bridge__DOT__tx_state));
    top__DOT____VdfgRegularize_h245778ca_0_2 = ((IData)(vlSelf->top__DOT__brg_awvalid) 
                                                & (IData)(vlSelf->top__DOT__brg_wvalid));
    vlSelf->top__DOT__wr_to_ram = (IData)((0x1000U 
                                           == (0x3000U 
                                               & vlSelf->top__DOT__brg_awaddr)));
    vlSelf->top__DOT__rd_to_axi_dbg = (IData)((0x3000U 
                                               == (0x3000U 
                                                   & vlSelf->top__DOT__brg_araddr)));
    vlSelf->top__DOT__rd_to_ram = (IData)((0x1000U 
                                           == (0x3000U 
                                               & vlSelf->top__DOT__brg_araddr)));
    vlSelf->top__DOT__dbg_addr_to_sniffer = (0xfffU 
                                             & ((0U 
                                                 == (IData)(vlSelf->top__DOT__dbg_rd_state))
                                                 ? vlSelf->top__DOT__brg_araddr
                                                 : (IData)(vlSelf->top__DOT__dbg_addr_latched)));
    vlSelf->top__DOT__u_sniffer__DOT__tx_is_cpl_err 
        = ((IData)(vlSelf->top__DOT__u_sniffer__DOT__tx_valid) 
           & (IData)(((0xa000000U == (0x1f000000U & 
                                      vlSelf->top__DOT__u_bridge__DOT__tx_hdr_r[3U])) 
                      & (0U != (7U & (vlSelf->top__DOT__u_bridge__DOT__tx_hdr_r[1U] 
                                      >> 0xdU))))));
    vlSelf->top__DOT__u_sniffer__DOT__rx_valid = ((IData)(vlSelf->rx_st_hvalid) 
                                                  & ((IData)(vlSelf->rx_st_ready) 
                                                     & (IData)(vlSelf->rx_st_sop)));
    vlSelf->top__DOT__pcie_dbg_wen = ((IData)(top__DOT____VdfgRegularize_h245778ca_0_2) 
                                      & (IData)((0x2000U 
                                                 == 
                                                 (0x3000U 
                                                  & vlSelf->top__DOT__brg_awaddr))));
    vlSelf->top__DOT__axi_dbg_wen = ((IData)(top__DOT____VdfgRegularize_h245778ca_0_2) 
                                     & (IData)((0x3000U 
                                                == 
                                                (0x3000U 
                                                 & vlSelf->top__DOT__brg_awaddr))));
    vlSelf->top__DOT__ram_bar_awvalid = ((IData)(vlSelf->top__DOT__brg_awvalid) 
                                         & (IData)(vlSelf->top__DOT__wr_to_ram));
    vlSelf->top__DOT__rd_to_dbg = ((IData)(vlSelf->top__DOT__rd_to_axi_dbg) 
                                   | (0x2000U == (0x3000U 
                                                  & vlSelf->top__DOT__brg_araddr)));
    vlSelf->top__DOT__ram_bar_arvalid = ((IData)(vlSelf->top__DOT__brg_arvalid) 
                                         & (IData)(vlSelf->top__DOT__rd_to_ram));
    vlSelf->top__DOT__u_bridge__DOT__host_mwr_ready_pulse 
        = __Vdly__top__DOT__u_bridge__DOT__host_mwr_ready_pulse;
    vlSelf->top__DOT__u_bridge__DOT__host_mwr_pending 
        = __Vdly__top__DOT__u_bridge__DOT__host_mwr_pending;
    vlSelf->top__DOT__u_sniffer__DOT__capture_tx = 
        ((IData)(vlSelf->top__DOT__u_sniffer__DOT__tx_valid) 
         & ((0U == (IData)(vlSelf->top__DOT__u_sniffer__DOT__filter_mode)) 
            | ((2U == (IData)(vlSelf->top__DOT__u_sniffer__DOT__filter_mode)) 
               | ((3U == (IData)(vlSelf->top__DOT__u_sniffer__DOT__filter_mode)) 
                  & (IData)(vlSelf->top__DOT__u_sniffer__DOT__tx_is_cpl_err)))));
    vlSelf->top__DOT__u_sniffer__DOT__rx_is_cpl_err 
        = ((IData)(vlSelf->top__DOT__u_sniffer__DOT__rx_valid) 
           & (IData)(((0xa000000U == (0x1f000000U & 
                                      vlSelf->rx_st_hdr[3U])) 
                      & (0U != (7U & (vlSelf->rx_st_hdr[1U] 
                                      >> 0xdU))))));
    vlSelf->top__DOT__u_sniffer__DOT____VdfgRegularize_h54215f63_1_0 
        = ((IData)(vlSelf->top__DOT__pcie_dbg_wen) 
           & (4U == (0xffcU & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))));
    vlSelf->top__DOT__u_axi_sniffer__DOT____VdfgRegularize_h1732209f_5_0 
        = ((IData)(vlSelf->top__DOT__axi_dbg_wen) & 
           (4U == (0xfcU & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))));
    vlSelf->top__DOT__u_sniffer__DOT__capture_rx = 
        ((IData)(vlSelf->top__DOT__u_sniffer__DOT__rx_valid) 
         & ((0U == (IData)(vlSelf->top__DOT__u_sniffer__DOT__filter_mode)) 
            | ((1U == (IData)(vlSelf->top__DOT__u_sniffer__DOT__filter_mode)) 
               | ((3U == (IData)(vlSelf->top__DOT__u_sniffer__DOT__filter_mode)) 
                  & (IData)(vlSelf->top__DOT__u_sniffer__DOT__rx_is_cpl_err)))));
    vlSelf->top__DOT__u_sniffer__DOT__ctrl_clear = 
        ((IData)(vlSelf->top__DOT__u_sniffer__DOT____VdfgRegularize_h54215f63_1_0) 
         & (IData)((vlSelf->top__DOT__brg_wdata >> 2U)));
    vlSelf->top__DOT__u_axi_sniffer__DOT__ctrl_clear 
        = ((IData)(vlSelf->top__DOT__u_axi_sniffer__DOT____VdfgRegularize_h1732209f_5_0) 
           & (IData)((vlSelf->top__DOT__brg_wdata >> 2U)));
    vlSelf->top__DOT__dma_host_wready = __Vdly__top__DOT__dma_host_wready;
    vlSelf->top__DOT__u_dma__DOT__u_c2h__DOT__cur_host 
        = __Vdly__top__DOT__u_dma__DOT__u_c2h__DOT__cur_host;
    vlSelf->top__DOT__u_dma__DOT__u_c2h__DOT__cur_local 
        = __Vdly__top__DOT__u_dma__DOT__u_c2h__DOT__cur_local;
    vlSelf->top__DOT__u_dma__DOT__u_c2h__DOT__bytes_left 
        = __Vdly__top__DOT__u_dma__DOT__u_c2h__DOT__bytes_left;
    vlSelf->top__DOT__u_dma__DOT__c2h_host_awvalid 
        = __Vdly__top__DOT__u_dma__DOT__c2h_host_awvalid;
    vlSelf->top__DOT__dma_host_awready = __Vdly__top__DOT__dma_host_awready;
    vlSelf->top__DOT__u_dma__DOT__c2h_host_wvalid = __Vdly__top__DOT__u_dma__DOT__c2h_host_wvalid;
    vlSelf->top__DOT__dma_host_bvalid = __Vdly__top__DOT__dma_host_bvalid;
    vlSelf->top__DOT__u_dma__DOT__length_reg = __Vdly__top__DOT__u_dma__DOT__length_reg;
    vlSelf->top__DOT__u_dma__DOT__host_addr = __Vdly__top__DOT__u_dma__DOT__host_addr;
    vlSelf->top__DOT__u_dma__DOT__local_addr = __Vdly__top__DOT__u_dma__DOT__local_addr;
    vlSelf->top__DOT__u_dma__DOT__c2h_local_arvalid 
        = __Vdly__top__DOT__u_dma__DOT__c2h_local_arvalid;
    vlSelf->top__DOT__u_dma__DOT__ctrl_reg = __Vdly__top__DOT__u_dma__DOT__ctrl_reg;
    vlSelf->top__DOT__ram_rdata = __Vdly__top__DOT__ram_rdata;
    vlSelf->top__DOT__u_dma__DOT__u_c2h__DOT__state 
        = __Vdly__top__DOT__u_dma__DOT__u_c2h__DOT__state;
    vlSelf->top__DOT__ram_arready = __Vdly__top__DOT__ram_arready;
    vlSelf->top__DOT__arb_owner = __Vdly__top__DOT__arb_owner;
    vlSelf->top__DOT__u_dma__DOT__start = (1U & vlSelf->top__DOT__u_dma__DOT__ctrl_reg);
    vlSelf->top__DOT__u_dma__DOT__busy = (((0U != (IData)(vlSelf->top__DOT__u_dma__DOT__u_c2h__DOT__state)) 
                                           & (5U != (IData)(vlSelf->top__DOT__u_dma__DOT__u_c2h__DOT__state))) 
                                          | ((0U != (IData)(vlSelf->top__DOT__u_dma__DOT__u_h2c__DOT__state)) 
                                             & (5U 
                                                != (IData)(vlSelf->top__DOT__u_dma__DOT__u_h2c__DOT__state))));
    vlSelf->top__DOT__u_dma__DOT__done = ((5U == (IData)(vlSelf->top__DOT__u_dma__DOT__u_c2h__DOT__state)) 
                                          | (5U == (IData)(vlSelf->top__DOT__u_dma__DOT__u_h2c__DOT__state)));
    if (vlSelf->top__DOT__arb_owner) {
        vlSelf->top__DOT__dma_local_bvalid = vlSelf->top__DOT__ram_bvalid;
        vlSelf->top__DOT__dma_local_rvalid = vlSelf->top__DOT__ram_rvalid;
        vlSelf->top__DOT__ram_wdata = vlSelf->top__DOT__u_dma__DOT__h2c_local_wdata;
        vlSelf->top__DOT__ram_wstrb = vlSelf->top__DOT__u_dma__DOT__h2c_local_wstrb;
    } else {
        vlSelf->top__DOT__dma_local_bvalid = 0U;
        vlSelf->top__DOT__dma_local_rvalid = 0U;
        vlSelf->top__DOT__ram_wdata = vlSelf->top__DOT__brg_wdata;
        vlSelf->top__DOT__ram_wstrb = vlSelf->top__DOT__brg_wstrb;
    }
    if (vlSelf->top__DOT__wr_to_ram) {
        vlSelf->top__DOT__brg_wready = ((~ (IData)(vlSelf->top__DOT__arb_owner)) 
                                        & (IData)(vlSelf->top__DOT__ram_wready));
        vlSelf->top__DOT__brg_awready = ((~ (IData)(vlSelf->top__DOT__arb_owner)) 
                                         & (IData)(vlSelf->top__DOT__ram_awready));
    } else {
        vlSelf->top__DOT__brg_wready = vlSelf->top__DOT__dma_s_wready;
        vlSelf->top__DOT__brg_awready = vlSelf->top__DOT__dma_s_awready;
    }
    vlSelf->top__DOT__ram_bar_bvalid = ((~ (IData)(vlSelf->top__DOT__arb_owner)) 
                                        & (IData)(vlSelf->top__DOT__ram_bvalid));
    vlSelf->top__DOT__brg_arready = ((IData)(vlSelf->top__DOT__rd_to_dbg)
                                      ? (0U == (IData)(vlSelf->top__DOT__dbg_rd_state))
                                      : ((IData)(vlSelf->top__DOT__rd_to_ram)
                                          ? ((~ (IData)(vlSelf->top__DOT__arb_owner)) 
                                             & (IData)(vlSelf->top__DOT__ram_arready))
                                          : (IData)(vlSelf->top__DOT__dma_s_arready)));
    vlSelf->top__DOT__ram_bar_rvalid = ((~ (IData)(vlSelf->top__DOT__arb_owner)) 
                                        & (IData)(vlSelf->top__DOT__ram_rvalid));
    vlSelf->top__DOT__brg_bvalid = ((IData)(vlSelf->top__DOT__dma_s_bvalid) 
                                    | (IData)(vlSelf->top__DOT__ram_bar_bvalid));
    vlSelf->top__DOT__u_axi_sniffer__DOT__aw_handshake 
        = ((IData)(vlSelf->top__DOT__brg_awready) & (IData)(vlSelf->top__DOT__brg_awvalid));
    vlSelf->top__DOT__u_axi_sniffer__DOT__ar_handshake 
        = ((IData)(vlSelf->top__DOT__brg_arready) & (IData)(vlSelf->top__DOT__brg_arvalid));
    vlSelf->top__DOT__brg_rvalid_mux = ((IData)(vlSelf->top__DOT__dma_s_rvalid) 
                                        | ((IData)(vlSelf->top__DOT__ram_bar_rvalid) 
                                           | (IData)(vlSelf->top__DOT__dbg_rvalid)));
    if (vlSelf->top__DOT__dma_s_rvalid) {
        vlSelf->top__DOT__brg_rresp_mux = vlSelf->top__DOT__dma_s_rresp;
        vlSelf->top__DOT__brg_rdata_mux = vlSelf->top__DOT__dma_s_rdata;
    } else if (vlSelf->top__DOT__ram_bar_rvalid) {
        vlSelf->top__DOT__brg_rresp_mux = vlSelf->top__DOT__ram_rresp;
        vlSelf->top__DOT__brg_rdata_mux = vlSelf->top__DOT__ram_rdata;
    } else {
        vlSelf->top__DOT__brg_rresp_mux = 0U;
        vlSelf->top__DOT__brg_rdata_mux = (QData)((IData)(vlSelf->top__DOT__dbg_rdata_latched));
    }
}

void Vtop___024root___eval_triggers__act(Vtop___024root* vlSelf);

bool Vtop___024root___eval_phase__act(Vtop___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__act\n"); );
    // Init
    VlTriggerVec<1> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vtop___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelf->__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
        vlSelf->__VnbaTriggered.thisOr(vlSelf->__VactTriggered);
        Vtop___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vtop___024root___eval_phase__nba(Vtop___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__nba\n"); );
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelf->__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vtop___024root___eval_nba(vlSelf);
        vlSelf->__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__ico(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__nba(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(Vtop___024root* vlSelf);
#endif  // VL_DEBUG

void Vtop___024root___eval(Vtop___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval\n"); );
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
            Vtop___024root___dump_triggers__ico(vlSelf);
#endif
            VL_FATAL_MT("../rtl/top.sv", 16, "", "Input combinational region did not converge.");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        __VicoContinue = 0U;
        if (Vtop___024root___eval_phase__ico(vlSelf)) {
            __VicoContinue = 1U;
        }
        vlSelf->__VicoFirstIteration = 0U;
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            Vtop___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("../rtl/top.sv", 16, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                Vtop___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("../rtl/top.sv", 16, "", "Active region did not converge.");
            }
            vlSelf->__VactIterCount = ((IData)(1U) 
                                       + vlSelf->__VactIterCount);
            vlSelf->__VactContinue = 0U;
            if (Vtop___024root___eval_phase__act(vlSelf)) {
                vlSelf->__VactContinue = 1U;
            }
        }
        if (Vtop___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vtop___024root___eval_debug_assertions(Vtop___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_debug_assertions\n"); );
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
