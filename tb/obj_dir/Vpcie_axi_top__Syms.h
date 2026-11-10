// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VPCIE_AXI_TOP__SYMS_H_
#define VERILATED_VPCIE_AXI_TOP__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vpcie_axi_top.h"

// INCLUDE MODULE CLASSES
#include "Vpcie_axi_top___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES)Vpcie_axi_top__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vpcie_axi_top* const __Vm_modelp;
    bool __Vm_activity = false;  ///< Used by trace routines to determine change occurred
    uint32_t __Vm_baseCode = 0;  ///< Used by trace routines when tracing multiple models
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vpcie_axi_top___024root        TOP;

    // CONSTRUCTORS
    Vpcie_axi_top__Syms(VerilatedContext* contextp, const char* namep, Vpcie_axi_top* modelp);
    ~Vpcie_axi_top__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
};

#endif  // guard
