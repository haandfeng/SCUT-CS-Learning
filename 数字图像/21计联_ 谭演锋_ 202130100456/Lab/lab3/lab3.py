import numpy as np
import cv2

import numpy as np
import matplotlib.pyplot as plt


def mean_filtering(img):
    res1 = img.copy()
    k = 1
    m, n, _ = img.shape
    for i in range(m):
        for j in range(n):
            i1 = max(0, i - k)
            i2 = min(m - 1, i + k)
            j1 = max(0, j - k)
            j2 = min(n - 1, j + k)
            tmp = img[i1:i2, j1:j2, :]
            s = np.sum(tmp) * (1.0 / (4 * (i2 - i1) * (j2 - j1) + 1))
            res1[i, j, :] = np.uint8(s)

    out = res1
    return out


def median_filtering(img):
    res1 = img.copy()
    k = 1
    m, n, _ = img.shape

    for i in range(m):
        for j in range(n):
            i1 = max(0, i - k)
            i2 = min(m - 1, i + k)
            j1 = max(0, j - k)
            j2 = min(n - 1, j + k)
            tmp = img[i1:i2, j1:j2, :]
            v = tmp.flatten()
            v = np.sort(v)
            res1[i, j, :] = v[int(np.ceil((i2 - i1) * (j2 - j1) / 2))]

    out = res1
    return out


# Load the image in BMP format
image_path = '噪声图像.bmp'
image_path2 = '原始图像.jpg'

image = cv2.imread(image_path)
orgin = cv2.imread(image_path2)

mean_img = mean_filtering(image)
median_img = median_filtering(image)
plt.figure(figsize=(10, 5))
plt.subplot(1, 3, 1)
plt.title("Origin")
plt.imshow(orgin)
plt.subplot(1, 3, 2)
plt.title("Noisy")
plt.imshow(image)
plt.subplot(1, 3, 3)
plt.title("Mean Filter")
plt.imshow(mean_img)

plt.show()

plt.figure(figsize=(10, 5))
plt.subplot(1, 3, 1)
plt.title("Origin")
plt.imshow(orgin)
plt.subplot(1, 3, 2)
plt.title("Noisy")
plt.imshow(image)
plt.subplot(1, 3, 3)
plt.title("Median Filter")
plt.imshow(median_img)

plt.show()
plt.figure(figsize=(10, 5))
plt.subplot(1, 3, 1)
plt.title("Noisy")
plt.imshow(image)
plt.subplot(1, 3, 2)
plt.title("Mean Filter")
plt.imshow(mean_img)

plt.subplot(1, 3, 3)
plt.title("Median Filter")
plt.imshow(median_img)
plt.show()