module top (
    input clk,
    input rst,
    output [7:0] seg0,
    output [7:0] seg1 ,   
    output [7:0] seg2  ,  
    output [7:0] seg3   , 
    output [7:0] seg4    ,
    output [7:0] seg5    ,
    output [7:0] seg6    ,
    output [7:0] seg7    
);

reg [7:0] lsfr = 8'h01;

always @(posedge clk) begin
    if(rst == 1)
        lsfr <= 8'h01;
    else
        lsfr <= {lsfr[4] ^ lsfr[3] ^ lsfr[2] ^ lsfr[0], lsfr[7:1]}; 
end

assign seg0 = lsfr[0] == 0 ? 8'b0000010 : 8'b10011110;    
assign seg1 = lsfr[1] == 0 ? 8'b0000010 : 8'b10011110;    
assign seg2 = lsfr[2] == 0 ? 8'b0000010 : 8'b10011110;   
assign seg3 = lsfr[3] == 0 ? 8'b0000010 : 8'b10011110;  
assign seg4 = lsfr[4] == 0 ? 8'b0000010 : 8'b10011110;    
assign seg5 = lsfr[5] == 0 ? 8'b0000010 : 8'b10011110;    
assign seg6 = lsfr[6] == 0 ? 8'b0000010 : 8'b10011110;   
assign seg7 = lsfr[7] == 0 ? 8'b0000010 : 8'b10011110;    

    
endmodule
