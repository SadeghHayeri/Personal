module Mux(input0, input1, input2, input3, selector, out);
  parameter inputSize = 32;

  input [inputSize-1:0] input0, input1, input2, input3;
  input [1:0] selector;
  output reg [inputSize-1:0] out;

  always @ ( * ) begin
    case (selector)
      2'b00: out = input0;
      2'b01: out = input1;
      2'b10: out = input2;
      2'b11: out = input3;
    endcase
  end

endmodule // Mux
