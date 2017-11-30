`timescale 1ns / 1ps

module Counter #(parameter size=8)(input clk , rsc , ce , output reg [size-1:0]O);
	always @ (posedge clk) begin
			if(rsc) O<=0;
			else if(ce) O<=O+1;
	end
endmodule
