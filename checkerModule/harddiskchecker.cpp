#include "harddiskchecker.h"
#include <QString>
#include <regex>
#include <QRegExp>
#include <QProcess>

HardDiskChecker::HardDiskChecker()
{
    QStringList names= this->getDiskByType("name");
    this->checkSystem(names);
}

vector<HardDiskModel> HardDiskChecker::Check()
{

    DiskInfoVec = getDiskInfoVec();
    int count = DiskInfoVec.size();
    return DiskInfoVec;
}

vector<HardDiskModel> HardDiskChecker::Filter(vector<HardDiskModel> models)
{

    return models;
}



vector<HardDiskModel> HardDiskChecker::getDiskInfoVec()
{
    string strOne = "lsblk --nodeps -no name,serial,model,size";
    vector<DiskInfoNoSys> tempVec =  this->rigDiskInfo(); //shexecOne(strOne.c_str());
//    if(tempVec.size() == 0)
//        tempVec = shexecOne(strOne.c_str());
    DiskInfoVec.clear();
    for(int i=0;i<tempVec.size();i++)
    {


        HardDiskModel model;
        if(QString::fromStdString( tempVec[i].seri).compare( this->systemDiskSerial.simplified())==0)
        {
            model.IsSystem=1;
        }
        else{
             model.IsSystem=-1;
        }

        model.DiskModel=tempVec[i].module;
        model.Serial=tempVec[i].seri;
        model.AllMem=tempVec[i].size;
        model.DiskName=tempVec[i].name;
        DiskInfoVec.push_back(model);
    }


//    char cmd[64];
//    char res[12][1024];
//    GetDiskName("lsblk");
//    for (vector<HardDiskModel>::iterator iter = DiskInfoVec.begin(); iter != DiskInfoVec.end(); iter++)
//    {
//        string strTmp = iter->DiskName;
//        string strDst = "smartctl -i /dev/";
//        strDst.append(strTmp);
//        shexec(*iter,strDst.c_str(), res, 10);
//        for (vector<DiskInfoNoSys>::iterator iterSys = tempVec.begin();iterSys!=tempVec.end();iterSys++)
//        {
//            if(strTmp == iterSys->name)
//            {
//                iter->Serial = iterSys->seri;
//                iter->AllMem = iterSys->size;
//                iter->DiskModel = iterSys->module;
//            }
//        }
//    }
    return DiskInfoVec;
}

int HardDiskChecker::GetDiskName(const char *cmd)
{
    printf("GetDiskName, cmd: %s\n", cmd);

    FILE *pp = popen(cmd, "r");
    if(!pp) {
       printf("error, cannot popen cmd: %s\n", cmd);
       return -1;
    }
    int i = 0;
    char tmp[1024];
    memset(tmp,0,1024);
    while(fgets(tmp, sizeof(tmp), pp) != NULL) {
        if(tmp[strlen(tmp)-1] == '\n') {
           tmp[strlen(tmp)-1] = '\0';
        }
//        QString qs = QString(QLatin1String(tmp));
        HardDiskModel disk;
        string str(tmp);
        string str1(tmp);
        string Name;
        string mem;
        if(str.find(("sd"))==0)
        {
            Name = str.substr(0,3);
            disk.DiskName = Name;
            int pos = str1.find("G");
            if(pos>0)
            {
                mem= str1.substr(pos-5,6);
            }
            disk.AllMem = mem;
            DiskInfoVec.push_back(disk);
        }
    }

    int rv = pclose(pp);
    printf("ifexited: %d\n", WIFEXITED(rv));

    if (WIFEXITED(rv))
    {
        printf("subprocess exited, exit code: %d\n", WEXITSTATUS(rv));
    }

    return i;
}



//execute shell command
int HardDiskChecker::shexec(HardDiskModel &outInfo,const char *cmd, char res[][1024], int count)
{
    printf("shexec, cmd: %s\n", cmd);
    outInfo.IsSystem = -1;
    FILE *pp = popen(cmd, "r");
    if(!pp) {
       printf("error, cannot popen cmd: %s\n", cmd);
       return -1;
    }
    int i = 0;
    char tmp[10240];
    memset(tmp,0,10240);
    while(fgets(tmp, sizeof(tmp), pp) != NULL) {
        if(tmp[strlen(tmp)-1] == '\n') {
           tmp[strlen(tmp)-1] = '\0';
        }
//        QString qs = QString(QLatin1String(tmp));
        std::string str(tmp);
        std::string str1 ;
        int dex;
//        dex = str.find(("Device Model:"));
//        if(dex==0)
//        {
//            str1 = str.substr(dex+12);
//            outInfo.DiskModel = str1;
//        }
//        dex = str.find(("Serial Number:"));
//        if(dex==0)
//        {
//            str1 = str.substr(dex+14);
//            outInfo.Serial = str1;
//        }
        dex = str.find(("Device is:        Not"));
        if(dex==0)
        {
            outInfo.IsSystem = 1;
        }
//        dex = str.find(("Disk identifier:"));
//        if(dex==0)
//        {
//            str1 = str.substr(dex+16);
//            outInfo.Identifier = str1;
//        }
       printf("%d.get return results: %s\n", i, tmp);

    }

    int rv = pclose(pp);
    printf("ifexited: %d\n", WIFEXITED(rv));

    if (WIFEXITED(rv))
    {
        printf("subprocess exited, exit code: %d\n", WEXITSTATUS(rv));
    }

    return i;
}



vector<DiskInfoNoSys> HardDiskChecker::shexecOne(const char *cmd)
{
    printf("shexec, cmd: %s\n", cmd);
    vector<DiskInfoNoSys> diskInfoVec;

    FILE *pp = popen(cmd, "r");
    if(!pp) {
       printf("error, cannot popen cmd: %s\n", cmd);
       return diskInfoVec;
    }
    char tmp[1024];
    memset(tmp,0,1024);
    while(fgets(tmp, sizeof(tmp), pp) != NULL) {
        if(tmp[strlen(tmp)-1] == '\n') {
           tmp[strlen(tmp)-1] = '\0';
        }
        DiskInfoNoSys temSturct;
        temSturct.name = "";
        temSturct.seri = "";
        temSturct.module = "";
        temSturct.size = "";
        string str(tmp);
        istringstream is(str);
        is>>temSturct.name;
        is>>temSturct.seri;
        is>>temSturct.module;
        if(temSturct.module.length()<6)
        {
            usleep(10);
        }
        is>>temSturct.size;
        if(temSturct.size == ""||temSturct.name == ""||temSturct.seri == ""||temSturct.module == "")
        {
            usleep(50);
            int rv = pclose(pp);
            printf("ifexited: %d\n", WIFEXITED(rv));

            if (WIFEXITED(rv))
            {
                printf("subprocess exited, exit code: %d\n", WEXITSTATUS(rv));
            }
            usleep(20);
            diskInfoVec.clear();
            return  diskInfoVec;
        }
        diskInfoVec.push_back(temSturct);

    }

    int rv = pclose(pp);
    printf("ifexited: %d\n", WIFEXITED(rv));

    if (WIFEXITED(rv))
    {
        printf("subprocess exited, exit code: %d\n", WEXITSTATUS(rv));
    }
    return diskInfoVec;
}

vector<DiskInfoNoSys> HardDiskChecker::rigDiskInfo()
{
    int count= this->getHardDiskCount();
   vector<DiskInfoNoSys> res;
   for(int i=0;i<count;i++)
   {   DiskInfoNoSys item;
       res.push_back(item);
   }
   QStringList names= this->getDiskByType("name");

//   string name;
//   string seri;
//   string module;
//   string size;
   for(int i=0;i<count;i++)
   {
       res[i].name=names[i].toStdString();
   }

  //string strOne = "lsblk --nodeps -no name,serial,model,size";

   QStringList seris=this->getDiskByType("serial");
   for(int i=0;i<count;i++)
   {
       res[i].seri=seris[i].toStdString();
   }

   QStringList models=this->getDiskByType("model");
   for(int i=0;i<count;i++)
   {
       res[i].module=models[i].toStdString();
   }



   QStringList sizes=this->getDiskByType("size");
   for(int i=0;i<count;i++)
   {
       res[i].size=sizes[i].toStdString();
   }
   return res;
}





QStringList HardDiskChecker::getDiskByType(QString item)
{
    QString str="lsblk --nodeps -no "+item;
    QProcess *p=new QProcess();
    p->start(str);
    p->waitForFinished();
    QByteArray bytes= p->readAllStandardOutput();
    QString res=bytes;
    QStringList li= res.split('\n');
    delete p;
    return  li;


}

void HardDiskChecker::checkSystem(QStringList disk)
{
   if(this->systemDiskSerial!="")
       return;
   else{
       for(int j=0;j<disk.size()-1;j++)
       {

           QString name=disk[j];
        string cc="smartctl -i /dev/"+ name.toStdString();
          const char* cmd=  cc.c_str();
           FILE *pp = popen(cmd, "r");
           if(!pp) {
              printf("error, cannot popen cmd: %s\n", cmd);
              return ;
           }
           int i = 0;
           char tmp[10240];
           memset(tmp,0,10240);
           while(fgets(tmp, sizeof(tmp), pp) != NULL) {
               if(tmp[strlen(tmp)-1] == '\n') {
                  tmp[strlen(tmp)-1] = '\0';
               }
       //        QString qs = QString(QLatin1String(tmp));
               std::string str(tmp);
               std::string str1 ;
               int dex;
       //        dex = str.find(("Device Model:"));
       //        if(dex==0)
       //        {
       //            str1 = str.substr(dex+12);
       //            outInfo.DiskModel = str1;
       //        }
       //        dex = str.find(("Serial Number:"));
       //        if(dex==0)
       //        {
       //            str1 = str.substr(dex+14);
       //            outInfo.Serial = str1;
       //        }
               dex = str.find(("Device is:        Not"));
               if(dex==0)
               {
                   QString str="lsblk /dev/"+disk[j] +" --nodeps -no serial";
                   QProcess *p=new QProcess();
                   p->start(str);
                   p->waitForFinished();
                   QByteArray bytes= p->readAllStandardOutput();
                   QString res=bytes;
                   this->systemDiskSerial=res;
                   delete p;
                   return;
               }
       //        dex = str.find(("Disk identifier:"));
       //        if(dex==0)
       //        {
       //            str1 = str.substr(dex+16);
       //            outInfo.Identifier = str1;
       //        }


           }

           //

}

   }

}


int HardDiskChecker::getHardDiskCount()
{
    QStringList res= this->getDiskByType("name");
    return res.length()-1;
}


