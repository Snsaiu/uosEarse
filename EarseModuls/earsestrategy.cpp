#include "earsestrategy.h"

#include <QFile>
#include<thread>
#include<QString>
#include <QDateTime>
#include <QThread>


EarseStrategy::EarseStrategy(QString logPath)
{
    this->logPath=logPath;
}

void EarseStrategy::AddEarse(EarseAbstraction *earseType)
{
    this->_earseTypes.append(earseType);
}

void EarseStrategy::UnEarse()
{
    for(int i=0;i<this->_earseTypes.size();i++)
    {
        this->_earseTypes[i]->UnEarse();
    }
    this->_earseTypes.clear();
    QFile file(this->logPath);
    file.remove();
}

 void* EarseStrategy::ThreadFun(void* arg)
{

    QTime startTime= QTime::currentTime();
    EarseStrategy* es = (EarseStrategy*)arg;
    while(true){
        if(es->_canNext)
        {

            if(es->_currentState<es->_earseTypes.size())
            {
                es->_earseTypes[es->_currentState]->Earse();
                es->_canNext=false;
            }

            else {
                QTime endTime=QTime::currentTime();
                QTime resTime;
                resTime.setHMS(0,0,0,0);
                QString earseTime=resTime.addSecs(startTime.secsTo(endTime)).toString("hh:mm:ss");

                es->_earseTypes.clear();
                QFile file(es->logPath);
                file.remove();

                emit es->UpdateProgressSignal(es->GetId(),"Success",earseTime);
                return nullptr;

            }


        }
        if(es->_earseTypes.size()==0)
            return nullptr;
        QString progress=es->ParseProgess();
        float progressNum=progress.toFloat();

        QString p=QString::number( es->_currentState+1)+" -> "+progress+"%";
        // todo:根据文件获得擦除是否失败

        emit es->UpdateProgressSignal(es->GetId(),"Doing",p);
        if(progressNum>=100.0)
        {
            QFile file(es->logPath);
            file.remove();
            es->_currentState++;
            es->_canNext=true;
            es->_pause = true;
            while(es->_pause)
            {
                QThread::sleep(1);
            }
        }


        //睡眠1秒
        QThread::sleep(3);
    }

}

QString EarseStrategy::id() const
{
    return _id;
}

void EarseStrategy::setId(const QString &id)
{
    _id = id;
}

QString EarseStrategy::GetId() const
{
    return _id;
}

void EarseStrategy::setPause()
{
    _pause = false;
}

QString EarseStrategy::ParseProgess()
{
    QFile f(this->logPath);
    if(f.open(QIODevice::ReadOnly)==false)
    {
        return "0";
    }

    QString content=QString(f.readAll());
    if(content.compare("")==0)
        return "0";
    // determine |
    int count= this->totalNum('|',content);
    count+=this->totalNum('.',content);
    float res= ((float)count)*2;
    f.close();
    return QString::number(res);
}

int EarseStrategy::totalNum(QChar search, QString source)
{

    if(search.isNull()||source.isNull())
        return 0;

    int count=0;
    for (int i=0;i<source.length();i++) {
        if(search==source[i])
            count++;
    }
    return count;
}

void EarseStrategy::Earse()
{

    if(this->_earseTypes.size()==0)
        throw "没有擦除方式";
    pthread_t pt;
    if(pthread_create(&pt,nullptr, EarseStrategy::ThreadFun,(void*)this) == -1)
    {
        printf("create thread error!\n");
        return;
    }
}
