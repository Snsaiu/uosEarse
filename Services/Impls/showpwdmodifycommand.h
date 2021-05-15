#ifndef SHOWPWDMODIFYCOMMAND_H
#define SHOWPWDMODIFYCOMMAND_H

#include <Services/commandservicebase.h>



class ShowPwdModifyCommand:public CommandServiceBase<QString>
{
public:
    ShowPwdModifyCommand();

    // CommandServiceBase interface
protected:
    QString Do(UserModel user, QString &errorMessage);
};

#endif // SHOWPWDMODIFYCOMMAND_H
