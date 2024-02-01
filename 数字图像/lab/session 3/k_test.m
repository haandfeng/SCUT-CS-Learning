noise = imread('噪声图像.bmp');
img = noise;
[height,width,~] = size(img);
k = 5;
n = 3;
half_window_size = floor(n/2);
output = uint8(zeros(height - 2*half_window_size,width - 2*half_window_size));
for i=1+half_window_size:height-half_window_size
    for j=1+half_window_size:width-half_window_size
        mask = img(i - half_window_size:i+half_window_size,j-half_window_size:j+half_window_size);
        center = img(i,j);
        [sorted_dis,index] = sort(reshape(abs(uint8(zeros(n,n))+center-mask),1,n*n));
        arraified_mask = reshape(mask,1,n*n);
        k_top_index = index(2:k+1);
        %k_top = arraified_mask(index(2:k+1));
        k_top = uint8(zeros(1,k));
        
        for l=1:k
            k_top(l)=arraified_mask(k_top_index(l));
        end
        output(i - 1,j - 1) = mean(k_top);
    end
end

%imshow(noise);
subplot(1,3,1);
imshow(noise);
title('原图');

subplot(1,3,2);
imshow(output);
title('自己写的');

subplot(1,3,3);
imshow(k_mean_filtering(noise,3,5));
title('网上找的');