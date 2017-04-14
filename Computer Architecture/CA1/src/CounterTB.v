module CounterTB;

reg en, clk, ld, reset;

wire [15:0] data;

Counter #16 test(clk, en, reset, data);

initial begin
    clk = 0;
    reset = 1;
    en = 1;
  #10;
    reset = 0;
  #10;
end

always
 #5  clk =  ! clk;

endmodule // RegisterTB
