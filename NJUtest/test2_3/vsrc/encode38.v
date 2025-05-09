module encode38(x, en, y, indicate);
	input [7:0] x;
	input en;
	output reg [2:0] y;
	output reg indicate;

	integer i;
	always @(x or en) begin
		if (en) begin
			y = 0;
			if (x != 0) indicate <= 1'b1;
			else indicate <= 1'b0;
			for ( i = 0; i <=7; i = i+1)
				if(x[i] == 1) y = i[2:0];
		end
		else y = 0;
	end
endmodule

