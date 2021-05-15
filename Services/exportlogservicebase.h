#ifndef EXPORTLOGSERVICEBASE_H
#define EXPORTLOGSERVICEBASE_H

#include <QString>


///
/// \brief The ExportLogServiceBase class 日志导出基类
///

class ExportLogServiceBase
{
public:
    ExportLogServiceBase();


    ///
    /// \brief Export 导出日志
    /// \param log 日志内容
    /// \param savepath 保存路径
    /// \param errorMessage
    /// \return 导出成功返回true，否则返回false
    ///
   virtual bool Export(QString log,QString savepath,QString errorMessage)=0;
};

#endif // EXPORTLOGSERVICEBASE_H
