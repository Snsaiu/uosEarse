#include "opttypeconst.h"

const QString OptTypeConst::Login="登录";
const QString OptTypeConst::Logout="登出";
const QString OptTypeConst::DiskInput="插入介质";
const QString OptTypeConst::DiskOut="拔出介质";
const QString OptTypeConst::EarseError="擦除失败";
const QString OptTypeConst::EarseSuccess="擦除成功";
const QString OptTypeConst::ExportLog="导出日志";
const QString OptTypeConst::ImportLog="导入日志";
const QString OptTypeConst::ModifyPwd="修改密码";
const QString OptTypeConst::ModifyThreshold="修改阈值";
const QString OptTypeConst::OutpSaveAs="转存";
const QString OptTypeConst::StartEarse="开始擦除";
OptTypeConst::OptTypeConst()
{

}

QVector<QString> OptTypeConst::GetList()
{
 QVector<QString> res;
 res.append(OptTypeConst::Login);
 res.append(OptTypeConst::Logout);
 res.append(OptTypeConst::DiskInput);
 res.append(OptTypeConst::DiskOut);
 res.append(OptTypeConst::EarseError);
 res.append(OptTypeConst::EarseSuccess);
 res.append(OptTypeConst::ExportLog);
 res.append(OptTypeConst::ImportLog);
 res.append(OptTypeConst::ModifyPwd);
 res.append(OptTypeConst::ModifyThreshold);
 res.append(OptTypeConst::OutpSaveAs);
 res.append(OptTypeConst::StartEarse);
 return res;
}
