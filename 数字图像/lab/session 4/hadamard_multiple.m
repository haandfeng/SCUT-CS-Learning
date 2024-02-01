function [out] = hadamard_multiple(A,B)
[r,c,~] = size(A);
if(sum(size(A) == size(B)) ~= 2)
    error('两矩阵大小不同！');
else
    out = zeros(r,c);
    for i=1:r
        for j=1:c
            out(i,j) = double(A(i,j))*double(B(i,j));
        end
    end
end
end

