#ifndef OPTTYPE_H
#define OPTTYPE_H

#include <QString>
#include<QVector>

///
/// \brief The OptType class 操作类型
///

class OptTypeConst
{
public:
    OptTypeConst();
    //登录
    static const QString Login;
    //登出
    static const QString Logout;
    //开始擦除
    static const QString StartEarse;
    // 擦除成功
    static const QString EarseSuccess;
    //擦除失败
    static const QString EarseError;
    //硬盘插入
    static const QString DiskInput;

    //硬盘拔出
    static const QString DiskOut;
    //修改密码
    static const QString ModifyPwd;

    //导入日志
    static const QString ImportLog;
    //导出日志
    static const QString ExportLog;
    //修改阈值
    static const QString ModifyThreshold;
    //转存
    static const QString OutpSaveAs;

    static QVector<QString> GetList();


};

#endif // OPTTYPE_H
