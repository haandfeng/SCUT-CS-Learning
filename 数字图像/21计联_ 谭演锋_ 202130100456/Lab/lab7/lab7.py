import cv2
import numpy as np
import matplotlib.pyplot as plt


def read_image(file_path):
    # 读取图像文件
    return cv2.imread(file_path)


def calculate_average_color(image, region_mask):
    # 根据给定的掩码计算图像中某个区域的平均颜色值
    masked_image = cv2.bitwise_and(image, image, mask=np.uint8(region_mask))
    average_color = np.mean(masked_image, axis=(0, 1))
    return average_color


def color_layering(image):
    # 对图像进行颜色分层处理
    # 创建大小为 220x160 的布尔数组
    a = np.zeros((220, 160), dtype=bool)

    # 将数组的所有元素设置为 True
    a.fill(False)
    b = np.zeros((220, 160), dtype=bool)

    # 将数组的所有元素设置为 True
    b.fill(False)

    for x in range(220):
        for y in range(160):
            if image[x][y][0] > 230 and image[x][y][2] < 120 and image[x][y][1] > 150:
                a[x][y] = True
            if image[x][y][0] > 120 and image[x][y][2] > 120 and image[x][y][1] > 150:
                b[x][y] = True

    return a, b


def remove_background(image, background_mask):
    # 根据背景掩码去除图像背景
    result = np.copy(image)
    result[background_mask] = [127, 127, 127]
    return result


def extract_skin(image, skin_mask):
    # 根据皮肤掩码提取图像皮肤区域
    result = np.copy(image)
    result[~skin_mask] = [127, 127, 127]
    return result


# 读取彩色图像
image_path = "sample7-1.bmp"
original_image = read_image(image_path)

layer_mask1, layer_mask2 = color_layering(original_image)
# 去除背景
image_without_background = remove_background(original_image, layer_mask1)

# 提取皮肤区域
skin_extraction_result1 = extract_skin(original_image, layer_mask2)

plt.figure(figsize=(10, 5))
plt.subplot(1, 3, 1)
plt.title("Origin")
plt.imshow(cv2.cvtColor(original_image, cv2.COLOR_BGR2RGB))

plt.subplot(1, 3, 2)
plt.title("Image Without background")
plt.imshow(cv2.cvtColor(image_without_background, cv2.COLOR_BGR2RGB))

plt.subplot(1, 3, 3)
plt.title("Skin Extraction Result")
plt.imshow(cv2.cvtColor(skin_extraction_result1, cv2.COLOR_BGR2RGB))
plt.show()
