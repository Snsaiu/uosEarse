#ifndef LOGMODEL_H
#define LOGMODEL_H

#include <QString>
#include <QDateTime>


class LogModel
{
public:
    LogModel();

private:
    int id;
    QDateTime data; //时间
    QString type;//类型
    QString  level; //密级
    QString source;// 原用途
    QString outto;// 介质去向
    QString auditor;//审批人
    QString rresponsible;//责任人
    QString department;//部门
    QString agent;//介质
    QString squ;//硬盘序列号
    QString opt_user;//操作用户
    int user_level;//用户等级
    QString summary;//备注

};

#endif // LOGMODEL_H
