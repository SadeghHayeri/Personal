module Counter(clk, en, reset, out);
  parameter width = 4;

  input clk, en, reset;
  output reg [width-1:0] out;

  always @ (posedge clk)
    if(reset)
      out <= 0;
    else
      out <= out + 1;

endmodule // end counter
