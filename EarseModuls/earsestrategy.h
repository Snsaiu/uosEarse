#ifndef EARSESTRATEGY_H
#define EARSESTRATEGY_H
#include "earseabstraction.h"

#include <QVector>

enum UpdateEnum{
    Doing,
    Error,
    Success

};

class EarseStrategy:public QObject
{
    Q_OBJECT
public:
    EarseStrategy(QString logPath);
    void AddEarse(EarseAbstraction* earseType);
    void UnEarse();
    void Earse();
    static void* ThreadFun(void* arg);

    QString id() const;
    void setId(const QString &id);
    QString GetId() const;
    void setPause();

signals:
    void UpdateProgressSignal(QString id,QString type ,QString Message);


private:
   QString _id;
    QString logPath;
    QVector<EarseAbstraction*> _earseTypes;
    bool _canNext=true;
    int _currentState=0;
    QString ParseProgess();//读取文件获得进度
     int totalNum(QChar search,QString srouce);
     bool _pause = false;


};

#endif // EARSESTRATEGY_H
