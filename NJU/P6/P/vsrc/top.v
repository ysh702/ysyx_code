module top(
	input clk,
	input reset,
	input load,
	input [7:0] in,
	output reg [6:0] hex0,
	output reg [6:0] hex1
);
	reg [7:0] lfsr;
	wire feedback;

	assign feedback = lfsr[4]^lfsr[3]^lfsr[2]^lfsr[0];

	always@(posedge clk or posedge reset)begin
		if(reset)begin
			lfsr <= 8'b0000_0001;
		end else if(load)begin
			lfsr <= (in == 0)?8'b0000_0001:in;
		end else begin
			lfsr <= {feedback,lfsr[7:1]};
		end
	end
always@(*)begin
	case(lfsr[3:0])
		4'h0: hex0 = 7'b1000000; // 0
		4'h1: hex0 = 7'b1111001;
		4'h2: hex0 = 7'b0100100; // 2
        	4'h3: hex0 = 7'b0110000; // 3
        	4'h4: hex0 = 7'b0011001; // 4
        	4'h5: hex0 = 7'b0010010; // 5
        	4'h6: hex0 = 7'b0000010; // 6
        	4'h7: hex0 = 7'b1111000; // 7
        	4'h8: hex0 = 7'b0000000; // 8
        	4'h9: hex0 = 7'b0010000; // 9
        	4'hA: hex0 = 7'b0001000; // A
        	4'hB: hex0 = 7'b0000011; // B
        	4'hC: hex0 = 7'b1000110; // C
        	4'hD: hex0 = 7'b0100001; // D
        	4'hE: hex0 = 7'b0000110; // E
        	4'hF: hex0 = 7'b0001110; // F
	endcase

	case(lfsr[7:4])
		4'h0: hex1 = 7'b1000000; // 0
        	4'h1: hex1 = 7'b1111001; // 1
        	4'h2: hex1 = 7'b0100100; // 2
        	4'h3: hex1 = 7'b0110000; // 3
        	4'h4: hex1 = 7'b0011001; // 4
        	4'h5: hex1 = 7'b0010010; // 5
       	 	4'h6: hex1 = 7'b0000010; // 6
        	4'h7: hex1 = 7'b1111000; // 7
        	4'h8: hex1 = 7'b0000000; // 8
        	4'h9: hex1 = 7'b0010000; // 9
        	4'hA: hex1 = 7'b0001000; // A
        	4'hB: hex1 = 7'b0000011; // B
        	4'hC: hex1 = 7'b1000110; // C
        	4'hD: hex1 = 7'b0100001; // D
        	4'hE: hex1 = 7'b0000110; // E
        	4'hF: hex1 = 7'b0001110; // F
	endcase
end
endmodule


				
