#include "eightpwdcomplex.h"
#include "userservice.h"

UserService::UserService()
{
    this->pwdcomplex=new EightPwdComplex();
}

UserService::~UserService()
{
    delete this->pwdcomplex;
}

bool UserService::ModifyPassword(int id, QString oldpassword, QString newpassword, QString &errorMessage)
{
        // 验证密码复杂度

    bool complex_res= this->pwdcomplex->Validate(newpassword,errorMessage);
    if(complex_res==false)
        return complex_res;

    QString query_user="select * from user where id="+id;


}

UserModel *UserService::CraateUser(QString username, QString passwd, PermissionType permission, QString &errorMessage)
{

}

bool UserService::RemoveUser(int id, QString &errorMessage)
{

}
