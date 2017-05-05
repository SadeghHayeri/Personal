module TB();

  reg clk = 0;
  reg rst = 0;

  CPU m(clk, rst);

  initial repeat(5000) begin
    #100
    clk = ~clk ;
  end

endmodule
