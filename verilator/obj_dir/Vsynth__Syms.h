// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VSYNTH__SYMS_H_
#define VERILATED_VSYNTH__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vsynth.h"

// INCLUDE MODULE CLASSES
#include "Vsynth___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vsynth__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vsynth* const __Vm_modelp;
    bool __Vm_activity = false;  ///< Used by trace routines to determine change occurred
    uint32_t __Vm_baseCode = 0;  ///< Used by trace routines when tracing multiple models
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vsynth___024root               TOP;

    // CONSTRUCTORS
    Vsynth__Syms(VerilatedContext* contextp, const char* namep, Vsynth* modelp);
    ~Vsynth__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
