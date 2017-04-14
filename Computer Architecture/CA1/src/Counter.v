module Counter(clk, en, rst, reset, out);
  parameter width = 32;

  input clk, en, rst, reset;
  output reg[width-1:0] out;

  always @ (posedge clk or posedge reset)
    if(en)
      if(reset)
        out <= 0;
      else
        out <= out + 1;

  always @ (rst)
    out <= 0;

endmodule // end counter
