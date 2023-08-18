/********************************************************************************
** Form generated from reading UI file 'input_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUT_DIALOG_H
#define UI_INPUT_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_input_dialog
{
public:
    QLineEdit *txt_1;
    QLineEdit *txt_2;
    QLineEdit *txt_3;
    QLineEdit *txt_4;
    QLineEdit *txt_5;
    QLineEdit *txt_6;
    QLineEdit *txt_7;
    QLineEdit *txt_8;
    QLineEdit *txt_9;
    QLabel *label;
    QLabel *lbl_back;
    QPushButton *btn_set;
    QPushButton *Btn_random;

    void setupUi(QDialog *input_dialog)
    {
        if (input_dialog->objectName().isEmpty())
            input_dialog->setObjectName(QString::fromUtf8("input_dialog"));
        input_dialog->resize(250, 365);
        input_dialog->setStyleSheet(QString::fromUtf8(""));
        txt_1 = new QLineEdit(input_dialog);
        txt_1->setObjectName(QString::fromUtf8("txt_1"));
        txt_1->setGeometry(QRect(10, 10, 70, 70));
        QFont font;
        font.setPointSize(33);
        txt_1->setFont(font);
        txt_1->setInputMethodHints(Qt::ImhNone);
        txt_1->setAlignment(Qt::AlignCenter);
        txt_2 = new QLineEdit(input_dialog);
        txt_2->setObjectName(QString::fromUtf8("txt_2"));
        txt_2->setGeometry(QRect(90, 10, 70, 70));
        txt_2->setFont(font);
        txt_2->setAlignment(Qt::AlignCenter);
        txt_3 = new QLineEdit(input_dialog);
        txt_3->setObjectName(QString::fromUtf8("txt_3"));
        txt_3->setGeometry(QRect(170, 10, 70, 70));
        txt_3->setFont(font);
        txt_3->setAlignment(Qt::AlignCenter);
        txt_4 = new QLineEdit(input_dialog);
        txt_4->setObjectName(QString::fromUtf8("txt_4"));
        txt_4->setGeometry(QRect(10, 90, 70, 70));
        txt_4->setFont(font);
        txt_4->setAlignment(Qt::AlignCenter);
        txt_5 = new QLineEdit(input_dialog);
        txt_5->setObjectName(QString::fromUtf8("txt_5"));
        txt_5->setGeometry(QRect(90, 90, 70, 70));
        txt_5->setFont(font);
        txt_5->setAlignment(Qt::AlignCenter);
        txt_6 = new QLineEdit(input_dialog);
        txt_6->setObjectName(QString::fromUtf8("txt_6"));
        txt_6->setGeometry(QRect(170, 90, 70, 70));
        txt_6->setFont(font);
        txt_6->setAlignment(Qt::AlignCenter);
        txt_7 = new QLineEdit(input_dialog);
        txt_7->setObjectName(QString::fromUtf8("txt_7"));
        txt_7->setGeometry(QRect(10, 170, 70, 70));
        txt_7->setFont(font);
        txt_7->setAlignment(Qt::AlignCenter);
        txt_8 = new QLineEdit(input_dialog);
        txt_8->setObjectName(QString::fromUtf8("txt_8"));
        txt_8->setGeometry(QRect(90, 170, 70, 70));
        txt_8->setFont(font);
        txt_8->setAlignment(Qt::AlignCenter);
        txt_9 = new QLineEdit(input_dialog);
        txt_9->setObjectName(QString::fromUtf8("txt_9"));
        txt_9->setGeometry(QRect(170, 170, 70, 70));
        txt_9->setFont(font);
        txt_9->setAlignment(Qt::AlignCenter);
        label = new QLabel(input_dialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 260, 230, 25));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        label->setFont(font1);
        label->setStyleSheet(QString::fromUtf8("border : 3px solid rgb(164, 0, 0);\n"
"background-color: rgb(252, 233, 79);"));
        label->setAlignment(Qt::AlignCenter);
        lbl_back = new QLabel(input_dialog);
        lbl_back->setObjectName(QString::fromUtf8("lbl_back"));
        lbl_back->setGeometry(QRect(0, 0, 250, 365));
        lbl_back->setStyleSheet(QString::fromUtf8("background-color: rgb(173, 127, 168);"));
        btn_set = new QPushButton(input_dialog);
        btn_set->setObjectName(QString::fromUtf8("btn_set"));
        btn_set->setGeometry(QRect(75, 325, 100, 25));
        Btn_random = new QPushButton(input_dialog);
        Btn_random->setObjectName(QString::fromUtf8("Btn_random"));
        Btn_random->setGeometry(QRect(75, 295, 100, 25));
        lbl_back->raise();
        txt_1->raise();
        txt_2->raise();
        txt_3->raise();
        txt_4->raise();
        txt_5->raise();
        txt_6->raise();
        txt_7->raise();
        txt_8->raise();
        txt_9->raise();
        label->raise();
        btn_set->raise();
        Btn_random->raise();

        retranslateUi(input_dialog);

        QMetaObject::connectSlotsByName(input_dialog);
    } // setupUi

    void retranslateUi(QDialog *input_dialog)
    {
        input_dialog->setWindowTitle(QCoreApplication::translate("input_dialog", "Input", nullptr));
        txt_1->setText(QString());
        txt_2->setText(QString());
        txt_3->setText(QString());
        txt_4->setText(QString());
        txt_5->setText(QString());
        txt_6->setText(QString());
        txt_7->setText(QString());
        txt_8->setText(QString());
        txt_9->setText(QString());
        label->setText(QCoreApplication::translate("input_dialog", "Enter '0' for Blank", nullptr));
        lbl_back->setText(QString());
        btn_set->setText(QCoreApplication::translate("input_dialog", "&SET", nullptr));
        Btn_random->setText(QCoreApplication::translate("input_dialog", "&Random", nullptr));
    } // retranslateUi

};

namespace Ui {
    class input_dialog: public Ui_input_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUT_DIALOG_H
