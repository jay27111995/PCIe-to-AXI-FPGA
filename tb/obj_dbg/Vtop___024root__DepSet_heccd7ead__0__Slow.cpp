// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop__pch.h"
#include "Vtop___024root.h"

VL_ATTR_COLD void Vtop___024root___eval_static(Vtop___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_static\n"); );
}

VL_ATTR_COLD void Vtop___024root___eval_initial__TOP(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_initial(Vtop___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_initial\n"); );
    // Body
    Vtop___024root___eval_initial__TOP(vlSelf);
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = vlSelf->clk;
    vlSelf->__Vtrigprevexpr___TOP__rst_n__0 = vlSelf->rst_n;
}

VL_ATTR_COLD void Vtop___024root___eval_initial__TOP(Vtop___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_initial__TOP\n"); );
    // Body
    vlSelf->rx_hcrdt_update_cnt = 0x3fU;
}

VL_ATTR_COLD void Vtop___024root___eval_final(Vtop___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_final\n"); );
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__stl(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vtop___024root___eval_phase__stl(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_settle(Vtop___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_settle\n"); );
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
            Vtop___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("../rtl/top.sv", 16, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (Vtop___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelf->__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__stl(Vtop___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ vlSelf->__VstlTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VstlTriggered.word(0U))) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtop___024root___stl_sequent__TOP__0(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_stl(Vtop___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_stl\n"); );
    // Body
    if ((1ULL & vlSelf->__VstlTriggered.word(0U))) {
        Vtop___024root___stl_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD void Vtop___024root___stl_sequent__TOP__0(Vtop___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___stl_sequent__TOP__0\n"); );
    // Init
    CData/*0:0*/ top__DOT____VdfgRegularize_h245778ca_0_2;
    top__DOT____VdfgRegularize_h245778ca_0_2 = 0;
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
    vlSelf->tx_st_hdr[0U] = vlSelf->top__DOT__u_bridge__DOT__tx_hdr_r[0U];
    vlSelf->tx_st_hdr[1U] = vlSelf->top__DOT__u_bridge__DOT__tx_hdr_r[1U];
    vlSelf->tx_st_hdr[2U] = vlSelf->top__DOT__u_bridge__DOT__tx_hdr_r[2U];
    vlSelf->tx_st_hdr[3U] = vlSelf->top__DOT__u_bridge__DOT__tx_hdr_r[3U];
    vlSelf->tx_st_data[0U] = vlSelf->top__DOT__u_bridge__DOT__tx_data_r[0U];
    vlSelf->tx_st_data[1U] = vlSelf->top__DOT__u_bridge__DOT__tx_data_r[1U];
    vlSelf->tx_st_data[2U] = vlSelf->top__DOT__u_bridge__DOT__tx_data_r[2U];
    vlSelf->tx_st_data[3U] = vlSelf->top__DOT__u_bridge__DOT__tx_data_r[3U];
    vlSelf->tx_st_data[4U] = vlSelf->top__DOT__u_bridge__DOT__tx_data_r[4U];
    vlSelf->tx_st_data[5U] = vlSelf->top__DOT__u_bridge__DOT__tx_data_r[5U];
    vlSelf->tx_st_data[6U] = vlSelf->top__DOT__u_bridge__DOT__tx_data_r[6U];
    vlSelf->tx_st_data[7U] = vlSelf->top__DOT__u_bridge__DOT__tx_data_r[7U];
    vlSelf->rx_dcrdt_update_cnt = ((3U == (IData)(vlSelf->top__DOT__u_bridge__DOT__u_crdt__DOT__state))
                                    ? 0U : 0xfffU);
    vlSelf->top__DOT__u_dma__DOT__start = (1U & vlSelf->top__DOT__u_dma__DOT__ctrl_reg);
    vlSelf->top__DOT__dma_local_bvalid = ((IData)(vlSelf->top__DOT__arb_owner) 
                                          & (IData)(vlSelf->top__DOT__ram_bvalid));
    vlSelf->top__DOT__dma_local_rvalid = ((IData)(vlSelf->top__DOT__arb_owner) 
                                          & (IData)(vlSelf->top__DOT__ram_rvalid));
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
    vlSelf->top__DOT__u_dma__DOT__busy = (((0U != (IData)(vlSelf->top__DOT__u_dma__DOT__u_c2h__DOT__state)) 
                                           & (5U != (IData)(vlSelf->top__DOT__u_dma__DOT__u_c2h__DOT__state))) 
                                          | ((0U != (IData)(vlSelf->top__DOT__u_dma__DOT__u_h2c__DOT__state)) 
                                             & (5U 
                                                != (IData)(vlSelf->top__DOT__u_dma__DOT__u_h2c__DOT__state))));
    vlSelf->top__DOT__u_dma__DOT__done = ((5U == (IData)(vlSelf->top__DOT__u_dma__DOT__u_c2h__DOT__state)) 
                                          | (5U == (IData)(vlSelf->top__DOT__u_dma__DOT__u_h2c__DOT__state)));
    if (vlSelf->top__DOT__arb_owner) {
        vlSelf->top__DOT__ram_wdata = vlSelf->top__DOT__u_dma__DOT__h2c_local_wdata;
        vlSelf->top__DOT__ram_wstrb = vlSelf->top__DOT__u_dma__DOT__h2c_local_wstrb;
    } else {
        vlSelf->top__DOT__ram_wdata = vlSelf->top__DOT__brg_wdata;
        vlSelf->top__DOT__ram_wstrb = vlSelf->top__DOT__brg_wstrb;
    }
    vlSelf->top__DOT__dbg_rdata = ((IData)(vlSelf->top__DOT__dbg_sel_axi_latched)
                                    ? vlSelf->top__DOT__axi_dbg_rdata
                                    : vlSelf->top__DOT__pcie_dbg_rdata);
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
    vlSelf->top__DOT__ram_bar_bvalid = ((~ (IData)(vlSelf->top__DOT__arb_owner)) 
                                        & (IData)(vlSelf->top__DOT__ram_bvalid));
    vlSelf->top__DOT__u_sniffer__DOT__tx_valid = ((IData)(vlSelf->tx_st_hvalid) 
                                                  & (IData)(vlSelf->tx_st_sop));
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
    vlSelf->rx_st_ready = (0U == (IData)(vlSelf->top__DOT__u_bridge__DOT__tx_state));
    vlSelf->top__DOT__ram_bar_rvalid = ((~ (IData)(vlSelf->top__DOT__arb_owner)) 
                                        & (IData)(vlSelf->top__DOT__ram_rvalid));
    vlSelf->top__DOT__wr_to_ram = (IData)((0x1000U 
                                           == (0x3000U 
                                               & vlSelf->top__DOT__brg_awaddr)));
    top__DOT____VdfgRegularize_h245778ca_0_2 = ((IData)(vlSelf->top__DOT__brg_awvalid) 
                                                & (IData)(vlSelf->top__DOT__brg_wvalid));
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
    vlSelf->top__DOT__brg_bvalid = ((IData)(vlSelf->top__DOT__dma_s_bvalid) 
                                    | (IData)(vlSelf->top__DOT__ram_bar_bvalid));
    vlSelf->top__DOT__u_sniffer__DOT__tx_is_cpl_err 
        = ((IData)(vlSelf->top__DOT__u_sniffer__DOT__tx_valid) 
           & (IData)(((0xa000000U == (0x1f000000U & 
                                      vlSelf->top__DOT__u_bridge__DOT__tx_hdr_r[3U])) 
                      & (0U != (7U & (vlSelf->top__DOT__u_bridge__DOT__tx_hdr_r[1U] 
                                      >> 0xdU))))));
    vlSelf->top__DOT__rd_to_dbg = ((IData)(vlSelf->top__DOT__rd_to_axi_dbg) 
                                   | (0x2000U == (0x3000U 
                                                  & vlSelf->top__DOT__brg_araddr)));
    vlSelf->top__DOT__ram_bar_arvalid = ((IData)(vlSelf->top__DOT__brg_arvalid) 
                                         & (IData)(vlSelf->top__DOT__rd_to_ram));
    vlSelf->top__DOT__u_sniffer__DOT__rx_valid = ((IData)(vlSelf->rx_st_hvalid) 
                                                  & ((IData)(vlSelf->rx_st_ready) 
                                                     & (IData)(vlSelf->rx_st_sop)));
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
    if (vlSelf->top__DOT__wr_to_ram) {
        vlSelf->top__DOT__ram_bar_awvalid = vlSelf->top__DOT__brg_awvalid;
        vlSelf->top__DOT__brg_wready = ((~ (IData)(vlSelf->top__DOT__arb_owner)) 
                                        & (IData)(vlSelf->top__DOT__ram_wready));
        vlSelf->top__DOT__brg_awready = ((~ (IData)(vlSelf->top__DOT__arb_owner)) 
                                         & (IData)(vlSelf->top__DOT__ram_awready));
    } else {
        vlSelf->top__DOT__ram_bar_awvalid = 0U;
        vlSelf->top__DOT__brg_wready = vlSelf->top__DOT__dma_s_wready;
        vlSelf->top__DOT__brg_awready = vlSelf->top__DOT__dma_s_awready;
    }
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
    vlSelf->top__DOT__u_sniffer__DOT__capture_tx = 
        ((IData)(vlSelf->top__DOT__u_sniffer__DOT__tx_valid) 
         & ((0U == (IData)(vlSelf->top__DOT__u_sniffer__DOT__filter_mode)) 
            | ((2U == (IData)(vlSelf->top__DOT__u_sniffer__DOT__filter_mode)) 
               | ((3U == (IData)(vlSelf->top__DOT__u_sniffer__DOT__filter_mode)) 
                  & (IData)(vlSelf->top__DOT__u_sniffer__DOT__tx_is_cpl_err)))));
    vlSelf->top__DOT__brg_arready = ((IData)(vlSelf->top__DOT__rd_to_dbg)
                                      ? (0U == (IData)(vlSelf->top__DOT__dbg_rd_state))
                                      : ((IData)(vlSelf->top__DOT__rd_to_ram)
                                          ? ((~ (IData)(vlSelf->top__DOT__arb_owner)) 
                                             & (IData)(vlSelf->top__DOT__ram_arready))
                                          : (IData)(vlSelf->top__DOT__dma_s_arready)));
    vlSelf->top__DOT__u_sniffer__DOT__rx_is_cpl_err 
        = ((IData)(vlSelf->top__DOT__u_sniffer__DOT__rx_valid) 
           & (IData)(((0xa000000U == (0x1f000000U & 
                                      vlSelf->rx_st_hdr[3U])) 
                      & (0U != (7U & (vlSelf->rx_st_hdr[1U] 
                                      >> 0xdU))))));
    vlSelf->top__DOT__u_axi_sniffer__DOT__aw_handshake 
        = ((IData)(vlSelf->top__DOT__brg_awready) & (IData)(vlSelf->top__DOT__brg_awvalid));
    vlSelf->top__DOT__u_sniffer__DOT____VdfgRegularize_h54215f63_1_0 
        = ((IData)(vlSelf->top__DOT__pcie_dbg_wen) 
           & (4U == (0xffcU & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))));
    vlSelf->top__DOT__u_axi_sniffer__DOT____VdfgRegularize_h1732209f_5_0 
        = ((IData)(vlSelf->top__DOT__axi_dbg_wen) & 
           (4U == (0xfcU & (IData)(vlSelf->top__DOT__dbg_addr_to_sniffer))));
    vlSelf->top__DOT__u_axi_sniffer__DOT__ar_handshake 
        = ((IData)(vlSelf->top__DOT__brg_arready) & (IData)(vlSelf->top__DOT__brg_arvalid));
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
}

VL_ATTR_COLD void Vtop___024root___eval_triggers__stl(Vtop___024root* vlSelf);

VL_ATTR_COLD bool Vtop___024root___eval_phase__stl(Vtop___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__stl\n"); );
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    Vtop___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelf->__VstlTriggered.any();
    if (__VstlExecute) {
        Vtop___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__ico(Vtop___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__ico\n"); );
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
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(Vtop___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__act\n"); );
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
VL_ATTR_COLD void Vtop___024root___dump_triggers__nba(Vtop___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__nba\n"); );
    // Body
    if ((1U & (~ vlSelf->__VnbaTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge clk or negedge rst_n)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtop___024root___ctor_var_reset(Vtop___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___ctor_var_reset\n"); );
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
    vlSelf->top__DOT__brg_awaddr = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__brg_araddr = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__brg_wdata = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__brg_wstrb = VL_RAND_RESET_I(8);
    vlSelf->top__DOT__brg_awvalid = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__brg_awready = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__brg_wvalid = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__brg_wready = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__brg_bvalid = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__brg_bready = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__brg_arvalid = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__brg_arready = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__brg_rdata_mux = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__brg_rresp_mux = VL_RAND_RESET_I(2);
    vlSelf->top__DOT__brg_rvalid_mux = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__brg_rready = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__dma_host_rdata = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__dma_host_awready = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__dma_host_wready = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__dma_host_bvalid = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__dma_host_arready = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__dma_host_rvalid = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__dma_s_rdata = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__dma_s_bresp = VL_RAND_RESET_I(2);
    vlSelf->top__DOT__dma_s_rresp = VL_RAND_RESET_I(2);
    vlSelf->top__DOT__dma_s_awready = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__dma_s_wready = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__dma_s_bvalid = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__dma_s_arready = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__dma_s_rvalid = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__ram_bar_awvalid = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__ram_bar_bvalid = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__ram_bar_arvalid = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__ram_bar_rvalid = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__dma_local_bvalid = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__dma_local_rvalid = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__ram_wdata = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__ram_rdata = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__ram_wstrb = VL_RAND_RESET_I(8);
    vlSelf->top__DOT__ram_bresp = VL_RAND_RESET_I(2);
    vlSelf->top__DOT__ram_rresp = VL_RAND_RESET_I(2);
    vlSelf->top__DOT__ram_awready = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__ram_wready = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__ram_bvalid = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__ram_arready = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__ram_rvalid = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__msix_valid_i = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__msix_ready_i = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__dma_irq_req = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__pcie_dbg_wen = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__pcie_dbg_rdata = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__axi_dbg_wen = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__axi_dbg_rdata = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__wr_to_ram = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__rd_to_ram = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__rd_to_axi_dbg = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__rd_to_dbg = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__dbg_rvalid = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__dbg_rdata_latched = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__dbg_addr_latched = VL_RAND_RESET_I(12);
    vlSelf->top__DOT__dbg_sel_axi_latched = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__dbg_rd_state = VL_RAND_RESET_I(2);
    vlSelf->top__DOT__dbg_addr_to_sniffer = VL_RAND_RESET_I(12);
    vlSelf->top__DOT__dbg_rdata = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__msix_addr_reg = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__msix_data_reg = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__msix_pending = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__arb_busy = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__arb_owner = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_bridge__DOT__rx_len = VL_RAND_RESET_I(10);
    vlSelf->top__DOT__u_bridge__DOT__rx_rid = VL_RAND_RESET_I(16);
    vlSelf->top__DOT__u_bridge__DOT__rx_tag = VL_RAND_RESET_I(8);
    vlSelf->top__DOT__u_bridge__DOT__rx_fbe = VL_RAND_RESET_I(4);
    vlSelf->top__DOT__u_bridge__DOT__rx_lbe = VL_RAND_RESET_I(4);
    vlSelf->top__DOT__u_bridge__DOT__rx_addr = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__u_bridge__DOT__rx_is_mrd = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_bridge__DOT__rx_is_mwr = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_bridge__DOT__rx_is_cpld = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_bridge__DOT__completer_id = VL_RAND_RESET_I(16);
    vlSelf->top__DOT__u_bridge__DOT__completer_id_valid = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_bridge__DOT__host_mrd_addr = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__u_bridge__DOT__host_mrd_tag = VL_RAND_RESET_I(8);
    vlSelf->top__DOT__u_bridge__DOT__host_mrd_pending = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_bridge__DOT__host_mrd_inflight = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_bridge__DOT__host_mwr_addr = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__u_bridge__DOT__host_mwr_data = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__u_bridge__DOT__host_mwr_pending = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_bridge__DOT__tx_state = VL_RAND_RESET_I(4);
    vlSelf->top__DOT__u_bridge__DOT__host_mrd_ready_pulse = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_bridge__DOT__host_mwr_ready_pulse = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_bridge__DOT__bar_req_rid = VL_RAND_RESET_I(16);
    vlSelf->top__DOT__u_bridge__DOT__bar_req_tag = VL_RAND_RESET_I(8);
    vlSelf->top__DOT__u_bridge__DOT__bar_req_lower_addr = VL_RAND_RESET_I(7);
    vlSelf->top__DOT__u_bridge__DOT__bar_req_addr = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__u_bridge__DOT__bar_dw_remaining = VL_RAND_RESET_I(10);
    VL_RAND_RESET_W(256, vlSelf->top__DOT__u_bridge__DOT__bar_cpl_buffer);
    vlSelf->top__DOT__u_bridge__DOT__bar_dw_count = VL_RAND_RESET_I(4);
    vlSelf->top__DOT__u_bridge__DOT__bar_cpl_status = VL_RAND_RESET_I(2);
    VL_RAND_RESET_W(128, vlSelf->top__DOT__u_bridge__DOT__tx_hdr_r);
    VL_RAND_RESET_W(256, vlSelf->top__DOT__u_bridge__DOT__tx_data_r);
    vlSelf->top__DOT__u_bridge__DOT__u_crdt__DOT__state = VL_RAND_RESET_I(2);
    vlSelf->top__DOT__u_bridge__DOT__u_crdt__DOT__cnt = VL_RAND_RESET_I(4);
    for (int __Vi0 = 0; __Vi0 < 256; ++__Vi0) {
        VL_RAND_RESET_W(256, vlSelf->top__DOT__u_sniffer__DOT__trace_ram[__Vi0]);
    }
    vlSelf->top__DOT__u_sniffer__DOT__write_ptr = VL_RAND_RESET_I(8);
    vlSelf->top__DOT__u_sniffer__DOT__entry_count = VL_RAND_RESET_I(9);
    vlSelf->top__DOT__u_sniffer__DOT__running = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_sniffer__DOT__triggered = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_sniffer__DOT__full = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_sniffer__DOT__capture_mode = VL_RAND_RESET_I(2);
    vlSelf->top__DOT__u_sniffer__DOT__filter_mode = VL_RAND_RESET_I(2);
    vlSelf->top__DOT__u_sniffer__DOT__trigger_type = VL_RAND_RESET_I(8);
    vlSelf->top__DOT__u_sniffer__DOT__trigger_type_en = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_sniffer__DOT__trigger_on_err = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_sniffer__DOT__armed = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_sniffer__DOT__read_ptr = VL_RAND_RESET_I(8);
    VL_RAND_RESET_W(256, vlSelf->top__DOT__u_sniffer__DOT__read_entry);
    vlSelf->top__DOT__u_sniffer__DOT__rx_count = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__u_sniffer__DOT__tx_count = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__u_sniffer__DOT__cycle_count = VL_RAND_RESET_Q(64);
    VL_RAND_RESET_W(128, vlSelf->top__DOT__u_sniffer__DOT__last_rx_hdr);
    VL_RAND_RESET_W(128, vlSelf->top__DOT__u_sniffer__DOT__last_tx_hdr);
    vlSelf->top__DOT__u_sniffer__DOT__last_rx_data = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__u_sniffer__DOT__last_tx_data = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__u_sniffer__DOT__rx_seen = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_sniffer__DOT__tx_seen = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_sniffer__DOT__last_rx_type = VL_RAND_RESET_I(8);
    vlSelf->top__DOT__u_sniffer__DOT__rx_valid = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_sniffer__DOT__tx_valid = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_sniffer__DOT__rx_is_cpl_err = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_sniffer__DOT__tx_is_cpl_err = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_sniffer__DOT__capture_rx = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_sniffer__DOT__capture_tx = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_sniffer__DOT__ctrl_clear = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_sniffer__DOT__unnamedblk1__DOT__should_capture = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(256, vlSelf->top__DOT__u_sniffer__DOT__unnamedblk1__DOT__unnamedblk2__DOT__entry);
    vlSelf->top__DOT__u_sniffer__DOT____VdfgRegularize_h54215f63_1_0 = VL_RAND_RESET_I(1);
    for (int __Vi0 = 0; __Vi0 < 64; ++__Vi0) {
        VL_RAND_RESET_W(128, vlSelf->top__DOT__u_axi_sniffer__DOT__trace_ram[__Vi0]);
    }
    vlSelf->top__DOT__u_axi_sniffer__DOT__write_ptr = VL_RAND_RESET_I(6);
    vlSelf->top__DOT__u_axi_sniffer__DOT__entry_count = VL_RAND_RESET_I(7);
    vlSelf->top__DOT__u_axi_sniffer__DOT__running = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_axi_sniffer__DOT__full = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_axi_sniffer__DOT__read_ptr = VL_RAND_RESET_I(6);
    VL_RAND_RESET_W(128, vlSelf->top__DOT__u_axi_sniffer__DOT__read_entry);
    vlSelf->top__DOT__u_axi_sniffer__DOT__aw_count = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__u_axi_sniffer__DOT__ar_count = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__u_axi_sniffer__DOT__timestamp = VL_RAND_RESET_I(22);
    vlSelf->top__DOT__u_axi_sniffer__DOT__aw_seen = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_axi_sniffer__DOT__w_seen = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_axi_sniffer__DOT__b_seen = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_axi_sniffer__DOT__ar_seen = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_axi_sniffer__DOT__r_seen = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_axi_sniffer__DOT__pending_awaddr = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__u_axi_sniffer__DOT__pending_awvalid = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_axi_sniffer__DOT__aw_handshake = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_axi_sniffer__DOT__ar_handshake = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_axi_sniffer__DOT__ctrl_clear = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(128, vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk1__DOT__entry);
    VL_RAND_RESET_W(128, vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk2__DOT__entry);
    VL_RAND_RESET_W(128, vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk3__DOT__entry);
    VL_RAND_RESET_W(128, vlSelf->top__DOT__u_axi_sniffer__DOT__unnamedblk4__DOT__entry);
    vlSelf->top__DOT__u_axi_sniffer__DOT____VdfgRegularize_h1732209f_5_0 = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_dma__DOT__ctrl_reg = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__u_dma__DOT__host_addr = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__u_dma__DOT__local_addr = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__u_dma__DOT__length_reg = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__u_dma__DOT__start = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_dma__DOT__busy = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_dma__DOT__done = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_dma__DOT__done_r = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_dma__DOT__h2c_host_araddr = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__u_dma__DOT__h2c_host_arvalid = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_dma__DOT__h2c_host_rready = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_dma__DOT__h2c_local_awaddr = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__u_dma__DOT__h2c_local_awvalid = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_dma__DOT__h2c_local_wvalid = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_dma__DOT__h2c_local_bready = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_dma__DOT__h2c_local_wdata = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__u_dma__DOT__h2c_local_wstrb = VL_RAND_RESET_I(8);
    vlSelf->top__DOT__u_dma__DOT__c2h_local_araddr = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__u_dma__DOT__c2h_local_arvalid = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_dma__DOT__c2h_local_rready = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_dma__DOT__c2h_host_awaddr = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__u_dma__DOT__c2h_host_awvalid = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_dma__DOT__c2h_host_wvalid = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_dma__DOT__c2h_host_bready = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_dma__DOT__c2h_host_wdata = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__u_dma__DOT__u_h2c__DOT__state = VL_RAND_RESET_I(3);
    vlSelf->top__DOT__u_dma__DOT__u_h2c__DOT__cur_host = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__u_dma__DOT__u_h2c__DOT__cur_local = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__u_dma__DOT__u_h2c__DOT__bytes_left = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__u_dma__DOT__u_c2h__DOT__state = VL_RAND_RESET_I(3);
    vlSelf->top__DOT__u_dma__DOT__u_c2h__DOT__cur_host = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__u_dma__DOT__u_c2h__DOT__cur_local = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__u_dma__DOT__u_c2h__DOT__bytes_left = VL_RAND_RESET_I(32);
    for (int __Vi0 = 0; __Vi0 < 512; ++__Vi0) {
        vlSelf->top__DOT__u_ram__DOT__mem[__Vi0] = VL_RAND_RESET_Q(64);
    }
    vlSelf->top__DOT__u_ram__DOT__rd_addr_latched = VL_RAND_RESET_I(9);
    vlSelf->top__DOT__u_ram__DOT__read_pending = VL_RAND_RESET_I(1);
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
}
