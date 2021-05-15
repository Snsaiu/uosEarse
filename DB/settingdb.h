#ifndef SETTINGDB_H
#define SETTINGDB_H

#include <Models/settingmodel.h>



class SettingDb
{
public:
    SettingDb();

    ///
    /// \brief GetSetting 获得设置内容
    /// \return
    ///
    SettingModel GetSetting();

    ///
    /// \brief SetIdentityCount 设置身份鉴别次数
    /// \return
    ///
    bool SetIdentityCount(int count);

    ///
    /// \brief SetPwdChangeCycle 设置口令修改周期
    /// \param count
    /// \return
    ///
    bool SetPwdChangeCycle(int count);

    ///
    /// \brief SetLogSaveCycle 设置日志保存最短周期
    /// \param count
    /// \return
    ///
    bool SetLogSaveCycle(int count);

};

#endif // SETTINGDB_H
