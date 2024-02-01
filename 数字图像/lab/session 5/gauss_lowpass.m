function [y] = gauss_lowpass(img,d0)
f=double(img);
g=fft2(f);
g=fftshift(g);
[M,N] = size(g);
m=fix(M/2);
n=fix(N/2);
for i=1:M
   for j=1:N
       d=sqrt((i-m)^2+(j-n)^2);
       if (d==0)
          h=0;
       else
          h=exp(-(d^2)/(2*(d0^2)));
       end
       y(i,j)=h*g(i,j);
    end
end
y=ifftshift(y);
y=ifft2(y);
y=uint8(real(y));
end

