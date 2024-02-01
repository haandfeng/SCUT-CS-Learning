img = imread('梯度算子.bmp');
F = img;
[m,n]=size(F); 
G=zeros(m,n); 
H=zeros(m,n); 
w=[0,-1,0;-1,4,-1;0,-1,0]; 
w = [1,1,1;1,-8,1;1,1,1]; 
asdf = 0;
for x=1:m     
    for y=1:n         
        if (x==1||y==1||x==m||y==n)            
            G(x,y)=F(x,y);
            asdf=asdf+1;
        else
            G(x,y)=w(1,1)*F(x-1,y-1)+w(1,2)*F(x-1,y)+w(1,3)*F(x-1,y+1)...                 
                +w(2,1)*F(x,y-1)+w(2,2)*F(x,y)+w(2,3)*F(x,y+1)...                 
                +w(3,1)*F(x+1,y-1)+w(3,2)*F(x+1,y)+w(3,3)*F(x+1,y+1);    
            hm=hadamard_multiple(w,F(x-1:x+1,y-1:y+1));
            if(G(x,y)==sum(hm(:)))
                asdf=asdf+1;
            else
                fprintf('jjj');
            end
        end
    end
end
figure 
subplot(121) 
imshow(F) 
title('原始图像'); 
subplot(122) 
imshow(uint8(G)); 
title('拉普拉斯算子处理后的图像');