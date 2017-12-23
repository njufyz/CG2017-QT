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

    void setxy(int x, int y);

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



private:
    Ui::MainWindow *ui;
    void  ClearSelect();
    void  ClearButton(int i);
    void  CloseSlide();

signals:
    void clickchoose();
    void getxy(int , int);
};

#endif // MAINWINDOW_H
