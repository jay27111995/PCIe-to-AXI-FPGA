// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vpcie_axi_top__Syms.h"


VL_ATTR_COLD void Vpcie_axi_top___024root__trace_init_sub__TOP__rtile_pkg__0(Vpcie_axi_top___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD void Vpcie_axi_top___024root__trace_init_sub__TOP__0(Vpcie_axi_top___024root* vlSelf, VerilatedVcd* tracep) {
    (void)vlSelf;  // Prevent unused variable warning
    Vpcie_axi_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpcie_axi_top___024root__trace_init_sub__TOP__0\n"); );
    // Init
    const int c = vlSymsp->__Vm_baseCode;
    // Body
    tracep->pushPrefix("rtile_pkg", VerilatedTracePrefixType::SCOPE_MODULE);
    Vpcie_axi_top___024root__trace_init_sub__TOP__rtile_pkg__0(vlSelf, tracep);
    tracep->popPrefix();
    tracep->declBit(c+155,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+156,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declArray(c+157,0,"rx_st_hdr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declArray(c+161,0,"rx_st_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 255,0);
    tracep->declBit(c+169,0,"rx_st_sop",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+170,0,"rx_st_eop",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+171,0,"rx_st_hvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+172,0,"rx_st_dvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+173,0,"rx_st_bar",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBit(c+174,0,"rx_st_ready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declArray(c+175,0,"tx_st_hdr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declArray(c+179,0,"tx_st_data",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 255,0);
    tracep->declBit(c+187,0,"tx_st_sop",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+188,0,"tx_st_eop",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+189,0,"tx_st_hvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+190,0,"tx_st_dvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+191,0,"tx_st_ready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+192,0,"rx_hcrdt_init",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+193,0,"rx_hcrdt_update",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+194,0,"rx_hcrdt_update_cnt",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+195,0,"rx_dcrdt_init",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+196,0,"rx_dcrdt_update",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+197,0,"rx_dcrdt_update_cnt",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 11,0);
    tracep->declBus(c+198,0,"tx_hcrdt_init",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+199,0,"tx_hcrdt_init_ack",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+200,0,"tx_hcrdt_update",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+201,0,"tx_hcrdt_update_cnt",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+202,0,"tx_dcrdt_init",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+203,0,"tx_dcrdt_init_ack",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+204,0,"tx_dcrdt_update",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+205,0,"tx_dcrdt_update_cnt",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 11,0);
    tracep->declBit(c+206,0,"link_up",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+207,0,"ltssm_state",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBit(c+208,0,"dma_irq",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("pcie_axi_top", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+155,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+156,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declArray(c+157,0,"rx_st_hdr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declArray(c+161,0,"rx_st_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 255,0);
    tracep->declBit(c+169,0,"rx_st_sop",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+170,0,"rx_st_eop",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+171,0,"rx_st_hvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+172,0,"rx_st_dvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+173,0,"rx_st_bar",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBit(c+174,0,"rx_st_ready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declArray(c+175,0,"tx_st_hdr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declArray(c+179,0,"tx_st_data",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 255,0);
    tracep->declBit(c+187,0,"tx_st_sop",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+188,0,"tx_st_eop",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+189,0,"tx_st_hvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+190,0,"tx_st_dvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+191,0,"tx_st_ready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+192,0,"rx_hcrdt_init",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+193,0,"rx_hcrdt_update",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+194,0,"rx_hcrdt_update_cnt",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+195,0,"rx_dcrdt_init",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+196,0,"rx_dcrdt_update",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+197,0,"rx_dcrdt_update_cnt",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 11,0);
    tracep->declBus(c+198,0,"tx_hcrdt_init",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+199,0,"tx_hcrdt_init_ack",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+200,0,"tx_hcrdt_update",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+201,0,"tx_hcrdt_update_cnt",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+202,0,"tx_dcrdt_init",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+203,0,"tx_dcrdt_init_ack",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+204,0,"tx_dcrdt_update",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+205,0,"tx_dcrdt_update_cnt",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 11,0);
    tracep->declBit(c+206,0,"link_up",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+207,0,"ltssm_state",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBit(c+208,0,"dma_irq",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+14,0,"brg_awaddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+15,0,"brg_araddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declQuad(c+16,0,"brg_wdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+18,0,"brg_rdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+20,0,"brg_wstrb",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+21,0,"brg_bresp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+22,0,"brg_rresp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+23,0,"brg_awvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+24,0,"brg_awready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+25,0,"brg_wvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+26,0,"brg_wready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+27,0,"brg_bvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+28,0,"brg_bready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+29,0,"brg_arvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+30,0,"brg_arready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+31,0,"brg_rvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+32,0,"brg_rready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+33,0,"dma_mrd_valid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+34,0,"dma_mrd_ready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declQuad(c+35,0,"dma_mrd_addr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+37,0,"dma_mrd_len",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 9,0);
    tracep->declBus(c+38,0,"dma_mrd_tag",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBit(c+39,0,"dma_mwr_valid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+40,0,"dma_mwr_ready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declQuad(c+41,0,"dma_mwr_addr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+43,0,"dma_mwr_data",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+45,0,"dma_mwr_len",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 9,0);
    tracep->declBit(c+46,0,"dma_cpl_valid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+47,0,"dma_cpl_tag",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declQuad(c+48,0,"dma_cpl_data",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+14,0,"dma_awaddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+15,0,"dma_araddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declQuad(c+16,0,"dma_wdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+50,0,"dma_rdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+20,0,"dma_wstrb",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+52,0,"dma_bresp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+53,0,"dma_rresp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+54,0,"dma_awvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+55,0,"dma_awready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+56,0,"dma_wvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+57,0,"dma_wready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+58,0,"dma_bvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+28,0,"dma_bready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+59,0,"dma_arvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+60,0,"dma_arready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+61,0,"dma_rvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+32,0,"dma_rready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+14,0,"ram_awaddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+15,0,"ram_araddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declQuad(c+16,0,"ram_wdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+62,0,"ram_rdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+20,0,"ram_wstrb",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+64,0,"ram_bresp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+65,0,"ram_rresp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+66,0,"ram_awvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+67,0,"ram_awready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+68,0,"ram_wvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+69,0,"ram_wready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+70,0,"ram_bvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+28,0,"ram_bready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+71,0,"ram_arvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+72,0,"ram_arready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+73,0,"ram_rvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+32,0,"ram_rready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+74,0,"dma_ram_awaddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+75,0,"dma_ram_araddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declQuad(c+76,0,"dma_ram_wdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+62,0,"dma_ram_rdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+78,0,"dma_ram_wstrb",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+64,0,"dma_ram_bresp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+65,0,"dma_ram_rresp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+79,0,"dma_ram_awvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+80,0,"dma_ram_awready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+81,0,"dma_ram_wvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+82,0,"dma_ram_wready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+83,0,"dma_ram_bvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+84,0,"dma_ram_bready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+85,0,"dma_ram_arvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+86,0,"dma_ram_arready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+87,0,"dma_ram_rvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+88,0,"dma_ram_rready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+89,0,"wr_sel",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+90,0,"rd_sel",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+91,0,"ram_busy",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+92,0,"ram_owner",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+93,0,"ram_real_awaddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+94,0,"ram_real_araddr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declQuad(c+95,0,"ram_real_wdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+62,0,"ram_real_rdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+97,0,"ram_real_wstrb",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+64,0,"ram_real_bresp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+65,0,"ram_real_rresp",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+98,0,"ram_real_awvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+99,0,"ram_real_awready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+100,0,"ram_real_wvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+101,0,"ram_real_wready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+102,0,"ram_real_bvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+103,0,"ram_real_bready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+104,0,"ram_real_arvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+105,0,"ram_real_arready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+106,0,"ram_real_rvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+107,0,"ram_real_rready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+108,0,"bar_owns",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("u_bridge", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+210,0,"AXI_ADDR_W",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+211,0,"AXI_DATA_W",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBit(c+155,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+156,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declArray(c+157,0,"rx_st_hdr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declArray(c+161,0,"rx_st_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 255,0);
    tracep->declBit(c+169,0,"rx_st_sop",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+170,0,"rx_st_eop",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+171,0,"rx_st_hvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+172,0,"rx_st_dvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+173,0,"rx_st_bar",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBit(c+174,0,"rx_st_ready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declArray(c+175,0,"tx_st_hdr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declArray(c+179,0,"tx_st_data",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 255,0);
    tracep->declBit(c+187,0,"tx_st_sop",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+188,0,"tx_st_eop",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+189,0,"tx_st_hvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+190,0,"tx_st_dvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+191,0,"tx_st_ready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+192,0,"rx_hcrdt_init",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+193,0,"rx_hcrdt_update",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+194,0,"rx_hcrdt_update_cnt",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+195,0,"rx_dcrdt_init",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+196,0,"rx_dcrdt_update",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+197,0,"rx_dcrdt_update_cnt",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 11,0);
    tracep->declBus(c+198,0,"tx_hcrdt_init",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+199,0,"tx_hcrdt_init_ack",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+200,0,"tx_hcrdt_update",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+201,0,"tx_hcrdt_update_cnt",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+202,0,"tx_dcrdt_init",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+203,0,"tx_dcrdt_init_ack",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+204,0,"tx_dcrdt_update",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+205,0,"tx_dcrdt_update_cnt",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 11,0);
    tracep->declBit(c+206,0,"link_up",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+207,0,"ltssm_state",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+14,0,"m_axi_awaddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+23,0,"m_axi_awvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+24,0,"m_axi_awready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declQuad(c+16,0,"m_axi_wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+20,0,"m_axi_wstrb",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBit(c+25,0,"m_axi_wvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+26,0,"m_axi_wready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+21,0,"m_axi_bresp",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+27,0,"m_axi_bvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+28,0,"m_axi_bready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+15,0,"m_axi_araddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+29,0,"m_axi_arvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+30,0,"m_axi_arready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declQuad(c+18,0,"m_axi_rdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+22,0,"m_axi_rresp",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+31,0,"m_axi_rvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+32,0,"m_axi_rready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+33,0,"dma_mrd_valid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+34,0,"dma_mrd_ready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declQuad(c+35,0,"dma_mrd_addr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+37,0,"dma_mrd_len",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 9,0);
    tracep->declBus(c+38,0,"dma_mrd_tag",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBit(c+39,0,"dma_mwr_valid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+40,0,"dma_mwr_ready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declQuad(c+41,0,"dma_mwr_addr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+43,0,"dma_mwr_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+45,0,"dma_mwr_len",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 9,0);
    tracep->declBit(c+46,0,"dma_cpl_valid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+47,0,"dma_cpl_tag",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declQuad(c+48,0,"dma_cpl_data",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBit(c+109,0,"tx_cpl_hdr_ok",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+110,0,"tx_cpl_data_ok",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+111,0,"tx_cpl_hdr_dec",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+112,0,"tx_cpl_data_dec",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+1,0,"rx_fmt",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+2,0,"rx_type",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+3,0,"rx_len",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 9,0);
    tracep->declBus(c+4,0,"rx_rid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+5,0,"rx_tag",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+6,0,"rx_fbe",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+7,0,"rx_lbe",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declQuad(c+8,0,"rx_addr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBit(c+10,0,"rx_is_mrd",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+11,0,"rx_is_mwr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+12,0,"rx_is_cpld",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+209,0,"cpl_rx_tag",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+113,0,"state",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+114,0,"bar_req_rid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+115,0,"bar_req_tag",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+116,0,"bar_req_lower_addr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 6,0);
    tracep->declQuad(c+117,0,"bar_cpl_data",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+119,0,"bar_cpl_status",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+13,0,"wstrb_from_be",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declArray(c+120,0,"tx_hdr_r",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declQuad(c+124,0,"tx_data_r",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->pushPrefix("u_crdt", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+155,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+156,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+192,0,"rx_hcrdt_init",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+193,0,"rx_hcrdt_update",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+194,0,"rx_hcrdt_update_cnt",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+195,0,"rx_dcrdt_init",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+196,0,"rx_dcrdt_update",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+197,0,"rx_dcrdt_update_cnt",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 11,0);
    tracep->declBus(c+198,0,"tx_hcrdt_init",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+199,0,"tx_hcrdt_init_ack",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+200,0,"tx_hcrdt_update",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+201,0,"tx_hcrdt_update_cnt",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBus(c+202,0,"tx_dcrdt_init",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+203,0,"tx_dcrdt_init_ack",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+204,0,"tx_dcrdt_update",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+205,0,"tx_dcrdt_update_cnt",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 11,0);
    tracep->declBit(c+212,0,"rx_cpl_hdr_ret",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+212,0,"rx_cpl_data_ret",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+213,0,"rx_cpl_data_cnt",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 11,0);
    tracep->declBit(c+109,0,"tx_cpl_hdr_ok",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+110,0,"tx_cpl_data_ok",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+111,0,"tx_cpl_hdr_dec",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+112,0,"tx_cpl_data_dec",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+214,0,"tx_cpl_data_amt",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 11,0);
    tracep->declBit(c+126,0,"init_done",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+127,0,"state",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+128,0,"cnt",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+129,0,"tx_cpl_hdr_cnt",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+130,0,"tx_cpl_data_cnt",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 19,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->pushPrefix("u_dma", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+210,0,"ADDR_W",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+211,0,"DATA_W",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBit(c+155,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+156,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+14,0,"s_axi_awaddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+54,0,"s_axi_awvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+55,0,"s_axi_awready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declQuad(c+16,0,"s_axi_wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+20,0,"s_axi_wstrb",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBit(c+56,0,"s_axi_wvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+57,0,"s_axi_wready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+52,0,"s_axi_bresp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+58,0,"s_axi_bvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+28,0,"s_axi_bready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+15,0,"s_axi_araddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+59,0,"s_axi_arvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+60,0,"s_axi_arready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declQuad(c+50,0,"s_axi_rdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+53,0,"s_axi_rresp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+61,0,"s_axi_rvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+32,0,"s_axi_rready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+74,0,"m_axi_awaddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+79,0,"m_axi_awvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+80,0,"m_axi_awready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declQuad(c+76,0,"m_axi_wdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+78,0,"m_axi_wstrb",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBit(c+81,0,"m_axi_wvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+82,0,"m_axi_wready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+64,0,"m_axi_bresp",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+83,0,"m_axi_bvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+84,0,"m_axi_bready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+75,0,"m_axi_araddr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+85,0,"m_axi_arvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+86,0,"m_axi_arready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declQuad(c+62,0,"m_axi_rdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+65,0,"m_axi_rresp",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+87,0,"m_axi_rvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+88,0,"m_axi_rready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+33,0,"pcie_mrd_valid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+34,0,"pcie_mrd_ready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declQuad(c+35,0,"pcie_mrd_addr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+37,0,"pcie_mrd_len",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 9,0);
    tracep->declBus(c+38,0,"pcie_mrd_tag",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBit(c+39,0,"pcie_mwr_valid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+40,0,"pcie_mwr_ready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declQuad(c+41,0,"pcie_mwr_addr",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declQuad(c+43,0,"pcie_mwr_data",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+45,0,"pcie_mwr_len",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 9,0);
    tracep->declBit(c+46,0,"pcie_cpl_valid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+47,0,"pcie_cpl_tag",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declQuad(c+48,0,"pcie_cpl_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBit(c+208,0,"dma_irq",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+131,0,"ctrl_reg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+132,0,"status_reg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+133,0,"host_addr_lo",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+134,0,"host_addr_hi",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+135,0,"local_addr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+136,0,"length_reg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+137,0,"start",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+138,0,"dir",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+139,0,"irq_en",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+140,0,"busy",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+141,0,"done",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+142,0,"dma_state",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 3,0);
    tracep->declBus(c+143,0,"bytes_remaining",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declQuad(c+144,0,"cur_host_addr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+146,0,"cur_local_addr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declQuad(c+147,0,"dma_data_buf",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+149,0,"cur_tag",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->popPrefix();
    tracep->pushPrefix("u_ram", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+210,0,"ADDR_W",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+211,0,"DATA_W",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+215,0,"DEPTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBit(c+155,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+156,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+93,0,"s_axi_awaddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+98,0,"s_axi_awvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+99,0,"s_axi_awready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declQuad(c+95,0,"s_axi_wdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+97,0,"s_axi_wstrb",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBit(c+100,0,"s_axi_wvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+101,0,"s_axi_wready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+64,0,"s_axi_bresp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+102,0,"s_axi_bvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+103,0,"s_axi_bready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+94,0,"s_axi_araddr",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+104,0,"s_axi_arvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+105,0,"s_axi_arready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declQuad(c+62,0,"s_axi_rdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 63,0);
    tracep->declBus(c+65,0,"s_axi_rresp",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+106,0,"s_axi_rvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+107,0,"s_axi_rready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+216,0,"ADDR_BITS",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+150,0,"wr_idx",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 8,0);
    tracep->declBus(c+151,0,"rd_idx",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 8,0);
    tracep->declBus(c+152,0,"rd_addr_latched",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 8,0);
    tracep->declBit(c+153,0,"read_pending",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->pushPrefix("unnamedblk1", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+154,0,"i",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->popPrefix();
    tracep->popPrefix();
    tracep->popPrefix();
}

VL_ATTR_COLD void Vpcie_axi_top___024root__trace_init_sub__TOP__rtile_pkg__0(Vpcie_axi_top___024root* vlSelf, VerilatedVcd* tracep) {
    (void)vlSelf;  // Prevent unused variable warning
    Vpcie_axi_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpcie_axi_top___024root__trace_init_sub__TOP__rtile_pkg__0\n"); );
    // Init
    const int c = vlSymsp->__Vm_baseCode;
    // Body
    tracep->declBus(c+217,0,"NUM_SEG",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+218,0,"SEG_DW",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+219,0,"HDR_DW",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+210,0,"PREFIX_DW",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+220,0,"LTSSM_L0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
}

VL_ATTR_COLD void Vpcie_axi_top___024root__trace_init_top(Vpcie_axi_top___024root* vlSelf, VerilatedVcd* tracep) {
    (void)vlSelf;  // Prevent unused variable warning
    Vpcie_axi_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpcie_axi_top___024root__trace_init_top\n"); );
    // Body
    Vpcie_axi_top___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vpcie_axi_top___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
VL_ATTR_COLD void Vpcie_axi_top___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vpcie_axi_top___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vpcie_axi_top___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/);

VL_ATTR_COLD void Vpcie_axi_top___024root__trace_register(Vpcie_axi_top___024root* vlSelf, VerilatedVcd* tracep) {
    (void)vlSelf;  // Prevent unused variable warning
    Vpcie_axi_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpcie_axi_top___024root__trace_register\n"); );
    // Body
    tracep->addConstCb(&Vpcie_axi_top___024root__trace_const_0, 0U, vlSelf);
    tracep->addFullCb(&Vpcie_axi_top___024root__trace_full_0, 0U, vlSelf);
    tracep->addChgCb(&Vpcie_axi_top___024root__trace_chg_0, 0U, vlSelf);
    tracep->addCleanupCb(&Vpcie_axi_top___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vpcie_axi_top___024root__trace_const_0_sub_0(Vpcie_axi_top___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vpcie_axi_top___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpcie_axi_top___024root__trace_const_0\n"); );
    // Init
    Vpcie_axi_top___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vpcie_axi_top___024root*>(voidSelf);
    Vpcie_axi_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    Vpcie_axi_top___024root__trace_const_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vpcie_axi_top___024root__trace_const_0_sub_0(Vpcie_axi_top___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    (void)vlSelf;  // Prevent unused variable warning
    Vpcie_axi_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpcie_axi_top___024root__trace_const_0_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullIData(oldp+210,(0x20U),32);
    bufp->fullIData(oldp+211,(0x40U),32);
    bufp->fullBit(oldp+212,(0U));
    bufp->fullSData(oldp+213,(0U),12);
    bufp->fullSData(oldp+214,(1U),12);
    bufp->fullIData(oldp+215,(0x200U),32);
    bufp->fullIData(oldp+216,(9U),32);
    bufp->fullIData(oldp+217,(4U),32);
    bufp->fullIData(oldp+218,(0x100U),32);
    bufp->fullIData(oldp+219,(0x80U),32);
    bufp->fullCData(oldp+220,(0x11U),6);
}

VL_ATTR_COLD void Vpcie_axi_top___024root__trace_full_0_sub_0(Vpcie_axi_top___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vpcie_axi_top___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpcie_axi_top___024root__trace_full_0\n"); );
    // Init
    Vpcie_axi_top___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vpcie_axi_top___024root*>(voidSelf);
    Vpcie_axi_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    Vpcie_axi_top___024root__trace_full_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vpcie_axi_top___024root__trace_full_0_sub_0(Vpcie_axi_top___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    (void)vlSelf;  // Prevent unused variable warning
    Vpcie_axi_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpcie_axi_top___024root__trace_full_0_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullCData(oldp+1,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_fmt),3);
    bufp->fullCData(oldp+2,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_type),5);
    bufp->fullSData(oldp+3,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_len),10);
    bufp->fullSData(oldp+4,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_rid),16);
    bufp->fullCData(oldp+5,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_tag),8);
    bufp->fullCData(oldp+6,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_fbe),4);
    bufp->fullCData(oldp+7,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_lbe),4);
    bufp->fullQData(oldp+8,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_addr),64);
    bufp->fullBit(oldp+10,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_is_mrd));
    bufp->fullBit(oldp+11,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_is_mwr));
    bufp->fullBit(oldp+12,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_is_cpld));
    bufp->fullCData(oldp+13,((((IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_lbe) 
                               << 4U) | (IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__rx_fbe))),8);
    bufp->fullIData(oldp+14,(vlSelf->pcie_axi_top__DOT__brg_awaddr),32);
    bufp->fullIData(oldp+15,(vlSelf->pcie_axi_top__DOT__brg_araddr),32);
    bufp->fullQData(oldp+16,(vlSelf->pcie_axi_top__DOT__brg_wdata),64);
    bufp->fullQData(oldp+18,(((IData)(vlSelf->pcie_axi_top__DOT__dma_rvalid)
                               ? vlSelf->pcie_axi_top__DOT__dma_rdata
                               : vlSelf->pcie_axi_top__DOT__ram_real_rdata)),64);
    bufp->fullCData(oldp+20,(vlSelf->pcie_axi_top__DOT__brg_wstrb),8);
    bufp->fullCData(oldp+21,(((IData)(vlSelf->pcie_axi_top__DOT__dma_bvalid)
                               ? (IData)(vlSelf->pcie_axi_top__DOT__dma_bresp)
                               : (IData)(vlSelf->pcie_axi_top__DOT__ram_real_bresp))),2);
    bufp->fullCData(oldp+22,(((IData)(vlSelf->pcie_axi_top__DOT__dma_rvalid)
                               ? (IData)(vlSelf->pcie_axi_top__DOT__dma_rresp)
                               : (IData)(vlSelf->pcie_axi_top__DOT__ram_real_rresp))),2);
    bufp->fullBit(oldp+23,(vlSelf->pcie_axi_top__DOT__brg_awvalid));
    bufp->fullBit(oldp+24,(vlSelf->pcie_axi_top__DOT__brg_awready));
    bufp->fullBit(oldp+25,(vlSelf->pcie_axi_top__DOT__brg_wvalid));
    bufp->fullBit(oldp+26,(vlSelf->pcie_axi_top__DOT__brg_wready));
    bufp->fullBit(oldp+27,(((IData)(vlSelf->pcie_axi_top__DOT__dma_bvalid) 
                            | ((~ (IData)(vlSelf->pcie_axi_top__DOT__ram_owner)) 
                               & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_bvalid)))));
    bufp->fullBit(oldp+28,(vlSelf->pcie_axi_top__DOT__brg_bready));
    bufp->fullBit(oldp+29,(vlSelf->pcie_axi_top__DOT__brg_arvalid));
    bufp->fullBit(oldp+30,(((0x1000U & vlSelf->pcie_axi_top__DOT__brg_araddr)
                             ? ((~ (IData)(vlSelf->pcie_axi_top__DOT__ram_owner)) 
                                & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_arready))
                             : (IData)(vlSelf->pcie_axi_top__DOT__dma_arready))));
    bufp->fullBit(oldp+31,(((IData)(vlSelf->pcie_axi_top__DOT__dma_rvalid) 
                            | ((~ (IData)(vlSelf->pcie_axi_top__DOT__ram_owner)) 
                               & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_rvalid)))));
    bufp->fullBit(oldp+32,(vlSelf->pcie_axi_top__DOT__brg_rready));
    bufp->fullBit(oldp+33,(vlSelf->pcie_axi_top__DOT__dma_mrd_valid));
    bufp->fullBit(oldp+34,(vlSelf->pcie_axi_top__DOT__dma_mrd_ready));
    bufp->fullQData(oldp+35,(vlSelf->pcie_axi_top__DOT__dma_mrd_addr),64);
    bufp->fullSData(oldp+37,(vlSelf->pcie_axi_top__DOT__dma_mrd_len),10);
    bufp->fullCData(oldp+38,(vlSelf->pcie_axi_top__DOT__dma_mrd_tag),8);
    bufp->fullBit(oldp+39,(vlSelf->pcie_axi_top__DOT__dma_mwr_valid));
    bufp->fullBit(oldp+40,(vlSelf->pcie_axi_top__DOT__dma_mwr_ready));
    bufp->fullQData(oldp+41,(vlSelf->pcie_axi_top__DOT__dma_mwr_addr),64);
    bufp->fullQData(oldp+43,(vlSelf->pcie_axi_top__DOT__dma_mwr_data),64);
    bufp->fullSData(oldp+45,(vlSelf->pcie_axi_top__DOT__dma_mwr_len),10);
    bufp->fullBit(oldp+46,(vlSelf->pcie_axi_top__DOT__dma_cpl_valid));
    bufp->fullCData(oldp+47,(vlSelf->pcie_axi_top__DOT__dma_cpl_tag),8);
    bufp->fullQData(oldp+48,(vlSelf->pcie_axi_top__DOT__dma_cpl_data),64);
    bufp->fullQData(oldp+50,(vlSelf->pcie_axi_top__DOT__dma_rdata),64);
    bufp->fullCData(oldp+52,(vlSelf->pcie_axi_top__DOT__dma_bresp),2);
    bufp->fullCData(oldp+53,(vlSelf->pcie_axi_top__DOT__dma_rresp),2);
    bufp->fullBit(oldp+54,(((~ (vlSelf->pcie_axi_top__DOT__brg_awaddr 
                                >> 0xcU)) & (IData)(vlSelf->pcie_axi_top__DOT__brg_awvalid))));
    bufp->fullBit(oldp+55,(vlSelf->pcie_axi_top__DOT__dma_awready));
    bufp->fullBit(oldp+56,(((~ (vlSelf->pcie_axi_top__DOT__brg_awaddr 
                                >> 0xcU)) & (IData)(vlSelf->pcie_axi_top__DOT__brg_wvalid))));
    bufp->fullBit(oldp+57,(vlSelf->pcie_axi_top__DOT__dma_wready));
    bufp->fullBit(oldp+58,(vlSelf->pcie_axi_top__DOT__dma_bvalid));
    bufp->fullBit(oldp+59,(((~ (vlSelf->pcie_axi_top__DOT__brg_araddr 
                                >> 0xcU)) & (IData)(vlSelf->pcie_axi_top__DOT__brg_arvalid))));
    bufp->fullBit(oldp+60,(vlSelf->pcie_axi_top__DOT__dma_arready));
    bufp->fullBit(oldp+61,(vlSelf->pcie_axi_top__DOT__dma_rvalid));
    bufp->fullQData(oldp+62,(vlSelf->pcie_axi_top__DOT__ram_real_rdata),64);
    bufp->fullCData(oldp+64,(vlSelf->pcie_axi_top__DOT__ram_real_bresp),2);
    bufp->fullCData(oldp+65,(vlSelf->pcie_axi_top__DOT__ram_real_rresp),2);
    bufp->fullBit(oldp+66,(vlSelf->pcie_axi_top__DOT__ram_awvalid));
    bufp->fullBit(oldp+67,(((~ (IData)(vlSelf->pcie_axi_top__DOT__ram_owner)) 
                            & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_awready))));
    bufp->fullBit(oldp+68,(((IData)(vlSelf->pcie_axi_top__DOT__brg_wvalid) 
                            & (vlSelf->pcie_axi_top__DOT__brg_awaddr 
                               >> 0xcU))));
    bufp->fullBit(oldp+69,(((~ (IData)(vlSelf->pcie_axi_top__DOT__ram_owner)) 
                            & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_wready))));
    bufp->fullBit(oldp+70,(((~ (IData)(vlSelf->pcie_axi_top__DOT__ram_owner)) 
                            & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_bvalid))));
    bufp->fullBit(oldp+71,(vlSelf->pcie_axi_top__DOT__ram_arvalid));
    bufp->fullBit(oldp+72,(((~ (IData)(vlSelf->pcie_axi_top__DOT__ram_owner)) 
                            & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_arready))));
    bufp->fullBit(oldp+73,(((~ (IData)(vlSelf->pcie_axi_top__DOT__ram_owner)) 
                            & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_rvalid))));
    bufp->fullIData(oldp+74,(vlSelf->pcie_axi_top__DOT__dma_ram_awaddr),32);
    bufp->fullIData(oldp+75,(vlSelf->pcie_axi_top__DOT__dma_ram_araddr),32);
    bufp->fullQData(oldp+76,(vlSelf->pcie_axi_top__DOT__dma_ram_wdata),64);
    bufp->fullCData(oldp+78,(vlSelf->pcie_axi_top__DOT__dma_ram_wstrb),8);
    bufp->fullBit(oldp+79,(vlSelf->pcie_axi_top__DOT__dma_ram_awvalid));
    bufp->fullBit(oldp+80,(((IData)(vlSelf->pcie_axi_top__DOT__ram_owner) 
                            & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_awready))));
    bufp->fullBit(oldp+81,(vlSelf->pcie_axi_top__DOT__dma_ram_wvalid));
    bufp->fullBit(oldp+82,(((IData)(vlSelf->pcie_axi_top__DOT__ram_owner) 
                            & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_wready))));
    bufp->fullBit(oldp+83,(((IData)(vlSelf->pcie_axi_top__DOT__ram_owner) 
                            & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_bvalid))));
    bufp->fullBit(oldp+84,(vlSelf->pcie_axi_top__DOT__dma_ram_bready));
    bufp->fullBit(oldp+85,(vlSelf->pcie_axi_top__DOT__dma_ram_arvalid));
    bufp->fullBit(oldp+86,(((IData)(vlSelf->pcie_axi_top__DOT__ram_owner) 
                            & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_arready))));
    bufp->fullBit(oldp+87,(((IData)(vlSelf->pcie_axi_top__DOT__ram_owner) 
                            & (IData)(vlSelf->pcie_axi_top__DOT__ram_real_rvalid))));
    bufp->fullBit(oldp+88,(vlSelf->pcie_axi_top__DOT__dma_ram_rready));
    bufp->fullBit(oldp+89,((1U & (vlSelf->pcie_axi_top__DOT__brg_awaddr 
                                  >> 0xcU))));
    bufp->fullBit(oldp+90,((1U & (vlSelf->pcie_axi_top__DOT__brg_araddr 
                                  >> 0xcU))));
    bufp->fullBit(oldp+91,(vlSelf->pcie_axi_top__DOT__ram_busy));
    bufp->fullBit(oldp+92,(vlSelf->pcie_axi_top__DOT__ram_owner));
    bufp->fullIData(oldp+93,(((IData)(vlSelf->pcie_axi_top__DOT__ram_owner)
                               ? vlSelf->pcie_axi_top__DOT__dma_ram_awaddr
                               : vlSelf->pcie_axi_top__DOT__brg_awaddr)),32);
    bufp->fullIData(oldp+94,(((IData)(vlSelf->pcie_axi_top__DOT__ram_owner)
                               ? vlSelf->pcie_axi_top__DOT__dma_ram_araddr
                               : vlSelf->pcie_axi_top__DOT__brg_araddr)),32);
    bufp->fullQData(oldp+95,(vlSelf->pcie_axi_top__DOT__ram_real_wdata),64);
    bufp->fullCData(oldp+97,(vlSelf->pcie_axi_top__DOT__ram_real_wstrb),8);
    bufp->fullBit(oldp+98,(((IData)(vlSelf->pcie_axi_top__DOT__ram_owner)
                             ? (IData)(vlSelf->pcie_axi_top__DOT__dma_ram_awvalid)
                             : (IData)(vlSelf->pcie_axi_top__DOT__ram_awvalid))));
    bufp->fullBit(oldp+99,(vlSelf->pcie_axi_top__DOT__ram_real_awready));
    bufp->fullBit(oldp+100,(((IData)(vlSelf->pcie_axi_top__DOT__ram_owner)
                              ? (IData)(vlSelf->pcie_axi_top__DOT__dma_ram_wvalid)
                              : ((IData)(vlSelf->pcie_axi_top__DOT__brg_wvalid) 
                                 & (vlSelf->pcie_axi_top__DOT__brg_awaddr 
                                    >> 0xcU)))));
    bufp->fullBit(oldp+101,(vlSelf->pcie_axi_top__DOT__ram_real_wready));
    bufp->fullBit(oldp+102,(vlSelf->pcie_axi_top__DOT__ram_real_bvalid));
    bufp->fullBit(oldp+103,(vlSelf->pcie_axi_top__DOT__ram_real_bready));
    bufp->fullBit(oldp+104,(((IData)(vlSelf->pcie_axi_top__DOT__ram_owner)
                              ? (IData)(vlSelf->pcie_axi_top__DOT__dma_ram_arvalid)
                              : (IData)(vlSelf->pcie_axi_top__DOT__ram_arvalid))));
    bufp->fullBit(oldp+105,(vlSelf->pcie_axi_top__DOT__ram_real_arready));
    bufp->fullBit(oldp+106,(vlSelf->pcie_axi_top__DOT__ram_real_rvalid));
    bufp->fullBit(oldp+107,(vlSelf->pcie_axi_top__DOT__ram_real_rready));
    bufp->fullBit(oldp+108,((1U & (~ (IData)(vlSelf->pcie_axi_top__DOT__ram_owner)))));
    bufp->fullBit(oldp+109,((0U < (IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__tx_cpl_hdr_cnt))));
    bufp->fullBit(oldp+110,((0U < vlSelf->pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__tx_cpl_data_cnt)));
    bufp->fullBit(oldp+111,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_cpl_hdr_dec));
    bufp->fullBit(oldp+112,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_cpl_data_dec));
    bufp->fullCData(oldp+113,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__state),4);
    bufp->fullSData(oldp+114,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__bar_req_rid),16);
    bufp->fullCData(oldp+115,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__bar_req_tag),8);
    bufp->fullCData(oldp+116,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__bar_req_lower_addr),7);
    bufp->fullQData(oldp+117,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__bar_cpl_data),64);
    bufp->fullCData(oldp+119,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__bar_cpl_status),2);
    bufp->fullWData(oldp+120,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_hdr_r),128);
    bufp->fullQData(oldp+124,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__tx_data_r),64);
    bufp->fullBit(oldp+126,((3U == (IData)(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__state))));
    bufp->fullCData(oldp+127,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__state),2);
    bufp->fullCData(oldp+128,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__cnt),4);
    bufp->fullSData(oldp+129,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__tx_cpl_hdr_cnt),16);
    bufp->fullIData(oldp+130,(vlSelf->pcie_axi_top__DOT__u_bridge__DOT__u_crdt__DOT__tx_cpl_data_cnt),20);
    bufp->fullIData(oldp+131,(vlSelf->pcie_axi_top__DOT__u_dma__DOT__ctrl_reg),32);
    bufp->fullIData(oldp+132,(vlSelf->pcie_axi_top__DOT__u_dma__DOT__status_reg),32);
    bufp->fullIData(oldp+133,(vlSelf->pcie_axi_top__DOT__u_dma__DOT__host_addr_lo),32);
    bufp->fullIData(oldp+134,(vlSelf->pcie_axi_top__DOT__u_dma__DOT__host_addr_hi),32);
    bufp->fullIData(oldp+135,(vlSelf->pcie_axi_top__DOT__u_dma__DOT__local_addr),32);
    bufp->fullIData(oldp+136,(vlSelf->pcie_axi_top__DOT__u_dma__DOT__length_reg),32);
    bufp->fullBit(oldp+137,((1U & vlSelf->pcie_axi_top__DOT__u_dma__DOT__ctrl_reg)));
    bufp->fullBit(oldp+138,((1U & (vlSelf->pcie_axi_top__DOT__u_dma__DOT__ctrl_reg 
                                   >> 1U))));
    bufp->fullBit(oldp+139,((1U & (vlSelf->pcie_axi_top__DOT__u_dma__DOT__ctrl_reg 
                                   >> 2U))));
    bufp->fullBit(oldp+140,((1U & vlSelf->pcie_axi_top__DOT__u_dma__DOT__status_reg)));
    bufp->fullBit(oldp+141,((1U & (vlSelf->pcie_axi_top__DOT__u_dma__DOT__status_reg 
                                   >> 1U))));
    bufp->fullCData(oldp+142,(vlSelf->pcie_axi_top__DOT__u_dma__DOT__dma_state),4);
    bufp->fullIData(oldp+143,(vlSelf->pcie_axi_top__DOT__u_dma__DOT__bytes_remaining),32);
    bufp->fullQData(oldp+144,(vlSelf->pcie_axi_top__DOT__u_dma__DOT__cur_host_addr),64);
    bufp->fullIData(oldp+146,(vlSelf->pcie_axi_top__DOT__u_dma__DOT__cur_local_addr),32);
    bufp->fullQData(oldp+147,(vlSelf->pcie_axi_top__DOT__u_dma__DOT__dma_data_buf),64);
    bufp->fullCData(oldp+149,(vlSelf->pcie_axi_top__DOT__u_dma__DOT__cur_tag),8);
    bufp->fullSData(oldp+150,((0x1ffU & (((IData)(vlSelf->pcie_axi_top__DOT__ram_owner)
                                           ? vlSelf->pcie_axi_top__DOT__dma_ram_awaddr
                                           : vlSelf->pcie_axi_top__DOT__brg_awaddr) 
                                         >> 3U))),9);
    bufp->fullSData(oldp+151,((0x1ffU & (((IData)(vlSelf->pcie_axi_top__DOT__ram_owner)
                                           ? vlSelf->pcie_axi_top__DOT__dma_ram_araddr
                                           : vlSelf->pcie_axi_top__DOT__brg_araddr) 
                                         >> 3U))),9);
    bufp->fullSData(oldp+152,(vlSelf->pcie_axi_top__DOT__u_ram__DOT__rd_addr_latched),9);
    bufp->fullBit(oldp+153,(vlSelf->pcie_axi_top__DOT__u_ram__DOT__read_pending));
    bufp->fullIData(oldp+154,(vlSelf->pcie_axi_top__DOT__u_ram__DOT__unnamedblk1__DOT__i),32);
    bufp->fullBit(oldp+155,(vlSelf->clk));
    bufp->fullBit(oldp+156,(vlSelf->rst_n));
    bufp->fullWData(oldp+157,(vlSelf->rx_st_hdr),128);
    bufp->fullWData(oldp+161,(vlSelf->rx_st_data),256);
    bufp->fullBit(oldp+169,(vlSelf->rx_st_sop));
    bufp->fullBit(oldp+170,(vlSelf->rx_st_eop));
    bufp->fullBit(oldp+171,(vlSelf->rx_st_hvalid));
    bufp->fullBit(oldp+172,(vlSelf->rx_st_dvalid));
    bufp->fullCData(oldp+173,(vlSelf->rx_st_bar),3);
    bufp->fullBit(oldp+174,(vlSelf->rx_st_ready));
    bufp->fullWData(oldp+175,(vlSelf->tx_st_hdr),128);
    bufp->fullWData(oldp+179,(vlSelf->tx_st_data),256);
    bufp->fullBit(oldp+187,(vlSelf->tx_st_sop));
    bufp->fullBit(oldp+188,(vlSelf->tx_st_eop));
    bufp->fullBit(oldp+189,(vlSelf->tx_st_hvalid));
    bufp->fullBit(oldp+190,(vlSelf->tx_st_dvalid));
    bufp->fullBit(oldp+191,(vlSelf->tx_st_ready));
    bufp->fullCData(oldp+192,(vlSelf->rx_hcrdt_init),3);
    bufp->fullCData(oldp+193,(vlSelf->rx_hcrdt_update),3);
    bufp->fullCData(oldp+194,(vlSelf->rx_hcrdt_update_cnt),6);
    bufp->fullCData(oldp+195,(vlSelf->rx_dcrdt_init),3);
    bufp->fullCData(oldp+196,(vlSelf->rx_dcrdt_update),3);
    bufp->fullSData(oldp+197,(vlSelf->rx_dcrdt_update_cnt),12);
    bufp->fullCData(oldp+198,(vlSelf->tx_hcrdt_init),3);
    bufp->fullCData(oldp+199,(vlSelf->tx_hcrdt_init_ack),3);
    bufp->fullCData(oldp+200,(vlSelf->tx_hcrdt_update),3);
    bufp->fullCData(oldp+201,(vlSelf->tx_hcrdt_update_cnt),6);
    bufp->fullCData(oldp+202,(vlSelf->tx_dcrdt_init),3);
    bufp->fullCData(oldp+203,(vlSelf->tx_dcrdt_init_ack),3);
    bufp->fullCData(oldp+204,(vlSelf->tx_dcrdt_update),3);
    bufp->fullSData(oldp+205,(vlSelf->tx_dcrdt_update_cnt),12);
    bufp->fullBit(oldp+206,(vlSelf->link_up));
    bufp->fullCData(oldp+207,(vlSelf->ltssm_state),6);
    bufp->fullBit(oldp+208,(vlSelf->dma_irq));
    bufp->fullCData(oldp+209,((0xffU & (vlSelf->rx_st_hdr[1U] 
                                        >> 8U))),8);
}
