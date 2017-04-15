module ALU( ALUOperation, A, B, ALUResult, zero );

  input [4:0] ALUOperation;
  input [31:0] A, B;
  output [31:0] ALUResult;
  output zero;

  reg ld;
  reg [31:0] hiInput, loInput;
  wire [31:0] hi, lo;

  SampleRegister #32 Hi(ld, hiInput, hi);
  SampleRegister #32 Lo(ld, loInput, lo);

  always @ ( * ) begin
    ld = 0;

    if( ALUOperation == 5'd14 ) begin
      {hiInput,loInput} = (A * B);
      ld = 1;
    end

    if( ALUOperation == 5'd13 ) begin
      hiInput = (A % B);
      loInput = (A / B);
      ld = 1;
    end

  end

  assign ALUResult =
    (ALUOperation == 5'd0) ? (A + B) :
    (ALUOperation == 5'd1) ? (A - B) :
    (ALUOperation == 5'd2) ? (A & B) :
    (ALUOperation == 5'd3) ? (A | B) :
    (ALUOperation == 5'd4) ? (A ^ B) :
    (ALUOperation == 5'd5) ? (A < B) :
    (ALUOperation == 5'd6) ? (B << 16) :
    (ALUOperation == 4'd11) ? (lo) :
    (ALUOperation == 4'd12) ? (hi) : 32'bz;

  assign zero = (ALUResult == 0) ? 1 : 0;

endmodule // ALU

// module ALU_TB();
//
//   reg [4:0] op;
//   reg [31:0] A, B;
//   wire [31:0] C;
//   wire zero;
//
//   ALU MUT(op ,A , B, C ,zero);
//   initial begin
//     A = 32'd12;
//     B = 32'd4;
//     op = 5'd5;
//     #10
//     A = 32'd4;
//     B = 32'd12;
//     op = 5'd5;
//     #10
//     A = 32'd13;
//     B = 32'd4;
//     op = 5'd7;
//     #10
//     A = 32'd12;
//     B = 32'd4;
//     op = 5'd8;
//     #10
//     A = 32'd3 ;
//     B = 32'd4;
//     op = 5'd9;
//     #10
//     A = 32'd11157689012 ;
//     B = 32'd5365789244;
//     op = 5'd3;
//     #50 $stop;
//   end
//
// endmodule
