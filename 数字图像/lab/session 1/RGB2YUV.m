function [YUV] = RGB2YUV(img)
[Y,U,V] = get_YUV(img);
YUV=cat(3,Y,U,V);
end

