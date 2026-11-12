// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary model header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef VERILATED_VPCIE_AXI_TOP_H_
#define VERILATED_VPCIE_AXI_TOP_H_  // guard

#include "verilated.h"

class Vpcie_axi_top__Syms;
class Vpcie_axi_top___024root;
class VerilatedVcdC;

// This class is the main interface to the Verilated model
class alignas(VL_CACHE_LINE_BYTES) Vpcie_axi_top VL_NOT_FINAL : public VerilatedModel {
  private:
    // Symbol table holding complete model state (owned by this class)
    Vpcie_axi_top__Syms* const vlSymsp;

  public:

    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(&clk,0,0);
    VL_IN8(&rst_n,0,0);
    VL_IN8(&rx_st_sop,0,0);
    VL_IN8(&rx_st_eop,0,0);
    VL_IN8(&rx_st_hvalid,0,0);
    VL_IN8(&rx_st_dvalid,0,0);
    VL_IN8(&rx_st_bar,2,0);
    VL_OUT8(&rx_st_ready,0,0);
    VL_OUT8(&tx_st_sop,0,0);
    VL_OUT8(&tx_st_eop,0,0);
    VL_OUT8(&tx_st_hvalid,0,0);
    VL_OUT8(&tx_st_dvalid,0,0);
    VL_IN8(&tx_st_ready,0,0);
    VL_OUT8(&rx_hcrdt_init,2,0);
    VL_OUT8(&rx_hcrdt_update,2,0);
    VL_OUT8(&rx_hcrdt_update_cnt,5,0);
    VL_OUT8(&rx_dcrdt_init,2,0);
    VL_OUT8(&rx_dcrdt_update,2,0);
    VL_IN8(&tx_hcrdt_init,2,0);
    VL_OUT8(&tx_hcrdt_init_ack,2,0);
    VL_IN8(&tx_hcrdt_update,2,0);
    VL_IN8(&tx_hcrdt_update_cnt,5,0);
    VL_IN8(&tx_dcrdt_init,2,0);
    VL_OUT8(&tx_dcrdt_init_ack,2,0);
    VL_IN8(&tx_dcrdt_update,2,0);
    VL_IN8(&link_up,0,0);
    VL_IN8(&ltssm_state,5,0);
    VL_OUT8(&dma_irq,0,0);
    VL_OUT16(&rx_dcrdt_update_cnt,11,0);
    VL_IN16(&tx_dcrdt_update_cnt,11,0);
    VL_INW(&rx_st_hdr,127,0,4);
    VL_INW(&rx_st_data,255,0,8);
    VL_OUTW(&tx_st_hdr,127,0,4);
    VL_OUTW(&tx_st_data,255,0,8);

    // CELLS
    // Public to allow access to /* verilator public */ items.
    // Otherwise the application code can consider these internals.

    // Root instance pointer to allow access to model internals,
    // including inlined /* verilator public_flat_* */ items.
    Vpcie_axi_top___024root* const rootp;

    // CONSTRUCTORS
    /// Construct the model; called by application code
    /// If contextp is null, then the model will use the default global context
    /// If name is "", then makes a wrapper with a
    /// single model invisible with respect to DPI scope names.
    explicit Vpcie_axi_top(VerilatedContext* contextp, const char* name = "TOP");
    explicit Vpcie_axi_top(const char* name = "TOP");
    /// Destroy the model; called (often implicitly) by application code
    virtual ~Vpcie_axi_top();
  private:
    VL_UNCOPYABLE(Vpcie_axi_top);  ///< Copying not allowed

  public:
    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval() { eval_step(); }
    /// Evaluate when calling multiple units/models per time step.
    void eval_step();
    /// Evaluate at end of a timestep for tracing, when using eval_step().
    /// Application must call after all eval() and before time changes.
    void eval_end_step() {}
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();
    /// Are there scheduled events to handle?
    bool eventsPending();
    /// Returns time at next time slot. Aborts if !eventsPending()
    uint64_t nextTimeSlot();
    /// Trace signals in the model; called by application code
    void trace(VerilatedTraceBaseC* tfp, int levels, int options = 0) { contextp()->trace(tfp, levels, options); }
    /// Retrieve name of this model instance (as passed to constructor).
    const char* name() const;

    // Abstract methods from VerilatedModel
    const char* hierName() const override final;
    const char* modelName() const override final;
    unsigned threads() const override final;
    /// Prepare for cloning the model at the process level (e.g. fork in Linux)
    /// Release necessary resources. Called before cloning.
    void prepareClone() const;
    /// Re-init after cloning the model at the process level (e.g. fork in Linux)
    /// Re-allocate necessary resources. Called after cloning.
    void atClone() const;
    std::unique_ptr<VerilatedTraceConfig> traceConfig() const override final;
  private:
    // Internal functions - trace registration
    void traceBaseModel(VerilatedTraceBaseC* tfp, int levels, int options);
};

#endif  // guard
