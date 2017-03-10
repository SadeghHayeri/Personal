[y,Fs] = audioread('noisy.wav');

% a)
% sound(y,Fs);

% b)
l = length(y);
n = (0:l-1);
plot(n, y)

% c)
slow = 0;
for R = 1:l
    slow(end+1) = y(R);
    slow(end+1) = y(R);
end
plot( (0:length(slow)-1) , slow)
% sound(slow, Fs);

% d)
fast = 0;
for R = 1:l
    if mod(R,2) == 0
        fast(end+1) = y(R);
    end
end
plot( (0:length(fast)-1) , fast);
% sound(fast, Fs)

% e)
f = fftshift( fft(y) );

ff = fft(y);
test = 0;
for R = 1:l
    if ff(R) < 10 && ff(R) > -10
        test(end+1) = ff(R);
    end
end
plot( (0:length(test)-1) , test);
test2 = ifft( test );
plot( (0:length(test2)-1) , test2);
% sound( test2, Fs );

plot( n, ff );


http://stackoverflow.com/questions/24195089/remove-noise-from-wav-file-matlabs
