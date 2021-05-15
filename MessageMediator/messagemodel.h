#ifndef MESSAGEMODEL_H
#define MESSAGEMODEL_H
#include <QObject>


class MessageModel
{
public:
    MessageModel();

    ///硬盘类型
    QString DiskModel;

    ///擦除次数
    QString EarseCount;

    ///错误信息
    QString ErrotMessage;

    ///序列号
    QString Serial;

    ///擦除时长
    QString EarseTime;

    ///硬盘容量大小
    QString Size;

    ///硬盘路径
    QString DiskPath;

    QString Approver;
    QString Department;
    QString Earser;


    ///硬盘用途
    QString DiskPurpose;


    ///秘密等级
    QString Secret;

    ///硬盘去向
    QString DiskDirection;


    QString Summery;

    QString DiskType;



    //1 defalut ,0 diskhard leave,  2 reEarse 3  human cancel
    int SendType=1;

};

#endif // MESSAGEMODEL_H
