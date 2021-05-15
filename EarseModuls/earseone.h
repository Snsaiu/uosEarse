#ifndef EARSEONE_H
#define EARSEONE_H

#include "earseabstraction.h"

#include <QObject>

class EarseOne :public EarseAbstraction
{

public:
     EarseOne(QString diskName,QString logPath);

signals:


    // EarseAbstraction interface
public:
    void Earse();
};

#endif // EARSEONE_H
