a = imread('sample6-1.bmp');
subplot(1,3,1);
imshow(a);
title('ԭͼ��');

subplot(1,3,2);
imshow(inverse_filter(a));
title('���˲�');

subplot(1,3,3);
imshow(wiener_filter(a));
title('ά���˲�');
