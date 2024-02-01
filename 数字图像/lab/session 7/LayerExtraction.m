function [output] = LayerExtraction(img,pos_x,pos_y,w,isAccept)
if(isAccept~=0 && isAccept~=1)
    error('参数错误！isAccept应该为0或1！');
end
img = double(img);
a = [0, 0, 0];
a(1) = img(pos_x, pos_y, 1);
a(2) = img(pos_x, pos_y, 2);
a(3) = img(pos_x, pos_y, 3);
a = a / 255;
B = img / 255.0;
m = size(img);
for i=1:m(1)
    for j=1:m(2)
        if(isAccept == 0)
             if(abs(B(i, j, 1) - a(1)) <= w / 2 && abs(B(i, j, 2) - a(2)) <= w / 2 && abs(B(i, j, 3) - a(3)) <= w / 2)
                  B(i, j, 1) = 0.5;
                  B(i, j, 2) = 0.5;
                  B(i, j, 3) = 0.5;
             end
        else
            if(abs(B(i, j, 1) - a(1)) > w / 2 || abs(B(i, j, 2) - a(2)) > w / 2 || abs(B(i, j, 3) - a(3)) > w / 2)
                  B(i, j, 1) = 0.5;
                  B(i, j, 2) = 0.5;
                  B(i, j, 3) = 0.5;
            end
        end
    end
end

output = uint8(B * 255.0);
end

