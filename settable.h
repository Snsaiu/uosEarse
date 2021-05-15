#ifndef SETTABLE_H
#define SETTABLE_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <qdebug.h>

#include <QWidget>

namespace Ui {
class settable;
}

class settable : public QWidget
{
    Q_OBJECT

public:
    explicit settable(QWidget *parent = 0);
    ~settable();
    QString* getdatabase(int num);
    int getdataCount(QString pwd);
    bool resetdatabase(QString passwd);
    void firstDeleteLog();

public:
    Ui::settable *ui;
    QSqlDatabase database;
    QString qs[2];
};

#endif // SETTABLE_H
