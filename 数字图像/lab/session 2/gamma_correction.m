function [out] = gamma_correction(img,rate)
img = double(img) / 256.0;
out = uint8(img.^(1/rate).*256.0);
end

