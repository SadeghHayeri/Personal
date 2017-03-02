module NeuronTB;
  reg signed [6:0] x1Input, x2Input;
  reg signed [1:0] tInput;
  reg clk = 1'b1, start;
  integer n = 0, i;
  reg [31:0] nInput;
  wire signed [13:0] w1, w2, b;
  wire done, requestFlag;
  reg dataReady, rst;

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
    file = $fopen("data_set.txt", "r");
    while(!$feof(file)) begin
      $fscanf(file, "%b %b %b", capturedX1, capturedX2, capturedt);
      X1Inputs[n] <= capturedX1;
      X2Inputs[n] <= capturedX2;
      tInputs[n] <= capturedt;
      n = n + 1;
    end
    $display("jalal %d", n);
    $stop;
    nInput <= n[31:0];
  end


  initial begin
    rst <= 1'b1;
    #100
    rst <= 1'b0;
    start <= 1'b1;
    #100
    while(!done) begin
        i = 0;
        $stop;
        while(i<n) begin
          if(requestFlag) begin
            $stop;
            x1Input <= X1Inputs[i];
            x2Input <= X2Inputs[i];
            tInput <= tInputs[i];
            i = i + 1;
            dataReady <= 1'b1;
            // $display("jallaaaaaal %d %d", n, i);
            #100;
          end
          if(i == n)
            i = 0;
          dataReady <= 1'b0;
        end
    end
    $stop;
  end

endmodule
