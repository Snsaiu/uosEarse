#ifndef USBCHECKER_H
#define USBCHECKER_H

#include "checkerdiskabstraction.h"
#include "harddiskmodel.h"
#include"publicuse.h"
#include <vector>
class UsbChecker:public CheckerDiskAbstraction
{
public:
    UsbChecker();
    vector<HardDiskModel> Check();
    vector<HardDiskModel> Filter(vector<HardDiskModel> models);

    vector<HardDiskModel> getDiskInfoVec();
private:
    int GetDiskName(const char *cmd);
    int shexec(HardDiskModel &outInfo,const char *cmd, char res[][10240], int count);
    vector<DiskInfoNoSys> shexecOne(const char *cmd);

private:
    vector<HardDiskModel> DiskInfoVec;
};

#endif // USBCHECKER_H
