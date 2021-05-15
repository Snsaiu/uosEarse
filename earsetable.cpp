#include "earsetable.h"
#include "ui_earsetable.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
#include "diskinfo.h"
#include "LogSql.h"
#include <QUuid>
#include <EarseModuls/earseone.h>
#include <EarseModuls/earsestrategy.h>
#include <EarseModuls/earsezero.h>
#include "EarseModuls/earserandom.h"
#include<QVector>

extern QMap <string,string> PortMap;
QVector<EarseStrategy*> strategy;

earsetable::earsetable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::earsetable)
{
    ui->setupUi(this);
    this->SetId("earsing");
    this->_messageMediator->Regist(this);

    ui->earsetableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->earsetableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->earsetableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:#143D70;font:15pt '黑体';color:black;}");
    ui->earsetableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{font:15pt '黑体';color:black;bs:#2042b1;}");
    /*表格外边框去除*/
    ui->earsetableWidget->setFrameShape(QFrame::NoFrame);
    ui->earsetableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);



}

earsetable::~earsetable()
{
    this->_messageMediator->UnRegist(this);
    delete ui;
}

void earsetable::Notify(MessageModel model)
{

    if(model.SendType == 1)
    {


        //todo /home/zjsj/Desktop
        QString logFile="/opt/" +QUuid().createUuid().toString().mid(1,6)+".txt";
        EarseStrategy *es=new EarseStrategy(logFile);
        QString earseStrategyId=model.Serial+model.DiskPath+model.DiskModel;
        es->setId(earseStrategyId);
        strategy.append(es);

        connect(es,&EarseStrategy::UpdateProgressSignal,this,[=](QString id,QString type,QString Message){
            for(int i=0;i<this->ui->earsetableWidget->rowCount();i++)
            {
                QString cpr=this->ui->earsetableWidget->item(i,1)->text()+this->ui->earsetableWidget->item(i,3)->text()+this->ui->earsetableWidget->item(i,0)->text();
                if(id.compare(cpr)==0)
                {

                    if(type=="Doing")
                    {
                        this->ui->earsetableWidget->setItem(i,4,new QTableWidgetItem(Message));
                        QString count = Message.mid(Message.indexOf("->")+2,Message.indexOf("%") - Message.indexOf("->")-2);
                        float index = count.toFloat();

                        if(index >= 100)
                        {
                            QWidget *widget = ui->earsetableWidget->cellWidget(i,7);
                            QPushButton *btn = (QPushButton*)widget;
                            btn->setText("继续");
                            QString info = QString("%1当前已擦除%2次,是否查看硬盘数据?").arg(ui->earsetableWidget->item(i,0)->text() + ui->earsetableWidget->item(i,3)->text()).arg(Message.mid(0,1));
                            QMessageBox msgBox(QMessageBox::Information,"提示",info);
                            msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
                            msgBox.setDefaultButton(QMessageBox::Ok);
                            msgBox.setButtonText(QMessageBox::Ok,QString("确定"));
                            msgBox.setButtonText(QMessageBox::Cancel,QString("取消"));
                            if(msgBox.exec() == QMessageBox::Ok)
                            {
                                QString deviceID = this->ui->earsetableWidget->item(i,3)->text();
                                QString deviceName = ui->earsetableWidget->item(i,0)->text() + ui->earsetableWidget->item(i,3)->text()+"数据展示";
                                system(QString("sudo mate-terminal -e 'hexedit %1' --hide-menubar -t '%2'").arg(deviceID).arg(deviceName).toStdString().c_str());
                            }
                        }



                    }
                    else if(type=="Success")
                    {
                        MessageModel *successModel=new MessageModel();
                        successModel->Size=this->ui->earsetableWidget->item(i,2)->text();
                        successModel->Serial=this->ui->earsetableWidget->item(i,1)->text();
                        successModel->DiskPath=this->ui->earsetableWidget->item(i,3)->text();
                        successModel->DiskModel=this->ui->earsetableWidget->item(i,0)->text();
                        successModel->EarseCount=this->ui->earsetableWidget->item(i,5)->text();
                        successModel->EarseTime=Message;
                        this->_messageMediator->Send("success",*successModel);
                        this->ui->earsetableWidget->removeRow(i);
                    }
                    else if(type=="Error")
                    {
                        MessageModel *errorModel=new MessageModel();
                        errorModel->Size=this->ui->earsetableWidget->item(i,2)->text();
                        errorModel->Serial=this->ui->earsetableWidget->item(i,1)->text();
                        errorModel->DiskPath=this->ui->earsetableWidget->item(i,3)->text();
                        errorModel->DiskModel=this->ui->earsetableWidget->item(i,0)->text();
                        errorModel->EarseCount=this->ui->earsetableWidget->item(i,5)->text();
                        errorModel->ErrotMessage=Message;
                        this->_messageMediator->Send("error",*errorModel);
                        this->ui->earsetableWidget->removeRow(i);
                    }
                    else
                    {
                        throw "更新错误类型";
                    }
                }
            }



        });


        if(model.EarseCount=="1")
        {
          es->AddEarse(new EarseZero(model.DiskPath,logFile));

        }
        else if(model.EarseCount=="3"){
            es->AddEarse(new EarseZero(model.DiskPath,logFile));
            es->AddEarse(new  EarseRandom(model.DiskPath,logFile));
            es->AddEarse(new  EarseZero(model.DiskPath,logFile));
        }

        else if(model.EarseCount=="2"){
           // es->AddEarse(new EarseZero(model.DiskPath,logFile));
            es->AddEarse(new  EarseRandom(model.DiskPath,logFile));
            es->AddEarse(new  EarseZero(model.DiskPath,logFile));
        }

        else if(model.EarseCount=="4"){
          //  es->AddEarse(new EarseZero(model.DiskPath,logFile));
            es->AddEarse(new  EarseRandom(model.DiskPath,logFile));
            es->AddEarse(new  EarseRandom(model.DiskPath,logFile));
            es->AddEarse(new  EarseRandom(model.DiskPath,logFile));
            es->AddEarse(new  EarseZero(model.DiskPath,logFile));
        }

        else if(model.EarseCount=="6")
        {
            es->AddEarse(new EarseZero(model.DiskPath,logFile));
            es->AddEarse(new EarseOne(model.DiskPath,logFile));
            es->AddEarse(new  EarseRandom(model.DiskPath,logFile));
            es->AddEarse(new  EarseRandom(model.DiskPath,logFile));
            es->AddEarse(new  EarseRandom(model.DiskPath,logFile));
            es->AddEarse(new  EarseZero(model.DiskPath,logFile));
        }
        else if (model.EarseCount=="12")
        {
            for(int i = 0;i<2;i++)
            {
                es->AddEarse(new EarseZero(model.DiskPath,logFile));
                es->AddEarse(new EarseOne(model.DiskPath,logFile));
                es->AddEarse(new  EarseRandom(model.DiskPath,logFile));
                es->AddEarse(new  EarseRandom(model.DiskPath,logFile));
                es->AddEarse(new  EarseRandom(model.DiskPath,logFile));
                es->AddEarse(new EarseZero(model.DiskPath,logFile));
            }
        }
        else if (model.EarseCount=="18")
        {
            for(int i = 0;i<3;i++)
            {
                es->AddEarse(new EarseZero(model.DiskPath,logFile));
                es->AddEarse(new EarseOne(model.DiskPath,logFile));
                es->AddEarse(new  EarseRandom(model.DiskPath,logFile));
                es->AddEarse(new  EarseRandom(model.DiskPath,logFile));
                es->AddEarse(new  EarseRandom(model.DiskPath,logFile));
                es->AddEarse(new EarseZero(model.DiskPath,logFile));
            }
        }

        //开始擦除
        es->Earse();


        string TempPort;
        if(PortMap.contains(model.Serial.toStdString()))
        {
             QMap <string,string>::iterator iter = PortMap.find(model.Serial.toStdString());
             TempPort = iter.value();
        }
        QPushButton *ptn = new QPushButton();
        ptn->setText("取消");
        int count=this->ui->earsetableWidget->rowCount();
        this->ui->earsetableWidget->insertRow(count);
        ui->earsetableWidget->setItem(count,0,new QTableWidgetItem(model.DiskModel));
        ui->earsetableWidget->item(count,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        ui->earsetableWidget->setItem(count,1,new QTableWidgetItem(model.Serial));
        ui->earsetableWidget->item(count,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        ui->earsetableWidget->setItem(count,2,new QTableWidgetItem(model.Size));
        ui->earsetableWidget->item(count,2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        ui->earsetableWidget->setItem(count,3,new QTableWidgetItem(model.DiskPath));
        ui->earsetableWidget->item(count,3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        ui->earsetableWidget->setItem(count,4,new QTableWidgetItem("0%") );
        ui->earsetableWidget->item(count,4)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        ui->earsetableWidget->setItem(count,5,new QTableWidgetItem(model.EarseCount));
        ui->earsetableWidget->item(count,5)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        ui->earsetableWidget->setItem(count,6,new QTableWidgetItem(QString::fromStdString(TempPort)) );
        ui->earsetableWidget->item(count,6)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        ui->earsetableWidget->setCellWidget(count,7,ptn);
        this->connect(ptn,&QPushButton::pressed,this,[=](){

            QString btnName = ptn->text();
            if(btnName == "取消")
            {
                stop *s=new stop ();
                s->setIndex(model.Serial);
                s->connect(s,&stop::CancelEarseSignal,this,[=](QString serial){

                    MessageModel *errorModel  =new MessageModel ();
                    errorModel->Size=model.Size;
                    errorModel->Serial=model.Serial;
                    errorModel->DiskPath=model.DiskPath;
                    errorModel->DiskModel=model.DiskModel;
                    errorModel->EarseCount=model.EarseCount;
                    errorModel->ErrotMessage="人工取消";
                    errorModel->SendType=3;

                    int index=0;
                    for (int i=0;i<this->ui->earsetableWidget->rowCount();i++) {
                        if(this->ui->earsetableWidget->item(i,1)->text().compare(serial)==0)
                        {
                            index=i;
                            break;
                        }
                    }

                    //model.Serial+model.DiskPath+model.DiskModel;
                     QString removeUUid=this->ui->earsetableWidget->item(index,1)->text()+this->ui->earsetableWidget->item(index,3)->text()+this->ui->earsetableWidget->item(index,0)->text();

                    for(int p=0;p<strategy.size();p++)
                    {

                        if(strategy[p]->GetId().compare(removeUUid)==0)
                        {
                            strategy[p]->UnEarse();
                            strategy.removeAt(p);
                            break;
                        }
                    }
                    this->_messageMediator->Send("error",*errorModel);
                    this->ui->earsetableWidget->removeRow(index);
                    QString  type = "硬盘"+errorModel->Serial+"被人工取消";
                    QString  YN = "取消按钮";
                    LogSql log;
                    log.RunInsert(YN,type);

                    LogSql logg;
                    QString  typee = "擦除失败";
                    QString  YNN= "擦除" + model.EarseCount + "次"+" 秘级:"+model.Secret
                         +" 审批人:"+model.Approver+" 部门:"+model.Department+" 责任人:"+model.Earser
                         +" 介质类型:"+model.DiskType+" 磁盘序列号:"+model.Serial
                         +" 容量:"+model.Summery+"G"+" 用途:"+model.DiskPurpose
                         +" 介质去向:"+model.DiskDirection;
                    logg.RunInsert(YNN,typee);
                });
                s->show();
                s->setAttribute(Qt::WA_DeleteOnClose);
            }
            else if(btnName == "继续")
            {
                int index=0;
                for (int i=0;i<this->ui->earsetableWidget->rowCount();i++) {
                    if(this->ui->earsetableWidget->item(i,1)->text().compare(model.Serial)==0)
                    {
                        index=i;
                        break;
                    }
                }

                //model.Serial+model.DiskPath+model.DiskModel;
                 QString removeUUid=this->ui->earsetableWidget->item(index,1)->text()+this->ui->earsetableWidget->item(index,3)->text()+this->ui->earsetableWidget->item(index,0)->text();

                for(int p=0;p<strategy.size();p++)
                {

                    if(strategy[p]->GetId().compare(removeUUid)==0)
                    {
                        strategy[p]->setPause();
                    }
                }

                ptn->setText("取消");
            }
        });
    }
    else if (model.SendType == 0)
    {
        deleteTable(model);
    }

}

void earsetable::deleteTable(MessageModel model)
{
    int count = this->ui->earsetableWidget->rowCount();
    for (int i = 0; i<count; i++)
    {
       QString squ= this->ui->earsetableWidget->item(i,1)->text();
        if(model.Serial.compare(squ)==0)
        {
            // close earse task
           QString removeUUid=this->ui->earsetableWidget->item(i,1)->text()+this->ui->earsetableWidget->item(i,3)->text()+this->ui->earsetableWidget->item(i,0)->text();
           for(int p=0;p<strategy.size();p++)
           {

               if(strategy[p]->GetId().compare(removeUUid)==0)
               {
                   strategy[p]->UnEarse();
                   strategy.removeAt(p);
                   break;
               }
           }
            model.ErrotMessage="磁盘被拔出";
            this->_messageMediator->Send("error",model);
            this->ui->earsetableWidget->removeRow(i);
            QString  type = "磁盘"+model.Serial+"被拔出";
            QString  YN = "硬盘擦除";
            LogSql log;
            log.RunInsert(type,YN);
            break;
        }
    }
}





