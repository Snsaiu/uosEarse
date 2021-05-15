#ifndef SHOWEARSEDSUCCESSTABLE_H
#define SHOWEARSEDSUCCESSTABLE_H

#include <Services/commandservicebase.h>


///
/// \brief The ShowEarsedSuccessTable class 显示擦除成功面板
///
class ShowEarsedSuccessTableCommand : public CommandServiceBase<QString>
{
public:
    ShowEarsedSuccessTableCommand(){

    }

    // CommandServiceBase interface
protected:
    QString Do(UserModel user, QString &errorMessage)
    {

    }
};

#endif // SHOWEARSEDSUCCESSTABLE_H
