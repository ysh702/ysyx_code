module top(
	input clk, clrn,ps2_clk,ps2_data,
	output [7:0] seg0,seg1,seg2,seg3,seg4,seg5,seg6,seg7
);
reg nextdata_n;
reg ready;
reg overflow;
reg [7:0] ascill_data,ps2_tmp_data,out_data;
reg [7:0] key_count;
reg [7:0] ascii;


reg [7:0] tmp_seg0,tmp_seg1,tmp_seg2,tmp_seg3,tmp_seg6,tmp_seg7;

reg [7:0] shift_data;
reg [7:0] ctrl_data;
reg [3:0] shift_key_count;
reg [3:0] ctrl_key_count;
reg [3:0] shift_flag;
reg [3:0] ctrl_flag;

reg [3:0] CapsLock_key_count;
reg [3:0] CapsLock_flag;

reg [3:0] STATE_IDLE=4'b0000;
reg [3:0] STATE_OUT=4'b0001;
reg [3:0] STATE_DISPLAY=4'b0010;
reg [3:0] STATE_WAIT=4'b0100;

reg [3:0] state=STATE_IDLE;
reg [3:0] next_state;




ps2_keyboard my_keyboard (.clk(clk),.clrn(clrn),.ps2_clk(ps2_clk),.ps2_data(ps2_data),
  .data(ps2_tmp_data),.ready(ready),.nextdata_n(nextdata_n),.overflow(overflow),
  .key_count(key_count),.shift_key_count(shift_key_count),
  .ctrl_key_count(ctrl_key_count),.shift_flag(shift_flag),.ctrl_flag(ctrl_flag),
  .CapsLock_key_count(CapsLock_key_count),.CapsLock_flag(CapsLock_flag));


ps2_to_ascii my_ps2_to_ascii (ascill_data,CapsLock_flag,ascii);

bcd7seg my_seg1 (ascill_data[3:0],tmp_seg0);
bcd7seg my_seg2 (ascill_data[7:4],tmp_seg1);
bcd7seg my_seg3 (ascii[3:0],tmp_seg2);
bcd7seg my_seg4 (ascii[7:4],tmp_seg3);
bcd7seg my_seg5 (key_count[3:0],seg4);
bcd7seg my_seg6 (key_count[7:4],seg5);

bcd7seg my_seg7 (shift_flag[3:0],seg6);
bcd7seg my_seg8 (ctrl_flag[3:0],seg7);


Reg #(8,8'b11111111) my_reg1 (clk,state!=STATE_OUT,tmp_seg0,seg0,state==STATE_OUT); //初始状态
Reg #(8,8'b11111111) my_reg2 (clk,state!=STATE_OUT,tmp_seg1,seg1,state==STATE_OUT); //out_data写入
Reg #(8,8'b11111111) my_reg3 (clk,state!=STATE_OUT,tmp_seg2,seg2,state==STATE_OUT); //数据显示在数码管
Reg #(8,8'b11111111) my_reg4 (clk,state!=STATE_OUT,tmp_seg3,seg3,state==STATE_OUT); //等待下一次输入，直接进入状态b

always@(posedge clk or ps2_clk)begin
	if(clrn)
		state <= STATE_IDLE;
	else
		state <= next_state;
end

always@(*)begin
	if(ready)begin
		case(state)
			STATE_IDLE:next_state=STATE_OUT;
			STATE_OUT:begin
				if(ps2_tmp_data==8'hf0)
					next_state=STATE_DISPLAY;
				else
					next_state=STATE_OUT;
			end
			STATE_DISPLAY:begin
				if(ps2_tmp_data !=8'hf0)
					next_state=STATE_WAIT;
				else
					next_state=STATE_DISPLAY;
			end
			STATE_WAIT:begin
				if(ps2_tmp_data!=8'hf0)
					next_state=STATE_OUT;
				else
					next_state=STATE_WAIT;
			end
			default:next_state=STATE_IDLE;
		endcase
		out_data=ps2_tmp_data;
	end
end

assign ascill_data=(state==STATE_OUT)?out_data:8'b0;
endmodule







module ps2_to_ascii(input [7:0]x,input [3:0]CapsLock_flag, output [7:0]y);
reg[7:0] tmp;
always@(*)begin
	case(x)
		8'h1c: tmp = (CapsLock_flag == 4'b0001) ? 8'h41 : 8'h61; // A/a
            	8'h32: tmp = (CapsLock_flag == 4'b0001) ? 8'h42 : 8'h62; // B/b
            	8'h21: tmp = (CapsLock_flag == 4'b0001) ? 8'h43 : 8'h63; // C/c
            	8'h23: tmp = (CapsLock_flag == 4'b0001) ? 8'h44 : 8'h64; // D/d
            	8'h24: tmp = (CapsLock_flag == 4'b0001) ? 8'h45 : 8'h65; // E/e
            	8'h2b: tmp = (CapsLock_flag == 4'b0001) ? 8'h46 : 8'h66; // F/f
            	8'h34: tmp = (CapsLock_flag == 4'b0001) ? 8'h47 : 8'h67; // G/g
            	8'h33: tmp = (CapsLock_flag == 4'b0001) ? 8'h48 : 8'h68; // H/h
            	8'h43: tmp = (CapsLock_flag == 4'b0001) ? 8'h49 : 8'h69; // I/i
            	8'h3b: tmp = (CapsLock_flag == 4'b0001) ? 8'h4a : 8'h6a; // J/j
            	8'h42: tmp = (CapsLock_flag == 4'b0001) ? 8'h4b : 8'h6b; // K/k
            	8'h4b: tmp = (CapsLock_flag == 4'b0001) ? 8'h4c : 8'h6c; // L/l
            	8'h3a: tmp = (CapsLock_flag == 4'b0001) ? 8'h4d : 8'h6d; // M/m
            	8'h31: tmp = (CapsLock_flag == 4'b0001) ? 8'h4e : 8'h6e; // N/n
            	8'h44: tmp = (CapsLock_flag == 4'b0001) ? 8'h4f : 8'h6f; // O/o
            	8'h4d: tmp = (CapsLock_flag == 4'b0001) ? 8'h50 : 8'h70; // P/p
            	8'h15: tmp = (CapsLock_flag == 4'b0001) ? 8'h51 : 8'h71; // Q/q
            	8'h2d: tmp = (CapsLock_flag == 4'b0001) ? 8'h52 : 8'h72; // R/r
            	8'h1b: tmp = (CapsLock_flag == 4'b0001) ? 8'h53 : 8'h73; // S/s
            	8'h2c: tmp = (CapsLock_flag == 4'b0001) ? 8'h54 : 8'h74; // T/t
            	8'h3c: tmp = (CapsLock_flag == 4'b0001) ? 8'h55 : 8'h75; // U/u
            	8'h2a: tmp = (CapsLock_flag == 4'b0001) ? 8'h56 : 8'h76; // V/v
            	8'h1d: tmp = (CapsLock_flag == 4'b0001) ? 8'h57 : 8'h77; // W/w
            	8'h22: tmp = (CapsLock_flag == 4'b0001) ? 8'h58 : 8'h78; // X/x
            	8'h35: tmp = (CapsLock_flag == 4'b0001) ? 8'h59 : 8'h79; // Y/y
            	8'h1a: tmp = (CapsLock_flag == 4'b0001) ? 8'h5a : 8'h7a; // Z/z
            	8'h45: tmp = (CapsLock_flag == 4'b0001) ? 8'h30 : 8'h30; // 0
            	8'h16: tmp = (CapsLock_flag == 4'b0001) ? 8'h21 : 8'h31; // 1
            	8'h1e: tmp = (CapsLock_flag == 4'b0001) ? 8'h40 : 8'h32; // 2
            	8'h26: tmp = (CapsLock_flag == 4'b0001) ? 8'h23 : 8'h33; // 3
            	8'h25: tmp = (CapsLock_flag == 4'b0001) ? 8'h24 : 8'h34; // 4
            	8'h2e: tmp = (CapsLock_flag == 4'b0001) ? 8'h25 : 8'h35; // 5
            	8'h36: tmp = (CapsLock_flag == 4'b0001) ? 8'h26 : 8'h36; // 6
            	8'h3d: tmp = (CapsLock_flag == 4'b0001) ? 8'h27 : 8'h37; // 7
            	8'h3e: tmp = (CapsLock_flag == 4'b0001) ? 8'h28 : 8'h38; // 8
            	8'h46: tmp = (CapsLock_flag == 4'b0001) ? 8'h29 : 8'h39; // 9
            	default: tmp = 8'h00; // 默认值
	endcase
end
	
assign y=tmp;
endmodule
