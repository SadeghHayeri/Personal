module SampleRegister(ld, dataIn, data);
  parameter width = 32;

  input ld;
  input [width-1:0] dataIn;
  output reg [width-1:0] data;

  always @ ( ld ) begin
    if( ld == 1 )
      data = dataIn;
  end

  initial
    data = 0;

endmodule
