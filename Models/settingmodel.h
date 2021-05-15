#ifndef SETTINGMODEL_H
#define SETTINGMODEL_H


class SettingModel
{
public:
    SettingModel();

    int getIdentityCount() const;
    void setIdentityCount(int value);

    int getPwdChangeCycle() const;
    void setPwdChangeCycle(int value);

private:

    ///
    /// \brief identityCount 身份鉴别次数
    ///
    int identityCount;

    ///
    /// \brief PwdChangeCycle 口令修改周期
    ///
    int PwdChangeCycle;

    ///
    /// \brief logSaveCycle 日志存储周期
    ///
    int logSaveCycle;
};

#endif // SETTINGMODEL_H
