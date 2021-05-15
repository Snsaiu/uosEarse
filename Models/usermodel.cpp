#include "usermodel.h"

UserModel::UserModel(QString username, QString password, PermissionType permission)
{
 this->username=username;
  this->password=password;
    this->permission=permission;
}

UserModel::UserModel(int id, QString username, QString passoword, PermissionType permission)
{

    this->username=username;
     this->password=password;
       this->permission=permission;
    this->id=id;
}

QString UserModel::getUsername() const
{
    return username;
}

QString UserModel::getPassword() const
{
    return password;
}

PermissionType UserModel::getPermission() const
{
    return permission;
}

bool UserModel::getId() const
{
    return id;
}

QDateTime UserModel::getLogindate() const
{
    return logindate;
}

void UserModel::setLogindate(const QDateTime &value)
{
    logindate = value;
}
