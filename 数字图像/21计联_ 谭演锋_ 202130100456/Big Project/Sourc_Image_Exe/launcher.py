import algorithms
import numpy as np
from PIL import Image

from PyQt5.QtWidgets import QApplication, QWidget, QFileDialog, QSlider

from PyQt5.uic import loadUi
from PyQt5.QtCore import Qt
from PyQt5.QtGui import QPixmap, QKeyEvent
from PyQt5 import QtGui
import os
import sys
import cv2


class Launcher(QWidget):
    def __init__(self, parent=None):
        super(Launcher, self).__init__(parent)
        self.ui = loadUi('qmain.ui', self)
        self.ui.setWindowTitle("数字图像处理大作业(谭演锋、杨竣尧、郭荣锦)")
        self.label = self.ui.label

        self.ui.horizontalSlider.valueChanged.connect(self.handel_enhance_sharpness)
        self.ui.horizontalSlider_2.valueChanged.connect(self.handel_enhance_contrast)
        self.ui.horizontalSlider_3.valueChanged.connect(self.handel_enhance_color)
        self.ui.horizontalSlider_4.valueChanged.connect(self.handel_enhance_brightness)

        # connect btn


        self.ui.btn_open.clicked.connect(self.open_folder)
        self.ui.original_btn.clicked.connect(self.set_original_img)
        self.ui.exp_btn.clicked.connect(self.handel_exponential)
        self.ui.gamma_btn.clicked.connect(self.handel_gamma)

        self.ui.hist_btn.clicked.connect(self.handel_histogram)
        self.ui.reverse_btn.clicked.connect(self.handel_reverse)

        self.ui.log_btn.clicked.connect(self.handel_logarithm)

        self.ui.mid_btn.clicked.connect(self.handel_oil_midFilter)
        self.ui.mean_btn.clicked.connect(self.handel_oil_avgFilter)

        self.ui.oil_btn.clicked.connect(self.handel_oil_paint)
        self.ui.sketch_btn.clicked.connect(self.handel_sketch)

        self.ui.lap_btn.clicked.connect(self.handel_laplacian)
        self.ui.fft_btn.clicked.connect(self.handel_fft_frequenct)

        self.ui.inverse_btn.clicked.connect(self.handel_inverse_filter)
        self.ui.vena_btn.clicked.connect(self.handel_vena_filter)

        self.ui.gauss_high_btn.clicked.connect(self.handel_gauss_high)
        self.ui.gauss_low_btn.clicked.connect(self.handel_gauss_low)

        self.ui.butter_high_btn.clicked.connect(self.handel_butterworth_high)
        self.ui.butter_low_btn.clicked.connect(self.handel_butterworth_low)

        self.ui.ostu_btn.clicked.connect(self.handel_ostu)
        self.ui.edge_btn.clicked.connect(self.handel_edge)

        # self.ui.enhance_bright_btn.clicked.connect(self.handel_enhance_brightness)
        # self.ui.enhance_sharp_btn.clicked.connect(self.handel_enhance_sharpness)
        # self.ui.enhance_color_btn.clicked.connect(self.handel_enhance_color)
        # self.ui.enhance_contrast_btn.clicked.connect(self.handel_enhance_contrast)

        self.ui.previous.clicked.connect(self.previous_img)
        self.ui.next.clicked.connect(self.next_img)

        self.working_dir = ""
        self.current_img_path = ""
        self.original_img = None
        self.img_arr = None
        self.all_img = []
        self.current_img_index = 0

    def set_img(self, path=""):
        if path != "":
            self.current_img_path = path
        self.img = QPixmap(self.current_img_path)
        self.original_img = self.img
        self.img = self.img.scaled(self.label.size(), aspectRatioMode=Qt.KeepAspectRatio,
                                   transformMode=Qt.SmoothTransformation)
        self.label.setPixmap(self.img)
        self.label_2.setPixmap(self.img)

    def set_original_img(self):
        self.set_img()

    def handel_reverse(self):
        print("handeling reverse")
        self.set_img_format()
        self.img_arr = algorithms.reverse_img(self.img_arr)
        self.handle_change_image()

    def handel_exponential(self):
        self.set_img_format()
        self.img_arr = algorithms.exponential(self.img_arr)
        self.handle_change_image()

    def handel_gamma(self):
        self.set_img_format()
        self.img_arr = algorithms.gamma_transformation(self.img_arr)
        self.handle_change_image()

    def handel_histogram(self):
        self.set_img_format()
        self.img_arr = algorithms.equalizeHist(self.img_arr)
        self.handle_change_image()

    def handel_logarithm(self):
        self.set_img_format()
        self.img_arr = algorithms.logarithmic_transform(self.img_arr)
        self.handle_change_image()
    def handel_oil_paint(self):
        self.set_img_format()
        self.img_arr = algorithms.oil_painting(self.img_arr)
        self.handle_change_image()

    def handel_oil_avgFilter(self):
        self.set_img_format()
        self.img_arr = algorithms.avgFilter(self.img_arr)
        self.handle_change_image()

    def handel_oil_midFilter(self):
        self.set_img_format()
        self.img_arr = algorithms.midFilter(self.img_arr)
        self.handle_change_image()

    def handel_sketch(self):
        self.set_img_format()
        self.img_arr = algorithms.sketch(self.img_arr)
        self.handle_change_image()

    def handel_gauss_high(self):
        self.set_img_format()
        self.img_arr = algorithms._filter(self.img_arr, method="gauss_high")
        self.handle_change_image()

    def handel_gauss_low(self):
        self.set_img_format()
        self.img_arr = algorithms._filter(self.img_arr, method="gauss_low")
        self.handle_change_image()

    def handel_butterworth_high(self):
        self.set_img_format()
        self.img_arr = algorithms._filter(self.img_arr, method="butterworth_high")
        self.handle_change_image()

    def handel_butterworth_low(self):
        self.set_img_format_gray()
        self.img_arr = algorithms._filter(self.img_arr, method="butterworth_low")
        self.handle_change_image()

    def handel_laplacian(self):
        self.set_img_format()
        self.img_arr = algorithms.laplaceSharpen(self.img_arr)
        self.handle_change_image()

    def handel_enhance_brightness(self):
        self.set_img_format()
        self.img_arr = algorithms.enhance_brightness(self.img_arr, self.ui.horizontalSlider_4.value())
        self.handle_change_image()

    def handel_enhance_sharpness(self):
        self.set_img_format()
        self.img_arr = algorithms.enhance_sharpeness(self.img_arr, self.ui.horizontalSlider.value())
        self.handle_change_image()

    def handel_enhance_color(self):
        self.set_img_format()
        self.img_arr = algorithms.enhance_color(self.img_arr, self.ui.horizontalSlider_3.value())
        self.handle_change_image()

    def handel_enhance_contrast(self):
        # self.ui.horizontalSlider.setTickPosition(QSlider.TicksLeft)
        self.set_img_format()
        self.img_arr = algorithms.enhance_contrast(self.img_arr, self.ui.horizontalSlider_2.value())

        self.handle_change_image()

    def handel_fft_frequenct(self):
        self.set_img_format()
        self.img_arr = algorithms.fft_frequency(self.img_arr)
        self.handle_change_image()

    def handel_inverse_filter(self):
        self.set_img_format()
        self.img_arr = algorithms._recover(self.img_arr, method="inverse")
        self.handle_change_image()

    def handel_vena_filter(self):
        self.set_img_format()
        self.img_arr = algorithms._recover(self.img_arr, method="wiener")
        self.handle_change_image()

    def handel_ostu(self):
        self.set_img_format()
        self.img_arr = algorithms.ostu(self.img_arr)
        self.handle_change_image()

    def handel_edge(self):
        self.set_img_format()
        self.img_arr = algorithms.laplaceSharpen(self.img_arr, "edge")
        self.handle_change_image()

    def open_folder(self):

        dialog = QFileDialog()
        dialog.setFileMode(QFileDialog.AnyFile)
        # 设置显示文件的模式，这里是详细模式
        dialog.setViewMode(QFileDialog.Detail)

        if dialog.exec_():
            fileNames = dialog.selectedFiles()
            print(fileNames)
            # print(fileNames[0])
            if self.is_folder_or_file(fileNames[0]):
                count = 0
                for filename in os.listdir(fileNames[0]):
                    file_path = os.path.join(fileNames[0], filename)
                    # 检查文件是否是图片文件（.bmp、.png、.jpg）
                    if os.path.isfile(file_path) and filename.lower().endswith(('.bmp', '.png', '.jpg')):
                        count += 1
                        if (count == 1):
                            self.current_img_path = file_path
                        self.all_img.append(filename)
                print(self.current_img_path)
                self.set_img()
                self.working_dir = fileNames[0]
                self.current_img_index = 0
            else:
                self.current_img_path = fileNames[0]
                self.set_img()
                self.set_working_dir()
                self.set_all_img_path()

    def set_img_format(self):
        img = Image.open(self.current_img_path).convert("RGB")
        self.img_arr = np.array(img)

    def set_img_format_gray(self):
        self.img_arr = cv2.imread(self.current_img_path, cv2.IMREAD_GRAYSCALE)

    def set_working_dir(self):
        path = str(self.current_img_path)
        index = 0
        for i in range(1, len(path)):
            if path[-i] == '/':
                index = i
                break
        self.working_dir = path[:-index]
        print("working", self.working_dir)

    def set_all_img_path(self):
        import os
        datanames = os.listdir(self.working_dir)
        for file in datanames:
            if os.path.splitext(file)[1] == '.bmp' or os.path.splitext(file)[1] == '.png':  # 目录下包含.json的文件
                self.all_img.append(file)
        print(self.all_img)
        temp = self.current_img_path.replace(self.working_dir, "")[1:]
        self.current_img_index = self.all_img.index(temp)

    def handle_change_image(self):
        # print(self.img_arr.shape)
        qimage = None
        if len(self.img_arr.shape) == 3:
            qimage = QtGui.QImage(self.img_arr, self.img_arr.shape[1], self.img_arr.shape[0]
                                  , self.img_arr.shape[1] * 3, QtGui.QImage.Format_RGB888)

        if len(self.img_arr.shape) == 2:
            print("gray")
            self.img_arr = cv2.cvtColor(self.img_arr, cv2.COLOR_GRAY2RGB)
            qimage = QtGui.QImage(self.img_arr, self.img_arr.shape[1], self.img_arr.shape[0]
                                  , self.img_arr.shape[1] * 3, QtGui.QImage.Format_RGB888)
            # qimage = QtGui.QImage(self.img_arr, self.img_arr.shape[1], self.img_arr.shape[0]
            #                       , QtGui.QImage.Format_Grayscale16)

        pix = QPixmap(qimage)
        pix = pix.scaled(self.label.size(), aspectRatioMode=Qt.KeepAspectRatio, transformMode=Qt.SmoothTransformation)
        self.label.setPixmap(pix)

    def keyPressEvent(self, keyevent):
        keyevent = QKeyEvent(keyevent)
        if (keyevent.key() == Qt.Key_A):
            self.previous_img()
        if (keyevent.key() == Qt.Key_D):
            self.next_img()
        if (keyevent.key() == Qt.Key_P):
            self.open_folder()
        if (keyevent.key() == Qt.Key_O):
            self.set_original_img()

    def next_img(self):
        if self.current_img_path == "":
            return
        if self.current_img_index + 1 < len(self.all_img):
            self.current_img_index += 1
        self.current_img_path = self.working_dir + '/' + self.all_img[self.current_img_index]
        self.set_img(self.current_img_path)

    def previous_img(self):
        if self.current_img_path == "":
            return
        if self.current_img_index > 0:
            self.current_img_index -= 1
        self.current_img_path = self.working_dir + '/' + self.all_img[self.current_img_index]
        self.set_img(self.current_img_path)

    def is_folder_or_file(self, path):

        if os.path.exists(path):
            if os.path.isdir(path):
                return True
            elif os.path.isfile(path):
                return False

        return None


# if __name__ == '__main__':
#     app = QApplication(sys.argv)
#     launcher = Launcher()
#     # 设置QSS样式
#     qssStyle = '''
#            /* 添加装饰效果的样式 */
#            QLabel#titleLabel {
#                color: red;
#                font-size: 24px;
#                font-weight: bold;
#                text-align: center;
#            }
#        '''
#     launcher.setStyleSheet(qssStyle)
#     launcher.ui.show()
#     app.exec_()
if __name__ == '__main__':
    app = QApplication(sys.argv)
    launcher = Launcher()

    # 设置QSS样式
    qssStyle = '''
    QWidget#Frame{
    background-color: rgb(251, 252, 255)
    }
    QLabel#label{
    font-family:'Microsoft YaHei';
    font-size:40px;
    font-weight: light;
    color: rgba(140,140,140,0.8)
    }
    QLabel#label_2{
    font-family:'Microsoft YaHei';
    font-size:40px;
    font-weight: light;
    color: rgba(140,140,140,0.8)
    }
    
    #R1{
    border: 0px;
    border-radius:  20px
    }
    #RR1{
    background-color: rgb(240,246,255);
    
    }
       QPushButton {
    background-color: rgb(255, 254, 250);
    border: 1px solid #dcdfe6;
    padding: 10px;
    border-radius: 5px;
    color: #010101;
}

QPushButton:hover {
    background-color: #ecf5ff;
    color: #409eff;
}

QPushButton:pressed, QPushButton:checked {
    border: 1px solid #3a8ee6;
    color: #409eff;
}


    '''
    launcher.setStyleSheet(qssStyle)

    launcher.ui.show()
    sys.exit(app.exec_())
