#include "logtable.h"
#include "ui_logtable.h"
#include<qdebug.h>
using namespace std;
using namespace std::placeholders;
logtable::logtable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::logtable)
{
    ui->setupUi(this);
    ui->logtableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->logtableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->logtableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:#143D70;font:15pt '黑体';color:black;}");
      ui->logtableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{font:15pt '黑体';color:black;bs:#2042b1;}");
    /*表格外边框去除*/
    ui->logtableWidget->setFrameShape(QFrame::NoFrame);
    ui->logtableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    bool iscon;
    Logsqll = new LogSql;

}

logtable::~logtable()
{
    delete ui;
    delete  Logsqll;
    Logsqll = nullptr;
}
//QString msgType,QString msgDetail,QString msgTime
void logtable::HasLog(QString qsType, QString qsYN,QString qsTime)
{
    QString Type,  YN, Time;
    Type = qsType;
    YN = qsYN;
    Time = qsTime;
    int rowcount = ui->logtableWidget->rowCount();
    ui->logtableWidget->insertRow(rowcount);
    ui->logtableWidget->setItem(rowcount,0,new QTableWidgetItem(Type));
    ui->logtableWidget->item(rowcount,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->logtableWidget->setItem(rowcount,1,new QTableWidgetItem(YN));
    ui->logtableWidget->item(rowcount,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->logtableWidget->setItem(rowcount,2,new QTableWidgetItem(Time));
    ui->logtableWidget->item(rowcount,2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
}

Fun logtable::GetFun()
{
    fun = bind(&logtable::HasLog,this,_1,_2,_3);
    return  fun;
}

void logtable::show_log()
{
    Logsqll->getLog(GetFun());
}

Callback logtable::Bind1(QString qsType, QString qsYN,QString qsTime)
{
//    return bind(&logtable::HasLog,this,_1,_2,_3);
}

void logtable::CleanTable()
{
    for(int row = 0; row < ui->logtableWidget->rowCount();)
        ui->logtableWidget->removeRow(0);
}

void logtable::initData()
{
    ui->comboBoxCheckType->setCurrentIndex(0);
    ui->comboBoxType->setCurrentIndex(0);
    ui->comboBoxLevel->setCurrentIndex(0);
    ui->comboBoxUser->setCurrentIndex(0);
    ui->dateTimeEditStart->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEditEnd->setDateTime(QDateTime::currentDateTime());
}


void logtable::on_pushButtonReset_clicked()//重置
{
    initData();
}

void logtable::on_pushButtonQuery_clicked()//查询
{
    //获取sql参数


    //组装参数
}

void logtable::on_pushButtonExport_clicked()//导出
{

}

void logtable::on_pushButtonImport_clicked()//导入
{

}
