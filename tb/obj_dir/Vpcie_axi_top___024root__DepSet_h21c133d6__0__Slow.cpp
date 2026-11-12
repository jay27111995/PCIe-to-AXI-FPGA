// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vpcie_axi_top.h for the primary calling header

#include "Vpcie_axi_top__pch.h"
#include "Vpcie_axi_top___024root.h"

VL_ATTR_COLD void Vpcie_axi_top___024root___eval_static(Vpcie_axi_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vpcie_axi_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpcie_axi_top___024root___eval_static\n"); );
}

VL_ATTR_COLD void Vpcie_axi_top___024root___eval_initial__TOP(Vpcie_axi_top___024root* vlSelf);

VL_ATTR_COLD void Vpcie_axi_top___024root___eval_initial(Vpcie_axi_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vpcie_axi_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpcie_axi_top___024root___eval_initial\n"); );
    // Body
    Vpcie_axi_top___024root___eval_initial__TOP(vlSelf);
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = vlSelf->clk;
    vlSelf->__Vtrigprevexpr___TOP__rst_n__0 = vlSelf->rst_n;
}

VL_ATTR_COLD void Vpcie_axi_top___024root___eval_initial__TOP(Vpcie_axi_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vpcie_axi_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpcie_axi_top___024root___eval_initial__TOP\n"); );
    // Body
    vlSelf->rx_st_ready = 1U;
    vlSelf->rx_hcrdt_update_cnt = 0x3fU;
}

VL_ATTR_COLD void Vpcie_axi_top___024root___eval_final(Vpcie_axi_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vpcie_axi_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpcie_axi_top___024root___eval_final\n"); );
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vpcie_axi_top___024root___dump_triggers__stl(Vpcie_axi_top___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vpcie_axi_top___024root___eval_phase__stl(Vpcie_axi_top___024root* vlSelf);

VL_ATTR_COLD void Vpcie_axi_top___024root___eval_settle(Vpcie_axi_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vpcie_axi_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpcie_axi_top___024root___eval_settle\n"); );
    // Init
    IData/*31:0*/ __VstlIterCount;
    CData/*0:0*/ __VstlContinue;
    // Body
    __VstlIterCount = 0U;
    vlSelf->__VstlFirstIteration = 1U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        if (VL_UNLIKELY((0x64U < __VstlIterCount))) {
#ifdef VL_DEBUG
            Vpcie_axi_top___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("../rtl/../rtl/pcie_axi_top.sv", 8, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (Vpcie_axi_top___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelf->__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vpcie_axi_top___024root___dump_triggers__stl(Vpcie_axi_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vpcie_axi_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpcie_axi_top___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ vlSelf->__VstlTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VstlTriggered.word(0U))) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vpcie_axi_top___024root___stl_sequent__TOP__0(Vpcie_axi_top___024root* vlSelf);

VL_ATTR_COLD void Vpcie_axi_top___024root___eval_stl(Vpcie_axi_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vpcie_axi_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpcie_axi_top___024root___eval_stl\n"); );
    // Body
    if ((1ULL & vlSelf->__VstlTriggered.word(0U))) {
        Vpcie_axi_top___024root___stl_sequent__TOP__0(vlSelf);
        vlSelf->__Vm_traceActivity[2U] = 1U;
        vlSelf->__Vm_traceActivity[1U] = 1U;
        vlSelf->__Vm_traceActivity[0U] = 1U;
    }
}

VL_ATTR_COLD void Vpcie_axi_top___024root___stl_sequent__TOP__0(Vpcie_axi_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vpcie_axi_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpcie_axi_top___024root___stl_sequent__TOP__0\n"); );
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
    vlSelf->rx_dcrdt_update_cnt = ((3U == (IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__state))
                                    ? 0U : 0xfffU);
    vlSelf->pcie_axi_top__DOT__u_dma__DOT__start = 
        (1U & vlSelf->pcie_axi_top__DOT__u_dma__DOT__ctrl_reg);
    vlSelf->pcie_axi_top__DOT__ram_awvalid = ((IData)(vlSelf->pcie_axi_top__DOT__brg_awvalid) 
                                              & (vlSelf->pcie_axi_top__DOT__brg_awaddr 
                                                 >> 0xcU));
    vlSelf->pcie_axi_top__DOT__ram_arvalid = ((IData)(vlSelf->pcie_axi_top__DOT__brg_arvalid) 
                                              & (vlSelf->pcie_axi_top__DOT__brg_araddr 
                                                 >> 0xcU));
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

VL_ATTR_COLD void Vpcie_axi_top___024root___eval_triggers__stl(Vpcie_axi_top___024root* vlSelf);

VL_ATTR_COLD bool Vpcie_axi_top___024root___eval_phase__stl(Vpcie_axi_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vpcie_axi_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpcie_axi_top___024root___eval_phase__stl\n"); );
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    Vpcie_axi_top___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelf->__VstlTriggered.any();
    if (__VstlExecute) {
        Vpcie_axi_top___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vpcie_axi_top___024root___dump_triggers__ico(Vpcie_axi_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vpcie_axi_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpcie_axi_top___024root___dump_triggers__ico\n"); );
    // Body
    if ((1U & (~ vlSelf->__VicoTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VicoTriggered.word(0U))) {
        VL_DBG_MSGF("         'ico' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vpcie_axi_top___024root___dump_triggers__act(Vpcie_axi_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vpcie_axi_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpcie_axi_top___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ vlSelf->__VactTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge clk or negedge rst_n)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vpcie_axi_top___024root___dump_triggers__nba(Vpcie_axi_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vpcie_axi_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpcie_axi_top___024root___dump_triggers__nba\n"); );
    // Body
    if ((1U & (~ vlSelf->__VnbaTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge clk or negedge rst_n)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vpcie_axi_top___024root___ctor_var_reset(Vpcie_axi_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vpcie_axi_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpcie_axi_top___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->clk = VL_RAND_RESET_I(1);
    vlSelf->rst_n = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(128, vlSelf->rx_st_hdr);
    VL_RAND_RESET_W(256, vlSelf->rx_st_data);
    vlSelf->rx_st_sop = VL_RAND_RESET_I(1);
    vlSelf->rx_st_eop = VL_RAND_RESET_I(1);
    vlSelf->rx_st_hvalid = VL_RAND_RESET_I(1);
    vlSelf->rx_st_dvalid = VL_RAND_RESET_I(1);
    vlSelf->rx_st_bar = VL_RAND_RESET_I(3);
    vlSelf->rx_st_ready = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(128, vlSelf->tx_st_hdr);
    VL_RAND_RESET_W(256, vlSelf->tx_st_data);
    vlSelf->tx_st_sop = VL_RAND_RESET_I(1);
    vlSelf->tx_st_eop = VL_RAND_RESET_I(1);
    vlSelf->tx_st_hvalid = VL_RAND_RESET_I(1);
    vlSelf->tx_st_dvalid = VL_RAND_RESET_I(1);
    vlSelf->tx_st_ready = VL_RAND_RESET_I(1);
    vlSelf->rx_hcrdt_init = VL_RAND_RESET_I(3);
    vlSelf->rx_hcrdt_update = VL_RAND_RESET_I(3);
    vlSelf->rx_hcrdt_update_cnt = VL_RAND_RESET_I(6);
    vlSelf->rx_dcrdt_init = VL_RAND_RESET_I(3);
    vlSelf->rx_dcrdt_update = VL_RAND_RESET_I(3);
    vlSelf->rx_dcrdt_update_cnt = VL_RAND_RESET_I(12);
    vlSelf->tx_hcrdt_init = VL_RAND_RESET_I(3);
    vlSelf->tx_hcrdt_init_ack = VL_RAND_RESET_I(3);
    vlSelf->tx_hcrdt_update = VL_RAND_RESET_I(3);
    vlSelf->tx_hcrdt_update_cnt = VL_RAND_RESET_I(6);
    vlSelf->tx_dcrdt_init = VL_RAND_RESET_I(3);
    vlSelf->tx_dcrdt_init_ack = VL_RAND_RESET_I(3);
    vlSelf->tx_dcrdt_update = VL_RAND_RESET_I(3);
    vlSelf->tx_dcrdt_update_cnt = VL_RAND_RESET_I(12);
    vlSelf->link_up = VL_RAND_RESET_I(1);
    vlSelf->ltssm_state = VL_RAND_RESET_I(6);
    vlSelf->dma_irq = VL_RAND_RESET_I(1);
    vlSelf->pcie_axi_top__DOT__brg_awaddr = VL_RAND_RESET_I(32);
    vlSelf->pcie_axi_top__DOT__brg_araddr = VL_RAND_RESET_I(32);
    vlSelf->pcie_axi_top__DOT__brg_wdata = VL_RAND_RESET_Q(64);
    vlSelf->pcie_axi_top__DOT__brg_wstrb = VL_RAND_RESET_I(8);
    vlSelf->pcie_axi_top__DOT__brg_awvalid = VL_RAND_RESET_I(1);
    vlSelf->pcie_axi_top__DOT__brg_awready = VL_RAND_RESET_I(1);
    vlSelf->pcie_axi_top__DOT__brg_wvalid = VL_RAND_RESET_I(1);
    vlSelf->pcie_axi_top__DOT__brg_wready = VL_RAND_RESET_I(1);
    vlSelf->pcie_axi_top__DOT__brg_bready = VL_RAND_RESET_I(1);
    vlSelf->pcie_axi_top__DOT__brg_arvalid = VL_RAND_RESET_I(1);
    vlSelf->pcie_axi_top__DOT__brg_arready = VL_RAND_RESET_I(1);
    vlSelf->pcie_axi_top__DOT__brg_rready = VL_RAND_RESET_I(1);
    vlSelf->pcie_axi_top__DOT__dma_mrd_valid = VL_RAND_RESET_I(1);
    vlSelf->pcie_axi_top__DOT__dma_mrd_ready = VL_RAND_RESET_I(1);
    vlSelf->pcie_axi_top__DOT__dma_mrd_addr = VL_RAND_RESET_Q(64);
    vlSelf->pcie_axi_top__DOT__dma_mrd_len = VL_RAND_RESET_I(10);
    vlSelf->pcie_axi_top__DOT__dma_mrd_tag = VL_RAND_RESET_I(8);
    vlSelf->pcie_axi_top__DOT__dma_mwr_valid = VL_RAND_RESET_I(1);
    vlSelf->pcie_axi_top__DOT__dma_mwr_ready = VL_RAND_RESET_I(1);
    vlSelf->pcie_axi_top__DOT__dma_mwr_addr = VL_RAND_RESET_Q(64);
    vlSelf->pcie_axi_top__DOT__dma_mwr_data = VL_RAND_RESET_Q(64);
    vlSelf->pcie_axi_top__DOT__dma_mwr_len = VL_RAND_RESET_I(10);
    vlSelf->pcie_axi_top__DOT__dma_cpl_valid = VL_RAND_RESET_I(1);
    vlSelf->pcie_axi_top__DOT__dma_cpl_tag = VL_RAND_RESET_I(8);
    vlSelf->pcie_axi_top__DOT__dma_cpl_data = VL_RAND_RESET_Q(64);
    vlSelf->pcie_axi_top__DOT__dma_rdata = VL_RAND_RESET_Q(64);
    vlSelf->pcie_axi_top__DOT__dma_bresp = VL_RAND_RESET_I(2);
    vlSelf->pcie_axi_top__DOT__dma_rresp = VL_RAND_RESET_I(2);
    vlSelf->pcie_axi_top__DOT__dma_awready = VL_RAND_RESET_I(1);
    vlSelf->pcie_axi_top__DOT__dma_wready = VL_RAND_RESET_I(1);
    vlSelf->pcie_axi_top__DOT__dma_bvalid = VL_RAND_RESET_I(1);
    vlSelf->pcie_axi_top__DOT__dma_arready = VL_RAND_RESET_I(1);
    vlSelf->pcie_axi_top__DOT__dma_rvalid = VL_RAND_RESET_I(1);
    vlSelf->pcie_axi_top__DOT__ram_awvalid = VL_RAND_RESET_I(1);
    vlSelf->pcie_axi_top__DOT__ram_arvalid = VL_RAND_RESET_I(1);
    vlSelf->pcie_axi_top__DOT__dma_ram_awaddr = VL_RAND_RESET_I(32);
    vlSelf->pcie_axi_top__DOT__dma_ram_araddr = VL_RAND_RESET_I(32);
    vlSelf->pcie_axi_top__DOT__dma_ram_wdata = VL_RAND_RESET_Q(64);
    vlSelf->pcie_axi_top__DOT__dma_ram_wstrb = VL_RAND_RESET_I(8);
    vlSelf->pcie_axi_top__DOT__dma_ram_awvalid = VL_RAND_RESET_I(1);
    vlSelf->pcie_axi_top__DOT__dma_ram_wvalid = VL_RAND_RESET_I(1);
    vlSelf->pcie_axi_top__DOT__dma_ram_bready = VL_RAND_RESET_I(1);
    vlSelf->pcie_axi_top__DOT__dma_ram_arvalid = VL_RAND_RESET_I(1);
    vlSelf->pcie_axi_top__DOT__dma_ram_rready = VL_RAND_RESET_I(1);
    vlSelf->pcie_axi_top__DOT__ram_busy = VL_RAND_RESET_I(1);
    vlSelf->pcie_axi_top__DOT__ram_owner = VL_RAND_RESET_I(1);
    vlSelf->pcie_axi_top__DOT__ram_real_wdata = VL_RAND_RESET_Q(64);
    vlSelf->pcie_axi_top__DOT__ram_real_rdata = VL_RAND_RESET_Q(64);
    vlSelf->pcie_axi_top__DOT__ram_real_wstrb = VL_RAND_RESET_I(8);
    vlSelf->pcie_axi_top__DOT__ram_real_bresp = VL_RAND_RESET_I(2);
    vlSelf->pcie_axi_top__DOT__ram_real_rresp = VL_RAND_RESET_I(2);
    vlSelf->pcie_axi_top__DOT__ram_real_awready = VL_RAND_RESET_I(1);
    vlSelf->pcie_axi_top__DOT__ram_real_wready = VL_RAND_RESET_I(1);
    vlSelf->pcie_axi_top__DOT__ram_real_bvalid = VL_RAND_RESET_I(1);
    vlSelf->pcie_axi_top__DOT__ram_real_bready = VL_RAND_RESET_I(1);
    vlSelf->pcie_axi_top__DOT__ram_real_arready = VL_RAND_RESET_I(1);
    vlSelf->pcie_axi_top__DOT__ram_real_rvalid = VL_RAND_RESET_I(1);
    vlSelf->pcie_axi_top__DOT__ram_real_rready = VL_RAND_RESET_I(1);
    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_cpl_hdr_dec = VL_RAND_RESET_I(1);
    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_cpl_data_dec = VL_RAND_RESET_I(1);
    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_fmt = VL_RAND_RESET_I(3);
    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_type = VL_RAND_RESET_I(5);
    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_len = VL_RAND_RESET_I(10);
    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_rid = VL_RAND_RESET_I(16);
    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_tag = VL_RAND_RESET_I(8);
    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_fbe = VL_RAND_RESET_I(4);
    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_lbe = VL_RAND_RESET_I(4);
    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_addr = VL_RAND_RESET_Q(64);
    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_is_mrd = VL_RAND_RESET_I(1);
    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_is_mwr = VL_RAND_RESET_I(1);
    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_is_cpld = VL_RAND_RESET_I(1);
    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__state = VL_RAND_RESET_I(4);
    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__bar_req_rid = VL_RAND_RESET_I(16);
    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__bar_req_tag = VL_RAND_RESET_I(8);
    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__bar_req_lower_addr = VL_RAND_RESET_I(7);
    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__bar_cpl_data = VL_RAND_RESET_Q(64);
    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__bar_cpl_status = VL_RAND_RESET_I(2);
    VL_RAND_RESET_W(128, vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_hdr_r);
    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_data_r = VL_RAND_RESET_Q(64);
    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__state = VL_RAND_RESET_I(2);
    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__cnt = VL_RAND_RESET_I(4);
    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__tx_cpl_hdr_cnt = VL_RAND_RESET_I(16);
    vlSelf->pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__tx_cpl_data_cnt = VL_RAND_RESET_I(20);
    vlSelf->pcie_axi_top__DOT__u_dma__DOT__ctrl_reg = VL_RAND_RESET_I(32);
    vlSelf->pcie_axi_top__DOT__u_dma__DOT__status_reg = VL_RAND_RESET_I(32);
    vlSelf->pcie_axi_top__DOT__u_dma__DOT__host_addr_lo = VL_RAND_RESET_I(32);
    vlSelf->pcie_axi_top__DOT__u_dma__DOT__host_addr_hi = VL_RAND_RESET_I(32);
    vlSelf->pcie_axi_top__DOT__u_dma__DOT__local_addr = VL_RAND_RESET_I(32);
    vlSelf->pcie_axi_top__DOT__u_dma__DOT__length_reg = VL_RAND_RESET_I(32);
    vlSelf->pcie_axi_top__DOT__u_dma__DOT__start = VL_RAND_RESET_I(1);
    vlSelf->pcie_axi_top__DOT__u_dma__DOT__dma_state = VL_RAND_RESET_I(4);
    vlSelf->pcie_axi_top__DOT__u_dma__DOT__bytes_remaining = VL_RAND_RESET_I(32);
    vlSelf->pcie_axi_top__DOT__u_dma__DOT__cur_host_addr = VL_RAND_RESET_Q(64);
    vlSelf->pcie_axi_top__DOT__u_dma__DOT__cur_local_addr = VL_RAND_RESET_I(32);
    vlSelf->pcie_axi_top__DOT__u_dma__DOT__dma_data_buf = VL_RAND_RESET_Q(64);
    vlSelf->pcie_axi_top__DOT__u_dma__DOT__cur_tag = VL_RAND_RESET_I(8);
    for (int __Vi0 = 0; __Vi0 < 512; ++__Vi0) {
        vlSelf->pcie_axi_top__DOT__u_ram__DOT__mem[__Vi0] = VL_RAND_RESET_Q(64);
    }
    vlSelf->pcie_axi_top__DOT__u_ram__DOT__rd_addr_latched = VL_RAND_RESET_I(9);
    vlSelf->pcie_axi_top__DOT__u_ram__DOT__read_pending = VL_RAND_RESET_I(1);
    vlSelf->pcie_axi_top__DOT__u_ram__DOT__unnamedblk1__DOT__i = 0;
    vlSelf->__Vfunc_is_4dw__7__Vfuncout = VL_RAND_RESET_I(1);
    vlSelf->__Vfunc_is_4dw__7__fmt = VL_RAND_RESET_I(3);
    vlSelf->__Vfunc_hdr_addr64__8__Vfuncout = VL_RAND_RESET_Q(64);
    VL_RAND_RESET_W(128, vlSelf->__Vfunc_hdr_addr64__8__h);
    vlSelf->__Vfunc_hdr_addr32__9__Vfuncout = VL_RAND_RESET_I(32);
    VL_RAND_RESET_W(128, vlSelf->__Vfunc_hdr_addr32__9__h);
    vlSelf->__Vfunc_has_data__10__Vfuncout = VL_RAND_RESET_I(1);
    vlSelf->__Vfunc_has_data__10__fmt = VL_RAND_RESET_I(3);
    vlSelf->__Vfunc_has_data__11__Vfuncout = VL_RAND_RESET_I(1);
    vlSelf->__Vfunc_has_data__11__fmt = VL_RAND_RESET_I(3);
    vlSelf->__Vfunc_has_data__12__Vfuncout = VL_RAND_RESET_I(1);
    vlSelf->__Vfunc_has_data__12__fmt = VL_RAND_RESET_I(3);
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = VL_RAND_RESET_I(1);
    vlSelf->__Vtrigprevexpr___TOP__rst_n__0 = VL_RAND_RESET_I(1);
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}
