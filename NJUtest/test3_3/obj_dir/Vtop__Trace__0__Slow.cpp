// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


VL_ATTR_COLD void Vtop___024root__trace_init_sub__TOP__0(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_init_sub__TOP__0\n"); );
    // Init
    const int c = vlSymsp->__Vm_baseCode;
    // Body
    tracep->declBus(c+4,"command_input", false,-1, 2,0);
    tracep->declBus(c+5,"a_input", false,-1, 3,0);
    tracep->declBus(c+6,"b_input", false,-1, 3,0);
    tracep->declBus(c+7,"clk", false,-1, 0,0);
    tracep->declBus(c+8,"ans", false,-1, 3,0);
    tracep->declBus(c+9,"overflow_flag", false,-1, 0,0);
    tracep->pushNamePrefix("top ");
    tracep->declBus(c+4,"command_input", false,-1, 2,0);
    tracep->declBus(c+5,"a_input", false,-1, 3,0);
    tracep->declBus(c+6,"b_input", false,-1, 3,0);
    tracep->declBus(c+7,"clk", false,-1, 0,0);
    tracep->declBus(c+8,"ans", false,-1, 3,0);
    tracep->declBus(c+9,"overflow_flag", false,-1, 0,0);
    tracep->declBus(c+1,"temp_ans", false,-1, 3,0);
    tracep->declBus(c+2,"temp_overflow_flag", false,-1, 0,0);
    tracep->declBus(c+4,"command", false,-1, 2,0);
    tracep->declBus(c+5,"a", false,-1, 3,0);
    tracep->declBus(c+3,"b", false,-1, 3,0);
    tracep->popNamePrefix(1);
}

VL_ATTR_COLD void Vtop___024root__trace_init_top(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_init_top\n"); );
    // Body
    Vtop___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vtop___024root__trace_full_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vtop___024root__trace_chg_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vtop___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/);

VL_ATTR_COLD void Vtop___024root__trace_register(Vtop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_register\n"); );
    // Body
    tracep->addFullCb(&Vtop___024root__trace_full_top_0, vlSelf);
    tracep->addChgCb(&Vtop___024root__trace_chg_top_0, vlSelf);
    tracep->addCleanupCb(&Vtop___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vtop___024root__trace_full_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vtop___024root__trace_full_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_full_top_0\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    Vtop___024root__trace_full_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vtop___024root__trace_full_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_full_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullCData(oldp+1,(vlSelf->top__DOT__temp_ans),4);
    bufp->fullBit(oldp+2,(vlSelf->top__DOT__temp_overflow_flag));
    bufp->fullCData(oldp+3,(vlSelf->top__DOT__b),4);
    bufp->fullCData(oldp+4,(vlSelf->command_input),3);
    bufp->fullCData(oldp+5,(vlSelf->a_input),4);
    bufp->fullCData(oldp+6,(vlSelf->b_input),4);
    bufp->fullBit(oldp+7,(vlSelf->clk));
    bufp->fullCData(oldp+8,(vlSelf->ans),4);
    bufp->fullBit(oldp+9,(vlSelf->overflow_flag));
}
