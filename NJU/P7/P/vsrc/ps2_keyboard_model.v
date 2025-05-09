module ps2_keyboard(clk,clrn,ps2_clk,ps2_data,data,ready,nextdata_n,overflow,key_count,shift_key_count,ctrl_key_count,shift_flag,ctrl_flag,CapsLock_key_count,CapsLock_flag);
input clk,clrn,ps2_clk,ps2_data;
input nextdata_n;

output [7:0] data;
output reg ready;
output reg overflow;
output reg [7:0] key_count;
output reg[3:0]shift_key_count;
output reg[3:0]ctrl_key_count;
output reg[3:0] shift_flag;
output reg[3:0] ctrl_flag;
output reg[3:0] CapsLock_key_count;
output reg[3:0] CapsLock_flag;
reg [9:0] buffer;
reg [7:0] fifo[7:0];
reg [2:0] w_ptr,r_ptr;
reg [3:0] count;
reg [2:0] ps2_clk_sync;

always@(posedge clk)begin
	ps2_clk_sync <= {ps2_clk_sync[1:0],ps2_clk};
end

wire sampling = ps2_clk_sync[2] & ~ps2_clk_sync[1];

always@(posedge clk)begin
	if(clrn == 1)begin
		count <= 0;w_ptr <= 0;r_ptr <= 0;overflow <= 0;ready<= 0;key_count<=0;shift_key_count<=0;ctrl_key_count<=0;shift_flag <= 0; ctrl_flag <= 0;CapsLock_key_count<=0;CapsLock_flag<=0;
	end else begin
		if(ready)begin
			if(nextdata_n == 1'b0)begin
				r_ptr <= r_ptr+3'b1;
				if(w_ptr==(r_ptr+1'b1))
					ready <= 1'b0;
			end
		end
		if(sampling)begin
			if(count == 4'd10)begin
				if((buffer[0] == 0)&&(ps2_data)&&(^buffer[9:1]))begin
					if(buffer[8:1] == 8'hf0)
						key_count <= key_count+1;
					if(buffer[8:1] == 8'h12)begin
						shift_key_count<=shift_key_count+1;
						$display("shift+1");
						$display("shift:%x",shift_key_count[3:0]);
					end
					if(buffer[8:1]==8'h14)begin
						ctrl_key_count<=ctrl_key_count+1;
						$display("ctrl+1");
                            			$display("ctrl:%x", ctrl_key_count[3:0]);
					end
					if(buffer[8:1] == 8'h58)begin
						CapsLock_key_count <= CapsLock_key_count+1;
						$display("CapsLock_key_count+1");
						$display("CapsLock_key_count:%x", CapsLock_key_count[3:0]);
					end

					fifo[w_ptr] <= buffer[8:1];
					w_ptr <= w_ptr+3'b1;
					ready <= 1'b1;
					overflow <= overflow | (r_ptr == (w_ptr+3'b1));
					$display("receive %x", buffer[8:1]);
					$display("shift:%x", shift_key_count[3:0]);
					$display("ctrl:%x", ctrl_key_count[3:0]);
					$display("CapsLock_key_count:%x", CapsLock_key_count[3:0]);
				end
				count <= 0;
			end else begin
				buffer[count] <= ps2_data;
				count<=count+3'b1;
			end
		end

		if(shift_key_count[3:0]>7)begin
			shift_key_count <=0;
		end
		if(ctrl_key_count[3:0]>7)begin
			ctrl_key_count <=0;
		end
		if(CapsLock_key_count[3:0]>7)begin
			CapsLock_key_count <=0;
		end

		if(shift_key_count[3:0]==0 ||shift_key_count[3:0]==1 |shift_key_count[3:0]==4 ||shift_key_count[3:0]==5)begin
			shift_flag <= 4'b0000;
		end else if(shift_key_count[3:0]==2 || shift_key_count[3:0] ==3 ||shift_key_count[3:0]==6 ||shift_key_count[3:0]==7)begin
			shift_flag<=4'b0001;
		end
		if (ctrl_key_count[3:0] == 0||ctrl_key_count[3:0] == 1 || ctrl_key_count[3:0] == 4 || ctrl_key_count[3:0] == 5) begin
			ctrl_flag<=4'b0000;
		end else if(ctrl_key_count[3:0] == 2 || ctrl_key_count[3:0] == 3 || ctrl_key_count[3:0] == 6 || ctrl_key_count[3:0] == 7) begin
			ctrl_flag<=4'b0001;
		end
		if(CapsLock_key_count[3:0] == 0 ||CapsLock_key_count[3:0] == 1 || CapsLock_key_count[3:0] == 4 || CapsLock_key_count[3:0] == 5) begin
			CapsLock_flag<=4'b0000;
		end else if(CapsLock_key_count[3:0] == 2 || CapsLock_key_count[3:0] == 3 || CapsLock_key_count[3:0] == 6 || CapsLock_key_count[3:0] == 7) begin
			CapsLock_flag<=4'b0001;
		end
	end
end
	assign data = fifo[r_ptr];
endmodule


		
