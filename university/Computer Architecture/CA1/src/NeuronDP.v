module NeuronDP(clk, rst, reset, nInput, x1Input, x2Input, tInput, nReset, ldRegN, ldRegx1, ldRegx2, ldRegT, ldRegW1, ldRegW2, ldRegB, ldRegFlag, counterEn, flagReset, counterReset, endFlag, yEqualt, flagEOF, w1, w2, b);

  input clk, rst, reset, nReset, flagReset, counterEn, counterReset;
  input ldRegN, ldRegx1, ldRegx2, ldRegT, ldRegW1, ldRegW2, ldRegB, ldRegFlag;
  input [31:0] nInput;
  input [6:0] x1Input, x2Input;
  input [1:0] tInput;
  output endFlag, yEqualt, flagEOF;
  output [13:0] w1, w2, b;

  wire [13:0] w1Input;
  wire [13:0] w2Input;
  wire [13:0] bInput;
  wire endFlagInput;

  wire [1:0] t;
  wire [6:0] x1;
  wire [6:0] x2;
  wire [13:0] y;

  Register #7 x1Reg(clk, rst, reset, ldRegx1, x1Input, x1);
  Register #7 x2Reg(clk, rst, reset, ldRegx2, x2Input, x2);
  Register #2 tReg(clk, rst, reset, ldRegT, tInput, t);

  Register #14 w1Reg(clk, rst, reset, ldRegW1, w1Input, w1);
  Register #14 w2Reg(clk, rst, reset, ldRegW2, w2Input, w2);
  Register #14 bReg(clk, rst, reset, ldRegB, bInput, b);
  Register #1 flagReg(clk, rst, flagReset, ldRegFlag, endFlagInput, endFlag);

  assign w1Input = (t * x1 * 5'b0_1100) + w1;
  assign w2Input = (t * x2 * 5'b0_1100) + w2;
  assign bInput = (t * 14'b0000_11000000) + b;

  assign y = ( ( x1 * (w1 << 4) ) + ( x2 * (w2 << 4) ) + b ); // ?
  assign yEqualt = (y[13] == t[1])? 1 : 0;
  assign endFlagInput = endFlag | yEqualt;

  wire [31:0] n;
  wire [31:0] counterOut;
  Counter #32 c(clk, counterEn, rst, counterReset, counterOut);
  Register #32 nReg(clk, rst, nReset, ldN, nInput, n);
  assign flagEOF = (counterOut == n) ? 1 : 0;

endmodule // NeuronDP
