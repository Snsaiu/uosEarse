#ifndef USERMODEL_H
#define USERMODEL_H
#include<QString>
#include<QDateTime>

#include<Enums/permissiontype.h>
///
/// \brief The UserModel class 用户模型
///
class UserModel
{
public:
    ///
    /// \brief UserModel
    /// \param username 用户名
    /// \param password 密码
    /// \param permission 权限
    ///
    UserModel(QString username,QString password,PermissionType permission);

    UserModel(int id,QString username,QString passoword,PermissionType permission);

    QString getUsername() const;

    QString getPassword() const;

    PermissionType getPermission() const;

    bool getId() const;

    QDateTime getLogindate() const;
    void setLogindate(const QDateTime &value);

private:
    ///
    /// \brief username 用户名
    ///
    QString username;
    ///
    /// \brief password 密码
    ///
    QString password;
    ///
    /// \brief id 主键
    ///
    bool id;
    ///
    /// \brief permission 权限
    ///
    PermissionType permission;
    ///
    /// \brief logindate 最后登录时间
    ///
    QDateTime logindate;

    ///
    /// \brief loginErrorCount 登录错误次数，如果是-1，表示登录成功
    ///
    int loginErrorCount;



};

#endif // USERMODEL_H
