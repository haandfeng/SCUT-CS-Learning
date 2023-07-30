#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<string>
#include <QMainWindow>
#include <QPushButton>
#include "mysearch.h"
#include <QVector>
#include <QLabel>
#include <QMessageBox>
#include <QRadioButton>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    int searchType = 0;
    string init_state = "123456780";
    string goal_state = "123456780";
    MySearch* s;
    QVector<QLabel*>table;
    QVector<QRadioButton*> buttonList;
private:
    void setTable(string& s);
};
#endif // MAINWINDOW_H
