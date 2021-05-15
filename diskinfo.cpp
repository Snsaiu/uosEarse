#include "diskinfo.h"

DiskInfo::DiskInfo()
{
}

DiskInfo::~DiskInfo()
{
}

vector<diskInfo> DiskInfo::getDiskVec()
{
    DiskNameVec.clear();
    char cmd[64];
    char res[10][10240];
    GetDiskName("lsblk");
    for (vector<diskInfo>::iterator iter = DiskNameVec.begin(); iter != DiskNameVec.end(); iter++)
    {
        string strTmp = iter->DiskName;
        string strDst = "smartctl -i /dev/";
        strDst.append(strTmp);
        shexec(*iter,strDst.c_str(), res, 10);
    }
    return DiskNameVec;
}

int DiskInfo::GetDiskName(const char *cmd)
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
        diskInfo disk;
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
            DiskNameVec.push_back(disk);
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
int DiskInfo::shexec(diskInfo &outInfo,const char *cmd, char res[][10240], int count)
{
    printf("shexec, cmd: %s\n", cmd);


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
        int dex = str.find(("Device Model:"));
        if(dex==0)
        {
            str1 = str.substr(dex+13);
            outInfo.DiskModel = str1;
        }
        dex = str.find(("Serial Number:"));
        if(dex==0)
        {
            str1 = str.substr(dex+13);
            outInfo.Serial = str1;
        }
        dex = str.find(("Device is:        Not"));
        if(dex==0)
        {
            outInfo.IsSystem = 1;
        }
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
