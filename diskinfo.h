#ifndef DISKINFO_H
#define DISKINFO_H

#include"publicuse.h"


class DiskInfo
{
public:
    DiskInfo();
    ~DiskInfo();
    int shexec(diskInfo &outInfo,const char *cmd, char res[][10240], int count);
    int GetDiskName(const char *cmd);
    vector<diskInfo> getDiskVec();

private:
    vector<diskInfo>DiskNameVec;//创建vector对象
};

#endif // DISKINFO_H
