// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsynth.h for the primary calling header

#include "Vsynth__pch.h"

void Vsynth___024root___ctor_var_reset(Vsynth___024root* vlSelf);

Vsynth___024root::Vsynth___024root(Vsynth__Syms* symsp, const char* namep)
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vsynth___024root___ctor_var_reset(this);
}

void Vsynth___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vsynth___024root::~Vsynth___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
