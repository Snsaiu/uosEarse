#ifndef LOGSPACEMODEL_H
#define LOGSPACEMODEL_H


class LogSpaceModel
{
public:

    ///
    /// \brief LogSpaceModel 日志存储空间模型
    /// \param threshold 阈值
    /// \param userd 已经使用
    /// \param remain 剩余
    ///
    LogSpaceModel(int threshold,int userd,int remain);
    int getThreshold() const;

    int getUserd() const;

    int getRemain() const;

private:
    int threshold;
    int userd;
    int remain;

};

#endif // LOGSPACEMODEL_H
