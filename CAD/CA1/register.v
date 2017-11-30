`timescale 1ns / 1ps

module Register #(parameter size=8) (input clk, ld, rst, input [size-1:0]data, output reg [size-1:0]O);
  always @(posedge clk, posedge rst) begin
    if(rst)
	  O <= {(size){1'b0}};
	else if(ld)
      O <= data;
  end
endmodule
