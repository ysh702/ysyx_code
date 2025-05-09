#include <nvboard.h>
#include "Vtop.h"

void nvboard_bind_all_pins(Vtop* top) {
	nvboard_bind_pin( &top->sw, 8, SW7, SW6, SW5, SW4, SW3, SW2, SW1, SW0);
	nvboard_bind_pin( &top->en, 1, SW9);
	nvboard_bind_pin( &top->led_out, 3, LD2, LD1, LD0);
	nvboard_bind_pin( &top->indicate, 1, LD4);
	nvboard_bind_pin( &top->seg_out, 7, SEG0A, SEG0B, SEG0C, SEG0D, SEG0E, SEG0F, SEG0G);
}
