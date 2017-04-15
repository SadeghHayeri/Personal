module MIPSDP(rst, clk, regWrite, memRead, memWrite, ALUOperation, sm1, sm2, sm3, sm4, sm5, zero, inst);

  input rst, clk, regWrite, memRead, memWrite;
  input [4:0] ALUOperation;
  input [1:0] sm1, sm2, sm3, sm4, sm5;
  output zero;
  output [31:0] inst;

  wire [31:0] pc, pc4, pcPlus, pcIn, wData, r1, r2, b, aluOut, memData, memAlu, i16Ext, i16ExtShift, jJal;
  wire [4:0]  wAddress;
  reg [4:0] R31 = 5'b11111;
  reg [31:0] tmp = 31'd0;

  Register #32 PC(clk, clk, pcIn, pc);

  InstructionMemory instMem(pc, inst);
  RegisterFile regFile(clk, rst, regWrite, inst[25:21], inst[20:16], wAddress, wData, r1, r2);
  ALU alu(ALUOperation, r1, b, aluOut, zero);
  MemoryFile mf(rst, aluOut, r2, memRead, memWrite, memData);

  Mux #5 m1(inst[20:16], inst[15:11], R31, tmp[4:0], sm1, wAddress);
  Mux #32 m2(pc4, memAlu, tmp, tmp, sm2, wData);
  Mux #32 m3(r2, i16Ext, tmp, tmp, sm3, b);
  Mux #32 m4(memData, aluOut, tmp, tmp, sm4, memAlu);
  Mux #32 m5(pc4, pcPlus, jJal, r1, sm5, pcIn);

  assign i16Ext = (inst[15] == 1) ? {16'b1111_1111_1111_1111, inst[15:0]} : {16'b0000_0000_0000_0000, inst[15:0]};
  assign i16ExtShift = i16Ext << 2;
  assign jJal = {pc4[31:28], (inst[26:0]<<2)};

  assign pc4 = pc + 4;
  assign pcPlus = i16ExtShift + pc4;

endmodule
