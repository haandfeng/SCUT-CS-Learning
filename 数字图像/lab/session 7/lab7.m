img = imread('sample7-1.bmp');
subplot(1,3,1);
imshow(img);
title('ԭͼ');

subplot(1,3,2);
imshow(LayerExtraction(img,10,10,0.2549*3,0));
title('ȥ������');

% subplot(2,3,3);
% imshow(LayerExtraction(img,10,10,0.2549*3,1));
% title('ֻ��������');

% subplot(2,3,4);
% imshow(LayerExtraction(img,80,120,0.2549*2.2,0));
% title('ȥ��Ƥ��');

subplot(1,3,3);
imshow(LayerExtraction(img,80,120,0.2549*2.2,1));
title('ֻ����Ƥ��');