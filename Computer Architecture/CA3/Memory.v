module Memory(input clk, input [12:0] address , input [15:0] WriteData , input MemRead , MemWrite, output [15:0] ReadData);
	reg [15:0] Memory [0:4095];
	initial $readmemh("Memory.txt", Memory);
	always @(posedge clk) begin
		if(MemWrite)
			Memory[address] <= WriteData;
	end
	assign ReadData =  (MemRead) ? Memory[address] : 'x;
endmodule
