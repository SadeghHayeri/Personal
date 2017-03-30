[y,Fs] = audioread('voice_noisy.wav');

% a)
sound(y,Fs);

% b)
l = length(y);
n = (0:l-1);    % [0, 1, 2, 3, ..., length(y)]
plot(n, y)

% c)
slow = [];
slowTime = 2;   % you can change this and make it slower

for R = 1:l
    for K = 1:slowTime
        slow(end+1) = y(R); % add this variable 'slowTime' times
    end
end
plot( (0:length(slow)-1) , slow)
sound(slow, Fs);

% d)
fast = [];
fastTime = 2;   % you can change this and make it faster

for R = 1:l
    if mod(R,fastTime) == 0
        fast(end+1) = y(R); % add this variable every 'fastTime' times
    end
end
plot( (0:length(fast)-1) , fast);
sound(fast, Fs)

% e & f)
f = fftshift( fft(y) );
absF = abs(f);
plot( n, f );

% g - 1)
fftNoisyLess = f;
for R = 1:l
    if absF(R) < 8000   
        fftNoisyLess(R) = f(R); % only smaller than 8000
    else
        fftNoisyLess(R) = 0;    % if variable is bigger than 8000 make it 0
    end
end

% g - 2)
% fftNoisyLess = filter(myFilter, f);  % deComment this line to use filter

% h)
noisyLess = ifft( fftshift(fftNoisyLess) );
plot( (0:length(noisyLess)-1), noisyLess );

% i)
sound( noisyLess, Fs );

% j)
audiowrite('noisyLess.wav', noisyLess, Fs);

% Q3)
whiteNoise = noisyLess;
for R = 1:l
    whiteNoise(R) = rand - .5;  % generate whiteNoise sound
end
whiteNoise = whiteNoise + noisyLess;    % combine together

sound( whiteNoise, Fs );
audiowrite('whiteNoise.wav', whiteNoise, Fs);

