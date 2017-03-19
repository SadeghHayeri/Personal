[y,Fs] = audioread('voice_noisy.wav');

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
    slow(end+1) = 0;
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

% e & f)
f = fftshift( fft(y) );
absF = abs(f);
plot( n, f );

% g)
noisyLess = f;
for R = 1:l
    if absF(R) < 10000
        noisyLess(R) = f(R);
    else
        noisyLess(R) = 7000;
    end
end
noisyLess = fftshift(noisyLess);
noisyLess = ifft( noisyLess );
plot( (0:length(noisyLess)-1), noisyLess );

% sound( noisyLess, Fs );
% sound( noisyLess, Fs );
audiowrite('noisyLess.wav', noisyLess, Fs);

for R = 1:l
    noisyLess(R) = noisyLess(R) + rand - .5;
end
sound( noisyLess, Fs );
audiowrite('whiteNoise.wav', noisyLess, Fs);


whiteNoise = y;
for R = 1:l
    whiteNoise(R) = rand - .5;
end

whiteNoise = whiteNoise + noisyLess;
plot( n, whiteNoise )


