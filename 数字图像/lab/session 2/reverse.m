function [out] = reverse(img)
b(:,:,1) = 255 - img(:,:,1);
b(:,:,2) = 255 - img(:,:,2);
b(:,:,3) = 255 - img(:,:,3);
out = uint8(b);
end

