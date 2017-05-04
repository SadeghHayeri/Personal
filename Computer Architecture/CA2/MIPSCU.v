module MIPSCU(rst, zero, opcode, func, regWrite, memRead, memWrite, sm1, sm2, sm3, sm4, sm5, ALUOp);

  input rst, zero;
  input [5:0] opcode, func;
  output reg regWrite, memRead, memWrite;
  output reg [1:0] sm1, sm2, sm3, sm4, sm5, ALUOp;

  always @ ( opcode, func, zero ) begin

    {regWrite, memRead, memWrite, sm1, sm2, sm3, sm4, sm5} = 13'b0;

    case (opcode)

      // R-type
      6'b000000: begin
        ALUOp = 2'b00;

        regWrite = (func == 6'b011000 || func == 6'b011010 || func == 6'b001000) ? 0 : 1; // (* / jr) - R-type
        memRead = 0;
        memWrite = 0;
        sm1 = 2'b01;
        sm2 = 2'b01;
        sm3 = 2'b00;
        sm4 = 2'b01;
        sm5 = (func == 6'b001000) ? 2'b11 : 2'b00; // jr - R-type
      end

      // addi
      6'b001000: begin
        ALUOp = 2'b01;

        regWrite = 1;

        memRead = 0;
        memWrite = 0;
        sm1 = 2'b00;
        sm2 = 2'b01;
        sm3 = 2'b01;
        sm4 = 2'b01;
        sm5 = 2'b00;
      end

      // slti
      6'b001010: begin
        ALUOp = 2'b11;

        regWrite = 1;

        memRead = 0;
        memWrite = 0;
        sm1 = 2'b00;
        sm2 = 2'b01;
        sm3 = 2'b01;
        sm4 = 2'b01;
        sm5 = 2'b00;
      end

      // lw
      6'b100011: begin
        ALUOp = 2'b01;

        regWrite = 1;

        memRead = 1;
        memWrite = 0;
        sm1 = 2'b00;
        sm2 = 2'b01;
        sm3 = 2'b01;
        sm4 = 2'b00;
        sm5 = 2'b00;
      end

      // sw
      6'b101011: begin
        ALUOp = 2'b01;

        regWrite = 0;

        memRead = 0;
        memWrite = 1;
        sm1 = 2'b00;
        sm2 = 2'b00;
        sm3 = 2'b01;
        sm4 = 2'b00;
        sm5 = 2'b00;
      end

      // lui
      6'b001111: begin
        ALUOp = 2'b00; //

        regWrite = 1;

        memRead = 0;
        memWrite = 0;
        sm1 = 2'b00;
        sm2 = 2'b01;
        sm3 = 2'b00;
        sm4 = 2'b01;
        sm5 = 2'b00;
      end

      // bne
      6'b000101: begin
        ALUOp = 2'b10;

        regWrite = 0;

        memRead = 0;
        memWrite = 0;
        sm1 = 2'b00;
        sm2 = 2'b00;
        sm3 = 2'b00;
        sm4 = 2'b00;
        sm5 = (zero == 1) ? 2'b00 : 2'b01;
      end

      // beq
      6'b000100: begin
        ALUOp = 2'b10;

        regWrite = 0;

        memRead = 0;
        memWrite = 0;
        sm1 = 2'b00;
        sm2 = 2'b00;
        sm3 = 2'b00;
        sm4 = 2'b00;
        sm5 = (zero == 0) ? 2'b00 : 2'b01;
      end

      // j
      6'b000010: begin
        ALUOp = 2'b01;

        regWrite = 0;

        memRead = 0;
        memWrite = 0;
        sm1 = 2'b00;
        sm2 = 2'b00;
        sm3 = 2'b00;
        sm4 = 2'b00;
        sm5 = 2'b10;
      end

      // jal
      6'b000011: begin
        ALUOp = 2'b01;

        regWrite = 1;

        memRead = 0;
        memWrite = 0;
        sm1 = 2'b10;
        sm2 = 2'b00;
        sm3 = 2'b00;
        sm4 = 2'b00;
        sm5 = 2'b10;
      end

      default: ;
    endcase

  end

endmodule // CU
