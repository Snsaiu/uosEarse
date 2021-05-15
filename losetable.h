#ifndef LOSETABLE_H
#define LOSETABLE_H

#include <QWidget>
#include "MessageMediator/messagesubject.h"
#include "MessageMediator/messagemediator.h"
namespace Ui {
class losetable;
}

class losetable : public QWidget,public MessageSubject
{
    Q_OBJECT

public:
    explicit losetable(QWidget *parent = nullptr);
    ~losetable();

private:
    Ui::losetable *ui;

    // MessageSubject interface
    MessageMediator *_messageMediator=MessageMediator::GetInstance();
public:
    void Notify(MessageModel model);
};

#endif // LOSETABLE_H
