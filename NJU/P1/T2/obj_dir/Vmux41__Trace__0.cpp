// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vmux41__Syms.h"


void Vmux41___024root__trace_chg_sub_0(Vmux41___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vmux41___024root__trace_chg_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmux41___024root__trace_chg_top_0\n"); );
    // Init
    Vmux41___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vmux41___024root*>(voidSelf);
    Vmux41__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    Vmux41___024root__trace_chg_sub_0((&vlSymsp->TOP), bufp);
}

void Vmux41___024root__trace_chg_sub_0(Vmux41___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vmux41__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmux41___024root__trace_chg_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[0U])) {
        bufp->chgCData(oldp+0,(vlSelf->mux41__DOT__i0__DOT__i0__DOT__key_list[0]),2);
        bufp->chgCData(oldp+1,(vlSelf->mux41__DOT__i0__DOT__i0__DOT__key_list[1]),2);
        bufp->chgCData(oldp+2,(vlSelf->mux41__DOT__i0__DOT__i0__DOT__key_list[2]),2);
        bufp->chgCData(oldp+3,(vlSelf->mux41__DOT__i0__DOT__i0__DOT__key_list[3]),2);
    }
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[1U])) {
        bufp->chgCData(oldp+4,(vlSelf->mux41__DOT__i0__DOT__i0__DOT__pair_list[0]),3);
        bufp->chgCData(oldp+5,(vlSelf->mux41__DOT__i0__DOT__i0__DOT__pair_list[1]),3);
        bufp->chgCData(oldp+6,(vlSelf->mux41__DOT__i0__DOT__i0__DOT__pair_list[2]),3);
        bufp->chgCData(oldp+7,(vlSelf->mux41__DOT__i0__DOT__i0__DOT__pair_list[3]),3);
        bufp->chgBit(oldp+8,(vlSelf->mux41__DOT__i0__DOT__i0__DOT__data_list[0]));
        bufp->chgBit(oldp+9,(vlSelf->mux41__DOT__i0__DOT__i0__DOT__data_list[1]));
        bufp->chgBit(oldp+10,(vlSelf->mux41__DOT__i0__DOT__i0__DOT__data_list[2]));
        bufp->chgBit(oldp+11,(vlSelf->mux41__DOT__i0__DOT__i0__DOT__data_list[3]));
        bufp->chgBit(oldp+12,(vlSelf->mux41__DOT__i0__DOT__i0__DOT__lut_out));
        bufp->chgBit(oldp+13,(vlSelf->mux41__DOT__i0__DOT__i0__DOT__hit));
    }
    bufp->chgCData(oldp+14,(vlSelf->a),4);
    bufp->chgCData(oldp+15,(vlSelf->s),2);
    bufp->chgBit(oldp+16,(vlSelf->y));
    bufp->chgSData(oldp+17,((0xa6U | ((0x200U & ((IData)(vlSelf->a) 
                                                 << 9U)) 
                                      | ((0x40U & ((IData)(vlSelf->a) 
                                                   << 5U)) 
                                         | ((8U & ((IData)(vlSelf->a) 
                                                   << 1U)) 
                                            | (1U & 
                                               ((IData)(vlSelf->a) 
                                                >> 3U))))))),12);
}

void Vmux41___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmux41___024root__trace_cleanup\n"); );
    // Init
    Vmux41___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vmux41___024root*>(voidSelf);
    Vmux41__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
}
