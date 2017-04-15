module ALUCU(ALUOp, func, ALUOperation);
  input [1:0] ALUOp;
  input [5:0] func;
  output reg [4:0] ALUOperation;

  always @ ( ALUOp, func ) begin

    ALUOperation = 5'b0;

    // R-Type
    if( ALUOp == 2'b00 ) begin

      case (func)
        6'b100000: ALUOperation = 5'd0; // +
        6'b100010: ALUOperation = 5'd1; // -
        6'b100100: ALUOperation = 5'd2; // &
        6'b100101: ALUOperation = 5'd3; // |
        6'b100110: ALUOperation = 5'd4; // ^
        6'b101010: ALUOperation = 5'd5; // <
        6'b011000: ALUOperation = 5'd14; // *
        6'b011010: ALUOperation = 5'd13; // /
        6'b010010: ALUOperation = 5'd11; // lo
        6'b010000: ALUOperation = 5'd12; // hi
        6'b001000: ALUOperation = 5'd0; // jr
      endcase

    end
    else if( ALUOp == 2'b01 ) begin
      ALUOperation = 5'd0; // +
    end
    else if( ALUOp == 2'b10 ) begin
      ALUOperation = 5'd1; // -
    end
    else begin
      ALUOperation = 5'd5; // <
    end

  end

endmodule // ALUCU
