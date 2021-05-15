#include "settingmodel.h"

SettingModel::SettingModel()
{

}

int SettingModel::getIdentityCount() const
{
    return identityCount;
}

void SettingModel::setIdentityCount(int value)
{
    identityCount = value;
}

int SettingModel::getPwdChangeCycle() const
{
    return PwdChangeCycle;
}

void SettingModel::setPwdChangeCycle(int value)
{
    PwdChangeCycle = value;
}
