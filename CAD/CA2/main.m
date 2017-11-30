size = 300;
testSize = 5;

P = zeros(1, size);
T = zeros(1, size);
for i = 1:size;
    P(1, i) = rand*100;
    P(2, i) = rand*100;
    P(3, i) = rand*100;
    
    T(i) = myfunc(P(1, i), P(2, i), P(3, i));
end;

net = newff([0 100; 0 100; 0 100],[10 10 10 1],{'tansig' 'tansig' 'tansig' 'purelin'});
[tnet,tr] = train(net, P, T);
plotperform(tr)

errSum = 0;
for i = 1:testSize;
    a = rand*100;
    b = rand*100;
    c = rand*100;
    
    realAns = myfunc(a, b, c);
    pridictAns = sim(tnet, [a; b; c;]);
    
    err = abs(realAns - pridictAns / realAns);
    errSum = errSum + err;
end;
err = errSum / testSize * 100;
err