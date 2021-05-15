#include "setlogcyclecommand.h"

SetLogCycleCommand::SetLogCycleCommand(int cycle)
{
    this->addPermission(PermissionType::SAFE_MANAGER);
    this->cycle=cycle;
}

bool SetLogCycleCommand::Do(UserModel user, QString &errorMessage)
{

}
