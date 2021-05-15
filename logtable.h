#ifndef LOGTABLE_H
#define LOGTABLE_H

#include <QWidget>
#include"LogSql.h"

//#include <functional>

namespace Ui {
class logtable;
}

//using namespace std;
//typedef function<void(QString, QString, QString)>Fun;
typedef void (* Callback )( QString qsType, QString qsYN,QString qsTime);//callback
class logtable : public QWidget
{
    Q_OBJECT

public:
    explicit logtable(QWidget *parent = nullptr);
    ~logtable();

private:
    Ui::logtable *ui;

private slots:


    void on_pushButtonReset_clicked();

    void on_pushButtonQuery_clicked();

    void on_pushButtonExport_clicked();

    void on_pushButtonImport_clicked();

public:
    void HasLog(QString qsType, QString qsYN,QString qsTime);
    Callback Bind1(QString qsType, QString qsYN,QString qsTime);
    Fun GetFun();
    void show_log();
    void CleanTable();

    void initData();
private:
    Fun fun;
public:

LogSql *Logsqll;

};

#endif // LOGTABLE_H
