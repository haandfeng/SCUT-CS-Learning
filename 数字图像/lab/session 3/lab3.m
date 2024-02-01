origin = imread('原始图像.jpg');
noise = imread('噪声图像.bmp');

subplot(2,3,1);
imshow(origin);
title('原始图像');
 
subplot(2,3,2);
imshow(noise);
title('噪声图像');

subplot(2,3,4);
imshow(mean_filtering(noise));
title('均值滤波');

subplot(2,3,5);
imshow(median_filtering(noise));
title('中值滤波');

subplot(2,3,6);
imshow(k_mean_filtering(noise,3,5));
title('k均值滤波');