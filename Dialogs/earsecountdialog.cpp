#include "earsecountdialog.h"
#include "ui_earsecountdialog.h"
#include "checkerModule/harddiskmodel.h"
#include <qmessagebox.h>

EarseCountDialog::EarseCountDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EarseCountDialog)
{
    ui->setupUi(this);
    this->setModal(true);

//    this->group.addButton(this->ui->oneRbtn,1);
//    this->group.addButton(this->ui->threeRbtn,3);
//    this->group.addButton(this->ui->sixRbtn,6);
//     this->group.addButton(this->ui->twelveRbtn,12);

    this->connect(this->ui->okBtn,&QPushButton::pressed,this,[=](){


        string Approver = this->ui->ApproverEdit->text().toStdString();
        string Department = this->ui->DepartmentEdit->text().toStdString();
        string Earser = this->ui->EarserEdit->text().toStdString();
        if(Approver==""||Department==""||Earser=="")
        {
            QMessageBox::warning(this,"警告","请确定所有内容都已填写！！！");
            return;
        }

        //int index= this->group.checkedId();
        int index = 2;

        emit this->EarseCountSignal(Approver,Department,Earser,index);
        emit this->EarseMessageModelSignal(this->messageModel);
        this->close();

    });
}

EarseCountDialog::~EarseCountDialog()
{
    delete ui;
}

QString EarseCountDialog::getSerial() const
{
    return serial;
}

void EarseCountDialog::setSerial(const QString &value)
{
    serial = value;
}

void EarseCountDialog::setMessageModel(MessageModel value)
{
    messageModel = value;
}



void EarseCountDialog::on_cancelBtn_pressed()
{
    this->close();
}


