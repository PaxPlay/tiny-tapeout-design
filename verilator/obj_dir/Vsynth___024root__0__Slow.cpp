// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsynth.h for the primary calling header

#include "Vsynth__pch.h"

VL_ATTR_COLD void Vsynth___024root___eval_static(Vsynth___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth___024root___eval_static\n"); );
    Vsynth__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
    vlSelfRef.__Vtrigprevexpr___TOP__rst_n__0 = vlSelfRef.rst_n;
}

VL_ATTR_COLD void Vsynth___024root___eval_initial(Vsynth___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth___024root___eval_initial\n"); );
    Vsynth__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vsynth___024root___eval_final(Vsynth___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth___024root___eval_final\n"); );
    Vsynth__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vsynth___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vsynth___024root___eval_phase__stl(Vsynth___024root* vlSelf);

VL_ATTR_COLD void Vsynth___024root___eval_settle(Vsynth___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth___024root___eval_settle\n"); );
    Vsynth__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vsynth___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("../src/../src/synth.v", 11, "", "DIDNOTCONVERGE: Settle region did not converge after '--converge-limit' of 100 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        vlSelfRef.__VstlPhaseResult = Vsynth___024root___eval_phase__stl(vlSelf);
        vlSelfRef.__VstlFirstIteration = 0U;
    } while (vlSelfRef.__VstlPhaseResult);
}

VL_ATTR_COLD void Vsynth___024root___eval_triggers_vec__stl(Vsynth___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth___024root___eval_triggers_vec__stl\n"); );
    Vsynth__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered[0U]) 
                                     | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
}

VL_ATTR_COLD bool Vsynth___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vsynth___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vsynth___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vsynth___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth___024root___trigger_anySet__stl\n"); );
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

VL_ATTR_COLD void Vsynth___024root___stl_sequent__TOP__0(Vsynth___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth___024root___stl_sequent__TOP__0\n"); );
    Vsynth__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*5:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    // Body
    __Vtableidx1 = vlSelfRef.midi_note;
    vlSelfRef.synth__DOT__phase_inc = Vsynth__ConstPool__TABLE_h115da5b7_0
        [__Vtableidx1];
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

VL_ATTR_COLD void Vsynth___024root____Vm_traceActivitySetAll(Vsynth___024root* vlSelf);

VL_ATTR_COLD void Vsynth___024root___eval_stl(Vsynth___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth___024root___eval_stl\n"); );
    Vsynth__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        Vsynth___024root___stl_sequent__TOP__0(vlSelf);
        Vsynth___024root____Vm_traceActivitySetAll(vlSelf);
    }
}

VL_ATTR_COLD bool Vsynth___024root___eval_phase__stl(Vsynth___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth___024root___eval_phase__stl\n"); );
    Vsynth__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vsynth___024root___eval_triggers_vec__stl(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vsynth___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
    __VstlExecute = Vsynth___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vsynth___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vsynth___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vsynth___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth___024root___dump_triggers__ico\n"); );
    // Body
    if ((1U & (~ (IData)(Vsynth___024root___trigger_anySet__ico(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

bool Vsynth___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vsynth___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vsynth___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @(negedge rst_n)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vsynth___024root____Vm_traceActivitySetAll(Vsynth___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth___024root____Vm_traceActivitySetAll\n"); );
    Vsynth__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vm_traceActivity[0U] = 1U;
    vlSelfRef.__Vm_traceActivity[1U] = 1U;
}

VL_ATTR_COLD void Vsynth___024root___ctor_var_reset(Vsynth___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth___024root___ctor_var_reset\n"); );
    Vsynth__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1638864771569018232ull);
    vlSelf->midi_note = VL_SCOPED_RAND_RESET_I(6, __VscopeHash, 1308894613039277079ull);
    vlSelf->gate = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14356587578699126677ull);
    vlSelf->audio_sample = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 10698702479527509892ull);
    vlSelf->audio_out = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16887251779955964156ull);
    vlSelf->synth__DOT__sample_div = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 5550646187497156449ull);
    vlSelf->synth__DOT__phase = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 11193736527105487326ull);
    vlSelf->synth__DOT__phase_inc = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 13867038243694372412ull);
    vlSelf->synth__DOT__env = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 10228608523941481838ull);
    vlSelf->synth__DOT__gate_prev = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9174394937080136404ull);
    vlSelf->synth__DOT__sd_accum = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 13797916856861025664ull);
    vlSelf->synth__DOT__sd_next = VL_SCOPED_RAND_RESET_I(17, __VscopeHash, 11200170837985318359ull);
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VicoTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__rst_n__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}
