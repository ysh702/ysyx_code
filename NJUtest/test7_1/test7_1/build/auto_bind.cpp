#include <nvboard.h>
#include "Vtop.h"

void nvboard_bind_all_pins(Vtop* top) {
	nvboard_bind_pin( &top->clk, 1, BTNC);
	nvboard_bind_pin( &top->out, 4, LD7, LD6, LD5, LD4);
	nvboard_bind_pin( &top->in, 1, SW1);
	nvboard_bind_pin( &top->out, 1, LD0);
}
