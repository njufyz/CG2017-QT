#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "common.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    select = LINE;
}

void MainWindow::on_pushButton_2_clicked()
{
    select = CIRCLE;
}

void MainWindow::on_pushButton_3_clicked()
{
    graph.clear();
    ui->widget->update();
}

void MainWindow::on_pushButton_4_clicked()
{
    if(!graph.empty())
        graph.pop_back();
    ui->widget->update();
}
