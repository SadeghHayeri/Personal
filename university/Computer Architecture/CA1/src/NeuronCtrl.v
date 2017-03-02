
module Controller( input , output reg  );

	parameter [2:0] start = 0, init = 1, getData = 2, changeWeight = 3, doneCheck = 4, flagReset = 5;
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
		ldRegx1 = 1'b0;
		ldRegx2 = 1'b0;
		ldRegT = 1'b0;
		ldRegW1 = 1'b0;
		ldRegW2 = 1'b0;
		ldRegFlag = 1'b0;

    case (ps)
      start: done = 1;
      init: reset = 1 ;
      getData: ldRegx1 = 1 , ldRegx2 = 1 , ldRegT = 1;
      changeWeight: ldRegW1 = 1 , ldRegW2 = 1 , ldRegB = 1;
      doneCheck: counterReset = 1;
      flagReset: ;
    endcase

  end

  always @ ( ps, start, counterCarryOut ) begin
    ns = start;
    case (ps)
      start: ns = (start == 1'b1)? waitOnStart0 : waitOnStart1;
      init: ns = ;
      getData: ns = ;
      changeWeight: ns = ;
      doneCheck: ns = ;
      reset: ns = ;
    endcase
  end

endmodule
