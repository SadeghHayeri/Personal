module RegisterTB;

reg [15:0] data;
reg ld;

wire [15:0] dataOut;

Register #16 test(ld, data, dataOut);

initial begin
  data = 0
  ld = 0
  #10;
  data = 20;
  ld = 0;

  #10;
  ld = 1;

  #10;
  data = 30;
  ld = 1;

  #10;
  ld = 0;

  #10;
end

endmodule // RegisterTB
