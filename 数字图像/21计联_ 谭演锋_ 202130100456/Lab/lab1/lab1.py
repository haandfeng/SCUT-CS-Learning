import cv2
import numpy as np
import matplotlib.pyplot as plt


def read_bmp_image(file_path):
    # 读 BMP 图像
    image = cv2.imread(file_path)
    return image


def manipulate_color(image):
    # 提取 RGB 通道
    red = image[:, :, 2]
    green = image[:, :, 1]
    blue = image[:, :, 0]
    zeros = np.zeros(image.shape[:2], dtype="uint8")  # 创建与image相同大小的零矩阵
    # 交换 red 和 blue 通道
    red_img = cv2.merge([red, zeros, zeros])
    blue_img = cv2.merge([zeros, zeros, blue])
    green_img = cv2.merge([zeros, green, zeros])
    return red_img, blue_img, green_img


def yuv_to_rgb(image):
    y = image[:, :, 0]
    u = image[:, :, 1]
    v = image[:, :, 2]
    # print(image)
    r = y + 1.402 * v
    g = y - 0.344 * u - 0.714 * v
    b = y + 1.772 * u
    rgb_image = np.round(cv2.merge([r, g, b])).astype(int)
    return rgb_image


def rgb_to_yuv(image):
    R = image[:, :, 2]
    G = image[:, :, 1]
    B = image[:, :, 0]
    y = 0.299 * R + 0.587 * G + 0.114 * B
    u = -0.14713 * R - 0.288862 * G + 0.436 * B
    v = 0.615 * R - 0.51498 * G - 0.10001 * B
    yuv_image = cv2.merge([y, u, v])
    return yuv_image


def adjust_brightness(image, factor):
    image[:, :, 0] *= factor
    return image


def check(image):
    x, y, z = image.shape
    for i in range(x):
        for j in range(y):
            for k in range(z):
                if image[i, j, k] < 0:
                    image[i, j, k] = 0
                elif image[i, j, k] > 255:
                    image[i, j, k] = 255
    return image


def adjust_contrast(image, a, b, c, d):
    x, y1, z = image.shape
    y = image[:, :, 0]
    u = image[:, :, 1]
    v = image[:, :, 2]
    y2 = y.copy()
    for i in range(x):
        for j in range(y1):
            if y[i, j] > b:
                y2[i, j] = d
            elif y[i, j] < a:
                y2[i, j] = c
            else:
                y2[i, j] = ((float(d - c)) / (float(b - a))) * (y[i, j] - a) + c
    yuv2_image = cv2.merge([y2, u, v])
    return yuv2_image


# Step 1: 读图
file_path = 'lena.bmp'
original_image = read_bmp_image(file_path)
# Step 2: Manipulate color (example: swap red and blue channels)
red_img, blue_img, green_img = manipulate_color(original_image.copy())

# Step 3: rgb2yuv
yuv_image = rgb_to_yuv(original_image.copy())

# 通过Y（亮度）通道作灰度的线性变换，改变数字图像的对比度
brightness_adjusted_image = adjust_brightness(yuv_image.copy(), 0.5)

# Example: increase contrast by 50%
contrast_adjusted_image = adjust_contrast(yuv_image.copy(), 100, 160, 50, 200)

# 结果
plt.figure(figsize=(12, 8))

plt.subplot(1, 4, 1)
plt.imshow(cv2.cvtColor(original_image, cv2.COLOR_BGR2RGB))
plt.title('Original Image')
plt.subplot(1, 4, 2)
plt.imshow(red_img)
plt.title('Red channel Image')
plt.subplot(1, 4, 3)
plt.imshow(green_img)
plt.title('Green channel Image')
plt.subplot(1, 4, 4)
plt.imshow(blue_img)
plt.title('Blue channel Image')
# plt.savefig('ManipulatedRGB.png')
plt.show()

plt.imshow(check(yuv_image).astype(int))
plt.title('yuv_image')
plt.show()

plt.imshow(check(yuv_to_rgb(brightness_adjusted_image)))
plt.title('Brightness Adjusted Image')
plt.show()

plt.imshow(check(yuv_to_rgb(contrast_adjusted_image)))
plt.title('Contrast Adjusted Image')
plt.show()
