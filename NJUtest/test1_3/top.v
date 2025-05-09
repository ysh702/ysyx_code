module top(F, Y, X0, X1, X2, X3);
	output reg F;
	input [1:0] Y;
	input X0, X1, X2, X3;
	always@(*)
		case(Y)
			2'b00:F = X0;
			2'b01:F = X1;
			2'b10:F = X2;
			2'b11:F = X3;
			default: F = 1'b00;
		endcase
endmodule
