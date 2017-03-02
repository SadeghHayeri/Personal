module Controller(clk, rst, start, dataReady, endFlag, yEqualt, flagEOF, done, requestFlag,ldRegx1, ldRegx2, ldRegT, ldRegW1, ldRegW2, ldRegB, ldRegFlag, counterReset, flagReset);

	input clk, rst, start, dataReady, endFlag, yEqualt, flagEOF;
	output done, requestFlag,ldRegx1, ldRegx2, ldRegT, ldRegW1, ldRegW2, ldRegB, ldRegFlag, counterReset, flagReset;

	parameter [2:0] start = 0, init = 1, requestData = 2, getData = 3, calculate = 4, changeWeight = 5, checkEndFlag = 6, resetingCounter = 7;
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
		requestFlag = 1'b0;

    case (ps)
      start: done = 1;
      init: reset = 1, counterReset = 1, flagReset = 1;
			requestData: requestFlag = 1;
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
      init: ns = requestData;
			requestData: ns = (dataReady == 1'b1)? getData : requestData;
      getData: ns = calculate;
			calculate: ns = (!flagEOF == 1'b1) ? ((!yEqualt == 1'b1) ? changeWeight : requestData ) : checkEndFlag;
      changeWeight: ns = requestData;
      checkEndFlag: ns = (endFlag == 1'b1)? resetingCounter : start;
      resetingCounter: ns = requestData;
    endcase
  end

endmodule
