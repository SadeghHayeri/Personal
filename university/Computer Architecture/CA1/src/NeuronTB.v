module TestBench;
  reg signed [6:0] x1Input, x2Input;
  reg signed [1:0] tInput;
  reg clk = 1'b1, start;
  integer n = 0, i;
  reg [31:0] nInput;
  //clk, rst, nInput, x1Input, x2Input, tInput,      dataReady, requestFlag, done, w1, w2, b
  wire signed [13:0] w1, w2, b;
  wire done, dataReady, requestFlag;

  Neuron N(clk, rst, nInput, x1Input, x2Input, tInput, dataReady, requestFlag, done, w1, w2, b);

  reg signed [6:0] X1Inputs[500:0];
  reg signed [6:0] X2Inputs[500:0];
  reg signed [1:0] tInputs[500:0];
  reg signed [6:0] capturedX1, capturedX2;
  reg signed [1:0] capturedt;
  integer file;
  // setting clock to pulse every 100ns
  initial repeat(500) begin
    #50
    clk = ~clk ;
  end

  initial begin
    file = $fopen("data_set_s.txt", "r");
    $stop;
    while(!$feof(file)) begin
      $fscanf(file, "%b %b %b", capturedX1, capturedX2, capturedt);
      X1Inputs[n] <= capturedX1;
      X2Inputs[n] <= capturedX2;
      tInputs[n] <= capturedt;
      n = n + 1;
    end
    nInput <= n[31:0];
  end


  initial begin
    reset <= 1'b1;
    #100
    reset <= 1'b0;
    start <= 1'b1;
    #100
    while(!done) begin
        i = 0;
        while(i<n) begin
          if(requestFlag) begin
            x1Input <= X1Inputs[i];
            x2Input <= X2Inputs[i];
            tInput <= tInputs[i];
            i = i + 1;
            dataReady <= 1'b1;
            // $display("jallaaaaaal %d %d", n, i);
            #100
          end
          if(i == n)
            i = 0;
          dataReady <= 1'b0;
        end
    end
    $stop;
  end

endmodule
