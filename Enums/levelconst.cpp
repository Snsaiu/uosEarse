#include "levelconst.h"
#include<QString>
#include<QVector>
const QString LevelConst::JI_MI="机密";
const QString LevelConst::MI_MI="秘密";
const QString LevelConst::JUE_MI="绝密";

LevelConst::LevelConst()
{

}

QVector<QString> LevelConst::GetList()
{
  QVector<QString> res_vec;
  res_vec.append(LevelConst::JI_MI);
  res_vec.append(LevelConst::MI_MI);
  res_vec.append(LevelConst::JUE_MI);
  return res_vec;

}
