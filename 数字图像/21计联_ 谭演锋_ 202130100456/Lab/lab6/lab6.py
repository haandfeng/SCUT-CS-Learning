import cv2
import numpy as np
from numpy.fft import fft2, ifft2, fftshift, ifftshift
import matplotlib.pyplot as plt

def read_image(file_path):
    # 读取图像文件
    return cv2.imread(file_path, cv2.IMREAD_GRAYSCALE)


def fourier_transform(image):
    # 进行二维Fourier变换
    return fftshift(fft2(image))


def inverse_fourier_transform(fourier_image):
    # 进行二维Fourier反变换
    img1 = np.abs(ifft2(ifftshift(fourier_image)))
    img1 = np.uint8(np.clip(img1, 0, 255))
    return img1


def frequency_domain_inverse_filter(fourier_image, k):
    # 频域逆滤波
    rows, cols = fourier_image.shape
    center_row, center_col = rows // 2, cols // 2

    u, v = np.meshgrid(np.arange(rows) - center_row, np.arange(cols) - center_col)
    H = np.exp(-80 * (u ** 2 + v ** 2) ** (5 / 6))
    H[H < 0.0001] = 0.78
    # 频域逆滤波
    result = fourier_image / H
    return result


def wiener_filter(fourier_image, k):
    # 维纳滤波
    rows, cols = fourier_image.shape
    center_row, center_col = rows // 2, cols // 2

    u, v = np.meshgrid(np.arange(rows) - center_row, np.arange(cols) - center_col)
    H = np.exp(-0.0025 * (u ** 2 + v ** 2) ** (5 / 6))

    # 维纳滤波
    result = (1 / H) * (np.abs(H) ** 2 / (np.abs(H) ** 2 + 0.0025)) * fourier_image
    return result


# 读取图像
image_path = "sample6-1.bmp"
original_image = read_image(image_path)

# 进行二维Fourier变换
fourier_transformed_image = fourier_transform(original_image)

# 频域逆滤波和维纳滤波
# k_value = 0.01
inverse_filtered_image = inverse_fourier_transform(frequency_domain_inverse_filter(fourier_transformed_image, 0.0025))
wiener_filtered_image = inverse_fourier_transform(wiener_filter(fourier_transformed_image, 0.0025))

# 显示结果
# cv2.imshow("Original Image", original_image)
# cv2.imshow("Inverse Filtered Image", inverse_filtered_image.astype(np.uint8))
# cv2.imshow("Wiener Filtered Image", wiener_filtered_image.astype(np.uint8))
# cv2.waitKey(0)
# cv2.destroyAllWindows()

plt.subplot(1, 2, 1)
plt.title("Origin Image")
plt.imshow(original_image, cmap='gray')

plt.subplot(1, 2, 2)
plt.title("Inverse Filtered Image")
plt.imshow(inverse_filtered_image, cmap='gray')

plt.show()

plt.subplot(1, 2, 1)
plt.title("Origin Image")
plt.imshow(original_image, cmap='gray')

plt.subplot(1, 2, 2)
plt.title("Wiener Filtered Image")
plt.imshow(wiener_filtered_image, cmap='gray')

plt.show()