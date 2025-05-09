#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vtop.h"

VerilatedContext* contextp = NULL;
VerilatedVcdC* tfp = NULL;

static Vtop* top;

void step_and_dump_wave(){
  top->eval();
  contextp->timeInc(1);
  tfp->dump(contextp->time());
}
void sim_init(){
  contextp = new VerilatedContext;
  tfp = new VerilatedVcdC;
  top = new Vtop;
  contextp->traceEverOn(true);
  top->trace(tfp, 0);
  tfp->open("dump.vcd");
}

void sim_exit(){
  step_and_dump_wave();
  tfp->close();
}

int main(){
	sim_init();
	int i,j;
	top->Y = 00;
	top->X0 = 0;
	top->X1 = 0;
	top->X2 = 0;
	top->X3 = 0; //对各个输入信号初始化
	for(j=0;j<=4;j++){
		for(i=0;i<=16;i++){
			step_and_dump_wave();
			top->X0 = !top->X0;
			if (i%2==1)
				top->X1 = !top->X1;
			if (i%4==3)
				top->X2 = !top->X2;
			if (i%8==7)
				top->X3 = !top->X3;
			printf("Y=%x,X3X2X1X0=%d%d%d%d,F=%x\n",top->Y,top->X3,top->X2,top->X1,top->X0,top->F);
}
	top->Y += 0b01;
	}
	sim_exit();
}
