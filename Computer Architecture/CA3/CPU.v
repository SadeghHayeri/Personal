module CPU(clk, rst);

  input clk, rst;
  wire AccSrc, MemRead, MemWrite, ldIR, ldMDR, ldAcc, IorD, Asrc, PCsrc, PCwrite, jz;
  wire [1:0] ALUop, Bsrc;
  wire [2:0] opcode;

  DP dp(clk, AccSrc, MemRead, MemWrite, ldIR, ldMDR, ldAcc, IorD, Asrc, Bsrc, PCsrc, PCwrite, jz, ALUop, opcode);
  Controller cnt(opcode, rst, clk,
    AccSrc, MemRead, MemWrite, ldIR, ldMDR, ldAcc, IorD, Asrc, PCsrc, PCwrite, jz,
    ALUop, Bsrc);

endmodule // CPU
