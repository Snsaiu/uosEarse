#include "dbbase.h"

DbBase::DbBase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("DataBase.db");
}

DbBase::DbBase(QString connectionStr)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(connectionStr);

}
