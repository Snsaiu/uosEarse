#ifndef DBBASE_H
#define DBBASE_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>


class DbBase
{
public:
    DbBase();
    DbBase(QString connectionStr);

protected:
    QSqlDatabase db;


};

#endif // DBBASE_H
