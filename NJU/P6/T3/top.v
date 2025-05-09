module top(
	input [63:0] in,
	input clk,
	input load,
	output reg [63:0] out
);
	reg [63:0] state;
	always@(posedge clk)begin
		if(load)begin
			state <= in;
		end else begin
			state <= {state[62:0], state[4]^state[3]^state[2]^state[0]};
		end
		out <= state;
	end
	endmodule
