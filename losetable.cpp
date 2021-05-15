#include "losetable.h"
#include "ui_losetable.h"
#include "LogSql.h"
#include <QPushButton>
#include <Dialogs/earsecountdialog.h>
#include<QVector>

extern QMap <string,string> PortMap;

losetable::losetable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::losetable)
{
    ui->setupUi(this);
    this->SetId("error");
    this->_messageMediator->Regist(this);
    ui->losetableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->losetableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->losetableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:#143D70;font:15pt '黑体';color:black;}");
         ui->losetableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{font:15pt '黑体';color:black;bs:#2042b1;}");
    /*表格外边框去除*/
    ui->losetableWidget->setFrameShape(QFrame::NoFrame);
    ui->losetableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

losetable::~losetable()
{
    this->_messageMediator->UnRegist(this);
    delete ui;
}

void losetable::Notify(MessageModel model)
{
    string TempPort;
    if(PortMap.contains(model.Serial.toStdString()))
    {
         QMap <string,string>::iterator iter = PortMap.find(model.Serial.toStdString());
         TempPort = iter.value();
    }

    int count = this->ui->losetableWidget->rowCount();
    this->ui->losetableWidget->insertRow(count);
    this->ui->losetableWidget->setItem(count,0,new QTableWidgetItem(model.DiskModel));
    ui->losetableWidget->item(count,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    this->ui->losetableWidget->setItem(count,1,new QTableWidgetItem(model.Serial));
    ui->losetableWidget->item(count,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    this->ui->losetableWidget->setItem(count,2,new QTableWidgetItem(model.DiskPath));
    ui->losetableWidget->item(count,2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    this->ui->losetableWidget->setItem(count,3,new QTableWidgetItem(model.Size));
    ui->losetableWidget->item(count,3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    this->ui->losetableWidget->setItem(count,4,new QTableWidgetItem(model.ErrotMessage));
    ui->losetableWidget->item(count,4)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    this->ui->losetableWidget->setItem(count,5,new QTableWidgetItem(QString::fromStdString(TempPort)));
    ui->losetableWidget->item(count,5)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_time =current_date_time.toString("yyyy.MM.dd hh:mm:ss");
    this->ui->losetableWidget->setItem(count,6,new QTableWidgetItem(current_time));
    ui->losetableWidget->item(count,6)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    QPushButton *reBtn=new QPushButton();
    //this->ui->losetableWidget->setCellWidget(count,6,reBtn);

    reBtn->setText("重试");
    reBtn->connect(reBtn,&QPushButton::pressed,this,[=](){

        // here send info to waittable to get diskhard is exist



        EarseCountDialog *earseCountDialog=new EarseCountDialog ();
        earseCountDialog->setSerial(model.Serial);
        earseCountDialog->setMessageModel(model);
        earseCountDialog->connect(earseCountDialog,&EarseCountDialog::EarseMessageModelSignal,this,[=](MessageModel temp){


            for (int p=0;p<this->ui->losetableWidget->rowCount();p++) {

                if(earseCountDialog->getSerial().compare(this->ui->losetableWidget->item(p,1)->text())==0)
                {
                    MessageModel *reModel=new MessageModel();
                    reModel->Size=this->ui->losetableWidget->item(p,3)->text();
                    reModel->Serial=this->ui->losetableWidget->item(p,1)->text();
                    reModel->DiskPath=this->ui->losetableWidget->item(p,2)->text();
                    reModel->DiskModel=this->ui->losetableWidget->item(p,0)->text();
                    reModel->Secret=temp.Secret;
                    reModel->Summery=temp.Summery;
                    reModel->Approver=temp.Approver;
                    reModel->DiskType=temp.DiskType;
                    reModel->Department=temp.Department;
                    reModel->DiskPurpose=temp.DiskPurpose;
                    reModel->EarseCount=temp.EarseCount;
                    reModel->Earser=temp.Earser;
                    reModel->DiskDirection=temp.DiskDirection;
                    reModel->SendType=model.SendType;
                    if(reModel->SendType==0)
                    {
                        reModel->SendType=2;
                    }
                    this->_messageMediator->Send("wait",*reModel);
                    this->ui->losetableWidget->removeRow(p);

                    break;
                }

            }

            QString  type = "重试按钮";
            QString  YN = "擦除" + model.EarseCount + "次"+" 秘级:"+model.Secret
                    +" 审批人:"+model.Approver+" 部门:"+model.Department+" 责任人:"+model.Earser
                    +" 介质类型:"+model.DiskType+" 磁盘序列号:"+model.Serial
                    +" 容量:"+model.Summery+"G"+" 用途:"+model.DiskPurpose
                    +" 介质去向:"+model.DiskDirection;
            LogSql log;
            log.RunInsert(YN,type);

        });
        earseCountDialog->show();
        earseCountDialog->setAttribute(Qt::WA_DeleteOnClose);


    });
}
