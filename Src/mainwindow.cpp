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

    ui->widget->setMouseTracking(true);
    STATE = DRAW;
    //Notice: Icon pictures all loaded in mainwindow.ui

    connect(ui->widget, SIGNAL(clickchoose()), this, SLOT(on_toolButton_4_clicked()));
    connect(ui->widget, SIGNAL(getxy(int,int)), this, SLOT(setxy(int,int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//line
void MainWindow::on_toolButton_clicked()
{
    ClearSelect();
    ui->toolButton_2->setChecked(false);
    ui->toolButton_3->setChecked(false);
    ui->toolButton_4->setChecked(false);
    ui->toolButton_5->setChecked(false);

    ui->toolButton_7->setChecked(false);
    ui->toolButton->setChecked(true);


    STATE = DRAW;
    SELECT = LINE;
}

//circle
void MainWindow::on_toolButton_2_clicked()
{
    ClearSelect();
    ui->toolButton->setChecked(false);
    ui->toolButton_3->setChecked(false);
    ui->toolButton_4->setChecked(false);
    ui->toolButton_5->setChecked(false);

    ui->toolButton_7->setChecked(false);
    ui->toolButton_2->setChecked(true);


    STATE = DRAW;
    SELECT = CIRCLE;
}

//elliipse
void MainWindow::on_toolButton_3_clicked()
{
    ClearSelect();
    ui->toolButton->setChecked(false);
    ui->toolButton_2->setChecked(false);
    ui->toolButton_4->setChecked(false);
    ui->toolButton_5->setChecked(false);

    ui->toolButton_7->setChecked(false);
    ui->toolButton_3->setChecked(true);

    STATE = DRAW;
    SELECT = ELLIPSE;
}

//choose
void MainWindow::on_toolButton_4_clicked()
{
    ui->toolButton->setChecked(false);
    ui->toolButton_2->setChecked(false);
    ui->toolButton_3->setChecked(false);
    ui->toolButton_5->setChecked(false);

    ui->toolButton_7->setChecked(false);
    ui->toolButton_4->setChecked(true);

    STATE = CHOOSE;
}


//polygon
void MainWindow::on_toolButton_5_clicked()
{
    ClearSelect();
    ui->toolButton->setChecked(false);
    ui->toolButton_2->setChecked(false);
    ui->toolButton_3->setChecked(false);
    ui->toolButton_4->setChecked(false);

    ui->toolButton_7->setChecked(false);
    ui->toolButton_5->setChecked(true);


    STATE = DRAW;
    SELECT = POLYGON;
}

//rotate
void MainWindow::on_toolButton_7_clicked()
{
    if(current == nullptr)
    {
       on_toolButton_4_clicked();
       QMessageBox::warning(NULL, "warning", "No graph selected!", QMessageBox::Ok);
       return;
    }
    ui->toolButton->setChecked(false);
    ui->toolButton_2->setChecked(false);
    ui->toolButton_3->setChecked(false);
    ui->toolButton_4->setChecked(false);
    ui->toolButton_5->setChecked(false);


    ui->toolButton_7->setChecked(true);

    STATE = ROTATE;
    rotate_start = false;


}

void MainWindow::ClearSelect()
{
    foreach (auto g, graph)
    {
      g->setSelect(false);
    }
    current = nullptr;
    ui->widget->update();
    ui->widget->setCursor(Qt::ArrowCursor);
    locked = false;
}


void MainWindow::on_pushButton_clicked()
{
    graph.clear();
    points_for_polygon.clear();
    polygon_start = false;
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

void MainWindow::on_toolButton_8_clicked()
{
    if(current == nullptr)
    {
       on_toolButton_4_clicked();
       QMessageBox::warning(NULL, "warning", "No graph selected!", QMessageBox::Ok);
       return;
    }

    current->setFill(true);
    current->setColor(gproperty.color);
    ui->widget->update();
}

void MainWindow::setxy(int x, int y)
{
    ui->label->setText(QString("X: " + QString("%1").arg(x)));
    ui->label_2->setText(QString("Y: " + QString("%1").arg(y)));
}
