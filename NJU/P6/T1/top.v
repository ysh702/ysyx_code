module top(
	input [7:0] a,
	input clk,
	input [2:0] count,
	input lin,
	output reg [7:0] dout
);
always@(posedge clk)begin
	case(count)
		3'b000:dout<=8'b00000000;//清0
		3'b001:dout<=a;//放置输入
		3'b010:dout<=dout>>1;//逻辑右移
		3'b011:dout<=dout<<1;//逻辑左移
		3'b100:dout<={dout[7],dout[7:1]};//算术右移
		3'b101:dout<={lin,dout[7:1]};//左端串行输入1位
		3'b110:dout<={dout[0],dout[7:1]};//循环右移
		3'b111:dout<={dout[6:0],dout[7]};//循环左移
		default:dout<=dout;
	endcase
end
endmodule
