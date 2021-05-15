#ifndef SHOWWAITTABLECOMMAND_H
#define SHOWWAITTABLECOMMAND_H
#include<Enums/permissiontype.h>
#include <Services/commandservicebase.h>


///
/// \brief The ShowWaitTableCommand class 显示带擦除面板
///
class ShowWaitTableCommand : public CommandServiceBase<QString>
{
public:
    ShowWaitTableCommand(){

    }

    // CommandServiceBase interface
protected:
    QString Do(UserModel user, QString &errorMessage)
    {

    }
};

#endif // SHOWWAITTABLECOMMAND_H
