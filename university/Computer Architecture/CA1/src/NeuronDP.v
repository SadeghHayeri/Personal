module NeuronDP(clk, reset, x1Input, x2Input, tInput, ldRegx1, ldRegx2, ldRegT, ldRegW1, ldRegW2, ldRegB, ldRegFlag, endFlag, yEqualt);

  input clk, reset;
  input ldRegx1, ldRegx2, ldRegT, ldRegW1, ldRegW2, ldRegB, ldRegFlag;
  input [6:0] x1Input;
  input [6:0] x2Input;
  input [1:0] tInput;
  output endFlag;
  output yEqualt;

  wire [13:0] w1Input;
  wire [13:0] w2Input;
  wire [13:0] bInput;
  wire endFlagInput;

  wire [1:0] t;
  wire [6:0] x1;
  wire [6:0] x2;
  wire [13:0] w1;
  wire [13:0] w2;
  wire [13:0] b;
  wire [13:0]y;

  Register #7 x1Reg(clk, en, reset, ldRegx1, x1Input, x1);
  Register #7 x2Reg(clk, en, reset, ldRegx2, x2Input, x2);
  Register #2 tReg(clk, en, reset, ldRegT, tInput, t);

  Register #14 w1Reg(clk, en, reset, ldRegW1, w1Input, w1);
  Register #14 w2Reg(clk, en, reset, ldRegW2, w2Input, w2);
  Register #14 bReg(clk, en, reset, ldRegB, bInput, b);
  Register #1 flagReg(clk, en, reset, ldRegFlag, endFlagInput, endFlag);

  assign w1Input = (t * x1 * 5'b0_1100) + w1Input;
  assign w2Input = (t * x2 * 5'b0_1100) + w2Input;
  assign bInput = (t * 14'b0000_11000000) + bInput;

  assign y = ( ( x1 * (w1 << 4) ) + ( x2 * (w2 << 4) ) + b ); // ?
  assign yEqualt = (y[13] == t[1])? 1 : 0;
  assign endFlagInput = endFlag | yEqualt;

endmodule // NeuronDP
