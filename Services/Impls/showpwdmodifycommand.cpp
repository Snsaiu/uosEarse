#include "showpwdmodifycommand.h"

ShowPwdModifyCommand::ShowPwdModifyCommand()
{
    this->addPermission(PermissionType::USER);
    this->addPermission(PermissionType::SYS_MANAGER);
    this->addPermission(PermissionType::SAFE_MANAGER);
    this->addPermission(PermissionType::AUDIT_MANAGER);
}

QString ShowPwdModifyCommand::Do(UserModel user, QString &errorMessage)
{

    return "";
}
