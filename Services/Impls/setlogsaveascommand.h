#ifndef SETLOGSAVEASCOMMAND_H
#define SETLOGSAVEASCOMMAND_H

#include <Services/commandservicebase.h>



///
/// \brief The SetLogSaveAsCommand class 设置日志转储
///
class SetLogSaveAsCommand:public CommandServiceBase<bool>
{
public:
    SetLogSaveAsCommand();
    SetLogSaveAsCommand(QString savepath);

    // CommandServiceBase interface
protected:
    bool  Do(UserModel user, QString &errorMessage);
private:
    QString savepath;
};

#endif // SETLOGSAVEASCOMMAND_H
