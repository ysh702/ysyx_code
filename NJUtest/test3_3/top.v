module top(
    input [2:0] command_input,
    input [3:0] a_input,
    input [3:0] b_input,
    input [0:0] clk,
    output [3:0] ans,
    output [0:0] overflow_flag
);

reg [3:0] temp_ans;
reg [0:0] temp_overflow_flag;
reg [2:0] command = command_input;
reg [3:0] a = a_input;   //如果你需要测试，command、a、b直接赋值就可以，例如
reg [3:0] b = b_input;	 //改成a = 4‘b0111;即可

    always @(posedge clk) begin
        case (command)
            3'b000:begin
            	 //这样写能够取出溢出的那一位，用以判断是否溢出，如果需要，可以输出
                 {temp_overflow_flag, temp_ans} = a + b;
            end
            3'b001:begin
                 b = ~b + 1;
                 {temp_overflow_flag, temp_ans} = a + b;
            end
            3'b010:begin
                 temp_ans = ~a;
            end
            3'b011:begin
                 temp_ans = a & b;
            end
            3'b100:begin
                 temp_ans = a | b;
            end
            3'b101:begin
                 temp_ans = a ^ b;
            end
            3'b110:begin
                if (a[3] == b[3]) begin		//判断符号位是否相等
                    if (a < b)  temp_ans = 1;	//符号位相等直接比大小
                        else  temp_ans = 0;
                end
                else begin					//符号位不相等直接比符号位
                    if ((a[3] == 0) && (b[3] == 1)) temp_ans = 0;
                    if ((a[3] == 1) && (b[3] == 0)) temp_ans = 1;
                end
            end
            3'b111:begin
                if (a == b)  temp_ans = 1;
                    else  temp_ans = 0;
            end
        endcase
    end

    assign ans = temp_ans;
    assign overflow_flag = temp_overflow_flag;		//溢出标志

endmodule

