#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMouseEvent>
#include<QLabel>
#include "form.h"
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

    void setxy(int x, int y);

    void showslider();

    void on_verticalSlider_valueChanged(int value);

    void on_Button1_clicked();

    void on_Button2_clicked();

    void on_Button3_clicked();

    void on_Button4_clicked();

    void on_Button5_clicked();

    void on_Button6_clicked();

    void on_Button7_clicked();

    void on_Button8_clicked();

    void on_Button9_clicked();

    void on_Button10_clicked();

    void on_Button11_clicked();

    void on_Button12_clicked();

    void on_verticalSlider_sliderReleased();

    void on_Button13_clicked();

    void on_Button14_clicked();

    void on_Button15_clicked();

private:
    Ui::MainWindow *ui;
    Form* form;
    void  ClearSelect();
    void  ClearButton(int i);
    void  CloseSlide();

signals:
    void clickchoose();
    void getxy(int , int);
    void startscale();
    void switchButton();
};

#endif // MAINWINDOW_H
