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

    // Test case 1: Left shift (lr=1)
    top->lr = 1;    // 左移模式
    top->al = 0;    // 无关项
    top->in = 0x0000000F;  // 输入数据
    top->shift = 4; // 移位量
    step_and_dump_wave();  // 输出应为 0x000000F0

    // Test case 2: Logical right shift (lr=0, al=0)
    top->lr = 0;    // 右移模式
    top->al = 0;    // 逻辑右移
    top->in = 0xF0000000;
    top->shift = 4;
    step_and_dump_wave();  // 输出应为 0x0F000000

    // Test case 3: Arithmetic right shift (lr=0, al=1)
    top->lr = 0;
    top->al = 1;    // 算术右移
    top->in = 0xF0000000; // 负数（最高位为1）
    top->shift = 4;
    step_and_dump_wave();  // 输出应为 0xFF000000（符号位扩展）

    // Test case 4: Edge case - zero shift
    top->lr = 1;
    top->shift = 0; // 不移位
    top->in = 0x12345678;
    step_and_dump_wave();  // 输出应为 0x12345678（原样输出）

    // Test case 5: Maximum shift (31 bits)
    top->lr = 0;
    top->al = 0;
    top->in = 0x80000000;
    top->shift = 31;
    step_and_dump_wave();  // 逻辑右移结果应为 0x00000001

    sim_exit();
}
