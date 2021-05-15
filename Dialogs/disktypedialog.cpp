#include "disktypedialog.h"
#include "ui_disktypedialog.h"
#include <qdesktopwidget.h>
#include <qmap.h>

QMap <string,string> PortMap;
diskTypeDialog::diskTypeDialog(HardDiskModel *model,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::diskTypeDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setModal(true);
    //设置窗体居中
    QDesktopWidget *desk=QApplication::desktop();
    int wd=desk->width();
    int ht=desk->height();
    this->move((wd-this->width())/2,(ht-this->height())/2);

    HardDiskModel* p=new HardDiskModel ();

    this->ui->modeTxt->setText(QString::fromStdString(model->DiskModel));
    this->ui->seriTxt->setText(QString::fromStdString(model->Serial));

    this->connect(this->ui->okResultBtn,&QPushButton::pressed,this,[=](){
        QString text= this->ui->diskTypeCbox->currentText();
        QString diskpurpos= this->ui->diskPurposeTxt->toPlainText();
        model->DiskPurpose=diskpurpos.toStdString();
        model->DiskType=text.toStdString();
        model->Secret=this->ui->secretCbox->currentText().toStdString();
        model->ports = this->ui->PortComboBox->currentText().toStdString();
        model->DiskDirection=this->ui->diskDirectionTxt->toPlainText().toStdString();
        if(PortMap.contains(model->Serial))
        {
             QMap <string,string>::iterator iter = PortMap.find(model->Serial);
             iter.value() = model->ports;
        }
        else {
            PortMap.insert(model->Serial,model->ports);
        }
        this->close();
    });
    this->connect(this->ui->cancelBtn,&QPushButton::pressed,this,[=](){
        QString text= this->ui->diskTypeCbox->currentText();
        QString diskpurpos= this->ui->diskPurposeTxt->toPlainText();
        model->DiskPurpose=diskpurpos.toStdString();
        model->DiskType=text.toStdString();
        model->Secret=this->ui->secretCbox->currentText().toStdString();
        model->ports = this->ui->PortComboBox->currentText().toStdString();
        model->DiskDirection=this->ui->diskDirectionTxt->toPlainText().toStdString();
       this->close();
    });

//    this->connect(this,&diskTypeDialog::c,this,[=](){
//        QString text= this->ui->diskTypeCbox->currentText();
//        QString diskpurpos= this->ui->diskPurposeTxt->toPlainText();
//        model->DiskPurpose=diskpurpos.toStdString();
//        model->DiskType=text.toStdString();
//        model->Secret=this->ui->secretCbox->currentText().toStdString();
//        model->DiskDirection=this->ui->diskDirectionTxt->toPlainText().toStdString();
////       this->close();
//    });


}

diskTypeDialog::~diskTypeDialog()
{
    delete ui;
}

//void diskTypeDialog::OkResultSlots()
//{
////    IsChange = true;
//    ui->comboBox->currentIndex();

//}

//bool diskTypeDialog::getRadio(int &count)
//{
////    count = radioId;
////    return IsChange;
//}
