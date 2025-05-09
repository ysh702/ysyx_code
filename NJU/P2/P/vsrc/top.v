module top(
    input [7:0]sw,
    input en,
    output reg [2:0] led_out,
    output reg indicate,
    output reg [6:0] seg_out
);

wire [2:0]w;

assign led_out = w;

encode38 encdr(
    .x(sw),
    .en(en),
    .y(w),
    .indicate(indicate)
);

bcd7seg seg0(
    .b({1'b0,w}),
    .h(seg_out)
);
endmodule
