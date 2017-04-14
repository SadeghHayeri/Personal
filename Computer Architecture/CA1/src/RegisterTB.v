module RegisterTB;

reg [15:0] data;
reg en, clk, ld, reset;

wire [15:0] dataOut;

Register #16 test(clk, en, reset, ld, data, dataOut);

initial begin
  clk = 0;
  reset = 0;
  en = 1;
  #10;
  data = 20;
  ld = 1;

  #10;
  ld = 0;

  #10;
  data = 30;
  ld = 1;

  #10;
  ld = 0;

  #10;
  reset = 1;

  #10;
end

always
 #5  clk =  ! clk;

endmodule // RegisterTB
