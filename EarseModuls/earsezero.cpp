#include "earsezero.h"


EarseZero::EarseZero(QString diskName, QString logPath):EarseAbstraction(diskName,logPath)
{

}

void EarseZero::Earse()
{
    QStringList *cmds =new QStringList ();
    cmds->append("bash -c ");
    cmds->append("\"");
    cmds->append("scrub -f -p fillzero ");
    cmds->append(this->diskName+" ");
    cmds->append("> "+this->logPath);
    cmds->append("\"");
    QString cmd= cmds->join("");
    this->earseProcess->start(cmd);
    qint64 pid= this->earseProcess->pid();
//    pid=pid+1;
    this->pid=QString::number(pid+1);
}

