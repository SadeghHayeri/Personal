module RegisterFile(input clk, rst, RegWrite, input[4:0] ReadReg1, ReadReg2, WriteReg, input[31:0] WriteData, output[31:0] ReadData1, ReadData2);
	reg [31:0] registers [31:0];
	initial $readmemh("registers.txt", registers);
	integer i;
	always @(posedge clk)begin
		if(rst)
			for(i = 0; i < 32; i = i + 1)
				registers[i] = 32'b0;
		else if(RegWrite == 1 )
			registers[WriteReg] <= WriteData;
	end
	assign ReadData1 = registers[ReadReg1];
	assign ReadData2 = registers[ReadReg2];
endmodule
