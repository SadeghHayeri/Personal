`timescale 1ns / 1ps
module Mux4 #(parameter busSize=8)
  (input [busSize-1:0] I1, I2, I3, I4,
   input [1:0] sel,
   output reg [busSize-1:0] O);
   always@(*)
		case(sel)
			2'b00 : O<=I1;
			2'b01 : O<=I2;
			2'b10 : O<=I3;
			2'b11 : O<=I4;
			default : O<=I1;
		endcase
 endmodule
