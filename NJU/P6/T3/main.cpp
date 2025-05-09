#include "verilated.h"
#include "verilated_vcd_c.h"
#include "obj_dir/Vtop.h"
#include <stdio.h>

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

void clock_cycle() {
    top->clk = 0; step_and_dump_wave();
    top->clk = 1; step_and_dump_wave(); // 上升沿触发
}

int main() {
    sim_init();

    // 初始化输入
    top->clk = 0;
    top->load = 0;
    top->in = 0;
    step_and_dump_wave();

    // 测试1: 加载初始值
    top->in = 0x123456789ABCDEF0;
    top->load = 1;
    clock_cycle(); // 加载后state=in, out=in
    top->load = 0;

    // 测试2: 运行LFSR 10个周期并打印输出
    for (int i = 0; i < 10; i++) {
        clock_cycle(); 
        printf("Cycle %2d: out = 0x%016lX\n", i, top->out);
    }

    sim_exit();
}
