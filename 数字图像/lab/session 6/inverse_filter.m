function [output] = inverse_filter(img)
f = double(img);
g = fft2(f);
g = fftshift(g);
[M,N] = size(g);
k = 80;
for u=1:M
    for v=1:N
        h(u,v) = exp(-k*(((u-M/2)^2+(v-N/2)^2)^(5/6)));
        if(h(u,v)<0.0001)
            f(u,v)=g(u,v)/0.78;
        else
            f(u,v)=g(u,v)/h(u,v);
        end
    end
end
y = ifftshift(f);
y = ifft2(y);
output = uint8(real(y));

end

