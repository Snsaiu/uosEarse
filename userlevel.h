#ifndef USERLEVEL_H
#define USERLEVEL_H

#include <QDialog>
#include <QWidget>
#include <qbuttongroup.h>

namespace Ui {
class UserLevel;
}

class UserLevel : public QDialog
{
    Q_OBJECT

public:
    explicit UserLevel(QDialog *parent = nullptr);
    ~UserLevel();

    QButtonGroup* btnGroupRadio;
    int radioId;
    void UiExit();

private slots:
    void on_OK_btn_pressed();

    void on_CancelBtn_pressed();

signals:
    void hasData();

private:
    Ui::UserLevel *ui;
};

#endif // USERLEVEL_H
