#ifndef LOGTHREAD_H
#define LOGTHREAD_H
#include <QThread>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include "publicuse.h"

class LogThread:public QThread
{
public:
    LogThread();
    void closeLogThread();
    void addData(QString type,QString YN);



protected:
    virtual void run();
    bool LogCreateTable();
    void LogInsertOne(QString type,QString YN);

private:
    volatile bool isStop;
    LogSqlType LogData;
    QSqlDatabase database;
};


#endif // LOGTHREAD_H
