#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QDebug>
#include<QMouseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_toolButton_3_clicked();

    void on_toolButton_4_clicked();

    void on_toolButton_5_clicked();

    void on_toolButton_7_clicked();

    void on_toolButton_8_clicked();

    void setxy(int x, int y);

    void on_toolButton_6_clicked();

    void on_verticalSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    void  ClearSelect();

signals:
    void clickchoose();
    void getxy(int , int);
};

#endif // MAINWINDOW_H
