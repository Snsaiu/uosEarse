#ifndef EARSECOUNTDIALOG_H
#define EARSECOUNTDIALOG_H

#include <QButtonGroup>
#include <QDialog>
#include <MessageMediator/messagemodel.h>
#include "checkerModule/harddiskmodel.h"
namespace Ui {
class EarseCountDialog;
}

class EarseCountDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EarseCountDialog( QWidget *parent = nullptr);
    ~EarseCountDialog();

    QString getSerial() const;
    void setSerial(const QString &value);


    void setMessageModel(MessageModel value);

private:
    Ui::EarseCountDialog *ui;
    QButtonGroup group;
    QString serial;
    MessageModel messageModel;



signals:
    void EarseCountSignal(string Approver,string Department,string Earser, int index);
    void EarseMessageModelSignal(MessageModel model);
private slots:
    void on_cancelBtn_pressed();
};

#endif // EARSECOUNTDIALOG_H
