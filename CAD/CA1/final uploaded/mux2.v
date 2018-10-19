`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    17:55:27 11/08/2017 
// Design Name: 
// Module Name:    mux2 
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
module Mux2 #(parameter busSize=8)
  (input [busSize-1:0] I1, I2,
   input sel,
   output reg [busSize-1:0] O);
   always@(*)
		case(sel)
			1'b0 : O<=I1;
			1'b1 : O<=I2;
			default : O<=I1;
		endcase
 endmodule
