function [out] = laplacian_sharpening(img,f)
[r,c,~] = size(img);
out = zeros(r,c);
img = im2double(img);
for x=1:r
    for y=1:c
        if (x==1||y==1||x==r||y==c)
            out(x,y)=img(x,y);
        else
            out(x,y)=f(1,1)*img(x-1,y-1)+f(1,2)*img(x-1,y)+f(1,3)*img(x-1,y+1)...
                +f(2,1)*img(x,y-1)+f(2,2)*img(x,y)+f(2,3)*img(x,y+1)...
                +f(3,1)*img(x+1,y-1)+f(3,2)*img(x+1,y)+f(3,3)*img(x+1,y+1);    
        end
    end
end
%out = uint8(out);
% adj = im2double(padarray(img,[1,1],'replicate'));
% for i = 2:r+1
%     for j =2:c+1
%         %window = double(adj(i-1:i+1,j-1:j+1));
%         out(i-1,j-1)=f(1,1)*adj(i-1,j-1)+f(1,2)*adj(i-1,j)+f(1,3)*adj(i-1,j+1)...                 
%                  +f(2,1)*adj(i,j-1)+f(2,2)*adj(i,j)+f(2,3)*adj(i,j+1)...
%                  +f(3,1)*adj(i+1,j-1)+f(3,2)*adj(i+1,j)+f(3,3)*adj(i+1,j+1); 
%     end
% end
%out=uint16(out);
end

