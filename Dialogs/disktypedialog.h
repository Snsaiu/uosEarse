#ifndef DISKTYPEDIALOG_H
#define DISKTYPEDIALOG_H

#include <QDialog>
#include <qbuttongroup.h>
#include "checkerModule/harddiskmodel.h"
namespace Ui {
class diskTypeDialog;
}

class diskTypeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit diskTypeDialog(HardDiskModel *model, QWidget *parent = nullptr);
    ~diskTypeDialog();

    QButtonGroup* btnGroupRadio;




private:
    Ui::diskTypeDialog *ui;
};

#endif // DISKTYPEDIALOG_H
