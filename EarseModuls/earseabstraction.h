#ifndef EARSEABSTRACTION_H
#define EARSEABSTRACTION_H

#include <QObject>
#include <QProcess>

class EarseAbstraction
{

public:
    EarseAbstraction(QString diskName,QString logPath);
    //擦除
    virtual void Earse()=0;

    ///取消擦除
     void UnEarse();


protected:
    QString diskName;
    QString logPath;
    QProcess* earseProcess;
    QString pid;

};

#endif // EARSEABSTRACTION_H
