#ifndef PWDLOGEXPORTSERVICE_H
#define PWDLOGEXPORTSERVICE_H

#include <Services/exportlogservicebase.h>



class PwdLogExportService : public ExportLogServiceBase
{
public:
    PwdLogExportService(QString password);

    // ExportLogServiceBase interface
public:

    bool Export(QString log, QString savepath, QString errorMessage);
private:
    QString password;
};

#endif // PWDLOGEXPORTSERVICE_H
