function [ res ] = myfunc(a, b, c)
    res = (-b + sqrt(abs(b^2 - 4*a * c)) / (2*a * sin(a*pi/180)));
end