#ifndef CHECKERDISKABSTRACTION_H
#define CHECKERDISKABSTRACTION_H
#include<vector>
#include "harddiskmodel.h"
class CheckerDiskAbstraction
{

public:
    CheckerDiskAbstraction();

    virtual vector<HardDiskModel> Check() = 0;

protected:
    virtual vector<HardDiskModel> Filter(vector<HardDiskModel> models) = 0;

};

#endif // CHECKERDISKABSTRACTION_H
