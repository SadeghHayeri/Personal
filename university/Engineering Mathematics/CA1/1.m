n = (0:1000-1);
N = 1000;
X = heaviside(n-200) - heaviside(n-400) + 0.05 * sin( (2*pi)/N * 100 * n ) + 0.1 * cos( (2*pi)/N * 50 * n );

% a)
plot(n, X)

% b)
fX = fftshift( fft(X) )
% plot(n, fX)

% d)
fX(451) = 0;
fX(551) = 0;
fX(401) = 0;
fX(601) = 0;
% plot(n, abs(fX))

% e)
iX = ifft( fftshift(fX) );
plot(n, iX);

% f)
