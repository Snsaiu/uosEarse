#include "logthread.h"
#include <QDebug>
#include <QDateTime>

LogThread::LogThread()
{
    isStop = false;
}

void LogThread::closeLogThread()
{
    isStop = true;
}

void LogThread::run()
{
    while (1)
    {
        if(isStop)
            return;
        if(LogCreateTable())
        {
            if(database.open())
            {
                LogInsertOne(LogData.TYPE,LogData.YN );
                database.close();
            }
        }
        sleep(2);
        break;
    }
}

void LogThread::addData(QString type,QString YN)
{
    LogData.TYPE = type;
    LogData.YN = YN;
    this->start();

}

bool LogThread::LogCreateTable()
{

    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("DataBaseLog.db");

    if (!database.open())
    {
        qDebug() << "Error: Failed to connect DataBaseLog." << database.lastError();
        return false;
    }
    else
    {
        qDebug() << "open db succwss" ;
        //创建表格
        QSqlQuery sql_query(database);
        if(!sql_query.exec("create table if not exists Log(id INTEGER PRIMARY KEY AUTOINCREMENT,"
                           "type TEXT NOT NULL,"
                           "detail TEXT NOT NULL,"
                           "time TEXT NOT NULL)"))
        {
            qDebug() << "Error: Fail to create table." << sql_query.lastError();
            database.close();
            return true;
        }
        else
        {
            qDebug() << "Table created!";
            database.close();
            return true;
        }
    }
}

void LogThread::LogInsertOne(QString type,QString YN)
{
    //插入数据
    QSqlQuery sql_query(database);
    QString username = "user";
    QString passwd = "7410";
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_time =current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd");
    if(!sql_query.prepare("INSERT INTO Log (type, detail,time) VALUES (:type, :detail, :time)"))
    {
        qDebug() << sql_query.lastError();
    }
    sql_query.bindValue(":type",current_time);
    sql_query.bindValue(":detail",type);
    sql_query.bindValue(":time",YN);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
    }
}
