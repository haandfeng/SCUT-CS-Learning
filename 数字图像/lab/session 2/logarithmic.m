function [out] = logarithmic(img)
C = 10;
c(:,:,1) = C*log(double(1 + img(:,:,1)));
c(:,:,2) = C*log(double(1 + img(:,:,2)));
c(:,:,3) = C*log(double(1 + img(:,:,3)));
out = uint8(c);
end

