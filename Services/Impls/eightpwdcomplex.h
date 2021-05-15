#ifndef EIGHTPWDCOMPLEX_H
#define EIGHTPWDCOMPLEX_H

#include <Services/pwdcomplexbase.h>



///
/// \brief The EightPwdComplex class 八位密码复杂度
///
class EightPwdComplex : public PwdComplexBase
{
public:
    EightPwdComplex();



    // PwdComplexBase interface
public:
    bool Validate(QString password, QString &errorMessage);
};

#endif // EIGHTPWDCOMPLEX_H
