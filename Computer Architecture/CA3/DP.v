module DP(clk, AccSrc, MemRead, MemWrite, ldIR, ldMDR, ldAcc, IorD, Asrc, Bsrc, PCsrc, PCwrite, jz, ALUop, opcode);

  input clk, AccSrc, MemRead, MemWrite, ldIR, ldMDR, ldAcc, IorD, Asrc, PCsrc, PCwrite, jz;
  input [1:0] ALUop, Bsrc;
  output [2:0] opcode;

  wire [15:0] ALUout, A, B, MemData, MDRIn, MEMout, IRAdd, AccIn;
  wire [12:0] newPC, PCIn, MemAdd;
  wire Zero;

  Register #13 pc(clk, ldPC, PCIn, newPC);
  Register #16 ir(clk, ldIR, MEMout, IRAdd);
  Register #16 mdr(clk, 1'b1, MEMout, MDRIn);
  Register #16 acc(clk, ldAcc, AccIn, MemData);

  Mux #13 pcMux(ALUout[12:0], IRAdd[12:0], 13'bz, 13'bz, {1'b0,PCsrc}, PCIn);
  Mux #13 memMux(newPC, IRAdd[12:0], 13'bz, 13'bz, {1'b0,IorD}, MemAdd);
  Mux #16 accMux(ALUout, MDRIn, 16'bz, 16'bz, {1'b0, AccSrc}, AccIn);
  Mux #16 aMux({3'b000, newPC}, MemData, 16'bz, 16'bz, {1'b0, Asrc}, A);
  Mux #16 bMux(16'b0, 16'b1, MDRIn, 16'bz, Bsrc, B);

  Memory mem(clk, MemAdd, MemData, MemRead, MemWrite, MEMout);
  ALU alu(A, B, ALUop, ALUout, Zero);

  assign ldPC = PCwrite | (jz & Zero);
  assign opcode = (IRAdd[15:13]);

endmodule // DP
