#include "verilated.h"
#include "verilated_vcd_c.h"
#include "obj_dir/Vtop.h"

VerilatedContext* contextp = NULL;
VerilatedVcdC* tfp = NULL;
static Vtop* top;

void step_and_dump_wave() {
    top->eval();
    contextp->timeInc(1);
    tfp->dump(contextp->time());
}

void sim_init() {
    contextp = new VerilatedContext;
    tfp = new VerilatedVcdC;
    top = new Vtop;
    contextp->traceEverOn(true);
    top->trace(tfp, 0);
    tfp->open("dump.vcd");
}

void sim_exit() {
    step_and_dump_wave();
    tfp->close();
}

int main() {
    sim_init();

    // Initialize inputs
    top->clk = 0;
    top->a = 0;
    top->count = 0;
    top->lin = 0;

    // Test case 1: Reset behavior (count=0)
    top->count = 0b000;
    for (int i = 0; i < 2; i++) {
        top->clk = !top->clk;
        step_and_dump_wave();
    }

    // Test case 2: Load input a (count=1)
    top->a = 0b10101010;
    top->count = 0b001;
    for (int i = 0; i < 2; i++) {
        top->clk = !top->clk;
        step_and_dump_wave();
    }

    // Test case 3: Right shift (count=2)
    top->count = 0b010;
    for (int i = 0; i < 4; i++) {
        top->clk = !top->clk;
        step_and_dump_wave();
    }

    // Test case 4: Left shift (count=3)
    top->count = 0b011;
    for (int i = 0; i < 4; i++) {
        top->clk = !top->clk;
        step_and_dump_wave();
    }

    // Test case 5: Arithmetic right shift (count=4)
    top->count = 0b100;
    for (int i = 0; i < 4; i++) {
        top->clk = !top->clk;
        step_and_dump_wave();
    }

    // Test case 6: Logical right shift with lin (count=5)
    top->count = 0b101;
    top->lin = 1;
    for (int i = 0; i < 4; i++) {
        top->clk = !top->clk;
        step_and_dump_wave();
    }

    // Test case 7: Rotate right (count=6)
    top->count = 0b110;
    for (int i = 0; i < 8; i++) {
        top->clk = !top->clk;
        step_and_dump_wave();
    }

    // Test case 8: Rotate left (count=7)
    top->count = 0b111;
    for (int i = 0; i < 8; i++) {
        top->clk = !top->clk;
        step_and_dump_wave();
    }

    sim_exit();
}
