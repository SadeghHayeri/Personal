module ALU(A, B, AluOp, AluOut, zero);
  input [15:0] A,B;
  input [1:0] AluOp;
  output reg zero;
  output reg [15:0] AluOut;

  always @ ( AluOp ) begin
    case (AluOp)
      2'b00: AluOut <= A + B;
      2'b01: begin AluOut <= A - B;     zero <= (A==B) ? 1 : 0; end
      2'b10: AluOut <= A & B;     
      2'b11: AluOut <= ~A;
    endcase
  end
endmodule
