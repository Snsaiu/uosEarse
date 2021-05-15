#ifndef SUCCESSTABLE_H
#define SUCCESSTABLE_H

#include <QWidget>

#include <MessageMediator/messagesubject.h>
#include <MessageMediator/messagemodel.h>
#include <MessageMediator/messagemediator.h>

namespace Ui {
class successtable;
}

class successtable : public QWidget,public MessageSubject
{
    Q_OBJECT

public:
    explicit successtable(QWidget *parent = 0);
    ~successtable();
    void Notify(MessageModel model);

private:
    Ui::successtable *ui;
    // MessageSubject interface
    MessageMediator *_messageMediator=MessageMediator::GetInstance();
};

#endif // SUCCESSTABLE_H
