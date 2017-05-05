module ALU(A, B, AluOp, AluOut, zero);
  input [15:0] A,B;
  input [1:0] AluOp;
  output zero;
  output reg [15:0] AluOut;

  always @ ( * ) begin
    case (AluOp)
      2'b00: AluOut <= A + B;
      2'b01: AluOut <= A - B;
      2'b10: AluOut <= A & B;
      2'b11: AluOut <= ~A;
    endcase
    // $display("A%b) B(%b) OUT(%b)", A, B, AluOut);
  end
  assign zero = (AluOut == 0) ? 0 : 1;

endmodule
