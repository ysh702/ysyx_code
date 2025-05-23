#include "verilated.h"
#include "verilated_vcd_c.h"
#include "obj_dir/Vtop.h"

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

	top -> a = 0b0; top-> b=0b0; top-> ci=0b0; step_and_dump_wave();
		top->b=0b0; top->ci=0b1; step_and_dump_wave();
		top->b=0b1; top->ci=0b0; step_and_dump_wave();
		top->b=0b1; top->ci=0b1; step_and_dump_wave();
	top->a=0b1; top-> b=0b0; top-> ci=0b0; step_and_dump_wave();
                top->b=0b0; top->ci=0b1; step_and_dump_wave();
                top->b=0b1; top->ci=0b0; step_and_dump_wave();
                top->b=0b1; top->ci=0b1; step_and_dump_wave();
	sim_exit();
}
