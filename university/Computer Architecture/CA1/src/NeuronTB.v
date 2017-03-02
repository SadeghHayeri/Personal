module Neuron_TB;

reg clk, reset;
Controller cu(clk, rst, start, endFlag, yEqualt, flagEOF, done, ldRegx1, ldRegx2, ldRegT, ldRegW1, ldRegW2, ldRegB, ldRegFlag, counterReset, flagReset);
NeuronDP dp(clk, rst, reset, nInput, x1Input, x2Input, tInput, ldRegN, ldRegx1, ldRegx2, ldRegT, ldRegW1, ldRegW2, ldRegB, ldRegFlag, counterEn, flagReset, counterReset, endFlag, yEqualt, flagEOF);
