#ifndef SETLOGSAVECYCLECOMMAND_H
#define SETLOGSAVECYCLECOMMAND_H

#include <Services/commandservicebase.h>


///
/// \brief The SetLogSaveCycleCommand class 显示日志存储周期
///
class ShowLogSaveCycleCommand : public CommandServiceBase<int>
{
public:
    ///
    /// \brief SetLogSaveCycleCommand
    /// \param cycle
    ///
    ShowLogSaveCycleCommand();
    // CommandServiceBase interface
protected:
    int Do(UserModel user, QString &errorMessage);
};

#endif // SETLOGSAVECYCLECOMMAND_H
