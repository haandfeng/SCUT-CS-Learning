function [out] = median_filtering(img)
res1 = img;
k = 1;
[m,n,~] = size(img);
for i = 1:m
    for j = 1:n
        i1 = max(1,i-k);
        i2 = min(m,i+k);
        j1 = max(1,j-k);
        j2 = min(n,j+k);
        tmp = img(i1:i2,j1:j2);
        v = tmp(1:end);
        v = sort(v);
        res1(i,j) = v(ceil((i2-i1)*(j2-j1)/2));
    end
end
out = res1;
end

