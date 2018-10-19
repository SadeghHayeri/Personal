`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company:
// Engineer:
//
// Create Date:   16:17:29 11/01/2017
// Design Name:   MatrixMultiplication
// Module Name:   F:/Amir/UT/Term 5/CAD/Assignments/CA1/LUT Design/MatrixMultiplier/tb.v
// Project Name:  MatrixMultiplier
// Target Device:
// Tool versions:
// Description:
//
// Verilog Test Fixture created by ISE for module: MatrixMultiplication
//
// Dependencies:
//
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
//
////////////////////////////////////////////////////////////////////////////////

module tb;

	// Inputs
	reg clk;
	reg rst;
	reg start;
	reg [7:0] in;

	// Outputs
	wire [7:0] out;
	wire done;
	// Instantiate the Unit Under Test (UUT)
	main uut (
		.clk(clk),
		.data_in(in),
		.start(start),
		.rst(rst),
		.data_out(out),
		.done(done)
	);
	always #50 clk = ~clk;
	always #50 in = in + 3;
	initial begin
		clk = 0;
		rst = 1;
		start = 0;
		in = 0;
		#80
		rst = 0;
		#100
		start = 1;
		#110
		start = 0;
		#100000
		$stop;

	end
endmodule
