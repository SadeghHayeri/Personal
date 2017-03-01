module Counter(clk, en, rst, out);

  parameter [2:0] start = 0, init = 1, getData = 2, changeWeight = 3, doneCheck = 4, reset = 5;
  reg [2:0] ns = 0, ps = 0;

  always @ ( posedge clk, posedge rst ) begin
    if( rst == 1'b1 )
        ps <= start;
    else
        ps <= ns;
  end

  always @ ( ps ) begin

    done = 1'b1;
    reset = 1'b0;
    
      Rshift = 1'b0;
      Rload = 1'b0;
      Rreset = 1'b0;
      Qshift = 1'b0;
      Qload = 1'b0;
      Mload = 1'b0;
      Cup = 1'b0;
      Creset = 1'b0;
      done = 1'b0;

      case (ps)
          waitOnStart1: done = 1'b1;
          waitOnStart0:;
          getInput: begin Rreset = 1'b1; Qload = 1'b1; Mload = 1'b1; Creset = 1'b1; end
          shiftR: Rshift = 1'b1;
          shiftQ: begin Qshift = 1'b1; Rload = 1'b1; end
          countUp: Cup = 1'b1;
      endcase
  end




  input clk, en, reset;
  output reg [3:0] out;

endmodule // end counter
