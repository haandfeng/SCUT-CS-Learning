noise = imread('sample5-1.bmp');

part = 4;
subplot(2,4,1);
imshow(noise);
title('‘Î…˘ÕºœÒ');
if(part == 1)
    subplot(2,4,5);
    imshow(gauss_lowpass(noise,10));
    title('Gauss lowpass G0=10');
    subplot(2,4,6);
    imshow(gauss_lowpass(noise,20));
    title('Gauss lowpass G0=20');
    subplot(2,4,7);
    imshow(gauss_lowpass(noise,40));
    title('Gauss lowpass G0=40');
    subplot(2,4,8);
    imshow(gauss_lowpass(noise,80));
    title('Gauss lowpass G0=80');
end
if(part == 2)
    subplot(2,4,5);
    imshow(gauss_highpass(noise,10));
    title('Gauss highpass G0=10');
    subplot(2,4,6);
    imshow(gauss_highpass(noise,20));
    title('Gauss highpass G0=20');
    subplot(2,4,7);
    imshow(gauss_highpass(noise,40));
    title('Gauss highpass G0=40');
    subplot(2,4,8);
    imshow(gauss_highpass(noise,80));
    title('Gauss highpass G0=80');
end
if(part == 3)
    subplot(2,4,5);
    imshow(butterworth_lowpass(noise,10,2));
    title('Butterworth lowpass G0=10 n=2');
    subplot(2,4,6);
    imshow(butterworth_lowpass(noise,20,2));
    title('Butterworth lowpass G0=20 n=2');
    subplot(2,4,7);
    imshow(butterworth_lowpass(noise,40,2));
    title('Butterworth lowpass G0=40 n=2');
    subplot(2,4,8);
    imshow(butterworth_lowpass(noise,80,2));
    title('Butterworth lowpass G0=80 n=2');
end
if(part == 4)
    subplot(2,4,5);
    imshow(butterworth_highpass(noise,10,2));
    title('Butterworth highpass G0=10 n=2');
    subplot(2,4,6);
    imshow(butterworth_highpass(noise,20,2));
    title('Butterworth highpass G0=20 n=2');
    subplot(2,4,7);
    imshow(butterworth_highpass(noise,40,2));
    title('Butterworth highpass G0=40 n=2');
    subplot(2,4,8);
    imshow(butterworth_highpass(noise,80,2));
    title('Butterworth highpass G0=80 n=2');
end
