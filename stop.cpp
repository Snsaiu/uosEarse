#include "stop.h"
#include "ui_stop.h"

stop::stop(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stop)
{
    ui->setupUi(this);

    this->setWindowTitle("警告");
//    this->setWindowFlags(Qt::Dialog);
    this->setModal(true);

    connect(this->ui->cancleBtn,&QPushButton::pressed,[=]{
        {
            this->close();
        }
    });

    connect(this->ui->okBtn,&QPushButton::pressed,[=]{
        {
            emit this->CancelEarseSignal(this->Index);
            this->close();
        }
    });
}

stop::~stop()
{
    delete ui;
}

QString stop::getIndex() const
{
    return Index;
}

void stop::setIndex(QString value)
{
    Index = value;
}
