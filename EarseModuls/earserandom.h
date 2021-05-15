#ifndef EARSERANDOM_H
#define EARSERANDOM_H

#include "earseabstraction.h"

#include <QObject>

class EarseRandom : public EarseAbstraction
{

public:
     EarseRandom(QString diskPath,QString logPath);

signals:


    // EarseAbstraction interface
public:
    void Earse();
};

#endif // EARSERANDOM_H
