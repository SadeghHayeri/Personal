`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date:    17:58:02 11/08/2017
// Design Name:
// Module Name:    memory
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
module Memory #(parameter width=8, size=100, addrSize=8)
  (
   input clk,
   input write,
   input [addrSize-1:0]addr,
   input [width-1:0]wrData,
   output reg [width-1:0]rdData
  );

  reg [width-1:0] Mem [0:size-1];

  initial begin
  Mem[0] = 8'd0;
  Mem[1] = 8'd0;
  Mem[2] = 8'd0;
  Mem[3] = 8'd0;
  Mem[4] = 8'd0;
  Mem[5] = 8'd0;
  Mem[6] = 8'd0;
  Mem[7] = 8'd0;
  Mem[8] = 8'd0;
  end
  always @(clk) begin
    if(write)
      Mem[addr] <= wrData;
      rdData <= Mem[addr];
  end
endmodule
