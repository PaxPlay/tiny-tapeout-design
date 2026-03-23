// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals

#include "verilated_vcd_c.h"
#include "Vsynth__Syms.h"


VL_ATTR_COLD void Vsynth___024root__trace_init_sub__TOP__0(Vsynth___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth___024root__trace_init_sub__TOP__0\n"); );
    Vsynth__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const int c = vlSymsp->__Vm_baseCode;
    tracep->pushPrefix("$rootio", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+9,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+10,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+11,0,"midi_note",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBit(c+12,0,"gate",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+13,0,"audio_sample",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBit(c+14,0,"audio_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->pushPrefix("synth", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+9,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+10,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+11,0,"midi_note",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 5,0);
    tracep->declBit(c+12,0,"gate",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+13,0,"audio_sample",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBit(c+14,0,"audio_out",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+0,0,"sample_div",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+1,0,"sample_tick",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+2,0,"phase",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+15,0,"phase_inc",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+3,0,"tri_wave",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+4,0,"env",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBit(c+5,0,"gate_prev",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+6,0,"tri_env",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+7,0,"sd_accum",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+8,0,"sd_next",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 16,0);
    tracep->popPrefix();
}

VL_ATTR_COLD void Vsynth___024root__trace_init_top(Vsynth___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth___024root__trace_init_top\n"); );
    Vsynth__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vsynth___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vsynth___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
VL_ATTR_COLD void Vsynth___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vsynth___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vsynth___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/);

VL_ATTR_COLD void Vsynth___024root__trace_register(Vsynth___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth___024root__trace_register\n"); );
    Vsynth__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    tracep->addConstCb(&Vsynth___024root__trace_const_0, 0, vlSelf);
    tracep->addFullCb(&Vsynth___024root__trace_full_0, 0, vlSelf);
    tracep->addChgCb(&Vsynth___024root__trace_chg_0, 0, vlSelf);
    tracep->addCleanupCb(&Vsynth___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vsynth___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth___024root__trace_const_0\n"); );
    // Body
    Vsynth___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vsynth___024root*>(voidSelf);
    Vsynth__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
}

VL_ATTR_COLD void Vsynth___024root__trace_full_0_sub_0(Vsynth___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vsynth___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth___024root__trace_full_0\n"); );
    // Body
    Vsynth___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vsynth___024root*>(voidSelf);
    Vsynth__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    Vsynth___024root__trace_full_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vsynth___024root__trace_full_0_sub_0(Vsynth___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsynth___024root__trace_full_0_sub_0\n"); );
    Vsynth__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    bufp->fullCData(oldp+0,(vlSelfRef.synth__DOT__sample_div),2);
    bufp->fullBit(oldp+1,((3U == (IData)(vlSelfRef.synth__DOT__sample_div))));
    bufp->fullSData(oldp+2,(vlSelfRef.synth__DOT__phase),16);
    bufp->fullSData(oldp+3,((0x0000ffffU & ((0x00008000U 
                                             & (IData)(vlSelfRef.synth__DOT__phase))
                                             ? (~ (IData)(vlSelfRef.synth__DOT__phase))
                                             : (IData)(vlSelfRef.synth__DOT__phase)))),16);
    bufp->fullSData(oldp+4,(vlSelfRef.synth__DOT__env),16);
    bufp->fullBit(oldp+5,(vlSelfRef.synth__DOT__gate_prev));
    bufp->fullIData(oldp+6,(((0x0000ffffU & ((0x00008000U 
                                              & (IData)(vlSelfRef.synth__DOT__phase))
                                              ? (~ (IData)(vlSelfRef.synth__DOT__phase))
                                              : (IData)(vlSelfRef.synth__DOT__phase))) 
                             * (IData)(vlSelfRef.synth__DOT__env))),32);
    bufp->fullSData(oldp+7,(vlSelfRef.synth__DOT__sd_accum),16);
    bufp->fullIData(oldp+8,(vlSelfRef.synth__DOT__sd_next),17);
    bufp->fullBit(oldp+9,(vlSelfRef.clk));
    bufp->fullBit(oldp+10,(vlSelfRef.rst_n));
    bufp->fullCData(oldp+11,(vlSelfRef.midi_note),6);
    bufp->fullBit(oldp+12,(vlSelfRef.gate));
    bufp->fullSData(oldp+13,(vlSelfRef.audio_sample),16);
    bufp->fullBit(oldp+14,(vlSelfRef.audio_out));
    bufp->fullSData(oldp+15,(vlSelfRef.synth__DOT__phase_inc),16);
}
