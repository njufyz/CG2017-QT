#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "common.h"

#include<QColorDialog>
#include<QFileDialog>
#include<QMessageBox>

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

    STATE = DRAW;

    //Note: Icon pictures all loaded in mainwindow.ui

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_toolButton_clicked()
{
    ClearSelect();
    ui->toolButton_2->setChecked(false);
    ui->toolButton_3->setChecked(false);
    ui->toolButton_4->setChecked(false);
    ui->toolButton_5->setChecked(false);
    ui->toolButton_6->setChecked(false);

    STATE = DRAW;
    SELECT = LINE;
}

void MainWindow::on_toolButton_2_clicked()
{
    ClearSelect();
    ui->toolButton->setChecked(false);
    ui->toolButton_3->setChecked(false);
    ui->toolButton_4->setChecked(false);
    ui->toolButton_5->setChecked(false);
    ui->toolButton_6->setChecked(false);

    STATE = DRAW;
    SELECT = CIRCLE;
}

void MainWindow::on_toolButton_3_clicked()
{
    ClearSelect();
    ui->toolButton->setChecked(false);
    ui->toolButton_2->setChecked(false);
    ui->toolButton_4->setChecked(false);
    ui->toolButton_5->setChecked(false);
    ui->toolButton_6->setChecked(false);

    STATE = DRAW;
    SELECT = ELLIPSE;
}

void MainWindow::on_toolButton_4_clicked()
{
    ui->toolButton->setChecked(false);
    ui->toolButton_2->setChecked(false);
    ui->toolButton_3->setChecked(false);
    ui->toolButton_5->setChecked(false);
    ui->toolButton_6->setChecked(false);

    STATE = CHOOSE;
}

void MainWindow::on_toolButton_5_clicked()
{
    ClearSelect();
    ui->toolButton->setChecked(false);
    ui->toolButton_2->setChecked(false);
    ui->toolButton_3->setChecked(false);
    ui->toolButton_4->setChecked(false);
    ui->toolButton_6->setChecked(false);

    STATE = DRAW;
    SELECT = POLYGON;
}

void MainWindow::on_toolButton_6_clicked()
{
    ui->toolButton->setChecked(false);
    ui->toolButton_2->setChecked(false);
    ui->toolButton_3->setChecked(false);
    ui->toolButton_4->setChecked(false);
    ui->toolButton_5->setChecked(false);

    if(current == nullptr)
    {
       ui->toolButton_4->setChecked(true);
       STATE = CHOOSE;
       ui->toolButton_6->setChecked(false);
       QMessageBox::warning(NULL, "warning", "No graph selected!", QMessageBox::Ok);
       return;
    }
    else
    {
        STATE = TRANSLATION;
    }
}

void MainWindow::ClearSelect()
{
    foreach (auto g, graph)
    {
      g->setSelect(false);
    }
    current = nullptr;
    ui->widget->update();
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



