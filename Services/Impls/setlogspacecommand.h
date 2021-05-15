#ifndef SETLOGSPACECOMMAND_H
#define SETLOGSPACECOMMAND_H

#include <Services/commandservicebase.h>

#include <Models/logspacemodel.h>


///
/// \brief The SetLogSpaceCommand class 设置日志报警阈值
///
class SetLogSpaceCommand:public CommandServiceBase<LogSpaceModel>
{
public:
    SetLogSpaceCommand(int threshold);


    // CommandServiceBase interface
protected:
    LogSpaceModel Do(UserModel user, QString &errorMessage);
private:
    int threshold;
};

#endif // SETLOGSPACECOMMAND_H
