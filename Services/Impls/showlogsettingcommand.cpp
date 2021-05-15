#include "showlogsettingcommand.h"

ShowLogSettingCommand::ShowLogSettingCommand()
{
    this->addPermission(PermissionType::SAFE_MANAGER);
    this->addPermission(PermissionType::SYS_MANAGER);
}

QString ShowLogSettingCommand::Do(UserModel user, QString &errorMessage)
{

    return "";
}
