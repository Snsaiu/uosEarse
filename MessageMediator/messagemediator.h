#ifndef MESSAGEMEDIATOR_H
#define MESSAGEMEDIATOR_H

#include <QObject>
#include "messagesubject.h"
#include<QVector>


class MessageMediator
{

public:

    void Regist(MessageSubject* subject);
    void UnRegist(MessageSubject* subject);
    void Send(QString to,MessageModel model);
    static MessageMediator* GetInstance();
private:
    MessageSubject* GetSubjectById(QString id);
    static MessageMediator *_instance;
    MessageMediator();
    QVector<MessageSubject*> _subjects;
};

#endif // MESSAGEMEDIATOR_H
