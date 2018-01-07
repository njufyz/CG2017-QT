#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "common.h"

#include<QColorDialog>
#include<QFileDialog>
#include<QMessageBox>
#include<QLabel>
#include<QStatusBar>

Property gproperty;
const int n_Button = 15;
QPushButton *pushButton[n_Button + 1];

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->width(), this->height());
    setWindowTitle("CG2017-151220026");

    ui->Button7->setStyleSheet("background-color: rgb(0, 0, 0);");
    ui->Button1->setChecked(true);
    ui->widget->setMouseTracking(true);
    ui->verticalSlider->close();

    connect(ui->widget, SIGNAL(clickchoose()), this, SLOT(on_Button5_clicked()));
    connect(ui->widget, SIGNAL(getxy(int,int)), this, SLOT(setxy(int,int)));
    connect(ui->widget, SIGNAL(startscale()), this, SLOT(showslider()));
    connect(this, SIGNAL(switchButton()), ui->widget, SLOT(clearPoints()));

    pushButton[0] = nullptr;
    pushButton[1] = ui->Button1;
    pushButton[2] = ui->Button2;
    pushButton[3] = ui->Button3;
    pushButton[4] = ui->Button4;
    pushButton[5] = ui->Button5;
    pushButton[6] = ui->Button6;
    pushButton[7] = ui->Button7;
    pushButton[8] = ui->Button8;
    pushButton[9] = ui->Button9;
    pushButton[10] = ui->Button10;
    pushButton[11] = ui->Button11;
    pushButton[12] = ui->Button12;
    pushButton[13] = ui->Button13;
    pushButton[14] = ui->Button14;
    pushButton[15] = ui->Button15;

    STATE = DRAW;


}

MainWindow::~MainWindow()
{
    delete ui;
}

#include<QDebug>
void MainWindow::keyPressEvent(QKeyEvent *event)
{
   if(SELECT != CUBE)
        return;
   switch(event->key()){
   case Qt::Key_Up : AngleX -= 5; break;
   case Qt::Key_Down: AngleX += 5; break;
   case Qt::Key_Left:AngleY -= 5; break;
   case Qt::Key_Right:AngleY +=5; break;
   defalut: break;
   }
   this->ui->widget->update();


}

//line
void MainWindow::on_Button1_clicked()
{
    ClearSelect();
    ClearButton(1);

    STATE = DRAW;
    SELECT = LINE;
}

//circle
void MainWindow::on_Button2_clicked()
{
    ClearSelect();
    ClearButton(2);


    STATE = DRAW;
    SELECT = CIRCLE;
}

//elliipse
void MainWindow::on_Button3_clicked()
{
    ClearSelect();
    ClearButton(3);
    STATE = DRAW;
    SELECT = ELLIPSE;
}

//polygon
void MainWindow::on_Button4_clicked()
{
    ClearSelect();
    ClearButton(4);

    STATE = DRAW;
    SELECT = POLYGON;
}

//bezier
void MainWindow::on_Button13_clicked()
{
    ClearSelect();
    ClearButton(13);


    STATE = DRAW;
    SELECT = BEZIER;
}

//cube
void MainWindow::on_Button15_clicked()
{
    ClearButton(15);
    SELECT = CUBE;
}


//choose
void MainWindow::on_Button5_clicked()
{
    ClearButton(5);
    CloseSlide();
    STATE = CHOOSE;
}

//scale
void MainWindow::on_Button6_clicked()
{
    if(current == nullptr)
    {
       on_Button5_clicked();
       QMessageBox::warning(NULL, "warning", "No graph selected!", QMessageBox::Ok);
       return;
    }
    ClearButton(6);

    STATE = SCALE;
}

//color
void MainWindow::on_Button7_clicked()
{
    gproperty.color = QColorDialog::getColor(gproperty.color, this);

    ui->Button7->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").arg(QString::number(gproperty.color.red()),
                                                                QString::number(gproperty.color.green()),
                                                                QString::number(gproperty.color.blue())));
    if(gproperty.color.isValid())
        ui->widget->changecolor(gproperty.color);
}

//rotate
void MainWindow::on_Button8_clicked()
{
    if(current == nullptr)
    {
       on_Button5_clicked();
       QMessageBox::warning(NULL, "warning", "No graph selected!", QMessageBox::Ok);
       return;
    }
   ClearButton(8);

    STATE = ROTATE;
    rotate_start = false;
}

//file
void MainWindow::on_Button9_clicked()
{
    QString fileName =
    QFileDialog::getSaveFileName(this,
                                 QString("Save"),
                                 QCoreApplication::applicationDirPath(),
                                 tr("Config Files (*.jpg)"));
    if(fileName.isNull()) return;
    ClearButton(9);
    QPixmap pixmap = ui->widget->grab();
    pixmap.save(QString(fileName),"JPG");
}

//clip
void MainWindow::on_Button14_clicked()
{
    if(current == nullptr)
    {
       on_Button5_clicked();
       QMessageBox::warning(NULL, "warning", "No graph selected!", QMessageBox::Ok);
       return;
    }
    ClearButton(14);

    STATE = CLIP;
}

//fill
void MainWindow::on_Button10_clicked()
{
    if(current == nullptr)
    {
       on_Button5_clicked();
       QMessageBox::warning(NULL, "warning", "No graph selected!", QMessageBox::Ok);
       return;
    }

    current->setFill(true);
    current->setColor(gproperty.color);
    ui->widget->update();
}

//undo
void MainWindow::on_Button11_clicked()
{
    if(!graph.empty())
        graph.pop_back();
    ui->widget->update();
}

//clear
void MainWindow::on_Button12_clicked()
{
    graph.clear();
    points_for_polygon.clear();
    polygon_start = false;
    ui->widget->update();
}


void MainWindow::setxy(int x, int y)
{
    ui->label->setText(QString("X: " + QString("%1").arg(x)));
    ui->label_2->setText(QString("Y: " + QString("%1").arg(y)));
}

void MainWindow::showslider()
{
    ui->verticalSlider->show();
}

void MainWindow::on_verticalSlider_valueChanged(int value)
{
    scale_last = scale_cur;
    scale_cur = value;
    current->scale(scale_point, 1.0 * (scale_cur - scale_last) /50 + 1) ;
    ui->widget->update();
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

void MainWindow::ClearButton(int index)
{
    if(index != 6)
       CloseSlide();

    for(int i = 1; i <= n_Button; i++)
    {
        if(i != index)
            pushButton[i]->setChecked(false);
        else
            pushButton[i]->setChecked(true);
    }

     emit switchButton();
}

void MainWindow::CloseSlide()
{
    ui->verticalSlider->close();
    scale_cur = scale_last = 50;
    ui->verticalSlider->setValue(50);
    scale_point = Point(0, 0);
    ui->widget->update();
}


void MainWindow::on_verticalSlider_sliderReleased()
{
   on_Button5_clicked();
}

