module top(
	input a,
	input b,
	input ci,
	output so,
	output co
);
	assign so = a ^ b ^ ci;
	assign co = (a&b) | (ci & (a ^ b));
endmodule



//1位全加器
