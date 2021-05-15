#ifndef EARSETABLE_H
#define EARSETABLE_H

#include <QWidget>
#include <QPushButton>
#include <MessageMediator/messagemediator.h>
#include <MessageMediator/messagesubject.h>
#include "stop.h"

namespace Ui {
class earsetable;
}

class earsetable : public QWidget,public MessageSubject
{
    Q_OBJECT

public:
    explicit earsetable(QWidget *parent = nullptr);
    ~earsetable();

private:
    Ui::earsetable *ui;
    QPushButton *ptn = new QPushButton();

    MessageMediator* _messageMediator=MessageMediator::GetInstance();
    // MessageSubject interface
public:
    void Notify(MessageModel model);
    void deleteTable(MessageModel model);
};

#endif // EARSETABLE_H
