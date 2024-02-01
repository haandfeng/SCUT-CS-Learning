function [output] = k_mean_filtering(img,n,k)
[height,width,~] = size(img);
half_window_size = floor(n/2);
output = uint8(zeros(height - 2*half_window_size,width - 2*half_window_size));
for i=1+half_window_size:height-half_window_size
    for j=1+half_window_size:width-half_window_size
        mask = img(i - half_window_size:i+half_window_size,j-half_window_size:j+half_window_size);
        center = img(i,j);
        [~,index] = sort(reshape(abs(uint8(zeros(n,n))+center-mask),1,n*n));
        arraified_mask = reshape(mask,1,n*n);
        k_top_index = index(2:k+1);
        k_top = uint8(zeros(1,k));
        
        for l=1:k
            k_top(l)=arraified_mask(k_top_index(l));
        end
        output(i - 1,j - 1) = mean(k_top);
    end
end
end

