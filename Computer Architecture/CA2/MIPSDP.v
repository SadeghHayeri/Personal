module MIPSDP(input clk , rst);

  wire [31:0] pc, pc4, pcPlus, pcIn, inst, wData, r1, r2, b, aluOut, memData, memAlu, i16Ext, i16ExtShift;
  wire [4:0]  wAddress;
  reg [31:0] R31 = 32'd31;

  Register #32 PC (clk, clk, pcIn, pc);
endmodule
