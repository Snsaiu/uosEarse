#ifndef USERSERVICE_H
#define USERSERVICE_H

#include <Services/pwdcomplexbase.h>
#include <Services/userservicebase.h>


///
/// \brief The UserService class 用户服务
///

class UserService:public UserServiceBase
{
public:
    UserService();
    ~UserService();

private:
    PwdComplexBase* pwdcomplex;

    // UserServiceBase interface
public:
    bool ModifyPassword(int id, QString oldpassword, QString newpassword, QString &errorMessage);
    UserModel *CraateUser(QString username, QString passwd, PermissionType permission, QString &errorMessage);
    bool RemoveUser(int id, QString &errorMessage);
};

#endif // USERSERVICE_H
