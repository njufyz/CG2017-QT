#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    update();
}

Form::~Form()
{
    delete ui;
}

void Form::display()
{
    update();
}
