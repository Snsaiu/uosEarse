#include "usbchecker.h"

UsbChecker::UsbChecker()
{

}

vector<HardDiskModel> UsbChecker::Check()
{
    DiskInfoVec = getDiskInfoVec();
    return DiskInfoVec;
}

vector<HardDiskModel> UsbChecker::Filter(vector<HardDiskModel> models)
{

}

vector<HardDiskModel> UsbChecker::getDiskInfoVec()
{
    string strOne = "lsblk --nodeps -no name,serial,model,size";
    vector<DiskInfoNoSys> tempVec = shexecOne(strOne.c_str());
    DiskInfoVec.clear();
    char cmd[64];
    char res[10][10240];
    GetDiskName("lsblk");
    for (vector<HardDiskModel>::iterator iter = DiskInfoVec.begin(); iter != DiskInfoVec.end(); iter++)
    {
        string strTmp = iter->DiskName;
        string strDst = "fdisk -l /dev/";
        strDst.append(strTmp);
        shexec(*iter,strDst.c_str(), res, 10);
        for (vector<DiskInfoNoSys>::iterator iterSys = tempVec.begin();iterSys!=tempVec.end();iterSys++)
        {
            if(strTmp == iterSys->name)
            {
                iter->Serial = iterSys->seri;
                iter->AllMem = iterSys->size;
                iter->DiskModel = iterSys->module;
            }
        }
    }
    return DiskInfoVec;
}

int UsbChecker::GetDiskName(const char *cmd)
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
int UsbChecker::shexec(HardDiskModel &outInfo,const char *cmd, char res[][10240], int count)
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
//        int dex = str.find(("Disk model:"));
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

vector<DiskInfoNoSys>UsbChecker::shexecOne(const char *cmd)
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
        string str(tmp);
        istringstream is(str);
        is>>temSturct.name>>temSturct.seri>>temSturct.module>>temSturct.size;

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
