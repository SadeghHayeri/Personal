module Neuron(clk, rst, nInput, x1Input, x2Input, tInput, dataReady, requestFlag, done, w1, w2, b);

  input clk, rst, dataReady;
  input [31:0] nInput;
  input [6:0] x1Input, x2Input;
  input [1:0] tInput;

  output requestFlag;
  output [13:0] w1, w2, b;

  wire reset, ldRegN, ldRegx1, ldRegx2, ldRegT, ldRegW1, ldRegW2, ldRegB, ldRegFlag, counterEn, flagReset, counterReset, endFlag, yEqualt, flagEOF;

  NeuronDP dp(clk, rst, reset, nInput, x1Input, x2Input, tInput, ldRegN, ldRegx1, ldRegx2, ldRegT, ldRegW1, ldRegW2, ldRegB, ldRegFlag, counterEn, flagReset, counterReset, endFlag, yEqualt, flagEOF);
  Controller cu(clk, rst, start, dataReady, endFlag, yEqualt, flagEOF, done, requestFlag,ldRegx1, ldRegx2, ldRegT, ldRegW1, ldRegW2, ldRegB, ldRegFlag, counterReset, flagReset);

endmodule // Neuron
