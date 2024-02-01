function [RGB] = set_brightness(img,rate)
[Y,U,V] = get_YUV(img);
Y=rate*Y;
R=Y+1.402*V;
G=Y-0.344*U-0.714*V;
B=Y+1.772*U;
RGB=uint8(cat(3,R,G,B));
end

