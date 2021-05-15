#ifndef MESSAGESUBJECT_H
#define MESSAGESUBJECT_H

#include "messagemodel.h"

#include <QObject>

class MessageSubject
{

public:
    QString GetId();
    MessageSubject();
    virtual void Notify(MessageModel model)=0;
private:
    QString _id;

protected:
    void SetId(QString id);
};

#endif // MESSAGESUBJECT_H
