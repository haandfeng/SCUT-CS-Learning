import os
import cv2
import numpy as np
import matplotlib.pyplot as plt
import math


def read_image(file_path):
    # 读 BMP 图像
    image = cv2.imread(file_path)
    return image


def reverse_transform(img):
    L = 256  # 灰度范围
    result = L - 1 - img
    return np.round(result).astype(int)


def logarithmic_transform(img, c=10):
    h, w, d = img.shape[0], img.shape[1], img.shape[2]
    new_img = np.zeros((h, w, d))
    for i in range(h):
        for j in range(w):
            for k in range(d):
                new_img[i, j, k] = c * (math.log(1.0 + img[i, j, k]))
    new_img = cv2.normalize(new_img, new_img, 0, 255, cv2.NORM_MINMAX)
    new_img = cv2.convertScaleAbs(new_img)
    return new_img.astype(int)


def power_law_transform(img, c=10, gamma=10):
    h, w, d = img.shape[0], img.shape[1], img.shape[2]
    new_img = np.zeros((h, w, d), dtype=np.float32)
    for i in range(h):
        for j in range(w):
            for k in range(d):
                new_img[i, j, k] = c * math.pow(img[i, j, k], gamma)
    cv2.normalize(new_img, new_img, 0, 255, cv2.NORM_MINMAX)
    new_img = cv2.convertScaleAbs(new_img)
    return new_img



def gamma_correction(image, gamma):
    # 伽马校正
    corrected_image = np.power(image / 255.0, 1/gamma) * 255
    cv2.normalize(corrected_image, corrected_image, 0, 255, cv2.NORM_MINMAX)
    corrected_image = cv2.convertScaleAbs(corrected_image)
    return corrected_image


# 读取图像
image_path_original = "grey.bmp"
image_path_gamma = "gamma.bmp"

img_gamma = read_image(image_path_gamma)
img_gamma = cv2.cvtColor(img_gamma, cv2.COLOR_BGR2RGB)

img = read_image(image_path_original)

img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
# 反转变换
reversed_img = reverse_transform(img.copy())

# 对数变换
logarithmic_img = logarithmic_transform(img.copy(), c=10)

# 幂律变换
power_law_img = power_law_transform(img.copy(), c=10, gamma=10)

plt.figure(figsize=(10, 5))
# plt.subplot(2, 3, 1)
# plt.title("Original Image")
# plt.imshow(img)
# plt.show()

plt.subplot(1, 3, 1)
plt.title("Reversed Transform")
plt.imshow(reversed_img)
# plt.show()

plt.subplot(1, 3, 2)
plt.title("Logarithmic Transform")
plt.imshow(logarithmic_img)
# plt.show()

plt.subplot(1, 3, 3)
plt.title("Power Law Transform")
plt.imshow(power_law_img)
plt.show()

plt.figure(figsize=(10, 5))
plt.subplot(1, 3, 1)
plt.title("Gamma_correction 0.4")
plt.imshow(gamma_correction(img_gamma.copy(), 0.4))
plt.subplot(1, 3, 2)
plt.title("Gamma_correction 0.6")
plt.imshow(gamma_correction(img_gamma.copy(), 0.6))
plt.subplot(1, 3, 3)
plt.title("Gamma_correction 0.8")
plt.imshow(gamma_correction(img_gamma.copy(), 0.8))

plt.show()
