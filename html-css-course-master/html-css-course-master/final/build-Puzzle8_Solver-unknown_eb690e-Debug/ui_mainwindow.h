/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *lbl_Back;
    QPushButton *btn_input;
    QPushButton *btn_solve;
    QPushButton *btn_refresh;
    QLabel *lbl_algo;
    QComboBox *combo_algorithm;
    QTextBrowser *txt_solution;
    QLabel *lbl_solution;
    QLabel *lbl_r1;
    QLabel *lbl_moves;
    QLabel *lbl_r2;
    QLabel *lbl_time;
    QPushButton *btn_nextstep;
    QLabel *lbl_info;
    QLabel *lbl_a1;
    QLabel *lbl_a2;
    QLabel *lbl_a3;
    QLabel *lbl_a4;
    QLabel *lbl_a5;
    QLabel *lbl_a6;
    QLabel *lbl_a7;
    QLabel *lbl_a8;
    QLabel *lbl_Blank;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(840, 580);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/Main_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        lbl_Back = new QLabel(centralWidget);
        lbl_Back->setObjectName(QString::fromUtf8("lbl_Back"));
        lbl_Back->setGeometry(QRect(9, 11, 576, 525));
        QFont font;
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(50);
        font.setStrikeOut(false);
        lbl_Back->setFont(font);
        lbl_Back->setStyleSheet(QString::fromUtf8("border : 4px solid rgb(204, 0, 0);\n"
"background-color: rgb(0, 0, 0);"));
        btn_input = new QPushButton(centralWidget);
        btn_input->setObjectName(QString::fromUtf8("btn_input"));
        btn_input->setGeometry(QRect(605, 10, 100, 25));
        btn_solve = new QPushButton(centralWidget);
        btn_solve->setObjectName(QString::fromUtf8("btn_solve"));
        btn_solve->setGeometry(QRect(605, 50, 215, 35));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setWeight(75);
        btn_solve->setFont(font1);
        btn_refresh = new QPushButton(centralWidget);
        btn_refresh->setObjectName(QString::fromUtf8("btn_refresh"));
        btn_refresh->setGeometry(QRect(720, 10, 100, 25));
        lbl_algo = new QLabel(centralWidget);
        lbl_algo->setObjectName(QString::fromUtf8("lbl_algo"));
        lbl_algo->setGeometry(QRect(605, 100, 100, 25));
        lbl_algo->setStyleSheet(QString::fromUtf8("border : 1.5px solid blue;\n"
"background-color: rgb(5, 203, 169);\n"
"\n"
""));
        lbl_algo->setAlignment(Qt::AlignCenter);
        combo_algorithm = new QComboBox(centralWidget);
        combo_algorithm->addItem(QString());
        combo_algorithm->addItem(QString());
        combo_algorithm->addItem(QString());
        combo_algorithm->setObjectName(QString::fromUtf8("combo_algorithm"));
        combo_algorithm->setGeometry(QRect(720, 100, 100, 25));
        txt_solution = new QTextBrowser(centralWidget);
        txt_solution->setObjectName(QString::fromUtf8("txt_solution"));
        txt_solution->setGeometry(QRect(605, 180, 215, 160));
        lbl_solution = new QLabel(centralWidget);
        lbl_solution->setObjectName(QString::fromUtf8("lbl_solution"));
        lbl_solution->setGeometry(QRect(605, 155, 215, 25));
        QFont font2;
        font2.setPointSize(15);
        lbl_solution->setFont(font2);
        lbl_solution->setStyleSheet(QString::fromUtf8("border : 2px solid rgb(204, 0, 0);\n"
"background-color: rgb(245, 133, 133);"));
        lbl_solution->setAlignment(Qt::AlignCenter);
        lbl_r1 = new QLabel(centralWidget);
        lbl_r1->setObjectName(QString::fromUtf8("lbl_r1"));
        lbl_r1->setGeometry(QRect(605, 360, 100, 25));
        QFont font3;
        font3.setPointSize(12);
        lbl_r1->setFont(font3);
        lbl_r1->setStyleSheet(QString::fromUtf8("border : 2px solid rgb(13, 10, 161);\n"
"background-color: rgb(173, 127, 168);"));
        lbl_r1->setAlignment(Qt::AlignCenter);
        lbl_moves = new QLabel(centralWidget);
        lbl_moves->setObjectName(QString::fromUtf8("lbl_moves"));
        lbl_moves->setGeometry(QRect(720, 360, 100, 25));
        lbl_moves->setStyleSheet(QString::fromUtf8("border : 2px solid rgb(13, 10, 161);\n"
"background-color: rgb(173, 127, 168);\n"
""));
        lbl_moves->setAlignment(Qt::AlignCenter);
        lbl_r2 = new QLabel(centralWidget);
        lbl_r2->setObjectName(QString::fromUtf8("lbl_r2"));
        lbl_r2->setGeometry(QRect(605, 405, 100, 25));
        lbl_r2->setFont(font3);
        lbl_r2->setStyleSheet(QString::fromUtf8("border : 2px solid rgb(9, 93, 12);\n"
"background-color: rgb(138, 226, 52);"));
        lbl_r2->setAlignment(Qt::AlignCenter);
        lbl_time = new QLabel(centralWidget);
        lbl_time->setObjectName(QString::fromUtf8("lbl_time"));
        lbl_time->setGeometry(QRect(720, 405, 100, 25));
        lbl_time->setFont(font3);
        lbl_time->setStyleSheet(QString::fromUtf8("border : 2px solid rgb(9, 93, 12);\n"
"background-color: rgb(138, 226, 52);"));
        lbl_time->setAlignment(Qt::AlignCenter);
        btn_nextstep = new QPushButton(centralWidget);
        btn_nextstep->setObjectName(QString::fromUtf8("btn_nextstep"));
        btn_nextstep->setGeometry(QRect(605, 450, 215, 35));
        QFont font4;
        font4.setPointSize(14);
        btn_nextstep->setFont(font4);
        lbl_info = new QLabel(centralWidget);
        lbl_info->setObjectName(QString::fromUtf8("lbl_info"));
        lbl_info->setGeometry(QRect(605, 500, 215, 36));
        QFont font5;
        font5.setPointSize(12);
        font5.setBold(true);
        font5.setUnderline(true);
        font5.setWeight(75);
        lbl_info->setFont(font5);
        lbl_info->setStyleSheet(QString::fromUtf8("border : 2px solid rgb(251, 73, 3);\n"
"background-color: rgb(237, 212, 0);"));
        lbl_info->setAlignment(Qt::AlignCenter);
        lbl_a1 = new QLabel(centralWidget);
        lbl_a1->setObjectName(QString::fromUtf8("lbl_a1"));
        lbl_a1->setGeometry(QRect(24, 26, 172, 155));
        lbl_a1->setStyleSheet(QString::fromUtf8("border : 1px solid blue;\n"
""));
        lbl_a1->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/imgs/1.jpg")));
        lbl_a1->setScaledContents(true);
        lbl_a2 = new QLabel(centralWidget);
        lbl_a2->setObjectName(QString::fromUtf8("lbl_a2"));
        lbl_a2->setGeometry(QRect(211, 26, 172, 155));
        lbl_a2->setStyleSheet(QString::fromUtf8("border : 1px solid blue;"));
        lbl_a2->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/imgs/2.jpg")));
        lbl_a2->setScaledContents(true);
        lbl_a2->setWordWrap(false);
        lbl_a3 = new QLabel(centralWidget);
        lbl_a3->setObjectName(QString::fromUtf8("lbl_a3"));
        lbl_a3->setGeometry(QRect(398, 26, 172, 155));
        lbl_a3->setStyleSheet(QString::fromUtf8("border : 1px solid blue;"));
        lbl_a3->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/imgs/3.jpg")));
        lbl_a3->setScaledContents(true);
        lbl_a4 = new QLabel(centralWidget);
        lbl_a4->setObjectName(QString::fromUtf8("lbl_a4"));
        lbl_a4->setGeometry(QRect(24, 196, 172, 155));
        lbl_a4->setStyleSheet(QString::fromUtf8("border : 1px solid blue;"));
        lbl_a4->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/imgs/4.jpg")));
        lbl_a4->setScaledContents(true);
        lbl_a5 = new QLabel(centralWidget);
        lbl_a5->setObjectName(QString::fromUtf8("lbl_a5"));
        lbl_a5->setGeometry(QRect(211, 196, 172, 155));
        lbl_a5->setStyleSheet(QString::fromUtf8("border : 1px solid blue;"));
        lbl_a5->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/imgs/5.jpg")));
        lbl_a5->setScaledContents(true);
        lbl_a6 = new QLabel(centralWidget);
        lbl_a6->setObjectName(QString::fromUtf8("lbl_a6"));
        lbl_a6->setGeometry(QRect(398, 196, 172, 155));
        lbl_a6->setStyleSheet(QString::fromUtf8("border : 1px solid blue;"));
        lbl_a6->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/imgs/6.jpg")));
        lbl_a6->setScaledContents(true);
        lbl_a7 = new QLabel(centralWidget);
        lbl_a7->setObjectName(QString::fromUtf8("lbl_a7"));
        lbl_a7->setGeometry(QRect(24, 366, 172, 155));
        lbl_a7->setStyleSheet(QString::fromUtf8("border : 1px solid blue;"));
        lbl_a7->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/imgs/7.jpg")));
        lbl_a7->setScaledContents(true);
        lbl_a8 = new QLabel(centralWidget);
        lbl_a8->setObjectName(QString::fromUtf8("lbl_a8"));
        lbl_a8->setGeometry(QRect(211, 366, 172, 155));
        lbl_a8->setStyleSheet(QString::fromUtf8("border : 1px solid blue;"));
        lbl_a8->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/imgs/8.jpg")));
        lbl_a8->setScaledContents(true);
        lbl_Blank = new QLabel(centralWidget);
        lbl_Blank->setObjectName(QString::fromUtf8("lbl_Blank"));
        lbl_Blank->setGeometry(QRect(398, 366, 172, 155));
        lbl_Blank->setStyleSheet(QString::fromUtf8("border : 1px solid blue;"));
        lbl_Blank->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/imgs/Blank.JPG")));
        lbl_Blank->setScaledContents(true);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 840, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Puzzle8_Solver", nullptr));
        lbl_Back->setText(QString());
        btn_input->setText(QCoreApplication::translate("MainWindow", "&Input", nullptr));
        btn_solve->setText(QCoreApplication::translate("MainWindow", "&Solve", nullptr));
        btn_refresh->setText(QCoreApplication::translate("MainWindow", "&Refresh", nullptr));
        lbl_algo->setText(QCoreApplication::translate("MainWindow", "Algorithm :", nullptr));
        combo_algorithm->setItemText(0, QCoreApplication::translate("MainWindow", "UCS", nullptr));
        combo_algorithm->setItemText(1, QCoreApplication::translate("MainWindow", "BFS", nullptr));
        combo_algorithm->setItemText(2, QCoreApplication::translate("MainWindow", "DFS", nullptr));

        lbl_solution->setText(QCoreApplication::translate("MainWindow", "Solution : ", nullptr));
        lbl_r1->setText(QCoreApplication::translate("MainWindow", "Moves : ", nullptr));
        lbl_moves->setText(QString());
        lbl_r2->setText(QCoreApplication::translate("MainWindow", "Time(ms) :", nullptr));
        lbl_time->setText(QString());
        btn_nextstep->setText(QCoreApplication::translate("MainWindow", "Next Step", nullptr));
        lbl_info->setText(QCoreApplication::translate("MainWindow", "Poorya mohammadi nasab", nullptr));
        lbl_a1->setText(QString());
        lbl_a2->setText(QString());
        lbl_a3->setText(QString());
        lbl_a4->setText(QString());
        lbl_a5->setText(QString());
        lbl_a6->setText(QString());
        lbl_a7->setText(QString());
        lbl_a8->setText(QString());
        lbl_Blank->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
