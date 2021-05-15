#ifndef SHOWEARSEDERRORTABLE_H
#define SHOWEARSEDERRORTABLE_H

#include <Services/commandservicebase.h>


///
/// \brief The ShowEarsedErrorTable class 显示擦除失败面板
///
class ShowEarsedErrorTableCommand : public CommandServiceBase<QString>
{
public:
    ShowEarsedErrorTableCommand(){

    }

    // CommandServiceBase interface
protected:
    QString Do(UserModel user, QString &errorMessage)
    {

    }
};

#endif // SHOWEARSEDERRORTABLE_H
