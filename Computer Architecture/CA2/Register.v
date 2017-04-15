module Register(clk, ld, dataIn, data);
  parameter width = 16;

  input clk, ld;
  input [width-1:0] dataIn;
  output reg [width-1:0] data;

  always @ (posedge clk) begin
    if (ld)
      data <= dataIn;
  end

  initial
    data = 0

endmodule
