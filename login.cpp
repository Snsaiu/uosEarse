#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <QDesktopWidget>
#include <QLibrary>
#include <QDebug>
#include <QProcess>
#include "LogSql.h"

int Login::PublicUserId = 0;
Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setScreen();
    /*居中显示*/
    QDesktopWidget *desktop = QApplication::desktop();
    move((desktop->width()-this->width())/2,(desktop->height()-this->height())/2);
    /*隐藏外边框*/
    setWindowFlags(Qt::FramelessWindowHint);
    QPalette pal = this->palette();
    pal.setBrush(QPalette::Background,QBrush(QPixmap(":/back/release/loginBack.jpg")));
    setPalette(pal);
    this->ui->userName->setStyleSheet("background:#dadada;border-width:0;border-style:outside;border-radius:15px");
    this->ui->userName->setClearButtonEnabled(true);
    this->ui->userName->setPlaceholderText(QStringLiteral("   请输入账号"));
    this->ui->password->setPlaceholderText(QStringLiteral("   请输入密码"));
    this->ui->password->setClearButtonEnabled(true);
//    CreateTable();
//    inserttabase();
    this->ui->password->setStyleSheet("background:#dadada;border-width:0;border-style:outside;border-radius:15px");
    this->connect(this->ui->loginBtn,&QPushButton::pressed,this,[=](){
      int tempCount = getSecrettimes();
      if(this->ui->userName->text()!=NULL&&this->ui->password->text()!=NULL)
      {
          if(IsTime(LogInTimes[radioId].OldTime))
          {
               LogInTimes[radioId].isStop = false;
          }
          else {
              LogInTimes[radioId].isStop = true;
          }
          if(LogInTimes[radioId].isStop)
          {
              QMessageBox::information(NULL, "Warning", "输入错误密码超过限定次数，请5分钟后再试！！！");
              return ;
          }
          QString  type = "用户登陆";
          QString *temp = getdatabase(radioId);
          if(this->ui->userName->text()==temp[0]&&this->ui->password->text()==temp[1])
          {
              this->GoLogin();
              QString  YN = "登陆成功";
              LogSql log;
              log.RunInsert(type,YN);
              PublicUserId = temp[2].toInt();
              if(isUpdateUserTable(temp[3]))
              {
                QMessageBox::information(NULL, "Warning", "密码太旧，安全起见，请修改密码！！！");
              }

              userName = ui->userName->text();
          }
          else {
              QString  YN = "登陆失败";
              LogSql log;
              log.RunInsert(type,YN);
              QMessageBox::information(NULL, "Warning", "用户种类错误或用户名、密码错误！！！");
              LogInTimes[radioId].count++;
              if(LogInTimes[radioId].count>=tempCount&&tempCount>0)
              {
                  LogInTimes[radioId].isStop = true;
                  LogInTimes[radioId].CountTimer->start(1000*60);
                  QDateTime current_date_time =QDateTime::currentDateTime();
                  LogInTimes[radioId].OldTime = current_date_time.toString("yyyy-MM-dd hh:mm:ss");
                  writerToLogin();
              }
          }
      }
      else
      {
        QString  type = "用户登陆";
        QString  YN = "登陆失败";
        LogSql log;
        log.RunInsert(type,YN);
        QMessageBox::information(NULL, "Warning", "用户名或密码错误！！！");
        LogInTimes[radioId].count++;
        if(LogInTimes[radioId].count>=tempCount&&tempCount>0)
        {
            LogInTimes[radioId].isStop = true;
            LogInTimes[radioId].CountTimer->start(1000*60);
        }
      }


    });
    this->connect(this->ui->cancleBtn,&QPushButton::pressed,this,[=]{
        this->ui->userName->setText("");
        this->ui->password->setText("");
    });
//    this->ui->userName->setText(getdatabase(1)[0]);
//    this->ui->password->setText(getdatabase(1)[1]);
//    resetdatabase();

    secretNumber = getSecrettimes();
    ///错误登陆次数
    LogInTimes[0].CountTimer = new QTimer;
    LogInTimes[0].isStop = false;
    LogInTimes[0].count = 0;
    LogInTimes[1].CountTimer = new QTimer;
    LogInTimes[1].isStop = false;
    LogInTimes[1].count = 0;
    LogInTimes[2].CountTimer = new QTimer;
    LogInTimes[2].isStop = false;
    LogInTimes[2].count = 0;
    connect(LogInTimes[0].CountTimer,SIGNAL(timeout()),this,SLOT(LogInTimesFlag0()));
    connect(LogInTimes[1].CountTimer ,SIGNAL(timeout()),this,SLOT(LogInTimesFlag1()));
    connect(LogInTimes[2].CountTimer ,SIGNAL(timeout()),this,SLOT(LogInTimesFlag2()));
    readfromFile();

    //用户登陆权限区分
    radioId = 0;
    btnGroupRadio = new QButtonGroup(this);
    btnGroupRadio->addButton(ui->radioButton_0,0);
    btnGroupRadio->addButton(ui->radioButton_1,1);
    btnGroupRadio->addButton(ui->radioButton_2,2);
    ui->radioButton_0->setChecked(true);
    connect(ui->radioButton_0,SIGNAL(clicked()),this,SLOT(onRadioGroupClick()));
    connect(ui->radioButton_1,SIGNAL(clicked()),this,SLOT(onRadioGroupClick()));
    connect(ui->radioButton_2,SIGNAL(clicked()),this,SLOT(onRadioGroupClick()));  
}

Login::~Login()
{
    delete ui;
}

void Login::resetdatabase(int num)
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("DataBase.db");
    database.setUserName("7410");
    database.setPassword("7410");
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
        QSqlQuery sql_query(database);
        //更新数据（修改数据）
        QString update_sql = "update User set passwd = :passwd where id = :id";
        sql_query.prepare(update_sql);
        QString passd = "lalala";
        sql_query.bindValue(":passwd",passd);
        sql_query.bindValue(":id", 2);
        if(!sql_query.exec())
        {
            qDebug() << sql_query.lastError();
        }
        else
        {
            qDebug() << "updated!";
        }
        database.close();
    }
}

void Login::inserttabase()
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("DataBase.db");
    database.setUserName("7410");
    database.setPassword("7410");
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
        //插入数据
        QSqlQuery sql_query(database);
        QString username = "user";
        QString passwd = "!Qaz123456";

        QDateTime current_date_time =QDateTime::currentDateTime();
        QString current_time =current_date_time.toString("yyyy-MM-dd hh:mm:ss");

        if(!sql_query.prepare("INSERT INTO User(name,passwd,seq,date) VALUES (:name, :passwd, :seq, :date)"))
        {
            qDebug() << sql_query.lastError();
        }
        sql_query.bindValue(":name",username);
        sql_query.bindValue(":passwd",passwd);
        sql_query.bindValue(":seq",2);
        sql_query.bindValue(":date",current_time);

        if(!sql_query.exec())
        {
            qDebug() << sql_query.lastError();
        }
        database.close();
    }
}

QString* Login::getdatabase(int num)
{
    QSqlDatabase database;
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("DataBase.db");
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
        QSqlQuery sql_query(database);
        QString select_sql = "select * from User";
        if(!sql_query.exec(select_sql))
        {
            qDebug()<<sql_query.lastError();
        }
        else
        {
            sql_query.seek(num);
            QSqlRecord rec=sql_query.record();
            qs[0] = rec.value("name").toString();
            qs[1] = rec.value("passwd").toString();
            qs[2] = rec.value("seq").toString();
            qs[3] = rec.value("date").toString();
            qDebug() << QObject::tr("automobil表字段数：" )<< rec.count();
            qDebug() << "qs[0] = "<<qs[0]<<"qs[1] ="<<qs[1] ;
            database.close();
            return qs;
        }
        database.close();
    }
}

bool Login::CreateTable()
{

    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("DataBase.db");

    if (!database.open())
    {
        qDebug() << "Error: Failed to connect DataBase." << database.lastError();
        return false;
    }
    else
    {
        qDebug() << "open db succwss" ;
        //创建表格
        QSqlQuery sql_query(database);
        if(!sql_query.exec("create table if not exists User(id INTEGER PRIMARY KEY AUTOINCREMENT,"
                           "name TEXT NOT NULL,"
                           "passwd TEXT NOT NULL,"
                           "seq TEXT NOT NULL,"
                           "date TEXT NOT NULL)"))
        {
            qDebug() << "Error: Fail to create table." << sql_query.lastError();
            return true;
        }
        else
        {
            qDebug() << "Table created!";
            database.close();
            return true;
        }
    }
}

void Login::onRadioGroupClick()
{
    radioId = btnGroupRadio->checkedId();
//    switch (btnGroupRadio->checkedId())
//    {
//    case 0:
//        break;
//    case 1:
//        break;
//    case 2:
//        break;
//    }
}

//判断是否更新密码，日期三个月
bool Login::isUpdateUserTable(QString Tabletime)
{
    QDateTime tableTime = QDateTime::fromString(Tabletime,"yyyy-MM-dd hh:mm:ss");
    QDateTime current_date_time =QDateTime::currentDateTime();
    uint table_Time = tableTime.toTime_t();
    uint current_time = current_date_time.toTime_t();
    int t_Ret = current_time - table_Time;
    if(t_Ret > 3*30*24*60*60)
    {
        return true;
    }
    else {
        return false;
    }
}

int Login::getSecrettimes()
{
    QString num;
    QString path = QDir::currentPath() + "/LogInNum";
    QFile *file = new QFile(path);//此路径下没有就会自己创建一个
    while(!file->open(QIODevice::ReadWrite));//以读写切追加写入的方式操作文本

    QTextStream txtOutput(file);
    QString first = txtOutput.readLine();
    num = first.section('/',1,1);
    return num.toInt();
}

void Login::LogInTimesFlag0()
{
    LogInTimes[0].isStop = false;
    LogInTimes[0].count = 0;
    LogInTimes[0].CountTimer->stop();
}
void Login::LogInTimesFlag1()
{
    LogInTimes[1].isStop = false;
    LogInTimes[1].count = 0;
    LogInTimes[1].CountTimer->stop();
}

void Login::LogInTimesFlag2()
{
    LogInTimes[2].isStop = false;
    LogInTimes[2].count = 0;
    LogInTimes[2].CountTimer->stop();
}

void Login::writerToLogin()
{
    QString path = QDir::currentPath() + "/LogInNum";
    QFile *file = new QFile(path);//此路径下没有就会自己创建一个
    while(!file->open(QIODevice::WriteOnly));//以读写切追加写入的方式操作文本

    QTextStream txtOutput(file);
    txtOutput<<"/"<<secretNumber<<endl;
//    QDateTime current_date_time =QDateTime::currentDateTime();
//    QString current_time =current_date_time.toString("yyyy-MM-dd hh:mm:ss");
//    txtOutput<<"/"<<0<<"/"<<current_time<<endl;
//    txtOutput<<"/"<<1<<"/"<<current_time<<endl;
//    txtOutput<<"/"<<2<<"/"<<current_time<<endl;
    txtOutput<<"/"<<0<<"/"<<LogInTimes[0].OldTime<<endl;
    txtOutput<<"/"<<1<<"/"<<LogInTimes[1].OldTime<<endl;
    txtOutput<<"/"<<2<<"/"<<LogInTimes[2].OldTime<<endl;

}

void Login::readfromFile()
{
    int num = 0;
    QString path = QDir::currentPath() + "/LogInNum";
    QFile *file = new QFile(path);//此路径下没有就会自己创建一个
    while(!file->open(QIODevice::ReadWrite));//以读写切追加写入的方式操作文本

    QTextStream txtOutput(file);
    while(!txtOutput.atEnd())
    {
        QString line = txtOutput.readLine();
        QString first = line.section('/',1,1);
        QString second = line.section('/',2,2);
        if(num == 0)
            secretNumber = first.toInt();
        if(0<num&&num<4)
        {
            LogInTimes[first.toInt()].OldTime = second;
        }
        num++;
    }
}

bool Login::IsTime(QString oldTime)
{
    QDateTime tableTime = QDateTime::fromString(oldTime,"yyyy-MM-dd hh:mm:ss");
    QDateTime current_date_time =QDateTime::currentDateTime();
    uint table_Time = tableTime.toTime_t();
    uint current_time = current_date_time.toTime_t();
    int t_Ret = current_time - table_Time;
    if(t_Ret > 5*60)
    {
        return true;
    }
    else {
        return false;
    }
}

void Login::setScreen()
{
    QProcess process;
    QStringList cmd = {"-c","xset -dpms"};
    //system("xset -dpms");
    process.start("/bin/bash",cmd);

}

QString Login::getUserName() const
{
    return userName;
}


