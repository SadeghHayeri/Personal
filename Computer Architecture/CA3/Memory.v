module Memory(input clk, input [12:0] address , input [15:0] WriteData , input MemRead , MemWrite, output [15:0] ReadData);
	reg [15:0] Memory [0:200];
	// initial $readmemh("Memory.txt", Memory);

/*	
  initial begin
    Memory[0] = 16'b0000000001100100;
    Memory[1] = 16'b0000000001100101;
    Memory[2] = 16'b0000000001100110;
    Memory[3] = 16'b0000000001100111;
    Memory[4] = 16'b0000000001101000;
    Memory[5] = 16'b0000000001101001;
    Memory[6] = 16'b0000000001101010;
    Memory[7] = 16'b0000000001101011;
    Memory[8] = 16'b0000000001101100;
    Memory[9] = 16'b0000000001101101;
    Memory[10] = 16'b1010000000000000;


    Memory[100] = 16'd10;
    Memory[101] = 16'd2;
    Memory[102] = 16'd3;
    Memory[103] = 16'd4;
    Memory[104] = 16'd5;
    Memory[105] = 16'd6;
    Memory[106] = 16'd7;
    Memory[107] = 16'd8;
    Memory[108] = 16'd9;
    Memory[109] = 16'd10;
  end
*/
  
  initial begin
    Memory[0] = 16'b1100000000001111;
    Memory[1] = 16'b0000000001100100;
    Memory[2] = 16'b1100000000000111;
    Memory[3] = 16'b0000000001100100;
    Memory[4] = 16'b0000000001100100;
    Memory[5] = 16'b0000000001100100;
    Memory[6] = 16'b0000000001100100;
    Memory[7] = 16'b1110000000000000;
    Memory[15] = 16'b1110000000000111;
  end

	always @(posedge clk) begin
		if(MemWrite)
			Memory[address] <= WriteData;
	end
	assign ReadData =  (MemRead) ? Memory[address] : 16'bx;

endmodule
