img = imread('梯度算子.bmp');
f1 = [0,1,0;1,-4,1;0,1,0]; 
f2 = [1,1,1;1,-8,1;1,1,1]; 
img = im2double(img);
subplot(2,3,1);
imshow(img);
title('原图');

subplot(2,3,2);
imshow(laplacian_sharpening(img,f1));
title('F1拉普拉斯滤波');

subplot(2,3,3);
imshow(img-laplacian_sharpening(img,f1));
title('F1锐化后');

subplot(2,3,4);
imshow(img);
title('原图');

subplot(2,3,5);
imshow(laplacian_sharpening(img,f2));
title('F2拉普拉斯滤波');

subplot(2,3,6);
imshow(img - laplacian_sharpening(img,f2));
title('F2锐化后');