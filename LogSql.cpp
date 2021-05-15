#include "LogSql.h"
#include<QDebug>
#include <qfile.h>
#include <qfiledialog.h>

LogSql::LogSql()
{   
}

LogSql::~LogSql()
{
}
//static LogThread *logThread;

LogThread *LogSql::logThread = new LogThread();

bool LogSql::LogCreateTable()
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

void LogSql::LogInsertOne(QString type,QString YN)
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

void LogSql::RunInsert(QString type,QString YN)
{
    logThread->addData(type,YN);
//    if(LogCreateTable())
//    {
//        if(database.open())
//        {
//            LogInsertOne(type,YN);
//            database.close();
//        }
////        getLog();
//    }
}

void LogSql::getLog(Fun fun)
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("DataBaseLog.db");
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
        QSqlQuery sql_query(database);
//        if(!sql_query.exec("create table if not exists Log(id INTEGER PRIMARY KEY AUTOINCREMENT,"
//                           "type TEXT NOT NULL,"
//                           "detail TEXT NOT NULL,"
//                           "time TEXT NOT NULL)"))
//        {
//            qDebug() << "Error: Fail to create table." << sql_query.lastError();
//        }
        //查询数据
        QString select_sql = "select * from Log order by id DESC";
        if(!sql_query.exec(select_sql))
        {
            qDebug()<<sql_query.lastError();
        }
        else
        {
//            sql_query.seek(0);
//            QSqlRecord rec=sql_query.record();
//            qDebug() << QObject::tr("automobil表字段数：" )<< rec.count();
            QString type  ;
            QString detail;
            QString time ;
            while(sql_query.next())
            {
                type   = sql_query.value(1).toString();
                detail = sql_query.value(2).toString();
                time   = sql_query.value(3).toString();
                fun(type,detail,time);
//                emit SendData();
            }
        }
    database.close();
    }
}

bool LogSql::CleanLog()
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("DataBaseLog.db");
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
        return false;
    }
    else
    {
        QSqlQuery sql_query(database);
        if(!sql_query.exec("DELETE FROM Log"))
        {
            qDebug()<<sql_query.lastError();
            return false;
        }
        database.close();
        return true;
    }

}

void LogSql::WriteLogToText()
{

    //文件夹路径
    QString file_path = QFileDialog::getExistingDirectory(this, "请选择文件路径...", "./");
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("DataBaseLog.db");
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
        QSqlQuery sql_query(database);
        //查询数据
        QString select_sql = "select * from Log order by id DESC";
        if(!sql_query.exec(select_sql))
        {
            qDebug()<<sql_query.lastError();
        }
        else
        {

            QString type  ;
            QString detail;
            QString time ;
            //指定文件路径，然后打开文件。
            QDateTime current_date_time =QDateTime::currentDateTime();
            QString current_time =current_date_time.toString("yyyy_MM_dd_hh_mm_ss");
            QFile *file = new QFile(file_path+"/"+current_time+"_OutLog.txt");//此路径下没有就会自己创建一个
            while(!file->open(QIODevice::ReadWrite | QIODevice::Append));//以读写切追加写入的方式操作文本
            //需要写入的数据
            QTextStream txtOutput(file);
            txtOutput<<QString("时间--------------------------------|")<<QString("----------描述---------|")<<QString("----------状态")<<endl;
            while(sql_query.next())
            {
                type   = sql_query.value(1).toString();
                detail = sql_query.value(2).toString();
                time   = sql_query.value(3).toString();
                txtOutput<<type<<QString("        |")<<detail<<QString("                |")<<time<<endl;
            }
            file->close();
        }
    database.close();
    }
}

void LogSql::CleanGetIndex(int num)
{
    int timee = num*30*24*60*60;
    int count = 0;
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("DataBaseLog.db");
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
        QSqlQuery sql_query(database);
        //查询数据
        QString select_sql = "select * from Log";
        if(!sql_query.exec(select_sql))
        {
            qDebug()<<sql_query.lastError();
        }
        else
        {

            QDateTime current_date_time =QDateTime::currentDateTime();
            uint cTime = current_date_time.toTime_t();
            QString time ;
            bool hasData = false;
            while(sql_query.next())
            {
                count++;
                time   = sql_query.value(1).toString();
                QDateTime timeLog = QDateTime::fromString(time, "yyyy.MM.dd hh:mm:ss.zzz ddd");
                uint LogGetime = timeLog.toTime_t();
                if(cTime - LogGetime >timee)
                {
                    hasData = true;
                    break;
                }
            }
            if(hasData)
            {
                select_sql = "delete from Log where id >" + QString::number(count);
                if(!sql_query.exec(select_sql))
                {
                    qDebug()<<sql_query.lastError();
                }
            }

        }
    database.close();
    }
}
