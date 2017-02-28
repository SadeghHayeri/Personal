module Register(clk, en, reset, ld, dataIn, dataOut);
  parameter width = 16;

  input en, clk, reset, ld;
  input [width-1:0] dataIn;
  output reg [width-1:0] dataOut;

  reg[width-1:0] data;

  always @ (posedge clk or negedge reset)
    if(en)
      if (reset)
        dataOut <= 0;
      else if (ld)
        data <= dataIn;

  always @ ( * )
    dataOut <= data;

endmodule
