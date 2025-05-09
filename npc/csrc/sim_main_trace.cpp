#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Vtop.h" 
#include "verilated.h"
#include "verilated_vcd_c.h" 

int main(int argc, char** argv) {
    VerilatedContext* contextp = new VerilatedContext;
    contextp->commandArgs(argc, argv);
    Vtop* top = new Vtop{contextp};

    // 初始化波形记录
    VerilatedVcdC* tfp = new VerilatedVcdC;//生成一个波形文件对象
    contextp->traceEverOn(true);  // contextp启用追踪功能
    top->trace(tfp, 0);          // top和tfp绑定，绑定追踪层级（0 表示所有信号）
    tfp->open("wave.vcd");       // tfp指定波形文件名（VCD格式）
 
    while (!contextp->gotFinish()) {
        int a = rand() & 1;//随机生成0或1
        int b = rand() & 1;
        top->a = a;//驱动top的输入端口a
        top->b = b;
        top->eval();//执行top模块的逻辑计算
        printf("a = %d, b = %d, f = %d\n", a, b, top->f); // 打印结果
        assert(top->f == (a ^ b)); // 检查输出是否正确
 
        // 记录当前时间点的波形
        tfp->dump(contextp->time());//dump保存当前信号状态到VCD文件
        contextp->timeInc(1);    // 推动仿真时间
    }
 
    tfp->close();  // 关闭波形文件
    delete top;
    delete contextp;
    return 0;
}
