#ifndef WAITTABLE_H
#define WAITTABLE_H

#include <QPushButton>
#include <QWidget>
#include "choose.h"
#include "diskinfo.h"
#include <MessageMediator/messagemediator.h>
#include <MessageMediator/messagesubject.h>
#include <QTimer>
#include <checkerModule/checkerfacade.h>


namespace Ui {
class waittable;
}

class waittable : public QWidget,public MessageSubject
{
    Q_OBJECT

public:
    explicit waittable(QWidget *parent = nullptr);
    ~waittable();
    void CleanTable();
    int getRadioCount();

    void StartCheck();
private:
    void Verify(vector<HardDiskModel> DiskNameVec);
    bool firstVerify = true;

private:
    Ui::waittable *ui;
    QPushButton *ptn = new QPushButton();
    QPushButton *ptn1 = new QPushButton();
    choose c;/*测试弹窗*/
    MessageMediator* _messageMediator=MessageMediator::GetInstance();
    vector<diskInfo>DiskNameVec;
    QTimer *qtimer;
    DiskInfo *disk;
    vector<HardDiskModel> _refeshList;
    CheckerFacade _cf;


public slots:

    void UpdateTimerState(int state);


private slots:
//    void STOPupdateTable();
    void updateTable();

    // MessageSubject interface
public:
    void Notify(MessageModel model);
};

#endif // WAITTABLE_H
