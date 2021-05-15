#include "setlogsaveascommand.h"


SetLogSaveAsCommand::SetLogSaveAsCommand()
{
    this->addPermission(PermissionType::SYS_MANAGER);
}

SetLogSaveAsCommand::SetLogSaveAsCommand(QString savepath)
{
this->savepath=savepath;
}

bool SetLogSaveAsCommand::Do(UserModel user, QString &errorMessage)
{

}
