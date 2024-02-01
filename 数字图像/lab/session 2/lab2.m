img = imread('灰度变换.bmp');

subplot(3,3,1);
imshow(reverse(img));
title('反转变换');

subplot(3,3,2);
imshow(logarithmic(img));
title('对数变换');

subplot(3,3,3);
imshow(power_law(img));
title('幂律变换');

gamma_img = imread('伽马校正.bmp');
subplot(3,3,4);
imshow(gamma_correction(gamma_img,0.4));
title('gamma with 0.4');

subplot(3,3,5);
imshow(gamma_correction(gamma_img,0.6));
title('gamma with 0.6');

subplot(3,3,6);
imshow(gamma_correction(gamma_img,0.8));
title('gamma with 0.8');

subplot(3,3,7);
bar(get_histogram(img));
title('灰度直方图');

