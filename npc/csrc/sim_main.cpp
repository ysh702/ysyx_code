#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Vtop.h" // 包含 Verilator 生成的头文件
#include "verilated.h"
 
int main(int argc, char** argv) {
    VerilatedContext* contextp = new VerilatedContext;
    contextp->commandArgs(argc, argv);
    Vtop* top = new Vtop{contextp}; // 实例化顶层模块
 
    while (!contextp->gotFinish()) { // 仿真循环
        int a = rand() & 1; // 随机生成 a 信号
        int b = rand() & 1; // 随机生成 b 信号
        top->a = a; // 驱动输入端口 a
        top->b = b; // 驱动输入端口 b
        top->eval(); // 更新电路状态
        printf("a = %d, b = %d, f = %d\n", a, b, top->f); // 打印结果
        assert(top->f == (a ^ b)); // 检查输出是否正确
    }
 
    delete top;
    delete contextp;
    return 0;
}
