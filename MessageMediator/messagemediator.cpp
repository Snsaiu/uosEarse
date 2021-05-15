#include "messagemediator.h"

MessageMediator::MessageMediator()
{

}

void MessageMediator::Regist(MessageSubject *subject)
{
    this->_subjects.append(subject);
}

void MessageMediator::UnRegist(MessageSubject *subject)
{
    for(int i=0;i<this->_subjects.size();i++)
    {
        if(subject->GetId().compare(this->_subjects[i]->GetId())==0)
        {
            this->_subjects.removeAt(i);
            return;
        }
    }
}

void MessageMediator::Send(QString to, MessageModel model)
{
       MessageSubject* subject= this->GetSubjectById(to);
       if(subject==nullptr)
           throw "未发现指定的订阅者";
       subject->Notify(model);
}

MessageMediator* MessageMediator::_instance;
MessageMediator* MessageMediator::GetInstance()
{
    if(MessageMediator::_instance==nullptr)
    {
        MessageMediator::_instance=new MessageMediator();

    }
    return MessageMediator::_instance;
}

MessageSubject *MessageMediator::GetSubjectById(QString id)
{
    for(int i=0;i<this->_subjects.size();i++)
    {
        if(id.compare(this->_subjects[i]->GetId())==0)
        {
           return this->_subjects[i];
        }
    }

    return nullptr;
}
