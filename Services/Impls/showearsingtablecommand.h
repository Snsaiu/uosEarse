#ifndef SHOWEARSINGTABLE_H
#define SHOWEARSINGTABLE_H

#include <QString>

#include <Services/commandservicebase.h>



class ShowEarsingTableCommand : public CommandServiceBase<QString>
{
public:
    ShowEarsingTableCommand(){

    }

    // CommandServiceBase interface
protected:
    QString Do(UserModel user, QString &errorMessage)
    {

    }
};

#endif // SHOWEARSINGTABLE_H
