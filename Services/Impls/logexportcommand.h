#ifndef LOGEXPORTCOMMAND_H
#define LOGEXPORTCOMMAND_H

#include <Services/commandservicebase.h>

#include <QVector>

#include <Models/logmodel.h>



///
/// \brief The LogExportCommand class 日志导出命令
///
class LogExportCommand : public CommandServiceBase<bool>
{
public:
    LogExportCommand(){

    }

    LogExportCommand(QString savepath,QVector<LogModel> log, QString user)
    {

    }

    // CommandServiceBase interface
protected:
    bool Do(UserModel user, QString &errorMessage);
};

#endif // LOGEXPORTCOMMAND_H
