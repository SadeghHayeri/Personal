`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date:    17:55:13 11/08/2017
// Design Name:
// Module Name:    register
// Project Name:
// Target Devices:
// Tool versions:
// Description:
//
// Dependencies:
//
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
//
//////////////////////////////////////////////////////////////////////////////////
module Register #(parameter size=8) (input clk, ld, rst, input [size-1:0]data, output reg [size-1:0]O);
  always @(posedge clk, posedge rst) begin
    if(rst)
	  O <= {(size){1'b0}};
	else if(ld)
      O <= data;
  end
endmodule
