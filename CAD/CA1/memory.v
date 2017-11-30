`timescale 1ns / 1ps
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
	Mem[9] = 8'd0;
	Mem[10] = 8'd0;
	Mem[11] = 8'd0;
	Mem[12] = 8'd0;
	Mem[13] = 8'd0;
	Mem[14] = 8'd0;
	Mem[15] = 8'd0;
	Mem[16] = 8'd0;
	Mem[17] = 8'd0;
	Mem[18] = 8'd0;
	Mem[19] = 8'd0;
  end
  always @(addr, write) begin
    if(write)
      Mem[addr] <= wrData;
      rdData <= Mem[addr];
  end
endmodule
