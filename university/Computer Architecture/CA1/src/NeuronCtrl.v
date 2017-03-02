module Controller(clk, rst, reset, start, dataReady, endFlag, yEqualt, flagEOF, done, requestFlag,ldRegx1, ldRegx2, ldRegT, ldRegW1, ldRegW2, ldRegB, ldRegFlag, counterReset, flagReset, counterEn);

	input clk, rst, start, dataReady, endFlag, yEqualt, flagEOF;
	output reg reset, done, requestFlag,ldRegx1, ldRegx2, ldRegT, ldRegW1, ldRegW2, ldRegB, ldRegFlag, counterReset, flagReset, counterEn;

	parameter [2:0] startState = 0, init = 1, requestData = 2, getData = 3, calculate = 4, changeWeight = 5, checkEndFlag = 6, resetingCounter = 7;
  reg [2:0] ns = 0, ps = 0;

  always @ ( posedge clk, posedge rst ) begin
    if( rst == 1'b1 )
      ps <= startState;
    else
      ps <= ns;
  end

  always @ ( ps ) begin

		done <= 1'b0;
		reset <= 1'b0;
		ldRegx1 <= 1'b0;
		ldRegx2 <= 1'b0;
		ldRegT <= 1'b0;
		ldRegW1 <= 1'b0;
		ldRegW2 <= 1'b0;
		ldRegB <= 1'b0;
		ldRegFlag <= 1'b0;
		counterReset <= 1'b0;
		flagReset <= 1'b0;
		requestFlag <= 1'b0;

    case (ps)
      startState: done <= 1;
      init: begin
				reset <= 1;
				counterReset <= 1;
				flagReset <= 1;
			end
			requestData: requestFlag <= 1;
      getData: begin
				ldRegx1 <= 1;
				ldRegx2 <= 1;
				ldRegT <= 1;
				counterEn <= 1;
			end
			calculate: ldRegFlag <= 1;
      changeWeight: begin
				ldRegW1 <= 1;
				ldRegW2 <= 1;
				ldRegB <= 1;
			end
      checkEndFlag:;
      resetingCounter: begin
				counterReset <= 1;
				flagReset <= 1;
			end
    endcase

  end

  always @ ( ps, start ) begin
    ns = startState;
    case (ps)
      startState: ns = (start == 1'b1)? init : startState;
      init: ns = requestData;
			requestData: ns = (dataReady == 1'b1)? getData : requestData;
      getData: ns = calculate;
			calculate: ns = (!flagEOF == 1'b1) ? ((!yEqualt == 1'b1) ? changeWeight : requestData ) : checkEndFlag;
      changeWeight: ns = requestData;
      checkEndFlag: ns = (endFlag == 1'b1)? resetingCounter : startState;
      resetingCounter: ns = requestData;
    endcase
  end

endmodule
