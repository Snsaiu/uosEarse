#ifndef PWDCOMPLEXBASE_H
#define PWDCOMPLEXBASE_H

#include <QString>



///
/// \brief The PwdComplexBase class 检查密码复杂度
///
class PwdComplexBase
{
public:
    PwdComplexBase();

    ///
    /// \brief Validate  检查密码复杂度
    /// \param password 原始密码
    /// \param errorMessage 错误信息
    /// \return  密码复杂度符合规则返回tr·ue，否则返回false
    ///
    virtual bool Validate(QString password,QString &errorMessage)=0;

};

#endif // PWDCOMPLEXBASE_H
