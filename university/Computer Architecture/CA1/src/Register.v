module Register(clk, rst, reset, ld, dataIn, data);
  parameter width = 16;

  input clk, rst, reset, ld;
  input [width-1:0] dataIn;
  output reg signed [width-1:0] data;

  always @ (posedge clk or negedge reset)
    if (reset)
      data <= 0;
    else if (ld)
      data <= dataIn;

  always @ (rst)
    data <= 0;

endmodule
