#ifndef PUBLICUSE_H
#define PUBLICUSE_H
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <scsi/sg.h>
#include <sys/ioctl.h>
#include <linux/hdreg.h>
#include <string>
#include <fstream>
#include <QString>
#include<string>
#include<string.h>
#include<vector>
#include<bits/stdc++.h>
#include <sys/statfs.h>
#include <qtimer.h>

using namespace std;

struct diskInfo
{
    int IsSystem;
    string DiskName;
    string DiskModel;
    string Serial;
    string AllMem;
    string UsedMem;

};

struct DiskInfoNoSys
{
    string name;
    string seri;
    string module;
    string size;
};

struct LogSqlType
{
    QString TYPE;
    QString YN;
};

struct LogInTime
{
    QTimer *CountTimer;
    int count;
    bool isStop;
    QString OldTime;
};

#endif // PUBLICUSE_H
