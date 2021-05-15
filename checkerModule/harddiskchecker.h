#ifndef HARDDISKCHECKER_H
#define HARDDISKCHECKER_H
#include "checkerdiskabstraction.h"
#include <vector>
#include "harddiskmodel.h"
#include "publicuse.h"
#include<QString>
class HardDiskChecker:public CheckerDiskAbstraction
{
public:
    HardDiskChecker();
    vector<HardDiskModel> Check();
    vector<HardDiskModel> Filter(vector<HardDiskModel> models);
    vector<HardDiskModel> getDiskInfoVec();

private:
    int GetDiskName(const char *cmd);
    int shexec(HardDiskModel &outInfo,const char *cmd, char res[][1024], int count);
    vector<DiskInfoNoSys> shexecOne(const char *cmd);
    vector<DiskInfoNoSys> rigDiskInfo();
    QStringList getDiskByType(QString item);
    void checkSystem(QStringList disk);
    int getHardDiskCount();
private:
    vector<HardDiskModel> DiskInfoVec;

    QString systemDiskSerial="LSL7025619315F00054";
};

#endif // HARDDISKCHECKER_H
