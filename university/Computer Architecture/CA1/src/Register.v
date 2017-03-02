module Register(clk, en, reset, ld, dataIn, data);
  parameter width = 16;

  input en, clk, reset, ld;
  input [width-1:0] dataIn;
  output reg signed [width-1:0] data;

  always @ (posedge clk or negedge reset)
    if(en)
      if (reset)
        data <= 0;
      else if (ld)
        data <= dataIn;

endmodule
