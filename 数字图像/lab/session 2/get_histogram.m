function [out] = get_histogram(img)
[height,width,~] = size(img);
histogram = zeros(1,256);
for i=1:height
    for j=1:width
        k= img(i,j);
        histogram(k+1)= histogram (k+1)+1;
     end
end
out = histogram;
end

