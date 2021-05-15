#include "waittable.h"
#include "ui_waittable.h"
#include "LogSql.h"
#include <QMessageBox>
#include <QDialog>
#include <checkerModule/harddiskmodel.h>
#include <Dialogs/earsecountdialog.h>
#include<QVector>
#include <qmap.h>
#include "Dialogs/disktypedialog.h"

#define Time_1000 1500
extern QMap <string,string> PortMap;
QVector<QString> EarsingVector;
QMap<string,HardDiskModel> VerifyVector;

waittable::waittable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::waittable)
{
    ui->setupUi(this);
    this->SetId("wait");
    this->_messageMediator->Regist(this);
    ui->waittableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->waittableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    ui->waittableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{font:15pt '黑体';color:black;bs:#2042b1;}");
    //    ui->waittableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:#1296db;}");
    /*表格外边框去除*/
    ui->waittableWidget->setFrameShape(QFrame::NoFrame);
    ui->waittableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //ui->waittableWidget->setContentsMargins(0,0,0,0);
    //隐藏表格线Stretch
    //ui->waittableWidget->setShowGrid(false);
    //表头不被选
    //ui->waittableWidget->horizontalHeader()->setHighlightSections(false);
    //字体加粗
    //QFont headfont = ui->waittableWidget->horizontalHeader()->font();
    //headfont.setBold(true);

    qtimer = new QTimer(this);
//    STopqtimer = new QTimer(this);
    connect(qtimer,SIGNAL(timeout()),this,SLOT(updateTable()));
//    connect(STopqtimer,SIGNAL(timeout()),this,SLOT(STOPupdateTable()));
//    STopqtimer->start(1000);

    //   ui->waittableWidget->setRowCount(2);
    //   ptn->setText("擦除");
    //   ptn1->setText("擦除");


    //   ui->waittableWidget->setItem(0,0,new QTableWidgetItem("CC10CE2B"));
    //   ui->waittableWidget->setItem(0,1,new QTableWidgetItem("冠捷2408W"));
    //   ui->waittableWidget->setItem(0,2,new QTableWidgetItem("098DFKUJHSF"));
    //   ui->waittableWidget->setItem(0,3,new QTableWidgetItem("100G"));
    //   ui->waittableWidget->setItem(0,4,new QTableWidgetItem("10G"));
    //   ui->waittableWidget->setCellWidget(0,5,ptn1);

    //   ui->waittableWidget->setItem(1,0,new QTableWidgetItem("DKHJ87567"));
    //   ui->waittableWidget->setItem(1,1,new QTableWidgetItem("技嘉4306"));
    //   ui->waittableWidget->setItem(1,2,new QTableWidgetItem("098OP5A779U"));
    //   ui->waittableWidget->setItem(1,3,new QTableWidgetItem("150G"));
    //   ui->waittableWidget->setItem(1,4,new QTableWidgetItem("21G"));
    //   ui->waittableWidget->setCellWidget(1,5,ptn);
    //connect(ptn,SIGNAL(clicked()),this,SLOT(OnClicked()));
    /*测试弹窗*/
    this->connect(ptn,&QPushButton::pressed,this,[=](){
        c.show();
    });

}


waittable::~waittable()
{
    this->_messageMediator->UnRegist(this);
    delete ui;
}



void OnClicked(void)
{
}



void waittable::updateTable()
{

    CleanTable();
    //    disk = new DiskInfo;
    //    DiskNameVec.clear();
    //    DiskNameVec = disk->getDiskVec();
    vector<HardDiskModel>  DiskNameVec =this->_cf.Check();
    this->_refeshList=DiskNameVec;
    Verify(DiskNameVec);
    for (int i=0;i<DiskNameVec.size();i++)
    {

     //todo 这里一定要把系统盘过滤掉
      if(DiskNameVec[i].IsSystem == 1)
          continue;

        DiskNameVec[i].DiskName="/dev/"+ DiskNameVec[i].DiskName;
         string strTmdiskDirectionp = DiskNameVec[i].DiskName;
        bool canAdd=true;
       for(int j=0;j<EarsingVector.size();j++)
       {
           QString cmp=  QString::fromStdString( DiskNameVec[i].Serial)+ QString::fromStdString( DiskNameVec[i].DiskName);

           if(EarsingVector[j].compare(cmp)==0)
           {
               canAdd=false;
           }
       }

       if(canAdd==false)
           continue;
       string TempPort;
       if(PortMap.contains(DiskNameVec[i].Serial))
       {
            QMap <string,string>::iterator iter = PortMap.find(DiskNameVec[i].Serial);
            TempPort = iter.value();
       }
        int count = ui->waittableWidget->rowCount();
        ui->waittableWidget->insertRow(count);
        ui->waittableWidget->setItem(count,0,new QTableWidgetItem(QString::fromStdString(DiskNameVec[i].DiskModel)));
        ui->waittableWidget->item(count,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->waittableWidget->setItem(count,1,new QTableWidgetItem(QString::fromStdString(DiskNameVec[i].Serial)));
        ui->waittableWidget->item(count,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->waittableWidget->setItem(count,2,new QTableWidgetItem(QString::fromStdString(DiskNameVec[i].AllMem)));
        ui->waittableWidget->item(count,2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->waittableWidget->setItem(count,3,new QTableWidgetItem(QString::fromStdString(DiskNameVec[i].DiskName)));
        ui->waittableWidget->item(count,3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->waittableWidget->setItem(count,4,new QTableWidgetItem(QString::fromStdString(TempPort)));
        ui->waittableWidget->item(count,4)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        QPushButton *qb=new QPushButton();
        qb->setText("擦除");
        qb->connect(qb,&QPushButton::pressed,this,[=](){
            EarseCountDialog *dialog=new EarseCountDialog(this);

            dialog->connect(dialog,&EarseCountDialog::EarseCountSignal,this,[=](string Approver,string Department,string Earser,int index){
                MessageModel *earseModel=new MessageModel ();
                    earseModel->Size = QString::fromStdString( DiskNameVec[i].AllMem);
                    earseModel->Serial = QString::fromStdString( DiskNameVec[i].Serial);
                    earseModel->DiskModel = QString::fromStdString( DiskNameVec[i].DiskModel);
                    earseModel->DiskPath = QString::fromStdString( DiskNameVec[i].DiskName);
                    earseModel->Approver=QString::fromStdString( Approver);
                    earseModel->Department=QString::fromStdString( Department);
                    earseModel->Earser=QString::fromStdString( Earser);
                    earseModel->EarseCount=QString::number(index);
                    earseModel->DiskType = QString::fromStdString( DiskNameVec[i].DiskType);
                    earseModel->DiskDirection=QString::fromStdString(DiskNameVec[i].DiskDirection);
                    earseModel->DiskPurpose=QString::fromStdString(DiskNameVec[i].DiskPurpose);
                    earseModel->Secret=QString::fromStdString(DiskNameVec[i].Secret);


                    this->_messageMediator->Send("earsing",*earseModel);
                    EarsingVector.append(earseModel->Serial+earseModel->DiskPath);

                    for (int x=0;x<this->ui->waittableWidget->rowCount();x++) {
                        if(QString::fromStdString( DiskNameVec[i].Serial).compare(this->ui->waittableWidget->item(x,1)->text())==0)
                        {

                            this->ui->waittableWidget->removeRow(x);
                        }
                        else if(this->ui->waittableWidget->rowCount()==1)
                            this->ui->waittableWidget->removeRow(1);
                    }


                    QString  type = "擦除按钮";
                    QString  YN = "擦除" + earseModel->EarseCount + "次"+" 秘级:"+QString::fromStdString(DiskNameVec[i].Secret)
                            +" 审批人:"+earseModel->Approver+" 部门:"+earseModel->Department+" 责任人:"+earseModel->Earser
                            +" 介质类型:"+QString::fromStdString(DiskNameVec[i].DiskType)+" 磁盘序列号:"+earseModel->Serial
                            +" 容量:"+QString::fromStdString(DiskNameVec[i].AllMem)+"G"+" 用途:"+QString::fromStdString( DiskNameVec[i].DiskPurpose)
                            +" 介质去向:"+QString::fromStdString(DiskNameVec[i].DiskDirection);
                    LogSql log;
                    log.RunInsert(type,YN);
            });
            dialog->show();
            dialog->setAttribute(Qt::WA_DeleteOnClose);

        });
        ui->waittableWidget->setCellWidget(count,5,qb);

    }
    //    delete disk;
}

void waittable::Notify(MessageModel model)
{
    //reEarse
   if(model.SendType==2)
   {
       bool canReEarse=false;
       for (int i=0;i<this->ui->waittableWidget->rowCount();i++) {
           if(model.Serial.compare(this->ui->waittableWidget->item(i,1)->text())==0)
           {
               canReEarse=true;
               this->ui->waittableWidget->removeRow(i);
               EarsingVector.append(model.Serial+model.DiskPath);
               break;
           }
       }
       if(canReEarse)
       {
          model.SendType=1;
          this->_messageMediator->Send("earsing",model);
       }
       else {

           QMessageBox::warning(this,"警告","未检测到硬盘信息，请重试");

       }
   }
   else if(model.SendType==3)
   {
       bool canDo=false;
       for (int i=0;i<this->_refeshList.size();i++) {
            if(QString::fromStdString( this->_refeshList[i].Serial).compare(model.Serial)==0)
            {
                canDo=true;
                break;
            }
       }
       if(canDo)
       {
           model.SendType=1;
           this->_messageMediator->Send("earsing",model);
       }
   }


}

void waittable::CleanTable()
{
    for(int row = 0; row < ui->waittableWidget->rowCount();)
        ui->waittableWidget->removeRow(0);
}

int waittable::getRadioCount()
{
//    diskTypeDialog *tempDialog=new diskTypeDialog();
//    tempDialog->show();
//    tempDialog->setAttribute(Qt::WA_DeleteOnClose);
//    int RadioCount = 0;
//    while(!tempDialog.getRadio(RadioCount))
//    {
//        sleep(1);
//    }
    //    return RadioCount;
}

void waittable::StartCheck()
{
    this->qtimer->start(Time_1000);
}

void waittable::Verify(vector<HardDiskModel> DiskNameVec)
{
    vector<HardDiskModel> DiskNameVecccc = DiskNameVec;
    ///第一次，全部获取
    if(firstVerify)
    {
        qtimer->stop();
        sleep(1);
        for(vector<HardDiskModel>::iterator iter = DiskNameVec.begin();iter!= DiskNameVec.end();iter++)
        {
            HardDiskModel tempModel;
            tempModel.Serial = iter->Serial;
            tempModel.AllMem = iter->AllMem;
            tempModel.DiskModel =iter->DiskModel;
            tempModel.DiskName = iter->DiskName;
            if(iter->IsSystem!=1&&iter->Serial!="")
            {
                diskTypeDialog *tempDialog=new diskTypeDialog(&tempModel);
                 tempDialog->setAttribute(Qt::WA_DeleteOnClose);
                tempDialog->exec();
            }


            VerifyVector.insert(tempModel.Serial,tempModel);
        }
        firstVerify = false;
        usleep(0);
        qtimer->start(Time_1000);
        return;
    }


    usleep(100);
    ///VerifyVector临时容器多余内容
    for(QMap< string,HardDiskModel >::iterator  finIndex = VerifyVector.begin();finIndex!=VerifyVector.end();finIndex++)
    {
        bool isCurrent = false;
        string tempInfo;
        for(vector<HardDiskModel>::iterator iter = DiskNameVec.begin();iter!= DiskNameVec.end();iter++)
        {
            tempInfo = iter->Serial;
            if(finIndex.value().Serial.compare(tempInfo)==0)
            {
                isCurrent = true;
                iter->DiskType=finIndex->DiskType;
                iter->DiskDirection=finIndex->DiskDirection;
                iter->DiskPurpose=finIndex->DiskPurpose;
                iter->Secret=finIndex->Secret;
                break;
            }

        }

        if(!isCurrent)
        {
            MessageModel *earseModel=new MessageModel ();

            if(tempInfo=="")
                continue ;
            earseModel->Size = QString::fromStdString(VerifyVector[finIndex.key()].AllMem);
            earseModel->Serial = QString::fromStdString(VerifyVector[finIndex.key()].Serial);
            earseModel->DiskModel = QString::fromStdString(VerifyVector[finIndex.key()].DiskModel);
            earseModel->DiskPath ="/dev/" + QString::fromStdString(VerifyVector[finIndex.key()].DiskName);
            earseModel->SendType = 0;
            for(int j=0;j<EarsingVector.size();j++)
            {
                  QString cmp=earseModel->Serial+earseModel->DiskPath;
                if(EarsingVector[j].compare(cmp)==0)
                {
                   EarsingVector.removeAt(j);
                }
            }

            this->_messageMediator->Send("earsing",*earseModel);
//            VerifyVector.remove(tempInfo);

        }
    }
    VerifyVector.clear();
    ///VerifyVector临时容器缺少内容
    int cc = DiskNameVecccc.size();
    int temCount = DiskNameVec.size();
    int i = 0;
    for(vector<HardDiskModel>::iterator iter = DiskNameVec.begin();iter!= DiskNameVec.end();iter++)
    {
        i++;
        HardDiskModel tempModel = *iter;
        QMap< string,HardDiskModel >::iterator  finIndex = VerifyVector.find(tempModel.Serial);
        if(finIndex == VerifyVector.end())
        {

            if(tempModel.DiskType==""&&tempModel.IsSystem!=1)
            {
                diskTypeDialog *tempDialog=new diskTypeDialog(&tempModel);
                 tempDialog->setAttribute(Qt::WA_DeleteOnClose);
                tempDialog->exec();
            }

            VerifyVector.insert(tempModel.Serial,tempModel);
        }
    }
}

///update timer state
void waittable::UpdateTimerState(int state)
{
    if(state==2)
        this->qtimer->start(Time_1000);
    else
        this->qtimer->stop();
}


