function [y] = butterworth_highpass(img,d0,nn)
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
          h=1/(1+(d0/d)^(2*nn));
       end
       y(i,j)=h*g(i,j);
    end
end
y=ifftshift(y);
y=ifft2(y);
y=uint8(real(y));
end

