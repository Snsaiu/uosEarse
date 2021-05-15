#ifndef BASEGRINDER_H
#define BASEGRINDER_H
#include "login.h"
#include <QWidget>
#include <QPalette>
#include "rousewidget.h"
#include "userlevel.h"

namespace Ui {
class basegrinder;
}

class basegrinder : public QWidget
{
    Q_OBJECT

public:
    explicit basegrinder(QWidget *parent = nullptr);
    ~basegrinder();
    QString* getdatabase(int num);
    bool resetdatabase(QString passwd);
    int getdataCount(QString pwd);
    void firstDeleteLog();

    UserLevel* userlev;
    int TempUserId;


private:
    Ui::basegrinder *ui;
    Login m_login;
    RouseWidget m_rouseWidget;
    void GoLogin();
    QPalette palette;
    int LonInTimes[3];
    QTimer *m_timer;

    bool successLogin = false;

public:
    QSqlDatabase database;
    QString qs[4];
private slots:
    void on_pushButton_pressed();
    void on_LogSaveBtn_pressed();

    void on_LogOkBtn_pressed();

    void on_trueBtn_3_pressed();

    void onTimeOut();
    void rouseShow();



public slots:
    void getData();

protected:
    bool eventFilter(QObject *obj,QEvent *event);
};

#endif // BASEGRINDER_H
