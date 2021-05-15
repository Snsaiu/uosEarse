#ifndef SETLOGCYCLECOMMAND_H
#define SETLOGCYCLECOMMAND_H

#include <Services/commandservicebase.h>



///
/// \brief The SetLogCycleCommand class 设置日志存储周期
///
class SetLogCycleCommand : public CommandServiceBase<bool>
{
public:
    SetLogCycleCommand(int cycle);

    // CommandServiceBase interface
protected:
    bool Do(UserModel user, QString &errorMessage);

private:
    int cycle;
};

#endif // SETLOGCYCLECOMMAND_H
