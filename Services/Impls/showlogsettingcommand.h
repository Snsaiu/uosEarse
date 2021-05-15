#ifndef SHOWLOGSETTINGCOMMAND_H
#define SHOWLOGSETTINGCOMMAND_H

#include <Services/commandservicebase.h>



///
/// \brief The ShowLogSettingCommand class 显示日志管理面板
///
class ShowLogSettingCommand:public CommandServiceBase<QString>
{
public:
    ShowLogSettingCommand();

    // CommandServiceBase interface
protected:
    QString Do(UserModel user, QString &errorMessage);
};

#endif // SHOWLOGSETTINGCOMMAND_H
