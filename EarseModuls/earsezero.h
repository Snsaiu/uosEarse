#ifndef EARSEZERO_H
#define EARSEZERO_H

#include "earseabstraction.h"

#include <QObject>

///  擦除0次
class EarseZero :public EarseAbstraction
{

public:
     EarseZero(QString diskName,QString logPath);

signals:


    // EarseAbstraction interface
public:
    void Earse();

};

#endif // EARSEZERO_H
