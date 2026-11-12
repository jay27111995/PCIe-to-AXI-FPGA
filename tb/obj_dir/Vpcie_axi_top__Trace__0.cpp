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
        bufp->chgQData(oldp+17,(((IData)(vlSelf->pcie_axi_top__DOT__dma_rvalid)
                                  ? vlSelf->pcie_axi_top__DOT__dma_rdata
                                  : vlSelf->pcie_axi_top__DOT__ram_real_rdata)),64);
        bufp->chgCData(oldp+19,(vlSelf->pcie_axi_top__DOT__brg_wstrb),8);
        bufp->chgCData(oldp+20,(((IData)(vlSelf->pcie_axi_top__DOT__dma_bvalid)
                                  ? (IData)(vlSelf->pcie_axi_top__DOT__dma_bresp)
                                  : (IData)(vlSelf->pcie_axi_top__DOT__ram_real_bresp))),2);
        bufp->chgCData(oldp+21,(((IData)(vlSelf->pcie_axi_top__DOT__dma_rvalid)
                                  ? (IData)(vlSelf->pcie_axi_top__DOT__dma_rresp)
                                  : (IData)(vlSelf->pcie_axi_top__DOT__ram_real_rresp))),2);
        bufp->chgBit(oldp+22,(vlSelf->pcie_axi_top__DOT__brg_awvalid));
        bufp->chgBit(oldp+23,(vlSelf->pcie_axi_top__DOT__brg_awready));
        bufp->chgBit(oldp+24,(vlSelf->pcie_axi_top__DOT__brg_wvalid));
        bufp->chgBit(oldp+25,(vlSelf->pcie_axi_top__DOT__brg_wready));
        bufp->chgBit(oldp+26,(((IData)(vlSelf->pcie_axi_top__DOT__dma_bvalid) 
                               | ((~ (IData)(vlSelf->pcie_axi_top__DOT__ram_owner)) 
                                  & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_bvalid)))));
        bufp->chgBit(oldp+27,(vlSelf->pcie_axi_top__DOT__brg_bready));
        bufp->chgBit(oldp+28,(vlSelf->pcie_axi_top__DOT__brg_arvalid));
        bufp->chgBit(oldp+29,(((0x1000U & vlSelf->pcie_axi_top__DOT__brg_araddr)
                                ? ((~ (IData)(vlSelf->pcie_axi_top__DOT__ram_owner)) 
                                   & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_arready))
                                : (IData)(vlSelf->pcie_axi_top__DOT__dma_arready))));
        bufp->chgBit(oldp+30,(((IData)(vlSelf->pcie_axi_top__DOT__dma_rvalid) 
                               | ((~ (IData)(vlSelf->pcie_axi_top__DOT__ram_owner)) 
                                  & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_rvalid)))));
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
        bufp->chgQData(oldp+49,(vlSelf->pcie_axi_top__DOT__dma_rdata),64);
        bufp->chgCData(oldp+51,(vlSelf->pcie_axi_top__DOT__dma_bresp),2);
        bufp->chgCData(oldp+52,(vlSelf->pcie_axi_top__DOT__dma_rresp),2);
        bufp->chgBit(oldp+53,(((~ (vlSelf->pcie_axi_top__DOT__brg_awaddr 
                                   >> 0xcU)) & (IData)(vlSelf->pcie_axi_top__DOT__brg_awvalid))));
        bufp->chgBit(oldp+54,(vlSelf->pcie_axi_top__DOT__dma_awready));
        bufp->chgBit(oldp+55,(((~ (vlSelf->pcie_axi_top__DOT__brg_awaddr 
                                   >> 0xcU)) & (IData)(vlSelf->pcie_axi_top__DOT__brg_wvalid))));
        bufp->chgBit(oldp+56,(vlSelf->pcie_axi_top__DOT__dma_wready));
        bufp->chgBit(oldp+57,(vlSelf->pcie_axi_top__DOT__dma_bvalid));
        bufp->chgBit(oldp+58,(((~ (vlSelf->pcie_axi_top__DOT__brg_araddr 
                                   >> 0xcU)) & (IData)(vlSelf->pcie_axi_top__DOT__brg_arvalid))));
        bufp->chgBit(oldp+59,(vlSelf->pcie_axi_top__DOT__dma_arready));
        bufp->chgBit(oldp+60,(vlSelf->pcie_axi_top__DOT__dma_rvalid));
        bufp->chgQData(oldp+61,(vlSelf->pcie_axi_top__DOT__ram_real_rdata),64);
        bufp->chgCData(oldp+63,(vlSelf->pcie_axi_top__DOT__ram_real_bresp),2);
        bufp->chgCData(oldp+64,(vlSelf->pcie_axi_top__DOT__ram_real_rresp),2);
        bufp->chgBit(oldp+65,(vlSelf->pcie_axi_top__DOT__ram_awvalid));
        bufp->chgBit(oldp+66,(((~ (IData)(vlSelf->pcie_axi_top__DOT__ram_owner)) 
                               & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_awready))));
        bufp->chgBit(oldp+67,(((IData)(vlSelf->pcie_axi_top__DOT__brg_wvalid) 
                               & (vlSelf->pcie_axi_top__DOT__brg_awaddr 
                                  >> 0xcU))));
        bufp->chgBit(oldp+68,(((~ (IData)(vlSelf->pcie_axi_top__DOT__ram_owner)) 
                               & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_wready))));
        bufp->chgBit(oldp+69,(((~ (IData)(vlSelf->pcie_axi_top__DOT__ram_owner)) 
                               & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_bvalid))));
        bufp->chgBit(oldp+70,(vlSelf->pcie_axi_top__DOT__ram_arvalid));
        bufp->chgBit(oldp+71,(((~ (IData)(vlSelf->pcie_axi_top__DOT__ram_owner)) 
                               & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_arready))));
        bufp->chgBit(oldp+72,(((~ (IData)(vlSelf->pcie_axi_top__DOT__ram_owner)) 
                               & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_rvalid))));
        bufp->chgIData(oldp+73,(vlSelf->pcie_axi_top__DOT__dma_ram_awaddr),32);
        bufp->chgIData(oldp+74,(vlSelf->pcie_axi_top__DOT__dma_ram_araddr),32);
        bufp->chgQData(oldp+75,(vlSelf->pcie_axi_top__DOT__dma_ram_wdata),64);
        bufp->chgCData(oldp+77,(vlSelf->pcie_axi_top__DOT__dma_ram_wstrb),8);
        bufp->chgBit(oldp+78,(vlSelf->pcie_axi_top__DOT__dma_ram_awvalid));
        bufp->chgBit(oldp+79,(((IData)(vlSelf->pcie_axi_top__DOT__ram_owner) 
                               & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_awready))));
        bufp->chgBit(oldp+80,(vlSelf->pcie_axi_top__DOT__dma_ram_wvalid));
        bufp->chgBit(oldp+81,(((IData)(vlSelf->pcie_axi_top__DOT__ram_owner) 
                               & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_wready))));
        bufp->chgBit(oldp+82,(((IData)(vlSelf->pcie_axi_top__DOT__ram_owner) 
                               & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_bvalid))));
        bufp->chgBit(oldp+83,(vlSelf->pcie_axi_top__DOT__dma_ram_bready));
        bufp->chgBit(oldp+84,(vlSelf->pcie_axi_top__DOT__dma_ram_arvalid));
        bufp->chgBit(oldp+85,(((IData)(vlSelf->pcie_axi_top__DOT__ram_owner) 
                               & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_arready))));
        bufp->chgBit(oldp+86,(((IData)(vlSelf->pcie_axi_top__DOT__ram_owner) 
                               & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_rvalid))));
        bufp->chgBit(oldp+87,(vlSelf->pcie_axi_top__DOT__dma_ram_rready));
        bufp->chgBit(oldp+88,((1U & (vlSelf->pcie_axi_top__DOT__brg_awaddr 
                                     >> 0xcU))));
        bufp->chgBit(oldp+89,((1U & (vlSelf->pcie_axi_top__DOT__brg_araddr 
                                     >> 0xcU))));
        bufp->chgBit(oldp+90,(vlSelf->pcie_axi_top__DOT__ram_busy));
        bufp->chgBit(oldp+91,(vlSelf->pcie_axi_top__DOT__ram_owner));
        bufp->chgIData(oldp+92,(((IData)(vlSelf->pcie_axi_top__DOT__ram_owner)
                                  ? vlSelf->pcie_axi_top__DOT__dma_ram_awaddr
                                  : vlSelf->pcie_axi_top__DOT__brg_awaddr)),32);
        bufp->chgIData(oldp+93,(((IData)(vlSelf->pcie_axi_top__DOT__ram_owner)
                                  ? vlSelf->pcie_axi_top__DOT__dma_ram_araddr
                                  : vlSelf->pcie_axi_top__DOT__brg_araddr)),32);
        bufp->chgQData(oldp+94,(vlSelf->pcie_axi_top__DOT__ram_real_wdata),64);
        bufp->chgCData(oldp+96,(vlSelf->pcie_axi_top__DOT__ram_real_wstrb),8);
        bufp->chgBit(oldp+97,(((IData)(vlSelf->pcie_axi_top__DOT__ram_owner)
                                ? (IData)(vlSelf->pcie_axi_top__DOT__dma_ram_awvalid)
                                : (IData)(vlSelf->pcie_axi_top__DOT__ram_awvalid))));
        bufp->chgBit(oldp+98,(vlSelf->pcie_axi_top__DOT__ram_real_awready));
        bufp->chgBit(oldp+99,(((IData)(vlSelf->pcie_axi_top__DOT__ram_owner)
                                ? (IData)(vlSelf->pcie_axi_top__DOT__dma_ram_wvalid)
                                : ((IData)(vlSelf->pcie_axi_top__DOT__brg_wvalid) 
                                   & (vlSelf->pcie_axi_top__DOT__brg_awaddr 
                                      >> 0xcU)))));
        bufp->chgBit(oldp+100,(vlSelf->pcie_axi_top__DOT__ram_real_wready));
        bufp->chgBit(oldp+101,(vlSelf->pcie_axi_top__DOT__ram_real_bvalid));
        bufp->chgBit(oldp+102,(vlSelf->pcie_axi_top__DOT__ram_real_bready));
        bufp->chgBit(oldp+103,(((IData)(vlSelf->pcie_axi_top__DOT__ram_owner)
                                 ? (IData)(vlSelf->pcie_axi_top__DOT__dma_ram_arvalid)
                                 : (IData)(vlSelf->pcie_axi_top__DOT__ram_arvalid))));
        bufp->chgBit(oldp+104,(vlSelf->pcie_axi_top__DOT__ram_real_arready));
        bufp->chgBit(oldp+105,(vlSelf->pcie_axi_top__DOT__ram_real_rvalid));
        bufp->chgBit(oldp+106,(vlSelf->pcie_axi_top__DOT__ram_real_rready));
        bufp->chgBit(oldp+107,((1U & (~ (IData)(vlSelf->pcie_axi_top__DOT__ram_owner)))));
        bufp->chgBit(oldp+108,((0U < (IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__tx_cpl_hdr_cnt))));
        bufp->chgBit(oldp+109,((0U < vlSelf->pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__tx_cpl_data_cnt)));
        bufp->chgBit(oldp+110,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_cpl_hdr_dec));
        bufp->chgBit(oldp+111,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_cpl_data_dec));
        bufp->chgCData(oldp+112,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__state),4);
        bufp->chgSData(oldp+113,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__bar_req_rid),16);
        bufp->chgCData(oldp+114,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__bar_req_tag),8);
        bufp->chgCData(oldp+115,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__bar_req_lower_addr),7);
        bufp->chgQData(oldp+116,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__bar_cpl_data),64);
        bufp->chgCData(oldp+118,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__bar_cpl_status),2);
        bufp->chgWData(oldp+119,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_hdr_r),128);
        bufp->chgQData(oldp+123,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_data_r),64);
        bufp->chgBit(oldp+125,((3U == (IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__state))));
        bufp->chgCData(oldp+126,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__state),2);
        bufp->chgCData(oldp+127,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__cnt),4);
        bufp->chgSData(oldp+128,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__tx_cpl_hdr_cnt),16);
        bufp->chgIData(oldp+129,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__tx_cpl_data_cnt),20);
        bufp->chgIData(oldp+130,(vlSelf->pcie_axi_top__DOT__u_dma__DOT__ctrl_reg),32);
        bufp->chgIData(oldp+131,(vlSelf->pcie_axi_top__DOT__u_dma__DOT__status_reg),32);
        bufp->chgIData(oldp+132,(vlSelf->pcie_axi_top__DOT__u_dma__DOT__host_addr_lo),32);
        bufp->chgIData(oldp+133,(vlSelf->pcie_axi_top__DOT__u_dma__DOT__host_addr_hi),32);
        bufp->chgIData(oldp+134,(vlSelf->pcie_axi_top__DOT__u_dma__DOT__local_addr),32);
        bufp->chgIData(oldp+135,(vlSelf->pcie_axi_top__DOT__u_dma__DOT__length_reg),32);
        bufp->chgBit(oldp+136,((1U & vlSelf->pcie_axi_top__DOT__u_dma__DOT__ctrl_reg)));
        bufp->chgBit(oldp+137,((1U & (vlSelf->pcie_axi_top__DOT__u_dma__DOT__ctrl_reg 
                                      >> 1U))));
        bufp->chgBit(oldp+138,((1U & (vlSelf->pcie_axi_top__DOT__u_dma__DOT__ctrl_reg 
                                      >> 2U))));
        bufp->chgBit(oldp+139,((1U & vlSelf->pcie_axi_top__DOT__u_dma__DOT__status_reg)));
        bufp->chgBit(oldp+140,((1U & (vlSelf->pcie_axi_top__DOT__u_dma__DOT__status_reg 
                                      >> 1U))));
        bufp->chgCData(oldp+141,(vlSelf->pcie_axi_top__DOT__u_dma__DOT__dma_state),4);
        bufp->chgIData(oldp+142,(vlSelf->pcie_axi_top__DOT__u_dma__DOT__bytes_remaining),32);
        bufp->chgQData(oldp+143,(vlSelf->pcie_axi_top__DOT__u_dma__DOT__cur_host_addr),64);
        bufp->chgIData(oldp+145,(vlSelf->pcie_axi_top__DOT__u_dma__DOT__cur_local_addr),32);
        bufp->chgQData(oldp+146,(vlSelf->pcie_axi_top__DOT__u_dma__DOT__dma_data_buf),64);
        bufp->chgCData(oldp+148,(vlSelf->pcie_axi_top__DOT__u_dma__DOT__cur_tag),8);
        bufp->chgSData(oldp+149,((0x1ffU & (((IData)(vlSelf->pcie_axi_top__DOT__ram_owner)
                                              ? vlSelf->pcie_axi_top__DOT__dma_ram_awaddr
                                              : vlSelf->pcie_axi_top__DOT__brg_awaddr) 
                                            >> 3U))),9);
        bufp->chgSData(oldp+150,((0x1ffU & (((IData)(vlSelf->pcie_axi_top__DOT__ram_owner)
                                              ? vlSelf->pcie_axi_top__DOT__dma_ram_araddr
                                              : vlSelf->pcie_axi_top__DOT__brg_araddr) 
                                            >> 3U))),9);
        bufp->chgSData(oldp+151,(vlSelf->pcie_axi_top__DOT__u_ram__DOT__rd_addr_latched),9);
        bufp->chgBit(oldp+152,(vlSelf->pcie_axi_top__DOT__u_ram__DOT__read_pending));
        bufp->chgIData(oldp+153,(vlSelf->pcie_axi_top__DOT__u_ram__DOT__unnamedblk1__DOT__i),32);
    }
    bufp->chgBit(oldp+154,(vlSelf->clk));
    bufp->chgBit(oldp+155,(vlSelf->rst_n));
    bufp->chgWData(oldp+156,(vlSelf->rx_st_hdr),128);
    bufp->chgWData(oldp+160,(vlSelf->rx_st_data),256);
    bufp->chgBit(oldp+168,(vlSelf->rx_st_sop));
    bufp->chgBit(oldp+169,(vlSelf->rx_st_eop));
    bufp->chgBit(oldp+170,(vlSelf->rx_st_hvalid));
    bufp->chgBit(oldp+171,(vlSelf->rx_st_dvalid));
    bufp->chgCData(oldp+172,(vlSelf->rx_st_bar),3);
    bufp->chgBit(oldp+173,(vlSelf->rx_st_ready));
    bufp->chgWData(oldp+174,(vlSelf->tx_st_hdr),128);
    bufp->chgWData(oldp+178,(vlSelf->tx_st_data),256);
    bufp->chgBit(oldp+186,(vlSelf->tx_st_sop));
    bufp->chgBit(oldp+187,(vlSelf->tx_st_eop));
    bufp->chgBit(oldp+188,(vlSelf->tx_st_hvalid));
    bufp->chgBit(oldp+189,(vlSelf->tx_st_dvalid));
    bufp->chgBit(oldp+190,(vlSelf->tx_st_ready));
    bufp->chgCData(oldp+191,(vlSelf->rx_hcrdt_init),3);
    bufp->chgCData(oldp+192,(vlSelf->rx_hcrdt_update),3);
    bufp->chgCData(oldp+193,(vlSelf->rx_hcrdt_update_cnt),6);
    bufp->chgCData(oldp+194,(vlSelf->rx_dcrdt_init),3);
    bufp->chgCData(oldp+195,(vlSelf->rx_dcrdt_update),3);
    bufp->chgSData(oldp+196,(vlSelf->rx_dcrdt_update_cnt),12);
    bufp->chgCData(oldp+197,(vlSelf->tx_hcrdt_init),3);
    bufp->chgCData(oldp+198,(vlSelf->tx_hcrdt_init_ack),3);
    bufp->chgCData(oldp+199,(vlSelf->tx_hcrdt_update),3);
    bufp->chgCData(oldp+200,(vlSelf->tx_hcrdt_update_cnt),6);
    bufp->chgCData(oldp+201,(vlSelf->tx_dcrdt_init),3);
    bufp->chgCData(oldp+202,(vlSelf->tx_dcrdt_init_ack),3);
    bufp->chgCData(oldp+203,(vlSelf->tx_dcrdt_update),3);
    bufp->chgSData(oldp+204,(vlSelf->tx_dcrdt_update_cnt),12);
    bufp->chgBit(oldp+205,(vlSelf->link_up));
    bufp->chgCData(oldp+206,(vlSelf->ltssm_state),6);
    bufp->chgBit(oldp+207,(vlSelf->dma_irq));
    bufp->chgCData(oldp+208,((0xffU & (vlSelf->rx_st_hdr[1U] 
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
