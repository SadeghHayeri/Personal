module SampleRegister(ld, dataIn, data);
  parameter width = 32;

  input ld;
  input [width-1:0] dataIn;
  output reg [width-1:0] data;

<<<<<<< HEAD
  always @ ( ld ) begin
=======
  always @ ( * ) begin
>>>>>>> 2d3cf3cc6908a26a8f298864c55aedea620bf858
    if( ld == 1 )
      data = dataIn;
  end

  initial
    data = 0;

endmodule
