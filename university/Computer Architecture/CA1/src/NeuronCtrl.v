
module Controller(clk, rst, start, dataReady, endFlag, yEqualt, flagEOF, done, requestFlag, ldRegN, ldRegx1, ldRegx2, ldRegT, ldRegW1, ldRegW2, ldRegB, ldRegFlag, counterReset, flagReset, counterEn, reset, nReset);
				 //(clk, rst, start, dataReady, endFlag, yEqualt, flagEOF, done, requestFlag, ldRegN, ldRegx1, ldRegx2, ldRegT, ldRegW1, ldRegW2, ldRegB, ldRegFlag, counterReset, flagReset, counterEn, reset, nReset);
	input clk, rst, start, dataReady, endFlag, yEqualt, flagEOF;
	output reg reset, nReset, done, requestFlag, ldRegN, ldRegx1, ldRegx2, ldRegT, ldRegW1, ldRegW2, ldRegB, ldRegFlag, counterReset, flagReset, counterEn;

	parameter [2:0] startState = 0, init = 1, requestData = 2, getData = 3, calculate = 4, changeWeight = 5, checkEndFlag = 6, resetingCounter = 7;
  reg [2:0] ns = 0, ps = 0;

  always @ ( posedge clk, posedge rst ) begin
    if( rst == 1'b1 )
      ps <= startState;
    else
      ps <= ns;
  end

  always @ ( * ) begin

		done <= 0;
		reset <= 0;
		nReset <= 0;
		ldRegx1 <= 0;
		ldRegx2 <= 0;
		ldRegT <= 0;
		ldRegW1 <= 0;
		ldRegW2 <= 0;
		ldRegB <= 0;
		ldRegFlag <= 0;
		counterReset <= 0;
		flagReset <= 0;
		requestFlag <= 0;
		counterEn <= 0;
		ldRegN <= 0;

    case (ps)
      startState: begin
				done <= 1;
				nReset <= 1;
			end
      init: begin
				reset <= 1;
				counterReset <= 1;
				flagReset <= 1;
				ldRegN <= 1;
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
				counterEn <= 1;
				flagReset <= 1;
			end
    endcase

  end

  always @ ( * ) begin
    ns = startState;
    case (ps)
      startState: ns = (start == 1) ? init : startState;
      init: ns = requestData;
			requestData: ns = (dataReady == 1) ? getData : requestData;
      getData: ns = calculate;
			calculate: ns = (!flagEOF == 1) ? ((!yEqualt == 1) ? changeWeight : requestData ) : checkEndFlag;
      changeWeight: ns = requestData;
      checkEndFlag: ns = (endFlag == 1) ? resetingCounter : startState;
      resetingCounter: ns = requestData;
    endcase
  end

endmodule
