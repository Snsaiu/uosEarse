#include "userdb.h"

UserDb::UserDb()
{

}

UserModel* UserDb::Get(QString name, QString pwd,QString &errorMessage)
{
    bool opened= this->db.open();
    if(opened==false)
    {
        QSqlError error_sql = this->db.lastError();
         errorMessage= error_sql.text();
         return nullptr;
    }

    //
    this->db.close();
}

int UserDb::Insert(UserModel *user)
{

}

bool UserDb::ModifyPwd(int id, QString new_pwd)
{

}

bool UserDb::RmoveUser(int id)
{

}
