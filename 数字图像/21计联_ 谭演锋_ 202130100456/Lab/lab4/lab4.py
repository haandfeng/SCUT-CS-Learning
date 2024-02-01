import cv2
import numpy as np
import matplotlib.pyplot as plt


def Laplace(img, kernel):
    des_8U = cv2.filter2D(img, -1, kernel=kernel, borderType=cv2.BORDER_DEFAULT)
    des_16S = cv2.filter2D(img, ddepth=cv2.CV_16SC1, kernel=kernel, borderType=cv2.BORDER_DEFAULT)
    g = img - des_16S
    g[g < 0] = 0
    g[g > 255] = 255

    plt.figure(figsize=(10, 14))

    # origin, des_8U, des_16S, filtered
    plt.subplot(221)
    plt.imshow(img, cmap='gray')
    plt.title('origin')

    plt.subplot(222)
    plt.imshow(des_8U, cmap='gray')
    plt.title('No demarcate')

    plt.subplot(223)
    plt.imshow(des_16S, cmap='gray')
    plt.title('demarcate')

    plt.subplot(224)
    plt.imshow(g, cmap='gray')
    plt.title('sharpen_image')
    plt.show()


img0 = 'b.bmp'

f = cv2.imread(img0, cv2.IMREAD_GRAYSCALE)

kernel1 = np.asarray([[0, 1, 0],
                      [1, -4, 1],
                      [0, 1, 0]])

Laplace(f, kernel1)

kernel2 = np.asarray([[1, 1, 1],
                      [1, -8, 1],
                      [1, 1, 1]])

Laplace(f, kernel2)
