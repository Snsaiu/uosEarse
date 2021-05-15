#ifndef SHOWLOGSPACECOMMAND_H
#define SHOWLOGSPACECOMMAND_H

#include <Services/commandservicebase.h>

#include <Models/logspacemodel.h>



///
/// \brief The ShowLogSpaceCommand class 显示日志存储大小
///
class ShowLogSpaceCommand : public CommandServiceBase<LogSpaceModel>
{
public:
    ShowLogSpaceCommand();

    // CommandServiceBase interface
protected:
    LogSpaceModel Do(UserModel user, QString &errorMessage);
};

#endif // SHOWLOGSPACECOMMAND_H
