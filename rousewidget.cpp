#include "rousewidget.h"
#include "ui_rousewidget.h"

RouseWidget::RouseWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RouseWidget)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);

}

RouseWidget::~RouseWidget()
{
    delete ui;
}

void RouseWidget::initPwd()
{
    ui->password->setText("");
}

void RouseWidget::setUserName(QString userName)
{
    ui->userName->setText(userName);
}

void RouseWidget::on_loginBtn_clicked()
{
    emit GoLogin();
    this->close();
}
