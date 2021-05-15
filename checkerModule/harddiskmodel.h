#ifndef HARDDISKMODEL_H
#define HARDDISKMODEL_H
#include <QString>
#include<string>
#include<string.h>

using namespace  std;
class HardDiskModel
{
public:
    HardDiskModel();

public:
    int IsSystem;
    string DiskName;
    string DiskModel;
    string Serial;
    string AllMem;
    string UsedMem;
    string Identifier;

    string DiskType="";

    string DiskOwer;

    ///审批人
    string Approver;

    ///硬盘用途
    string DiskPurpose;

    ///擦除人
    string Earser;

    ///秘密等级
    string Secret;

    ///硬盘去向
    string DiskDirection;

    ///部门
    string Department;

    string Summery;

    ///端口号
    string ports;
};

#endif // HARDDISKMODEL_H
