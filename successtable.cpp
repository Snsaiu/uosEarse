#include "LogSql.h"
#include "successtable.h"
#include "ui_successtable.h"
#include<QVector>

extern QMap <string,string> PortMap;

successtable::successtable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::successtable)
{
    ui->setupUi(this);
    this->SetId("success");
    this->_messageMediator->Regist(this);

    ui->successtableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->successtableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->successtableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:#143D70;font:15pt '黑体';color:black;}");
       ui->successtableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{font:15pt '黑体';color:black;bs:#2042b1;}");
    /*表格外边框去除*/
    ui->successtableWidget->setFrameShape(QFrame::NoFrame);
    ui->successtableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

successtable::~successtable()
{
    this->_messageMediator->UnRegist(this);
    delete ui;
}

void successtable::Notify(MessageModel model)
{

    string TempPort;
    if(PortMap.contains(model.Serial.toStdString()))
    {
         QMap <string,string>::iterator iter = PortMap.find(model.Serial.toStdString());
         TempPort = iter.value();
    }

    QString SucessStrategyId=model.Serial+model.DiskPath+model.DiskModel;
    int count = ui->successtableWidget->rowCount();
    ui->successtableWidget->insertRow(count);
    ui->successtableWidget->setItem(count,0,new QTableWidgetItem(model.DiskModel));
    ui->successtableWidget->item(count,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->successtableWidget->setItem(count,1,new QTableWidgetItem(model.Serial));
    ui->successtableWidget->item(count,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->successtableWidget->setItem(count,2,new QTableWidgetItem(model.Size));
    ui->successtableWidget->item(count,2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->successtableWidget->setItem(count,3,new QTableWidgetItem(model.EarseTime));
    ui->successtableWidget->item(count,3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->successtableWidget->setItem(count,4,new QTableWidgetItem(model.EarseCount));
    ui->successtableWidget->item(count,4)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->successtableWidget->setItem(count,5,new QTableWidgetItem(QString::fromStdString(TempPort)));
    ui->successtableWidget->item(count,5)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    QString  type = "硬盘"+model.Serial+"擦除完成";
    QString  YN = "擦除" + model.EarseCount + "次"+" 秘级:"+model.Secret
            +" 审批人:"+model.Approver+" 部门:"+model.Department+" 责任人:"+model.Earser
            +" 介质类型:"+model.DiskType+" 磁盘序列号:"+model.Serial
            +" 容量:"+model.Summery+"G"+" 用途:"+model.DiskPurpose
            +" 介质去向:"+model.DiskDirection;
    LogSql log;
    log.RunInsert(YN,type);
}
