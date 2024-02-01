lena = imread('lena.bmp');
red = get_channel(lena,1);
green = get_channel(lena,2);
blue = get_channel(lena,3);
subplot(2,3,1);
imshow(red);
title('Red Channel');
subplot(2,3,2);
imshow(green);
title('Green Channel');
subplot(2,3,3);
imshow(blue);
title('Blue Channel');

YUV = RGB2YUV(lena);
subplot(2,3,4);
imshow(YUV);
title('YUV image');

half_brightness = set_brightness(lena,0.5);
subplot(2,3,5);
imshow(half_brightness);
title('0.5 brightness image');

contrast_img = set_contrast(lena);
subplot(2,3,6);
imshow(contrast_img);
title('contrast image');


