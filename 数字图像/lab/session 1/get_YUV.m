function [Y,U,V] = get_YUV(img)
R=img(:,:,1);
G=img(:,:,2);
B=img(:,:,3);
Y=0.299*R+0.587*G+0.114*B;
U=0.564*(B-Y);
V=0.713*(R-Y);
end

