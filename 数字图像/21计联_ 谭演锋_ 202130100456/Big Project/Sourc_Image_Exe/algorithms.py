import numpy as np
import cv2
from PIL import Image, ImageEnhance
import math
import matplotlib.pyplot as plt

def assign(num):
    if num >= 255:
        return 255
    elif num < 0:
        return 0
    else:
        return num


def laplaceSharpen(imarray, method="enhance"):
    edge = 1
    KERNEL = np.array([[0, 1, 0],
                       [1, -4, 1],
                       [0, 1, 0]])
    if len(imarray.shape) == 3:
        height, width, _ = imarray.shape
        if _ == 4:
            imarray = imarray[:, :, :3]
    else:
        height, width = imarray.shape
        imarray = np.expand_dims(imarray, axis=2)
        imarray = np.concatenate((imarray, imarray, imarray), axis=-1)

    new_arr = np.zeros((height, width, 3))
    for i in range(height):
        for j in range(width):
            if i <= edge - 1 or i >= height - 1 - edge or j <= edge - 1 or j >= width - edge - 1:
                new_arr[i, j] = 0
            else:
                num = imarray[i - edge: i + edge + 1, j - edge: j + edge + 1]
                if method == "enhance":
                    new_arr[i][j][0] = assign(imarray[i][j][0] - np.sum(num[:, :, 0] * KERNEL))
                    new_arr[i][j][1] = assign(imarray[i][j][1] - np.sum(num[:, :, 1] * KERNEL))
                    new_arr[i][j][2] = assign(imarray[i][j][2] - np.sum(num[:, :, 2] * KERNEL))
                if method == "edge":
                    new_arr[i][j][0] = assign(np.sum(num[:, :, 0] * KERNEL))
                    new_arr[i][j][1] = assign(np.sum(num[:, :, 1] * KERNEL))
                    new_arr[i][j][2] = assign(np.sum(num[:, :, 2] * KERNEL))

    new_arr = new_arr.astype(np.uint8)
    return new_arr


def equalizeHist(img):
    if len(img.shape) == 3:
        R = img[:, :, 0]
        G = img[:, :, 1]
        B = img[:, :, 2]
        R = cv2.equalizeHist(R)
        G = cv2.equalizeHist(G)
        B = cv2.equalizeHist(B)
        img[:, :, 0] = R
        img[:, :, 1] = G
        img[:, :, 2] = B
    else:  # 单通道灰度图像
        img = cv2.equalizeHist(img)
    return img


def exponential(img, C=10, gamma=0.4):
    h, w, d = img.shape[0], img.shape[1], img.shape[2]
    new_img = np.zeros((h, w, d), dtype=np.float32)
    for i in range(h):
        for j in range(w):
            for k in range(d):
                new_img[i, j, k] = C * math.pow(img[i, j, k], gamma)
    cv2.normalize(new_img, new_img, 0, 255, cv2.NORM_MINMAX)
    new_img = cv2.convertScaleAbs(new_img)
    return new_img


def logarithmic_transform(img, c=10):
    h, w, d = img.shape[0], img.shape[1], img.shape[2]
    print(h,w,d)
    new_img = np.zeros((h, w, d))
    for i in range(h):
        for j in range(w):
            for k in range(d):
                new_img[i, j, k] = c * (math.log(1.0 + img[i, j, k]))
                print(new_img[i][j][k],img[i][j][k])
    new_img = cv2.normalize(new_img, new_img, 0, 255, cv2.NORM_MINMAX)
    new_img = cv2.convertScaleAbs(new_img)
    # new_img = np.clip(new_img, 0, 255).astype(np.uint8)

    return new_img


def reverse_img(img):
    return 255 - img


def gamma_transformation(img, gamma=0.4):
    img1 = np.power(img / float(255), 1 / float(gamma)) * 255
    img1 = img1.astype(np.uint8)
    return img1


def midFilter(imarray, k=3):
    if len(imarray.shape) == 3:
        height, width, _ = imarray.shape
        if _ == 4:
            imarray = imarray[:, :, :3]
    else:
        height, width = imarray.shape
        imarray = np.expand_dims(imarray, axis=2)
        imarray = np.concatenate((imarray, imarray, imarray), axis=-1)

    edge = int((k - 1) / 2)
    new_arr = np.zeros((height, width, 3), dtype="uint8")
    for i in range(height):
        for j in range(width):
            if i <= edge - 1 or i >= height - 1 - edge or j <= edge - 1 or j >= width - edge - 1:
                new_arr[i, j] = imarray[i, j]
            else:
                num = imarray[i - edge: i + edge + 1, j - edge: j + edge + 1]
                num = num.reshape((k * k, 3))
                num = list(num[:, 0])
                temp = np.median(num)
                idex_tem = num.index(temp)  # 获取中值在数组中的坐标
                l1 = int((idex_tem / k)) - edge + i  # 根据进制转换反推出中值在图像中的坐标
                l2 = (idex_tem % k) - edge + j
                new_arr[i][j] = imarray[l1][l2]  # 赋值
    return new_arr


def avgFilter(imarray, k=3):
    if len(imarray.shape) == 3:
        height, width, _ = imarray.shape
        if _ == 4:
            imarray = imarray[:, :, :3]
    else:
        height, width = imarray.shape
        imarray = np.expand_dims(imarray, axis=2)
        imarray = np.concatenate((imarray, imarray, imarray), axis=-1)

    edge = int((k - 1) / 2)

    new_arr = np.zeros((height, width, 3), dtype="uint8")
    for i in range(height):
        for j in range(width):
            if i <= edge - 1 or i >= height - 1 - edge or j <= edge - 1 or j >= width - edge - 1:
                new_arr[i, j] = imarray[i, j]
            else:
                num = imarray[i - edge: i + edge + 1, j - edge: j + edge + 1]
                new_arr[i][j][0] = np.average(num[:, :, 0])
                new_arr[i][j][1] = np.average(num[:, :, 1])
                new_arr[i][j][2] = np.average(num[:, :, 2])
    return new_arr


def oil_painting(img, template=4, bucket=8, step=2):  # ,img,template, bucket, step
    grey = cv2.cvtColor(img, cv2.COLOR_RGB2GRAY)
    grey = (grey / float(256) * bucket).astype(np.uint8)
    h, w = grey.shape
    oil_img = np.zeros(img.shape, np.uint8)

    for i in range(0, h, step):  # 确定模板的位置
        top = i - template
        bottom = i + template
        if top < 0:
            top = 0
        if bottom >= h:
            bottom = h - 1
        for j in range(0, w, step):
            left = j - template
            right = j + template
            if left < 0:
                left = 0
            if right >= w:
                right = w - 1

            bucket_mat = np.zeros(bucket, np.uint8)
            for x in range(top, bottom):  # 计算bucket中每个值的个数
                for y in range(left, right):
                    bucket_mat[grey[x, y]] += 1

            maxBucket = np.max(bucket_mat)  # 找出像素最多的桶的次数以及它的索引
            maxBucketIndex = np.argmax(bucket_mat)

            mean = [0, 0, 0]
            for x in range(top, bottom):
                for y in range(left, right):
                    if grey[x, y] == maxBucketIndex:
                        mean += img[x, y]
            mean = (mean / maxBucket).astype(np.uint8)  # 三通道均值

            for m in range(step):
                for n in range(step):
                    if m + i >= h or n + j >= w:
                        continue
                    oil_img[m + i, n + j] = (mean[0], mean[1], mean[2])
    return oil_img


def sketch(img_array):
    img = Image.fromarray(img_array)
    new = Image.new("L", img.size, 255)
    width, height = img.size
    img = img.convert("L")
    # 定义画笔的大小
    Pen_size = 3
    # 色差扩散器
    Color_Diff = 6
    for i in range(Pen_size + 1, width - Pen_size - 1):
        for j in range(Pen_size + 1, height - Pen_size - 1):
            # 原始的颜色
            originalColor = 255
            lcolor = sum([img.getpixel((i - r, j)) for r in range(Pen_size)]) // Pen_size
            rcolor = sum([img.getpixel((i + r, j)) for r in range(Pen_size)]) // Pen_size

            # 通道----颜料
            if abs(lcolor - rcolor) > Color_Diff:
                originalColor -= (255 - img.getpixel((i, j))) // 4
                new.putpixel((i, j), originalColor)

            ucolor = sum([img.getpixel((i, j - r)) for r in range(Pen_size)]) // Pen_size
            dcolor = sum([img.getpixel((i, j + r)) for r in range(Pen_size)]) // Pen_size

            # 通道----颜料
            if abs(ucolor - dcolor) > Color_Diff:
                originalColor -= (255 - img.getpixel((i, j))) // 4
                new.putpixel((i, j), originalColor)

            acolor = sum([img.getpixel((i - r, j - r)) for r in range(Pen_size)]) // Pen_size
            bcolor = sum([img.getpixel((i + r, j + r)) for r in range(Pen_size)]) // Pen_size

            # 通道----颜料
            if abs(acolor - bcolor) > Color_Diff:
                originalColor -= (255 - img.getpixel((i, j))) // 4
                new.putpixel((i, j), originalColor)

            qcolor = sum([img.getpixel((i + r, j - r)) for r in range(Pen_size)]) // Pen_size
            wcolor = sum([img.getpixel((i - r, j + r)) for r in range(Pen_size)]) // Pen_size

            # 通道----颜料
            if abs(qcolor - wcolor) > Color_Diff:
                originalColor -= (255 - img.getpixel((i, j))) // 4
                new.putpixel((i, j), originalColor)
    arr = np.array(new)
    return arr


def gauss_low(fshift, d0):
    M = fshift.shape[0]
    N = fshift.shape[1]
    h = np.zeros((M, N))
    for i in range(M):
        for j in range(N):
            d = math.sqrt(math.pow(i - M // 2, 2) + math.pow(j - N // 2, 2))
            h[i][j] = math.exp(-(math.pow(d, 2)) / (2 * math.pow(d0, 2)))
    return np.multiply(fshift, h)


def butterworth_low(fshift, d0):
    M = fshift.shape[0]
    N = fshift.shape[1]
    h = np.zeros((M,N))
    nn = 2
    for i in range(M):
        for j in range(N):
            d = math.sqrt(math.pow(i-M//2,2)+math.pow(j-N//2,2))
            h[i][j] = 1/(1+math.pow(d/d0,2*nn))
    return np.multiply(fshift,h)

def butterworth_high(fshift, d0):
    M = fshift.shape[0]
    N = fshift.shape[1]
    h = np.zeros((M, N))
    nn = 2
    for i in range(M):
        for j in range(N):
            d = math.sqrt(math.pow(i - M // 2, 2) + math.pow(j - N // 2, 2))
            if d == 0:
                h[i][j] = 0
            else:
                h[i][j] = 1 / (1 + math.pow(d0 / d, 2 * nn))
    return np.multiply(fshift, h)


def gauss_high(fshift, d0):
    M = fshift.shape[0]
    N = fshift.shape[1]
    h = np.zeros((M, N))
    for i in range(M):
        for j in range(N):
            d = math.sqrt(math.pow(i - M // 2, 2) + math.pow(j - N // 2, 2))
            h[i][j] = 1 - math.exp(-(math.pow(d, 2)) / (2 * math.pow(d0, 2)))

    return np.multiply(fshift, h)


def _filter(img, d0=20, method='butterworth_high'):
    print(img.shape)
    print(method)
    if len(img.shape) == 3:
        img = np.array(Image.fromarray(img).convert("L"))
    f = np.float64(img)
    f = np.fft.fft2(f)
    fshift = np.fft.fftshift(f)
    if method == 'gauss_low':
        fshift = gauss_low(fshift, d0)
    elif method == 'gauss_high':
        fshift = gauss_high(fshift, d0)
    elif method == 'butterworth_low':
        fshift = butterworth_low(fshift, d0)
    elif method == 'butterworth_high':
        fshift = butterworth_high(fshift, d0)
    else:
        return None

    ifshift = np.fft.ifftshift(fshift)
    ift = np.fft.ifft2(ifshift)
    ift = np.real(ift)
    ift = np.uint8(np.clip(ift, 0, 255))

    height, width = ift.shape
    new = np.zeros(ift.shape, dtype=np.uint8)
    for i in range(height):
        for j in range(width):
            new[i, j] = ift[i, j]

    return new


def inverse_recover(fshift):
    rows, cols = fshift.shape
    center_row, center_col = rows // 2, cols // 2

    u, v = np.meshgrid(np.arange(rows) - center_row, np.arange(cols) - center_col)
    H = np.exp(-80 * (u ** 2 + v ** 2) ** (5 / 6))
    H[H < 0.0001] = 0.78
    # 频域逆滤波
    result = fshift / H
    return  result


def wiener_recover(fshift):
    rows, cols = fshift.shape
    center_row, center_col = rows // 2, cols // 2

    u, v = np.meshgrid(np.arange(rows) - center_row, np.arange(cols) - center_col)
    H = np.exp(-0.0025 * (u ** 2 + v ** 2) ** (5 / 6))

    # 维纳滤波
    result = (1 / H) * (np.abs(H) ** 2 / (np.abs(H) ** 2 + 0.0025)) * fshift
    return result



def _recover(img, method='wiener'):
    if len(img.shape) == 3:
        img = np.array(Image.fromarray(img).convert("L"))
    print(method)
    f = np.fft.fft2(img)
    fshift = np.fft.fftshift(f)
    if method == 'inverse':
        fshift = inverse_recover(fshift)
    elif method == 'wiener':
        fshift = wiener_recover(fshift)
    else:
        return None

    ifshift = np.fft.ifftshift(fshift)
    ift = np.fft.ifft2(ifshift)
    ift = np.abs(ift)
    # ift = ift.astype(np.uint8)
    ift = np.uint8(np.clip(ift, 0, 255))
    # img = Image.fromarray(ift.astype(np.uint8))
    # img.show()

    height, width = ift.shape
    new = np.zeros(ift.shape, dtype=np.uint8)
    for i in range(height):
        for j in range(width):
            new[i, j] = ift[i, j]

    return new


def getThreshold(img_array):
    height, width = img_array.shape
    img_array = img_array.reshape(height * width)
    threshold = 0
    max_value = 0
    for i in range(0, 256):
        a = [x for x in img_array if x < i]
        b = [x for x in img_array if x >= i]
        mean_a, mean_b = np.mean(a), np.mean(b)
        value = len(a) * len(b) * (mean_a - mean_b) * (mean_a - mean_b)
        max_value, threshold = (value, i) if value > max_value else (max_value, threshold)
        print(max_value, threshold, i)
        if threshold != i:
            return threshold
    return threshold


def ostu(img_array):
    if len(img_array.shape) == 3:
        img_array = np.array(Image.fromarray(img_array).convert("L"))
    height, width = img_array.shape
    threshold = getThreshold(img_array)
    print(threshold)
    new = np.zeros(img_array.shape, dtype=np.uint8)
    for i in range(height):
        for j in range(width):
            new[i, j] = 0 if img_array[i, j] < threshold else 255

    return new



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
def fft_frequency(img):
    if len(img.shape) == 3:
        img = np.array(Image.fromarray(img).convert("L"))
    height, width = img.shape

    f = np.fft.fft2(img)
    fshift = np.fft.fftshift(f)
    fshift = np.abs(fshift)
    fimg = np.log(fshift)

    img = Image.fromarray(fimg.astype(np.uint8))
    img.show()

    height, width = fimg.shape
    new = np.zeros(fimg.shape, dtype=np.uint8)
    for i in range(height):
        for j in range(width):
            new[i, j] = fimg[i, j]

    return new


def enhance_brightness(img, co):
    img = Image.fromarray(img)
    img = img.point(lambda i: int(i * co))
    img = np.array(img)
    return img


def enhance_sharpeness(img, co):
    img = Image.fromarray(img)
    img = ImageEnhance.Sharpness(img).enhance(co)
    img = np.array(img)
    return img


def enhance_contrast(img, co):
    img = Image.fromarray(img)
    img = ImageEnhance.Contrast(img).enhance(co)
    img = np.array(img)
    return img


def enhance_color(img, co):
    img = Image.fromarray(img)
    img = ImageEnhance.Color(img).enhance(co)
    img = np.array(img)
    return img
