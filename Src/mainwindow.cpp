#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "common.h"

#include<QColorDialog>
#include<QFileDialog>

Property gproperty;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->width(), this->height());

    setWindowTitle("CG2017-151220026");

    ui->pushButton_3->setStyleSheet("background-color: rgb(0, 0, 0);");
    ui->toolButton->setChecked(true);


    //Note: Icon pictures all loaded in mainwindow.ui

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_toolButton_clicked()
{
    ui->toolButton_2->setChecked(false);
    ui->toolButton->setChecked(true);
    SELECT = LINE;
}

void MainWindow::on_toolButton_2_clicked()
{
    ui->toolButton_2->setChecked(true);
    ui->toolButton->setChecked(false);
    SELECT = CIRCLE;
}

void MainWindow::on_pushButton_clicked()
{
    graph.clear();
    ui->widget->update();
}

void MainWindow::on_pushButton_2_clicked()
{
    if(!graph.empty())
        graph.pop_back();
    ui->widget->update();
}

void MainWindow::on_pushButton_3_clicked()
{
    gproperty.color = QColorDialog::getColor(gproperty.color, this);

    ui->pushButton_3->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").arg(QString::number(gproperty.color.red()),
                                                                QString::number(gproperty.color.green()),
                                                                QString::number(gproperty.color.blue())));
    if(gproperty.color.isValid())
        ui->widget->changecolor(gproperty.color);

}

void MainWindow::on_pushButton_4_clicked()
{
    QString fileName =
    QFileDialog::getSaveFileName(this,
                                 QString("Save"),
                                 QCoreApplication::applicationDirPath(),
                                 tr("Config Files (*.jpg)"));
    if(fileName.isNull()) return;

    QPixmap pixmap = ui->widget->grab();
    pixmap.save(QString(fileName),"JPG");

}
