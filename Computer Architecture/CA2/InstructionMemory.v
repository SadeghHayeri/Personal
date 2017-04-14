module InstructionMemory(input [31:0] address , output [31:0] instruction);
	reg [31:0]ram [100:0];
	initial $readmemb("Instructions.txt", ram);
	assign instruction = ram[address / 4];
endmodule
