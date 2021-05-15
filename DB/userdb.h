#ifndef USERDB_H
#define USERDB_H

#include "dbbase.h"
#include<Models/usermodel.h>


class UserDb : public DbBase
{
public:
    UserDb();
    ///
    /// \brief Get 获得用户
    /// \param name 用户名
    /// \param pwd 密码
    /// \return
    ///
    UserModel* Get(QString name,QString pwd,QString &errorMessage);

    ///
    /// \brief Insert 新建用户
    /// \param user 用户模型
    /// \return  插入成功返回主键，否则返回-1
    ///
    int Insert(UserModel* user);

    bool ModifyPwd(int id,QString new_pwd);

    ///
    /// \brief RmoveUser 移除用户
    /// \param id 用户id
    /// \return 成功返回true，否则返回false
    ///
    bool RmoveUser(int id);

    ///
    /// \brief SetLoginTime 更新登录时间
    /// \param id 用户id
    /// \param logintime 登录时间
    /// \return  修改成功返回true，否则返回false
    ///
    bool SetLoginTime(int id,QDateTime logintime);
};

#endif // USERDB_H
