// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vsynth__pch.h"
#include "verilated_vcd_c.h"

//============================================================
// Constructors

Vsynth::Vsynth(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vsynth__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , rst_n{vlSymsp->TOP.rst_n}
    , midi_note{vlSymsp->TOP.midi_note}
    , gate{vlSymsp->TOP.gate}
    , audio_out{vlSymsp->TOP.audio_out}
    , audio_sample{vlSymsp->TOP.audio_sample}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
    contextp()->traceBaseModelCbAdd(
        [this](VerilatedTraceBaseC* tfp, int levels, int options) { traceBaseModel(tfp, levels, options); });
}

Vsynth::Vsynth(const char* _vcname__)
    : Vsynth(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vsynth::~Vsynth() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vsynth___024root___eval_debug_assertions(Vsynth___024root* vlSelf);
#endif  // VL_DEBUG
void Vsynth___024root___eval_static(Vsynth___024root* vlSelf);
void Vsynth___024root___eval_initial(Vsynth___024root* vlSelf);
void Vsynth___024root___eval_settle(Vsynth___024root* vlSelf);
void Vsynth___024root___eval(Vsynth___024root* vlSelf);

void Vsynth::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vsynth::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vsynth___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_activity = true;
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vsynth___024root___eval_static(&(vlSymsp->TOP));
        Vsynth___024root___eval_initial(&(vlSymsp->TOP));
        Vsynth___024root___eval_settle(&(vlSymsp->TOP));
        vlSymsp->__Vm_didInit = true;
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vsynth___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vsynth::eventsPending() { return false; }

uint64_t Vsynth::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vsynth::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vsynth___024root___eval_final(Vsynth___024root* vlSelf);

VL_ATTR_COLD void Vsynth::final() {
    Vsynth___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vsynth::hierName() const { return vlSymsp->name(); }
const char* Vsynth::modelName() const { return "Vsynth"; }
unsigned Vsynth::threads() const { return 1; }
void Vsynth::prepareClone() const { contextp()->prepareClone(); }
void Vsynth::atClone() const {
    contextp()->threadPoolpOnClone();
}
std::unique_ptr<VerilatedTraceConfig> Vsynth::traceConfig() const {
    return std::unique_ptr<VerilatedTraceConfig>{new VerilatedTraceConfig{false, false, false}};
};

//============================================================
// Trace configuration

void Vsynth___024root__trace_decl_types(VerilatedVcd* tracep);

void Vsynth___024root__trace_init_top(Vsynth___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD static void trace_init(void* voidSelf, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vsynth___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vsynth___024root*>(voidSelf);
    Vsynth__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->pushPrefix(vlSymsp->name(), VerilatedTracePrefixType::SCOPE_MODULE);
    Vsynth___024root__trace_decl_types(tracep);
    Vsynth___024root__trace_init_top(vlSelf, tracep);
    tracep->popPrefix();
}

VL_ATTR_COLD void Vsynth___024root__trace_register(Vsynth___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD void Vsynth::traceBaseModel(VerilatedTraceBaseC* tfp, int levels, int options) {
    (void)levels; (void)options;
    VerilatedVcdC* const stfp = dynamic_cast<VerilatedVcdC*>(tfp);
    if (VL_UNLIKELY(!stfp)) {
        vl_fatal(__FILE__, __LINE__, __FILE__,"'Vsynth::trace()' called on non-VerilatedVcdC object;"
            " use --trace-fst with VerilatedFst object, and --trace-vcd with VerilatedVcd object");
    }
    stfp->spTrace()->addModel(this);
    stfp->spTrace()->addInitCb(&trace_init, &(vlSymsp->TOP), name(), false, 16);
    Vsynth___024root__trace_register(&(vlSymsp->TOP), stfp->spTrace());
}
