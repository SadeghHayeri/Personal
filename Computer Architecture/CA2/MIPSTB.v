module MIPSTB();

  reg clk = 0;
  reg rst = 0;

  MIPS m(rst, clk);

  initial repeat(50000000) begin
    #1000
    clk = ~clk ;
  end

endmodule //
