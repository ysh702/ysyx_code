module top(
	input [31:0] in,
	input [4:0] shift,
	input lr,
	input al,
	output reg [31:0] out
);
always@(*)begin
	if(lr)begin
		out=in<<shift;
	end else begin
		if(al)begin
			out = $signed(in)>>>shift;
		end else begin
			out = in >>shift;
		end
	end
end
endmodule
