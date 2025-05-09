module top(
	input clk,
	input rst,
	output [15:0] ledr
);
	reg [31:0] count;
	reg [15:0] led;

	always@(posedge clk or posedge rst)begin
		if(rst)begin
			count <= 32'b0;
			led <= 16'b0000000000000001;
		end else if(count >= 5000000)begin
			count <= 32'b0;
			led <= {led[14:0],led[15]};
		end else begin
			count <= count + 1;
		end
	end
	assign ledr = led;
endmodule
