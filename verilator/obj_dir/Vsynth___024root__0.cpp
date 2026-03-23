// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsynth.h for the primary calling header

#include "Vsynth__pch.h"

void Vsynth___024root___eval_triggers_vec__ico(Vsynth___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth___024root___eval_triggers_vec__ico\n"); );
    Vsynth__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VicoTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VicoTriggered[0U]) 
                                     | (IData)((IData)(vlSelfRef.__VicoFirstIteration)));
}

bool Vsynth___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth___024root___trigger_anySet__ico\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

extern const VlUnpacked<SData/*15:0*/, 64> Vsynth__ConstPool__TABLE_h115da5b7_0;

void Vsynth___024root___ico_sequent__TOP__0(Vsynth___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth___024root___ico_sequent__TOP__0\n"); );
    Vsynth__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*5:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    // Body
    __Vtableidx1 = vlSelfRef.midi_note;
    vlSelfRef.synth__DOT__phase_inc = Vsynth__ConstPool__TABLE_h115da5b7_0
        [__Vtableidx1];
}

void Vsynth___024root___eval_ico(Vsynth___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth___024root___eval_ico\n"); );
    Vsynth__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered[0U])) {
        Vsynth___024root___ico_sequent__TOP__0(vlSelf);
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vsynth___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vsynth___024root___eval_phase__ico(Vsynth___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth___024root___eval_phase__ico\n"); );
    Vsynth__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VicoExecute;
    // Body
    Vsynth___024root___eval_triggers_vec__ico(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vsynth___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
    }
#endif
    __VicoExecute = Vsynth___024root___trigger_anySet__ico(vlSelfRef.__VicoTriggered);
    if (__VicoExecute) {
        Vsynth___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void Vsynth___024root___eval_triggers_vec__act(Vsynth___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth___024root___eval_triggers_vec__act\n"); );
    Vsynth__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    ((((~ (IData)(vlSelfRef.rst_n)) 
                                                       & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__rst_n__0)) 
                                                      << 1U) 
                                                     | ((IData)(vlSelfRef.clk) 
                                                        & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clk__0))))));
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
    vlSelfRef.__Vtrigprevexpr___TOP__rst_n__0 = vlSelfRef.rst_n;
}

bool Vsynth___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth___024root___trigger_anySet__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

void Vsynth___024root___nba_sequent__TOP__0(Vsynth___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth___024root___nba_sequent__TOP__0\n"); );
    Vsynth__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*1:0*/ __Vdly__synth__DOT__sample_div;
    __Vdly__synth__DOT__sample_div = 0;
    // Body
    __Vdly__synth__DOT__sample_div = vlSelfRef.synth__DOT__sample_div;
    if (vlSelfRef.rst_n) {
        __Vdly__synth__DOT__sample_div = (3U & ((IData)(1U) 
                                                + (IData)(vlSelfRef.synth__DOT__sample_div)));
        if ((3U == (IData)(vlSelfRef.synth__DOT__sample_div))) {
            vlSelfRef.synth__DOT__env = ((IData)(vlSelfRef.gate)
                                          ? 0x0000ffffU
                                          : (0x0000ffffU 
                                             & ((IData)(vlSelfRef.synth__DOT__env) 
                                                - VL_SHIFTR_III(16,16,32, (IData)(vlSelfRef.synth__DOT__env), 0x0000000dU))));
            vlSelfRef.synth__DOT__phase = (0x0000ffffU 
                                           & ((IData)(vlSelfRef.synth__DOT__phase) 
                                              + (IData)(vlSelfRef.synth__DOT__phase_inc)));
            vlSelfRef.synth__DOT__gate_prev = vlSelfRef.gate;
        }
        vlSelfRef.synth__DOT__sd_accum = (0x0000ffffU 
                                          & vlSelfRef.synth__DOT__sd_next);
    } else {
        __Vdly__synth__DOT__sample_div = 0U;
        vlSelfRef.synth__DOT__env = 0U;
        vlSelfRef.synth__DOT__phase = 0U;
        vlSelfRef.synth__DOT__gate_prev = 0U;
        vlSelfRef.synth__DOT__sd_accum = 0U;
    }
    vlSelfRef.audio_out = ((IData)(vlSelfRef.rst_n) 
                           && (1U & (vlSelfRef.synth__DOT__sd_next 
                                     >> 0x10U)));
    vlSelfRef.synth__DOT__sample_div = __Vdly__synth__DOT__sample_div;
    vlSelfRef.audio_sample = (0x0000ffffU & (0x8000U 
                                             ^ (((0x0000ffffU 
                                                  & ((0x00008000U 
                                                      & (IData)(vlSelfRef.synth__DOT__phase))
                                                      ? 
                                                     (~ (IData)(vlSelfRef.synth__DOT__phase))
                                                      : (IData)(vlSelfRef.synth__DOT__phase))) 
                                                 * (IData)(vlSelfRef.synth__DOT__env)) 
                                                >> 0x0000000fU)));
    vlSelfRef.synth__DOT__sd_next = (0x0001ffffU & 
                                     ((IData)(vlSelfRef.synth__DOT__sd_accum) 
                                      + (IData)(vlSelfRef.audio_sample)));
}

void Vsynth___024root___eval_nba(Vsynth___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth___024root___eval_nba\n"); );
    Vsynth__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vsynth___024root___nba_sequent__TOP__0(vlSelf);
        vlSelfRef.__Vm_traceActivity[1U] = 1U;
    }
}

void Vsynth___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth___024root___trigger_orInto__act_vec_vec\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((0U >= n));
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vsynth___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vsynth___024root___eval_phase__act(Vsynth___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth___024root___eval_phase__act\n"); );
    Vsynth__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vsynth___024root___eval_triggers_vec__act(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vsynth___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vsynth___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    return (0U);
}

void Vsynth___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vsynth___024root___eval_phase__nba(Vsynth___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth___024root___eval_phase__nba\n"); );
    Vsynth__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vsynth___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vsynth___024root___eval_nba(vlSelf);
        Vsynth___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vsynth___024root___eval(Vsynth___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth___024root___eval\n"); );
    Vsynth__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VicoIterCount;
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VicoIterCount = 0U;
    vlSelfRef.__VicoFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VicoIterCount)))) {
#ifdef VL_DEBUG
            Vsynth___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
#endif
            VL_FATAL_MT("../src/../src/synth.v", 11, "", "DIDNOTCONVERGE: Input combinational region did not converge after '--converge-limit' of 100 tries");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        vlSelfRef.__VicoPhaseResult = Vsynth___024root___eval_phase__ico(vlSelf);
        vlSelfRef.__VicoFirstIteration = 0U;
    } while (vlSelfRef.__VicoPhaseResult);
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vsynth___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("../src/../src/synth.v", 11, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vsynth___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("../src/../src/synth.v", 11, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 100 tries");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactPhaseResult = Vsynth___024root___eval_phase__act(vlSelf);
        } while (vlSelfRef.__VactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vsynth___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

#ifdef VL_DEBUG
void Vsynth___024root___eval_debug_assertions(Vsynth___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth___024root___eval_debug_assertions\n"); );
    Vsynth__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clk & 0xfeU)))) {
        Verilated::overWidthError("clk");
    }
    if (VL_UNLIKELY(((vlSelfRef.rst_n & 0xfeU)))) {
        Verilated::overWidthError("rst_n");
    }
    if (VL_UNLIKELY(((vlSelfRef.midi_note & 0xc0U)))) {
        Verilated::overWidthError("midi_note");
    }
    if (VL_UNLIKELY(((vlSelfRef.gate & 0xfeU)))) {
        Verilated::overWidthError("gate");
    }
}
#endif  // VL_DEBUG
