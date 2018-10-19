`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    17:58:49 11/08/2017 
// Design Name: 
// Module Name:    counter 
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
module Counter #(parameter size=8)(input clk , rsc , ce , output reg [size-1:0]O);
	always @ (posedge clk) begin
			if(rsc) O<=0;
			else if(ce) O<=O+1;
	end
endmodule