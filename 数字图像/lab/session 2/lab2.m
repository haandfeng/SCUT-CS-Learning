img = imread('�Ҷȱ任.bmp');

subplot(3,3,1);
imshow(reverse(img));
title('��ת�任');

subplot(3,3,2);
imshow(logarithmic(img));
title('�����任');

subplot(3,3,3);
imshow(power_law(img));
title('���ɱ任');

gamma_img = imread('٤��У��.bmp');
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
title('�Ҷ�ֱ��ͼ');

