#include "logspacemodel.h"


LogSpaceModel::LogSpaceModel(int threshold, int userd, int remain)
{
this->threshold=threshold;
    this->userd=userd;
    this->remain=remain;
}

int LogSpaceModel::getThreshold() const
{
    return threshold;
}

int LogSpaceModel::getUserd() const
{
    return userd;
}

int LogSpaceModel::getRemain() const
{
    return remain;
}
