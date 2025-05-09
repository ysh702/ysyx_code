module top(
	input [3:0] A,
	input [3:0] B,
	input [2:0] ALUctr,//ALU控制端
	output reg [3:0] F,   // 输出四位补码结果
    	output reg cf,    // 进位位
    	output reg zero,  // 零标志
    	output reg of     // 溢出位
);
wire [3:0] sum;
wire [3:0] diff;
wire add_cf;//加法进位
wire add_of;//加法溢出
wire sub_cf;//减法进位
wire sub_of;//减法溢出

//+
assign {add_cf,sum} = A+B;
assign add_of=(A[3] == B[3])&&(sum[3] != A[3]);
//-
assign {sub_cf,diff}=A-B;
assign sub_of = (A[3] != B[3])&&(diff[3] != A[3]);

always@(*)begin
	case(ALUctr)
		3'b000:begin
			F=sum;
			cf=add_cf;
			of=add_of;
		end
		3'b001:begin
			F=diff;
			cf=sub_cf;
			of=sub_of;
		end
		3'b010:begin
			F=~A;
			cf=0;
			of=0;
		end
		3'b011:begin
			F=A&B;
			cf=0;
			of=0;
		end
		3'b100:begin
			F=A|B;
			cf=0;
			of=0;
		end
		3'b101:begin
			F=A^B;
			cf=0;
			of=0;
		end
		3'b110:begin
			if($signed(A)>$signed(B))
				F=4'b0001;
			else
				F=4'b0000;
			cf=0;
			of=0;
		end
		3'b111:begin
			if(A==B)
				F=4'b0001;
			else
				F=4'b0000;
			cf=0;
			of=0;
		end
		default:begin
			F=4'b0000;
			cf=0;
			of=0;
		end
	endcase

	zero=(F==4'b0000)? 1:0;
end
endmodule
