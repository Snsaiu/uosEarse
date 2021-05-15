#ifndef CHECKERFACADE_H
#define CHECKERFACADE_H
#include <vector>
#include "harddiskmodel.h"
#include "checkerstrategy.h"
class CheckerFacade
{
public:
    CheckerFacade();
    vector<HardDiskModel> Check();

private:
    void Add();
    CheckerStrategy checkerStrategy;



};

#endif // CHECKERFACADE_H
