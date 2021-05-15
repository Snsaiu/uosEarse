#include "checkerstrategy.h"

CheckerStrategy::CheckerStrategy()
{

}

void CheckerStrategy::AddChecker(CheckerDiskAbstraction *checker)
{
    _list.push_back(checker);
}

vector<HardDiskModel> CheckerStrategy::Perform()
{
     vector<HardDiskModel> _res;

     bool canWrite=true;
     for (int i=0;i<_list.size();i++) {
         vector<HardDiskModel>  items = this->_list[i]->Check();
         if(items.size()==0)
             continue;
         for (int j=0;j<items.size();j++) {
             //filter
             for (int k = 0;k<_res.size();k++) {
                 if(_res[k].Serial==items[j].Serial&&_res[k].DiskModel==items[j].DiskModel){
                     canWrite=false;
                     if(items[j].IsSystem==1)
                     {
                        _res[k].IsSystem = 1;
                     }
                     // add filter
                     break;
                 }
             }
             if(canWrite)
             {
                 _res.push_back(items[j]);
             }
             canWrite=true;
         }
     }
    return _res;
}
