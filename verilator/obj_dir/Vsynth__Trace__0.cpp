// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals

#include "verilated_vcd_c.h"
#include "Vsynth__Syms.h"


void Vsynth___024root__trace_chg_0_sub_0(Vsynth___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vsynth___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth___024root__trace_chg_0\n"); );
    // Body
    Vsynth___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vsynth___024root*>(voidSelf);
    Vsynth__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    Vsynth___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vsynth___024root__trace_chg_0_sub_0(Vsynth___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth___024root__trace_chg_0_sub_0\n"); );
    Vsynth__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 0);
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[1U]))) {
        bufp->chgCData(oldp+0,(vlSelfRef.synth__DOT__sample_div),2);
        bufp->chgBit(oldp+1,((3U == (IData)(vlSelfRef.synth__DOT__sample_div))));
        bufp->chgSData(oldp+2,(vlSelfRef.synth__DOT__phase),16);
        bufp->chgSData(oldp+3,((0x0000ffffU & ((0x00008000U 
                                                & (IData)(vlSelfRef.synth__DOT__phase))
                                                ? (~ (IData)(vlSelfRef.synth__DOT__phase))
                                                : (IData)(vlSelfRef.synth__DOT__phase)))),16);
        bufp->chgSData(oldp+4,(vlSelfRef.synth__DOT__env),16);
        bufp->chgBit(oldp+5,(vlSelfRef.synth__DOT__gate_prev));
        bufp->chgIData(oldp+6,(((0x0000ffffU & ((0x00008000U 
                                                 & (IData)(vlSelfRef.synth__DOT__phase))
                                                 ? 
                                                (~ (IData)(vlSelfRef.synth__DOT__phase))
                                                 : (IData)(vlSelfRef.synth__DOT__phase))) 
                                * (IData)(vlSelfRef.synth__DOT__env))),32);
        bufp->chgSData(oldp+7,(vlSelfRef.synth__DOT__sd_accum),16);
        bufp->chgIData(oldp+8,(vlSelfRef.synth__DOT__sd_next),17);
    }
    bufp->chgBit(oldp+9,(vlSelfRef.clk));
    bufp->chgBit(oldp+10,(vlSelfRef.rst_n));
    bufp->chgCData(oldp+11,(vlSelfRef.midi_note),6);
    bufp->chgBit(oldp+12,(vlSelfRef.gate));
    bufp->chgSData(oldp+13,(vlSelfRef.audio_sample),16);
    bufp->chgBit(oldp+14,(vlSelfRef.audio_out));
    bufp->chgSData(oldp+15,(vlSelfRef.synth__DOT__phase_inc),16);
}

void Vsynth___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth___024root__trace_cleanup\n"); );
    // Body
    Vsynth___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vsynth___024root*>(voidSelf);
    Vsynth__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
}
