#ifndef CHECKERSTRATEGY_H
#define CHECKERSTRATEGY_H
#include <vector>
#include "checkerdiskabstraction.h"
#include "harddiskmodel.h"
class CheckerStrategy
{
public:
    CheckerStrategy();

    void AddChecker(CheckerDiskAbstraction* checker);

    vector<HardDiskModel> Perform();
public:
    vector<HardDiskModel> _res;

private:

    vector<CheckerDiskAbstraction*> _list;
};

#endif // CHECKERSTRATEGY_H
