#ifndef COMMANDSERVICEBASE_H
#define COMMANDSERVICEBASE_H
#include<QVector>
#include<Enums/permissiontype.h>
#include <Models/usermodel.h>
template<typename T>
class CommandServiceBase
{
public:
    CommandServiceBase()
    {

    }

    ///
    /// \brief ValidatePermission 验证权限
    /// \param user 需要被验证的用户
    /// \return 验证成功返回true，否则返回false
    ///
    bool ValidatePermission(UserModel user)
    {

        foreach (PermissionType p, this->permissions) {
            if(p==user.getPermission())
            {
                return true;
            }
        }
        return false;
    }

    ///
    /// \brief Perform 执行命令
    /// \param user 执行的用户
    /// \param errorMessage 错误消息
    ///
    void Perform(UserModel user,T &res_data, QString &errorMessage)
    {

        foreach (PermissionType p, this->permissions) {

            if(p==user.getPermission())
            {

                T res= this->Do(user,errorMessage);
                res_data=res;
                return ;
            }
        }

        errorMessage="您没有权限执行此操作";
    }

protected:
     QVector<PermissionType> permissions;

protected:
     ///
     /// \brief addPermission 添加权限，该函数建议在构造函数中调用
     /// \param permission 需要添加的权限类型
     ///
     void addPermission(PermissionType permission)
     {
         // 理论上应该要添加重复判断
         this->permissions.append(permission);

     }

     ///
     /// \brief Do 执行命令
     /// \param user 执行的用户
     /// \param errorMessage 错误消息
     /// \return  返回泛型结果
     ///
     virtual T Do(UserModel user,QString &errorMessage)=0;
};

#endif // COMMANDSERVICEBASE_H
