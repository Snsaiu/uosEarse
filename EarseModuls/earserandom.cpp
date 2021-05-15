#include "earserandom.h"

EarseRandom::EarseRandom(QString diskName,QString logPath):EarseAbstraction(diskName,logPath)
{

}

void EarseRandom::Earse()
{
    QStringList *cmds =new QStringList ();
    cmds->append("bash -c ");
    cmds->append("\"");
    cmds->append("scrub -f -p random ");
    cmds->append(this->diskName+" ");
    cmds->append(">"+this->logPath);
    cmds->append("\"");
    QString cmd= cmds->join("");
    this->earseProcess->startDetached(cmd);
    qint64 pid= this->earseProcess->pid();
    this->pid=QString::number(pid+1);
}
