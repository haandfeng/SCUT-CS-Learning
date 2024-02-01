img = imread('sample7-1.bmp');
subplot(1,3,1);
imshow(img);
title('原图');

subplot(1,3,2);
imshow(LayerExtraction(img,10,10,0.2549*3,0));
title('去除背景');

% subplot(2,3,3);
% imshow(LayerExtraction(img,10,10,0.2549*3,1));
% title('只保留背景');

% subplot(2,3,4);
% imshow(LayerExtraction(img,80,120,0.2549*2.2,0));
% title('去除皮肤');

subplot(1,3,3);
imshow(LayerExtraction(img,80,120,0.2549*2.2,1));
title('只保留皮肤');