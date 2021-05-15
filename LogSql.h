#ifndef LOGSQL_H
#define LOGSQL_H
#include<qstring.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QObject>
#include <QWidget>
#include <functional>
#include <QDateTime>
#include <qfile.h>
#include <qdir.h>
#include"ForLogThread/logthread.h"

using namespace std;
typedef function<void(QString, QString, QString)>Fun;
typedef void (* Callback )( QString qsType, QString qsYN,QString qsTime);//callback

class LogSql:public QWidget
{
    Q_OBJECT
public:

    LogSql();
    ~LogSql();

    bool LogCreateTable();
    void LogInsertOne(QString type,QString YN);
    void RunInsert(QString type,QString YN);
    void getLog(Fun fun);
    bool CleanLog();
    void WriteLogToText();
    void CleanGetIndex(int num);
public:
    Callback LogCallback;
    static LogThread *logThread;

private:
    QString logType;
    QString logYN;
    QString logTime;
    QSqlDatabase database;

signals:

    void SendData();
};

#endif // LOGSQL_H
