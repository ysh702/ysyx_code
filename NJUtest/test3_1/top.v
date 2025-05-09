module top(
  input a, // 输入a
  input b, // 输入b
  output sum, // 输出和
  output carry // 输出进位
);
  assign sum = a ^ b; // 异或操作得到和
  assign carry = a & b; // 与操作得到进位
endmodule

