#ifndef USERSERVICEBASE_H
#define USERSERVICEBASE_H
#include <Models/usermodel.h>
#include<QString>

///
/// \brief The UserServiceBase class 用户服务基类
///
class UserServiceBase
{
public:
    UserServiceBase();

    ///
    /// \brief ModifyPassword  修改用户密码
    /// \param id
    /// \param oldpassword 旧密码
    /// \param newpassword 新密码
    /// \param errorMessage 错误消息
    /// \return  修改成功返回true，否则返回false
    ///
    virtual bool ModifyPassword(int id, QString oldpassword,QString newpassword,QString &errorMessage)=0;



    ///
    /// \brief CraateUser 创建用户
    /// \param username 用户名
    /// \param passwd 密码
    /// \param permission 权限
    /// \param errorMessage 错误消息
    /// \return  创建成功返回模型，否则返回空
    ///
    virtual UserModel* CraateUser(QString username,QString passwd,PermissionType permission,QString &errorMessage)=0;


    ///
    /// \brief RemoveUser 移除用户
    /// \param id 用户id
    /// \param errorMessage 错误消息
    /// \return  移除成功返回true，否则返回false
    ///
    virtual bool RemoveUser(int id,QString &errorMessage)=0;

};

#endif // USERSERVICEBASE_H
