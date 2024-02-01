function [RGB] = set_contrast(img)
a=100;
b=160;
c=50;
d=200;
[Y,U,V] = get_YUV(img);
[height,width,~] = size(img);
Y3=Y;
for i=1:height
    for j=1:width
        if (Y(i,j)>b)
            Y3(i,j)=d;
        elseif (Y(i,j)<a)
            Y3(i,j)=c;
        else
            Y3(i,j)=((double(d-c))/(double(b-a)))*(Y(i,j)-a)+c;
        end
    end
end
R=Y3+1.402*V;
G=Y3-0.344*U-0.714*V;
B=Y3+1.772*U;
RGB = uint8(cat(3,R,G,B));
end

