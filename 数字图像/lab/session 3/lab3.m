origin = imread('ԭʼͼ��.jpg');
noise = imread('����ͼ��.bmp');

subplot(2,3,1);
imshow(origin);
title('ԭʼͼ��');
 
subplot(2,3,2);
imshow(noise);
title('����ͼ��');

subplot(2,3,4);
imshow(mean_filtering(noise));
title('��ֵ�˲�');

subplot(2,3,5);
imshow(median_filtering(noise));
title('��ֵ�˲�');

subplot(2,3,6);
imshow(k_mean_filtering(noise,3,5));
title('k��ֵ�˲�');