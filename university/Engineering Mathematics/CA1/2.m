[y,Fs] = audioread('voice_noisy.wav');

% a)
% sound(y,Fs);

% b)
l = length(y);
n = (0:l-1);
% plot(n, y)

% c)
slow = 0;
for R = 1:l
    slow(end+1) = y(R);
    slow(end+1) = y(R);
end
% plot( (0:length(slow)-1) , slow)
% sound(slow, Fs);

% d)
fast = 0;
for R = 1:l
    if mod(R,2) == 0
        fast(end+1) = y(R);
    end
end
% plot( (0:length(fast)-1) , fast);
% sound(fast, Fs)

% e)
f = fftshift( fft(y) );
absF = abs(f);

noisyLess = 0;
for R = 1:l
    if absF(R) < 10000
        noisyLess(end+1) = absF(R);
    else
        noisyLess(end+1) = 0.000;
    end
end
% plot( (0:length(noisyLess)-1), noisyLess);

% noisyLess = fftshift(noisyLess);
% noisyLess = ifft( noisyLess );
% sound( noisyLess, Fs );
plot( (0:length(noisyLess)-1), noisyLess);

% http://stackoverflow.com/questions/24195089/remove-noise-from-wav-file-matlabs
