function [output] = wiener_filter(img)
f = double(img);
g = fft2(f);
g = fftshift(g);
[M,N] = size(g);
k = 0.0025;
for u=1:M
    for v=1:N
        h(u,v) = exp(-k*(((u-M/2)^2+(v-N/2)^2)^(5/6)));
        f(u,v) = (1/h(u,v))*(h(u,v)^2/(h(u,v)^2+k))*g(u,v);
    end
end
y = ifftshift(f);
y = ifft2(y);
output = uint8(real(y));
end

