// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vsynth.h for the primary calling header

#ifndef VERILATED_VSYNTH___024ROOT_H_
#define VERILATED_VSYNTH___024ROOT_H_  // guard

#include "verilated.h"


class Vsynth__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vsynth___024root final {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rst_n,0,0);
    VL_IN8(midi_note,5,0);
    VL_IN8(gate,0,0);
    VL_OUT8(audio_out,0,0);
    CData/*1:0*/ synth__DOT__sample_div;
    CData/*0:0*/ synth__DOT__gate_prev;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VstlPhaseResult;
    CData/*0:0*/ __VicoFirstIteration;
    CData/*0:0*/ __VicoPhaseResult;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    CData/*0:0*/ __Vtrigprevexpr___TOP__rst_n__0;
    CData/*0:0*/ __VactPhaseResult;
    CData/*0:0*/ __VnbaPhaseResult;
    VL_OUT16(audio_sample,15,0);
    SData/*15:0*/ synth__DOT__phase;
    SData/*15:0*/ synth__DOT__phase_inc;
    SData/*15:0*/ synth__DOT__env;
    SData/*15:0*/ synth__DOT__sd_accum;
    IData/*16:0*/ synth__DOT__sd_next;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VicoTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    VlUnpacked<CData/*0:0*/, 2> __Vm_traceActivity;

    // INTERNAL VARIABLES
    Vsynth__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vsynth___024root(Vsynth__Syms* symsp, const char* namep);
    ~Vsynth___024root();
    VL_UNCOPYABLE(Vsynth___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
