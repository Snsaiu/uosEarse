#include "userlevel.h"
#include "ui_userlevel.h"
#include "login.h"
#include<qmessagebox.h>
#include <QDesktopWidget>

UserLevel::UserLevel(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::UserLevel)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->activateWindow();
    this->setModal(true);

    //设置窗体居中
    QDesktopWidget *desk=QApplication::desktop();
    int wd=desk->width();
    int ht=desk->height();
    this->move((wd-this->width())/2,(ht-this->height())/2);

    this->setStyleSheet("background:#e2e2e2");
    //阻塞除当前窗体之外的所有的窗体
    this->setWindowModality(Qt::ApplicationModal);
//    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);

    radioId = 0;
    btnGroupRadio = new QButtonGroup(this);
    btnGroupRadio->addButton(ui->radioButton_0,0);
    btnGroupRadio->addButton(ui->radioButton_1,1);
    btnGroupRadio->addButton(ui->radioButton_2,2);
    ui->radioButton_0->setChecked(true);
    connect(ui->radioButton_0,SIGNAL(clicked()),this,SLOT(onRadioGroupClick()));
    connect(ui->radioButton_1,SIGNAL(clicked()),this,SLOT(onRadioGroupClick()));
    connect(ui->radioButton_2,SIGNAL(clicked()),this,SLOT(onRadioGroupClick()));
}

UserLevel::~UserLevel()
{
    delete ui;
}

void UserLevel::on_OK_btn_pressed()
{
    radioId = btnGroupRadio->checkedId();

    int flag = Login::PublicUserId;
    if((flag <2&&radioId!=flag)||(flag==2&&radioId==1))
    {
        QMessageBox::warning(this,"警告","没有修改的权限！");
        return;
    }
    emit hasData();
    this->hide();
}

void UserLevel::UiExit()
{
    this->close();
}

void UserLevel::on_CancelBtn_pressed()
{
    this->hide();
}
