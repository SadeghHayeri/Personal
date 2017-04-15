module MIPS(rst, clk);

  input rst, clk;
  wire regWrite, memRead, memWrite, zero;
  wire [1:0] sm1, sm2, sm3, sm4, sm5, ALUOp;
  wire [4:0] ALUOperation;
  wire [31:0] inst;


  MIPSDP dp(rst, clk, regWrite, memRead, memWrite, ALUOperation, sm1, sm2, sm3, sm4, sm5, zero, inst);
  MIPSCU cu(rst, zero, inst[31:26], inst[5:0], regWrite, memRead, memWrite, sm1, sm2, sm3, sm4, sm5, ALUOp);
  ALUCU acu(ALUOp, inst[5:0], ALUOperation);

endmodule // MIPS
