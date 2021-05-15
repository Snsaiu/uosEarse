#include "showlogsavecyclecommand.h"



ShowLogSaveCycleCommand::ShowLogSaveCycleCommand()
{
 this->addPermission(PermissionType::SAFE_MANAGER);
}

int ShowLogSaveCycleCommand::Do(UserModel user, QString &errorMessage)
{

}

