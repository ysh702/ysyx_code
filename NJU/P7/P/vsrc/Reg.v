module Reg #(WIDTH = 1, RESET_VAL=0)(
	input clk,
	input rst,
	input [WIDTH-1:0] data_in,
	output reg [WIDTH-1:0] data_out,
	input wen
);
always@(posedge clk)begin
	if(rst)
		data_out <= RESET_VAL;
	else if(wen)
		data_out <= data_in;
end
endmodule
