#include "choose.h"
#include "ui_choose.h"


choose::choose(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::choose)
{
    ui->setupUi(this);
    this->setWindowTitle("擦除模式");
    this->setWindowFlags(Qt::Dialog);

    connect(this->ui->trueBtn,&QPushButton::pressed,[=]{
        {
            this->close();
        }
    });
}

choose::~choose()
{
    delete ui;
}

