function [out] = power_law(img)
C = 10;
gamma = 10;
d(:,:,1) = C*(img(:,:,1).^gamma);
d(:,:,2) = C*(img(:,:,2).^gamma);
d(:,:,3) = C*(img(:,:,3).^gamma);
out = uint8(d);
end

