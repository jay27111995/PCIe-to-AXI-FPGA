// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vpcie_axi_top__Syms.h"


void Vpcie_axi_top___024root__trace_chg_0_sub_0(Vpcie_axi_top___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vpcie_axi_top___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpcie_axi_top___024root__trace_chg_0\n"); );
    // Init
    Vpcie_axi_top___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vpcie_axi_top___024root*>(voidSelf);
    Vpcie_axi_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    Vpcie_axi_top___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vpcie_axi_top___024root__trace_chg_0_sub_0(Vpcie_axi_top___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    (void)vlSelf;  // Prevent unused variable warning
    Vpcie_axi_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpcie_axi_top___024root__trace_chg_0_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[1U])) {
        bufp->chgCData(oldp+0,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_fmt),3);
        bufp->chgCData(oldp+1,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_type),5);
        bufp->chgSData(oldp+2,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_len),10);
        bufp->chgSData(oldp+3,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_rid),16);
        bufp->chgCData(oldp+4,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_tag),8);
        bufp->chgCData(oldp+5,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_fbe),4);
        bufp->chgCData(oldp+6,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_lbe),4);
        bufp->chgQData(oldp+7,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_addr),64);
        bufp->chgBit(oldp+9,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_is_mrd));
        bufp->chgBit(oldp+10,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_is_mwr));
        bufp->chgBit(oldp+11,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_is_cpld));
        bufp->chgCData(oldp+12,((((IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_lbe) 
                                  << 4U) | (IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_fbe))),8);
    }
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[2U])) {
        bufp->chgIData(oldp+13,(vlSelf->pcie_axi_top__DOT__brg_awaddr),32);
        bufp->chgIData(oldp+14,(vlSelf->pcie_axi_top__DOT__brg_araddr),32);
        bufp->chgQData(oldp+15,(vlSelf->pcie_axi_top__DOT__brg_wdata),64);
        bufp->chgQData(oldp+17,(((IData)(vlSelf->pcie_axi_top__DOT__reg_rvalid)
                                  ? vlSelf->pcie_axi_top__DOT__reg_rdata
                                  : ((IData)(vlSelf->pcie_axi_top__DOT__dma_rvalid)
                                      ? vlSelf->pcie_axi_top__DOT__dma_rdata
                                      : vlSelf->pcie_axi_top__DOT__ram_real_rdata))),64);
        bufp->chgCData(oldp+19,(vlSelf->pcie_axi_top__DOT__brg_wstrb),8);
        bufp->chgCData(oldp+20,(((IData)(vlSelf->pcie_axi_top__DOT__reg_bvalid)
                                  ? (IData)(vlSelf->pcie_axi_top__DOT__reg_bresp)
                                  : ((IData)(vlSelf->pcie_axi_top__DOT__dma_bvalid)
                                      ? (IData)(vlSelf->pcie_axi_top__DOT__dma_bresp)
                                      : (IData)(vlSelf->pcie_axi_top__DOT__ram_real_bresp)))),2);
        bufp->chgCData(oldp+21,(((IData)(vlSelf->pcie_axi_top__DOT__reg_rvalid)
                                  ? (IData)(vlSelf->pcie_axi_top__DOT__reg_rresp)
                                  : ((IData)(vlSelf->pcie_axi_top__DOT__dma_rvalid)
                                      ? (IData)(vlSelf->pcie_axi_top__DOT__dma_rresp)
                                      : (IData)(vlSelf->pcie_axi_top__DOT__ram_real_rresp)))),2);
        bufp->chgBit(oldp+22,(vlSelf->pcie_axi_top__DOT__brg_awvalid));
        bufp->chgBit(oldp+23,(vlSelf->pcie_axi_top__DOT__brg_awready));
        bufp->chgBit(oldp+24,(vlSelf->pcie_axi_top__DOT__brg_wvalid));
        bufp->chgBit(oldp+25,(vlSelf->pcie_axi_top__DOT__brg_wready));
        bufp->chgBit(oldp+26,(((IData)(vlSelf->pcie_axi_top__DOT__reg_bvalid) 
                               | ((IData)(vlSelf->pcie_axi_top__DOT__dma_bvalid) 
                                  | ((~ (IData)(vlSelf->pcie_axi_top__DOT__ram_owner)) 
                                     & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_bvalid))))));
        bufp->chgBit(oldp+27,(vlSelf->pcie_axi_top__DOT__brg_bready));
        bufp->chgBit(oldp+28,(vlSelf->pcie_axi_top__DOT__brg_arvalid));
        bufp->chgBit(oldp+29,(((0U == (3U & (vlSelf->pcie_axi_top__DOT__brg_araddr 
                                             >> 0xcU)))
                                ? (IData)(vlSelf->pcie_axi_top__DOT__reg_arready)
                                : ((1U == (3U & (vlSelf->pcie_axi_top__DOT__brg_araddr 
                                                 >> 0xcU)))
                                    ? (IData)(vlSelf->pcie_axi_top__DOT__dma_arready)
                                    : ((~ (IData)(vlSelf->pcie_axi_top__DOT__ram_owner)) 
                                       & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_arready))))));
        bufp->chgBit(oldp+30,(((IData)(vlSelf->pcie_axi_top__DOT__reg_rvalid) 
                               | ((IData)(vlSelf->pcie_axi_top__DOT__dma_rvalid) 
                                  | ((~ (IData)(vlSelf->pcie_axi_top__DOT__ram_owner)) 
                                     & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_rvalid))))));
        bufp->chgBit(oldp+31,(vlSelf->pcie_axi_top__DOT__brg_rready));
        bufp->chgBit(oldp+32,(vlSelf->pcie_axi_top__DOT__dma_mrd_valid));
        bufp->chgBit(oldp+33,(vlSelf->pcie_axi_top__DOT__dma_mrd_ready));
        bufp->chgQData(oldp+34,(vlSelf->pcie_axi_top__DOT__dma_mrd_addr),64);
        bufp->chgSData(oldp+36,(vlSelf->pcie_axi_top__DOT__dma_mrd_len),10);
        bufp->chgCData(oldp+37,(vlSelf->pcie_axi_top__DOT__dma_mrd_tag),8);
        bufp->chgBit(oldp+38,(vlSelf->pcie_axi_top__DOT__dma_mwr_valid));
        bufp->chgBit(oldp+39,(vlSelf->pcie_axi_top__DOT__dma_mwr_ready));
        bufp->chgQData(oldp+40,(vlSelf->pcie_axi_top__DOT__dma_mwr_addr),64);
        bufp->chgQData(oldp+42,(vlSelf->pcie_axi_top__DOT__dma_mwr_data),64);
        bufp->chgSData(oldp+44,(vlSelf->pcie_axi_top__DOT__dma_mwr_len),10);
        bufp->chgBit(oldp+45,(vlSelf->pcie_axi_top__DOT__dma_cpl_valid));
        bufp->chgCData(oldp+46,(vlSelf->pcie_axi_top__DOT__dma_cpl_tag),8);
        bufp->chgQData(oldp+47,(vlSelf->pcie_axi_top__DOT__dma_cpl_data),64);
        bufp->chgQData(oldp+49,(vlSelf->pcie_axi_top__DOT__reg_rdata),64);
        bufp->chgCData(oldp+51,(vlSelf->pcie_axi_top__DOT__reg_bresp),2);
        bufp->chgCData(oldp+52,(vlSelf->pcie_axi_top__DOT__reg_rresp),2);
        bufp->chgBit(oldp+53,(vlSelf->pcie_axi_top__DOT__reg_awvalid));
        bufp->chgBit(oldp+54,(vlSelf->pcie_axi_top__DOT__reg_awready));
        bufp->chgBit(oldp+55,(vlSelf->pcie_axi_top__DOT__reg_wvalid));
        bufp->chgBit(oldp+56,(vlSelf->pcie_axi_top__DOT__reg_wready));
        bufp->chgBit(oldp+57,(vlSelf->pcie_axi_top__DOT__reg_bvalid));
        bufp->chgBit(oldp+58,(((IData)(vlSelf->pcie_axi_top__DOT__brg_arvalid) 
                               & (0U == (0x3000U & vlSelf->pcie_axi_top__DOT__brg_araddr)))));
        bufp->chgBit(oldp+59,(vlSelf->pcie_axi_top__DOT__reg_arready));
        bufp->chgBit(oldp+60,(vlSelf->pcie_axi_top__DOT__reg_rvalid));
        bufp->chgQData(oldp+61,(vlSelf->pcie_axi_top__DOT__dma_rdata),64);
        bufp->chgCData(oldp+63,(vlSelf->pcie_axi_top__DOT__dma_bresp),2);
        bufp->chgCData(oldp+64,(vlSelf->pcie_axi_top__DOT__dma_rresp),2);
        bufp->chgBit(oldp+65,(((IData)(vlSelf->pcie_axi_top__DOT__brg_awvalid) 
                               & (0x1000U == (0x3000U 
                                              & vlSelf->pcie_axi_top__DOT__brg_awaddr)))));
        bufp->chgBit(oldp+66,(vlSelf->pcie_axi_top__DOT__dma_awready));
        bufp->chgBit(oldp+67,(((IData)(vlSelf->pcie_axi_top__DOT__brg_wvalid) 
                               & (0x1000U == (0x3000U 
                                              & vlSelf->pcie_axi_top__DOT__brg_awaddr)))));
        bufp->chgBit(oldp+68,(vlSelf->pcie_axi_top__DOT__dma_wready));
        bufp->chgBit(oldp+69,(vlSelf->pcie_axi_top__DOT__dma_bvalid));
        bufp->chgBit(oldp+70,(((IData)(vlSelf->pcie_axi_top__DOT__brg_arvalid) 
                               & (0x1000U == (0x3000U 
                                              & vlSelf->pcie_axi_top__DOT__brg_araddr)))));
        bufp->chgBit(oldp+71,(vlSelf->pcie_axi_top__DOT__dma_arready));
        bufp->chgBit(oldp+72,(vlSelf->pcie_axi_top__DOT__dma_rvalid));
        bufp->chgQData(oldp+73,(vlSelf->pcie_axi_top__DOT__ram_real_rdata),64);
        bufp->chgCData(oldp+75,(vlSelf->pcie_axi_top__DOT__ram_real_bresp),2);
        bufp->chgCData(oldp+76,(vlSelf->pcie_axi_top__DOT__ram_real_rresp),2);
        bufp->chgBit(oldp+77,(vlSelf->pcie_axi_top__DOT__ram_awvalid));
        bufp->chgBit(oldp+78,(((~ (IData)(vlSelf->pcie_axi_top__DOT__ram_owner)) 
                               & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_awready))));
        bufp->chgBit(oldp+79,(((IData)(vlSelf->pcie_axi_top__DOT__brg_wvalid) 
                               & (0x2000U == (0x3000U 
                                              & vlSelf->pcie_axi_top__DOT__brg_awaddr)))));
        bufp->chgBit(oldp+80,(((~ (IData)(vlSelf->pcie_axi_top__DOT__ram_owner)) 
                               & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_wready))));
        bufp->chgBit(oldp+81,(((~ (IData)(vlSelf->pcie_axi_top__DOT__ram_owner)) 
                               & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_bvalid))));
        bufp->chgBit(oldp+82,(vlSelf->pcie_axi_top__DOT__ram_arvalid));
        bufp->chgBit(oldp+83,(((~ (IData)(vlSelf->pcie_axi_top__DOT__ram_owner)) 
                               & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_arready))));
        bufp->chgBit(oldp+84,(((~ (IData)(vlSelf->pcie_axi_top__DOT__ram_owner)) 
                               & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_rvalid))));
        bufp->chgIData(oldp+85,(vlSelf->pcie_axi_top__DOT__dma_ram_awaddr),32);
        bufp->chgIData(oldp+86,(vlSelf->pcie_axi_top__DOT__dma_ram_araddr),32);
        bufp->chgQData(oldp+87,(vlSelf->pcie_axi_top__DOT__dma_ram_wdata),64);
        bufp->chgCData(oldp+89,(vlSelf->pcie_axi_top__DOT__dma_ram_wstrb),8);
        bufp->chgBit(oldp+90,(vlSelf->pcie_axi_top__DOT__dma_ram_awvalid));
        bufp->chgBit(oldp+91,(((IData)(vlSelf->pcie_axi_top__DOT__ram_owner) 
                               & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_awready))));
        bufp->chgBit(oldp+92,(vlSelf->pcie_axi_top__DOT__dma_ram_wvalid));
        bufp->chgBit(oldp+93,(((IData)(vlSelf->pcie_axi_top__DOT__ram_owner) 
                               & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_wready))));
        bufp->chgBit(oldp+94,(((IData)(vlSelf->pcie_axi_top__DOT__ram_owner) 
                               & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_bvalid))));
        bufp->chgBit(oldp+95,(vlSelf->pcie_axi_top__DOT__dma_ram_bready));
        bufp->chgBit(oldp+96,(vlSelf->pcie_axi_top__DOT__dma_ram_arvalid));
        bufp->chgBit(oldp+97,(((IData)(vlSelf->pcie_axi_top__DOT__ram_owner) 
                               & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_arready))));
        bufp->chgBit(oldp+98,(((IData)(vlSelf->pcie_axi_top__DOT__ram_owner) 
                               & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_rvalid))));
        bufp->chgBit(oldp+99,(vlSelf->pcie_axi_top__DOT__dma_ram_rready));
        bufp->chgCData(oldp+100,((3U & (vlSelf->pcie_axi_top__DOT__brg_awaddr 
                                        >> 0xcU))),2);
        bufp->chgCData(oldp+101,((3U & (vlSelf->pcie_axi_top__DOT__brg_araddr 
                                        >> 0xcU))),2);
        bufp->chgBit(oldp+102,(vlSelf->pcie_axi_top__DOT__ram_busy));
        bufp->chgBit(oldp+103,(vlSelf->pcie_axi_top__DOT__ram_owner));
        bufp->chgIData(oldp+104,(((IData)(vlSelf->pcie_axi_top__DOT__ram_owner)
                                   ? vlSelf->pcie_axi_top__DOT__dma_ram_awaddr
                                   : vlSelf->pcie_axi_top__DOT__brg_awaddr)),32);
        bufp->chgIData(oldp+105,(((IData)(vlSelf->pcie_axi_top__DOT__ram_owner)
                                   ? vlSelf->pcie_axi_top__DOT__dma_ram_araddr
                                   : vlSelf->pcie_axi_top__DOT__brg_araddr)),32);
        bufp->chgQData(oldp+106,(vlSelf->pcie_axi_top__DOT__ram_real_wdata),64);
        bufp->chgCData(oldp+108,(vlSelf->pcie_axi_top__DOT__ram_real_wstrb),8);
        bufp->chgBit(oldp+109,(((IData)(vlSelf->pcie_axi_top__DOT__ram_owner)
                                 ? (IData)(vlSelf->pcie_axi_top__DOT__dma_ram_awvalid)
                                 : (IData)(vlSelf->pcie_axi_top__DOT__ram_awvalid))));
        bufp->chgBit(oldp+110,(vlSelf->pcie_axi_top__DOT__ram_real_awready));
        bufp->chgBit(oldp+111,(((IData)(vlSelf->pcie_axi_top__DOT__ram_owner)
                                 ? (IData)(vlSelf->pcie_axi_top__DOT__dma_ram_wvalid)
                                 : ((IData)(vlSelf->pcie_axi_top__DOT__brg_wvalid) 
                                    & (0x2000U == (0x3000U 
                                                   & vlSelf->pcie_axi_top__DOT__brg_awaddr))))));
        bufp->chgBit(oldp+112,(vlSelf->pcie_axi_top__DOT__ram_real_wready));
        bufp->chgBit(oldp+113,(vlSelf->pcie_axi_top__DOT__ram_real_bvalid));
        bufp->chgBit(oldp+114,(vlSelf->pcie_axi_top__DOT__ram_real_bready));
        bufp->chgBit(oldp+115,(((IData)(vlSelf->pcie_axi_top__DOT__ram_owner)
                                 ? (IData)(vlSelf->pcie_axi_top__DOT__dma_ram_arvalid)
                                 : (IData)(vlSelf->pcie_axi_top__DOT__ram_arvalid))));
        bufp->chgBit(oldp+116,(vlSelf->pcie_axi_top__DOT__ram_real_arready));
        bufp->chgBit(oldp+117,(vlSelf->pcie_axi_top__DOT__ram_real_rvalid));
        bufp->chgBit(oldp+118,(vlSelf->pcie_axi_top__DOT__ram_real_rready));
        bufp->chgBit(oldp+119,((1U & (~ (IData)(vlSelf->pcie_axi_top__DOT__ram_owner)))));
        bufp->chgBit(oldp+120,((0U < (IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__tx_cpl_hdr_cnt))));
        bufp->chgBit(oldp+121,((0U < vlSelf->pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__tx_cpl_data_cnt)));
        bufp->chgBit(oldp+122,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_cpl_hdr_dec));
        bufp->chgBit(oldp+123,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_cpl_data_dec));
        bufp->chgCData(oldp+124,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__state),4);
        bufp->chgSData(oldp+125,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__bar_req_rid),16);
        bufp->chgCData(oldp+126,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__bar_req_tag),8);
        bufp->chgCData(oldp+127,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__bar_req_lower_addr),7);
        bufp->chgQData(oldp+128,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__bar_cpl_data),64);
        bufp->chgCData(oldp+130,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__bar_cpl_status),2);
        bufp->chgWData(oldp+131,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_hdr_r),128);
        bufp->chgQData(oldp+135,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_data_r),64);
        bufp->chgBit(oldp+137,((3U == (IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__state))));
        bufp->chgCData(oldp+138,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__state),2);
        bufp->chgCData(oldp+139,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__cnt),4);
        bufp->chgSData(oldp+140,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__tx_cpl_hdr_cnt),16);
        bufp->chgIData(oldp+141,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__tx_cpl_data_cnt),20);
        bufp->chgIData(oldp+142,(vlSelf->pcie_axi_top__DOT__u_dma__DOT__ctrl_reg),32);
        bufp->chgIData(oldp+143,(vlSelf->pcie_axi_top__DOT__u_dma__DOT__status_reg),32);
        bufp->chgIData(oldp+144,(vlSelf->pcie_axi_top__DOT__u_dma__DOT__host_addr_lo),32);
        bufp->chgIData(oldp+145,(vlSelf->pcie_axi_top__DOT__u_dma__DOT__host_addr_hi),32);
        bufp->chgIData(oldp+146,(vlSelf->pcie_axi_top__DOT__u_dma__DOT__local_addr),32);
        bufp->chgIData(oldp+147,(vlSelf->pcie_axi_top__DOT__u_dma__DOT__length_reg),32);
        bufp->chgBit(oldp+148,((1U & vlSelf->pcie_axi_top__DOT__u_dma__DOT__ctrl_reg)));
        bufp->chgBit(oldp+149,((1U & (vlSelf->pcie_axi_top__DOT__u_dma__DOT__ctrl_reg 
                                      >> 1U))));
        bufp->chgBit(oldp+150,((1U & (vlSelf->pcie_axi_top__DOT__u_dma__DOT__ctrl_reg 
                                      >> 2U))));
        bufp->chgBit(oldp+151,((1U & vlSelf->pcie_axi_top__DOT__u_dma__DOT__status_reg)));
        bufp->chgBit(oldp+152,((1U & (vlSelf->pcie_axi_top__DOT__u_dma__DOT__status_reg 
                                      >> 1U))));
        bufp->chgCData(oldp+153,(vlSelf->pcie_axi_top__DOT__u_dma__DOT__dma_state),4);
        bufp->chgIData(oldp+154,(vlSelf->pcie_axi_top__DOT__u_dma__DOT__bytes_remaining),32);
        bufp->chgQData(oldp+155,(vlSelf->pcie_axi_top__DOT__u_dma__DOT__cur_host_addr),64);
        bufp->chgIData(oldp+157,(vlSelf->pcie_axi_top__DOT__u_dma__DOT__cur_local_addr),32);
        bufp->chgQData(oldp+158,(vlSelf->pcie_axi_top__DOT__u_dma__DOT__dma_data_buf),64);
        bufp->chgCData(oldp+160,(vlSelf->pcie_axi_top__DOT__u_dma__DOT__cur_tag),8);
        bufp->chgSData(oldp+161,((0x1ffU & (((IData)(vlSelf->pcie_axi_top__DOT__ram_owner)
                                              ? vlSelf->pcie_axi_top__DOT__dma_ram_awaddr
                                              : vlSelf->pcie_axi_top__DOT__brg_awaddr) 
                                            >> 3U))),9);
        bufp->chgSData(oldp+162,((0x1ffU & (((IData)(vlSelf->pcie_axi_top__DOT__ram_owner)
                                              ? vlSelf->pcie_axi_top__DOT__dma_ram_araddr
                                              : vlSelf->pcie_axi_top__DOT__brg_araddr) 
                                            >> 3U))),9);
        bufp->chgIData(oldp+163,(vlSelf->pcie_axi_top__DOT__u_ram__DOT__unnamedblk1__DOT__i),32);
        bufp->chgQData(oldp+164,(vlSelf->pcie_axi_top__DOT__u_regs__DOT__scratch_reg),64);
        bufp->chgIData(oldp+166,(vlSelf->pcie_axi_top__DOT__u_regs__DOT__write_cnt),32);
        bufp->chgCData(oldp+167,(vlSelf->pcie_axi_top__DOT__u_regs__DOT__wr_state),2);
        bufp->chgIData(oldp+168,(vlSelf->pcie_axi_top__DOT__u_regs__DOT__wr_addr),32);
        bufp->chgCData(oldp+169,(vlSelf->pcie_axi_top__DOT__u_regs__DOT__rd_state),2);
    }
    bufp->chgBit(oldp+170,(vlSelf->clk));
    bufp->chgBit(oldp+171,(vlSelf->rst_n));
    bufp->chgWData(oldp+172,(vlSelf->rx_st_hdr),128);
    bufp->chgWData(oldp+176,(vlSelf->rx_st_data),256);
    bufp->chgBit(oldp+184,(vlSelf->rx_st_sop));
    bufp->chgBit(oldp+185,(vlSelf->rx_st_eop));
    bufp->chgBit(oldp+186,(vlSelf->rx_st_hvalid));
    bufp->chgBit(oldp+187,(vlSelf->rx_st_dvalid));
    bufp->chgCData(oldp+188,(vlSelf->rx_st_bar),3);
    bufp->chgBit(oldp+189,(vlSelf->rx_st_ready));
    bufp->chgWData(oldp+190,(vlSelf->tx_st_hdr),128);
    bufp->chgWData(oldp+194,(vlSelf->tx_st_data),256);
    bufp->chgBit(oldp+202,(vlSelf->tx_st_sop));
    bufp->chgBit(oldp+203,(vlSelf->tx_st_eop));
    bufp->chgBit(oldp+204,(vlSelf->tx_st_hvalid));
    bufp->chgBit(oldp+205,(vlSelf->tx_st_dvalid));
    bufp->chgBit(oldp+206,(vlSelf->tx_st_ready));
    bufp->chgCData(oldp+207,(vlSelf->rx_hcrdt_init),3);
    bufp->chgCData(oldp+208,(vlSelf->rx_hcrdt_update),3);
    bufp->chgCData(oldp+209,(vlSelf->rx_hcrdt_update_cnt),6);
    bufp->chgCData(oldp+210,(vlSelf->rx_dcrdt_init),3);
    bufp->chgCData(oldp+211,(vlSelf->rx_dcrdt_update),3);
    bufp->chgSData(oldp+212,(vlSelf->rx_dcrdt_update_cnt),12);
    bufp->chgCData(oldp+213,(vlSelf->tx_hcrdt_init),3);
    bufp->chgCData(oldp+214,(vlSelf->tx_hcrdt_init_ack),3);
    bufp->chgCData(oldp+215,(vlSelf->tx_hcrdt_update),3);
    bufp->chgCData(oldp+216,(vlSelf->tx_hcrdt_update_cnt),6);
    bufp->chgCData(oldp+217,(vlSelf->tx_dcrdt_init),3);
    bufp->chgCData(oldp+218,(vlSelf->tx_dcrdt_init_ack),3);
    bufp->chgCData(oldp+219,(vlSelf->tx_dcrdt_update),3);
    bufp->chgSData(oldp+220,(vlSelf->tx_dcrdt_update_cnt),12);
    bufp->chgBit(oldp+221,(vlSelf->link_up));
    bufp->chgCData(oldp+222,(vlSelf->ltssm_state),6);
    bufp->chgQData(oldp+223,(vlSelf->scratch_reg),64);
    bufp->chgIData(oldp+225,(vlSelf->write_count),32);
    bufp->chgBit(oldp+226,(vlSelf->dma_irq));
    bufp->chgCData(oldp+227,((0xffU & (vlSelf->rx_st_hdr[1U] 
                                       >> 8U))),8);
}

void Vpcie_axi_top___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpcie_axi_top___024root__trace_cleanup\n"); );
    // Init
    Vpcie_axi_top___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vpcie_axi_top___024root*>(voidSelf);
    Vpcie_axi_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[2U] = 0U;
}
