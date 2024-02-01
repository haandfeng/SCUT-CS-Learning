import cv2
import numpy as np
import matplotlib.pyplot as plt


# 读取图像
def Gaussian_low_pass(a, origin):
    # 将噪声图像转换为双精度
    f = np.float64(a)
    # 执行傅立叶变换，并将零频率分量移动到频谱中心
    g = np.fft.fft2(f)
    g_shifted = np.fft.fftshift(g)

    # 获取图像尺寸
    M, N = g_shifted.shape

    # 生成高斯滤波器的中心
    x = np.arange(-N / 2, N / 2)
    y = np.arange(-M / 2, M / 2)
    x, y = np.meshgrid(x, y)

    # 设定高斯滤波器的标准差
    D0 = 20
    # 创建高斯滤波器
    Gaussian = np.exp(-(x ** 2 + y ** 2) / (2 * D0 ** 2))

    # 应用高斯低通滤波器到频域图像
    g_filtered = g_shifted * Gaussian

    # 将频率域中的零频率还原到左上角
    y_shifted_back = np.fft.ifftshift(g_filtered)

    # 执行逆傅立叶变换，并取实部
    y = np.fft.ifft2(y_shifted_back)
    y = np.real(y)

    # 将图像转换回8位格式
    y = np.uint8(np.clip(y, 0, 255))

    plt.figure(figsize=(10, 5))
    plt.subplot(1, 3, 1)
    plt.title("Origin")
    plt.imshow(origin, cmap='gray')

    plt.subplot(1, 3, 2)
    plt.title("Noisy")
    plt.imshow(a, cmap='gray')

    plt.subplot(1, 3, 3)
    plt.title("Gaussian_low_pass Image")
    plt.imshow(y, cmap='gray')

    plt.show()


def Gaussian_high_pass(a, origin):
    # 将噪声图像转换为双精度
    f = np.float64(a)

    # 执行傅立叶变换，并将零频率分量移动到频谱中心
    g = np.fft.fft2(f)
    g_shifted = np.fft.fftshift(g)

    # 获取图像尺寸
    M, N = g_shifted.shape

    # 生成高斯滤波器的中心
    x = np.arange(-N / 2, N / 2)
    y = np.arange(-M / 2, M / 2)
    x, y = np.meshgrid(x, y)

    # 设定高斯滤波器的标准差
    D0 = 20

    # 创建高斯低通滤波器
    Gaussian_low_pass = np.exp(-(x ** 2 + y ** 2) / (2 * D0 ** 2))

    # 创建高斯高通滤波器
    Gaussian_high_pass = 1 - Gaussian_low_pass

    # 应用高斯高通滤波器到频域图像
    g_filtered = g_shifted * Gaussian_high_pass

    # 将频率域中的零频率还原到左上角
    y_shifted_back = np.fft.ifftshift(g_filtered)

    # 执行逆傅立叶变换，并取实部
    y = np.fft.ifft2(y_shifted_back)
    y = np.real(y)

    # 将图像转换回8位格式
    y = np.uint8(np.clip(y, 0, 255))

    plt.figure(figsize=(10, 5))
    plt.subplot(1, 3, 1)
    plt.title("Origin")
    plt.imshow(origin, cmap='gray')

    plt.subplot(1, 3, 2)
    plt.title("Noisy")
    plt.imshow(a, cmap='gray')

    plt.subplot(1, 3, 3)
    plt.title("Gaussian_high_pass Image")
    plt.imshow(y, cmap='gray')

    plt.show()


def Butterworth_high_pass(a, origin):
    # 将噪声图像转换为双精度
    f = np.float64(a)

    # 执行傅立叶变换，并将零频率分量移动到频谱中心
    g = np.fft.fft2(f)
    g_shifted = np.fft.fftshift(g)

    # 获取图像尺寸
    M, N = g_shifted.shape

    # 生成滤波器的中心
    x = np.arange(-N / 2, N / 2)
    y = np.arange(-M / 2, M / 2)
    x, y = np.meshgrid(x, y)

    # 设定布特沃斯滤波器的参数
    D0 = 20.0  # 截止频率
    n = 3  # 滤波器的阶数

    # 计算距离中心的距离
    D = np.sqrt(x ** 2 + y ** 2)

    # 创建布特沃斯高通滤波器
    Butterworth_high_pass = 1 / (1 + (D0 / D) ** (2 * n))

    # 应用布特沃斯高通滤波器到频域图像
    g_filtered = g_shifted * Butterworth_high_pass

    # 将频率域中的零频率还原到左上角
    y_shifted_back = np.fft.ifftshift(g_filtered)

    # 执行逆傅立叶变换，并取实部
    y = np.fft.ifft2(y_shifted_back)
    y = np.real(y)

    # 将图像转换回8位格式
    y = np.uint8(np.clip(y, 0, 255))

    plt.figure(figsize=(10, 5))
    plt.subplot(1, 3, 1)
    plt.title("Origin")
    plt.imshow(origin, cmap='gray')

    plt.subplot(1, 3, 2)
    plt.title("Noisy")
    plt.imshow(a, cmap='gray')

    plt.subplot(1, 3, 3)
    plt.title("Butterworth_high_pass Image")
    plt.imshow(y, cmap='gray')

    plt.show()


def Butterworth_low_pass(a, origin):
    # 将噪声图像转换为双精度
    f = np.float64(a)

    # 执行傅立叶变换，并将零频率分量移动到频谱中心
    g = np.fft.fft2(f)
    g_shifted = np.fft.fftshift(g)

    # 获取图像尺寸
    M, N = g_shifted.shape

    # 生成滤波器的中心
    x = np.arange(-N / 2, N / 2)
    y = np.arange(-M / 2, M / 2)
    x, y = np.meshgrid(x, y)

    # 设定布特沃斯滤波器的参数
    D0 = 20.0  # 截止频率
    n = 3  # 滤波器的阶数

    # 计算距离中心的距离
    D = np.sqrt(x ** 2 + y ** 2)

    # 创建布特沃斯低通滤波器
    Butterworth_low_pass = 1 / (1 + (D / D0) ** (2 * n))

    # 应用布特沃斯低通滤波器到频域图像
    g_filtered = g_shifted * Butterworth_low_pass

    # 将频率域中的零频率还原到左上角
    y_shifted_back = np.fft.ifftshift(g_filtered)

    # 执行逆傅立叶变换，并取实部
    y = np.fft.ifft2(y_shifted_back)
    y = np.real(y)

    # 将图像转换回8位格式
    y = np.uint8(np.clip(y, 0, 255))

    plt.figure(figsize=(10, 5))
    plt.subplot(1, 3, 1)
    plt.title("Origin")
    plt.imshow(origin, cmap='gray')

    plt.subplot(1, 3, 2)
    plt.title("Noisy")
    plt.imshow(a, cmap='gray')

    plt.subplot(1, 3, 3)
    plt.title("Butterworth_low_pass Image")
    plt.imshow(y, cmap='gray')

    plt.show()


a = cv2.imread('sample5-1.bmp', 0)  # 0表示以灰度模式读取图像
origin = cv2.imread('sample5-2.bmp', 0)
Butterworth_low_pass(a.copy(), origin.copy())
Gaussian_low_pass(a.copy(), origin.copy())
Butterworth_high_pass(a.copy(), origin.copy())
Gaussian_high_pass(a.copy(), origin.copy())
