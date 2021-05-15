#ifndef LEVELCONST_H
#define LEVELCONST_H

#include <QString>



class LevelConst
{
public:
    LevelConst();
public:
  static const QString MI_MI;
  static const QString JI_MI;
  static const QString JUE_MI;
  static QVector<QString> GetList();
};



#endif // LEVELCONST_H
