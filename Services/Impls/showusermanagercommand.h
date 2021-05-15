#ifndef SHOWUSERMANAGERCOMMAND_H
#define SHOWUSERMANAGERCOMMAND_H

#include <Services/commandservicebase.h>



class ShowUserManagerCommand : public CommandServiceBase<QString>
{
public:
    ShowUserManagerCommand();

    // CommandServiceBase interface
protected:
    QString Do(UserModel user, QString &errorMessage);
};

#endif // SHOWUSERMANAGERCOMMAND_H
