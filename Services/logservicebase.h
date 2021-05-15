#ifndef LOGSERVICEBASE_H
#define LOGSERVICEBASE_H
#include<QString>

class LogServiceBase
{
public:
    LogServiceBase();

    ///
    /// \brief AddLog 添加新日志
    /// \param opt_type 类型 使用opttypeconst变量
    /// \param level 密级 使用levelconst
    /// \param source 原用途
    /// \param outto 介质去向
    /// \param auditor 审批人
    /// \param department 部门
    /// \param repositor 责任人
    /// \param agent 介质
    /// \param squ 硬盘序列号
    /// \param summary备注
    /// \return 插入成返回true，否则返回false
    ///
    bool AddLog(QString opt_type,QString level,QString source,QString outto,QString auditor,QString department,QString repositor,QString agent,QString squ,QString summary);


};

#endif // LOGSERVICEBASE_H
