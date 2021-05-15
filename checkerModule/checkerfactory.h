#ifndef CHECKERFACTORY_H
#define CHECKERFACTORY_H

#include "checkerdiskabstraction.h"
#include "usbchecker.h"
#include "harddiskchecker.h"

class CheckerFactory
{
public:
    CheckerFactory();
    ~CheckerFactory();
    CheckerDiskAbstraction* CreateHardDiskChecker();
    CheckerDiskAbstraction* CreateUsbChecker();
};

#endif // CHECKERFACTORY_H
