#include "messagesubject.h"

QString MessageSubject::GetId()
{
 return this->_id;
}

MessageSubject::MessageSubject()
{

}

void MessageSubject::SetId(QString id)
{
    this->_id=id;
}
