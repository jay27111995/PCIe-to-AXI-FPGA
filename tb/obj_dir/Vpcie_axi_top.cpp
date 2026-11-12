// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vpcie_axi_top__pch.h"
#include "verilated_vcd_c.h"

//============================================================
// Constructors

Vpcie_axi_top::Vpcie_axi_top(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vpcie_axi_top__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , rst_n{vlSymsp->TOP.rst_n}
    , rx_st_sop{vlSymsp->TOP.rx_st_sop}
    , rx_st_eop{vlSymsp->TOP.rx_st_eop}
    , rx_st_hvalid{vlSymsp->TOP.rx_st_hvalid}
    , rx_st_dvalid{vlSymsp->TOP.rx_st_dvalid}
    , rx_st_bar{vlSymsp->TOP.rx_st_bar}
    , rx_st_ready{vlSymsp->TOP.rx_st_ready}
    , tx_st_sop{vlSymsp->TOP.tx_st_sop}
    , tx_st_eop{vlSymsp->TOP.tx_st_eop}
    , tx_st_hvalid{vlSymsp->TOP.tx_st_hvalid}
    , tx_st_dvalid{vlSymsp->TOP.tx_st_dvalid}
    , tx_st_ready{vlSymsp->TOP.tx_st_ready}
    , rx_hcrdt_init{vlSymsp->TOP.rx_hcrdt_init}
    , rx_hcrdt_update{vlSymsp->TOP.rx_hcrdt_update}
    , rx_hcrdt_update_cnt{vlSymsp->TOP.rx_hcrdt_update_cnt}
    , rx_dcrdt_init{vlSymsp->TOP.rx_dcrdt_init}
    , rx_dcrdt_update{vlSymsp->TOP.rx_dcrdt_update}
    , tx_hcrdt_init{vlSymsp->TOP.tx_hcrdt_init}
    , tx_hcrdt_init_ack{vlSymsp->TOP.tx_hcrdt_init_ack}
    , tx_hcrdt_update{vlSymsp->TOP.tx_hcrdt_update}
    , tx_hcrdt_update_cnt{vlSymsp->TOP.tx_hcrdt_update_cnt}
    , tx_dcrdt_init{vlSymsp->TOP.tx_dcrdt_init}
    , tx_dcrdt_init_ack{vlSymsp->TOP.tx_dcrdt_init_ack}
    , tx_dcrdt_update{vlSymsp->TOP.tx_dcrdt_update}
    , link_up{vlSymsp->TOP.link_up}
    , ltssm_state{vlSymsp->TOP.ltssm_state}
    , dma_irq{vlSymsp->TOP.dma_irq}
    , rx_dcrdt_update_cnt{vlSymsp->TOP.rx_dcrdt_update_cnt}
    , tx_dcrdt_update_cnt{vlSymsp->TOP.tx_dcrdt_update_cnt}
    , rx_st_hdr{vlSymsp->TOP.rx_st_hdr}
    , rx_st_data{vlSymsp->TOP.rx_st_data}
    , tx_st_hdr{vlSymsp->TOP.tx_st_hdr}
    , tx_st_data{vlSymsp->TOP.tx_st_data}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
    contextp()->traceBaseModelCbAdd(
        [this](VerilatedTraceBaseC* tfp, int levels, int options) { traceBaseModel(tfp, levels, options); });
}

Vpcie_axi_top::Vpcie_axi_top(const char* _vcname__)
    : Vpcie_axi_top(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vpcie_axi_top::~Vpcie_axi_top() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vpcie_axi_top___024root___eval_debug_assertions(Vpcie_axi_top___024root* vlSelf);
#endif  // VL_DEBUG
void Vpcie_axi_top___024root___eval_static(Vpcie_axi_top___024root* vlSelf);
void Vpcie_axi_top___024root___eval_initial(Vpcie_axi_top___024root* vlSelf);
void Vpcie_axi_top___024root___eval_settle(Vpcie_axi_top___024root* vlSelf);
void Vpcie_axi_top___024root___eval(Vpcie_axi_top___024root* vlSelf);

void Vpcie_axi_top::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vpcie_axi_top::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vpcie_axi_top___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_activity = true;
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vpcie_axi_top___024root___eval_static(&(vlSymsp->TOP));
        Vpcie_axi_top___024root___eval_initial(&(vlSymsp->TOP));
        Vpcie_axi_top___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vpcie_axi_top___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vpcie_axi_top::eventsPending() { return false; }

uint64_t Vpcie_axi_top::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "%Error: No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vpcie_axi_top::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vpcie_axi_top___024root___eval_final(Vpcie_axi_top___024root* vlSelf);

VL_ATTR_COLD void Vpcie_axi_top::final() {
    Vpcie_axi_top___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vpcie_axi_top::hierName() const { return vlSymsp->name(); }
const char* Vpcie_axi_top::modelName() const { return "Vpcie_axi_top"; }
unsigned Vpcie_axi_top::threads() const { return 1; }
void Vpcie_axi_top::prepareClone() const { contextp()->prepareClone(); }
void Vpcie_axi_top::atClone() const {
    contextp()->threadPoolpOnClone();
}
std::unique_ptr<VerilatedTraceConfig> Vpcie_axi_top::traceConfig() const {
    return std::unique_ptr<VerilatedTraceConfig>{new VerilatedTraceConfig{false, false, false}};
};

//============================================================
// Trace configuration

void Vpcie_axi_top___024root__trace_decl_types(VerilatedVcd* tracep);

void Vpcie_axi_top___024root__trace_init_top(Vpcie_axi_top___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD static void trace_init(void* voidSelf, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vpcie_axi_top___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vpcie_axi_top___024root*>(voidSelf);
    Vpcie_axi_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->pushPrefix(std::string{vlSymsp->name()}, VerilatedTracePrefixType::SCOPE_MODULE);
    Vpcie_axi_top___024root__trace_decl_types(tracep);
    Vpcie_axi_top___024root__trace_init_top(vlSelf, tracep);
    tracep->popPrefix();
}

VL_ATTR_COLD void Vpcie_axi_top___024root__trace_register(Vpcie_axi_top___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD void Vpcie_axi_top::traceBaseModel(VerilatedTraceBaseC* tfp, int levels, int options) {
    (void)levels; (void)options;
    VerilatedVcdC* const stfp = dynamic_cast<VerilatedVcdC*>(tfp);
    if (VL_UNLIKELY(!stfp)) {
        vl_fatal(__FILE__, __LINE__, __FILE__,"'Vpcie_axi_top::trace()' called on non-VerilatedVcdC object;"
            " use --trace-fst with VerilatedFst object, and --trace with VerilatedVcd object");
    }
    stfp->spTrace()->addModel(this);
    stfp->spTrace()->addInitCb(&trace_init, &(vlSymsp->TOP));
    Vpcie_axi_top___024root__trace_register(&(vlSymsp->TOP), stfp->spTrace());
}
