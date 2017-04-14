module MemoryFile(input Clk, Rst,input [31:0] address , WriteData , input MemRead , MemWrite, output [31:0] ReadData);
	reg [31:0] Memory [999:0];
	initial $readmemh("Memory.txt", Memory);
	integer i;
	always @(posedge Clk) begin
		if(Rst) begin
			for(i = 0; i < 1000; i = i + 1)
				Memory[i] = 32'b0;
		end
		else if(MemWrite)
			Memory[address / 4] <= WriteData;
	end
	assign ReadData =  Memory[address / 4];
endmodule
