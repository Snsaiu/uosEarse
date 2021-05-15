#include "earseabstraction.h"



EarseAbstraction::EarseAbstraction(QString diskName, QString logPath):diskName(diskName),logPath(logPath)
{
   this->earseProcess=new QProcess ();

}

void EarseAbstraction::UnEarse()
{


 if(this->pid.compare("")==0)
     return;

// QProcess::startDetached("kill -9 "+this->pid);

 QStringList *cmds =new QStringList ();
 cmds->append("bash -c ");
 cmds->append("kill -9 ");
 cmds->append(this->pid);

 QString cmd= cmds->join("");
 QProcess::execute(cmd);

 this->earseProcess->close();
 this->earseProcess->kill();

}
