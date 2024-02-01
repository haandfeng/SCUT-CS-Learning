function [out] = mean_filtering(img)
res1 = img;
k = 1;
[m,n,~] = size(img);
img=int16(img);
for i = 1:m
    for j = 1:n
        i1 = max(1,i-k);
        i2 = min(m,i+k);
        j1 = max(1,j-k);
        j2 = min(n,j+k);
        tmp = img(i1:i2,j1:j2);
        %s = sum(tmp(:)) * (1.0/(4*(i2-i1)*(j2-j1)+1));
        s = sum(tmp(:)) * (1.0/((i2-i1+1)*(j2-j1+1)));
        res1(i,j) = uint8(s);
    end
end
out = res1;
end

