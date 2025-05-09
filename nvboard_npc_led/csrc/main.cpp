#include <nvboard.h>
#include <Vtop.h>
 
static TOP_NAME dut;//dut模块实例化，通过这个驱动输入信号和读取输出信号
 
void nvboard_bind_all_pins(TOP_NAME* top);//绑定引脚
 
static void single_cycle() {//模拟时钟周期
  dut.clk = 0; dut.eval();//下降沿时，计算组合逻辑和时序逻辑的更新
  dut.clk = 1; dut.eval();//上升沿
}
 
static void reset(int n) {//复位
  dut.rst = 1;//激活模块的复位信号
  while (n -- > 0) single_cycle();//持续n个周期
  dut.rst = 0;//解除复位
}
 
int main() {
  nvboard_bind_all_pins(&dut);//&dut指的就是实例化的模块，绑定引脚
  nvboard_init();//初始化nvboard
 
  reset(10);//复位10个周期
 
  while(1) {
    nvboard_update();//读取nvboard的输入（按钮、开关）并更新到实例化模块dut的输入端口
    single_cycle();//运行一个周期
  }
}
