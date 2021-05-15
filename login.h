#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "choose.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <qbuttongroup.h>
#include "publicuse.h"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT
signals:
    void GoLogin();

public:

    explicit Login(QWidget *parent = 0);
    void resetdatabase(int num);
    void inserttabase();
    QString* getdatabase(int num);
    bool CreateTable();
    QButtonGroup *btnGroupRadio;
    ~Login();
    bool isUpdateUserTable(QString Tabletime);
    static int PublicUserId;
    int getSecrettimes();
    int secretNumber;
    void writerToLogin();
    void readfromFile();
    bool IsTime(QString oldTime);

private:
    Ui::Login *ui;
    int radioId;
    int loginCount = 0;
    LogInTime LogInTimes[3];

    choose c;/*测试弹窗*/
    //设置屏幕长亮
   void setScreen();

   QString userName;



public:
    QSqlDatabase database;
    QString qs[4];

    QString getUserName() const;

public slots:
    void onRadioGroupClick();
    void LogInTimesFlag0();
    void LogInTimesFlag1();
    void LogInTimesFlag2();

};

#endif // LOGIN_H
