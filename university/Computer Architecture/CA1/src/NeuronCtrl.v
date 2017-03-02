
module Controller(clk, rst, start, endFlag, yEqualt, flagEOF, done, ldRegx1, ldRegx2, ldRegT, ldRegW1, ldRegW2, ldRegB, ldRegFlag, counterReset, flagReset);

	parameter [2:0] start = 0, init = 1, getData = 2, calculate = 3, changeWeight = 4, checkEndFlag = 5, resetingCounter = 6;
  reg [2:0] ns = 0, ps = 0;

  always @ ( posedge clk, posedge rst ) begin
    if( rst == 1'b1 )
      ps <= start;
    else
      ps <= ns;
  end

  always @ ( ps ) begin

		done = 1'b0;
		reset = 1'b0;
		ldRegx1 = 1'b0;
		ldRegx2 = 1'b0;
		ldRegT = 1'b0;
		ldRegW1 = 1'b0;
		ldRegW2 = 1'b0;
		ldRegB = 1'b0;
		ldRegFlag = 1'b0;
		counterReset = 1'b0;
		flagReset = 1'b0;


    case (ps)
      start: done = 1;
      init: reset = 1, counterReset = 1, flagReset = 1;
      getData: ldRegx1 = 1, ldRegx2 = 1, ldRegT = 1, counterEn = 1;
			calculate: ldRegFlag = 1;
      changeWeight: ldRegW1 = 1, ldRegW2 = 1, ldRegB = 1;
      checkEndFlag:;
      resetingCounter: counterReset = 1, flagReset = 1;
    endcase

  end

  always @ ( ps, start, counterCarryOut ) begin
    ns = start;
    case (ps)
      start: ns = (start == 1'b1)? init : start;
      init: ns = getData;
      getData: ns = calculate;
			calculate: ns = (!flagEOF == 1'b1) ? ((!yEqualt == 1'b1) ? changeWeight : getData ) : checkEndFlag;
      changeWeight: ns = getData;
      checkEndFlag: ns = (endFlag == 1'b1)? resetingCounter : start;
      resetingCounter: ns = getData;
    endcase
  end

endmodule
