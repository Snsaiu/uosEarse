#include "basegrinder.h"
#include "ui_basegrinder.h"
#include <QMessageBox>
#include <QDesktopWidget>
#include <QDebug>
#include <QImage>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "LogSql.h"



basegrinder::basegrinder(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::basegrinder)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog);
    this->ui->settingBtnControl->setStyleSheet("background:#e2e2e2");
    /*居中显示*/
    QDesktopWidget *desktop = QApplication::desktop();
    move((desktop->width()-this->width())/2,(desktop->height()-this->height())/2);
    /*隐藏外边框*/
    setWindowFlags(Qt::FramelessWindowHint);
    QPixmap pixmapwait(":/back/release/waitCh.png");
    this->ui->waitingBtn->setIcon(QIcon(pixmapwait));
    this->ui->mainWidget->setCurrentIndex(0);

    this->m_login.show();
    /*登录成功弹窗*/
    connect(&this->m_login,&Login::GoLogin,this,&basegrinder::GoLogin);
    /*退出系统*/
    connect(this->ui->exitBtn,SIGNAL(clicked()),this,SLOT(close()));
    /*等待擦除*/
    connect(this->ui->waitingBtn,&QPushButton::pressed,[=]{
        {
            QPixmap pixmapwait(":/back/release/waitCh.png");
            this->ui->waitingBtn->setIcon(QIcon(pixmapwait));
            QPixmap pixmapearse(":/back/release/erase.png");
            this->ui->erasingBtn->setIcon(QIcon(pixmapearse));
            QPixmap pixmapsuccess(":/back/release/success.png");
            this->ui->succrssBtn->setIcon(QIcon(pixmapsuccess));
            QPixmap pixmaplose(":/back/release/lose.png");
            this->ui->loseBtn->setIcon(QIcon(pixmaplose));
            QPixmap pixmaplog(":/back/release/logger.png");
            this->ui->loggerBtn->setIcon(QIcon(pixmaplog));
            QPixmap pixmapset(":/back/release/set.png");
            this->ui->settingBtn->setIcon(QIcon(pixmapset));
            this->ui->mainWidget->setCurrentIndex(0);
//            QString  type = "等待擦除界面";
//            QString  YN = "进入界面";
//            LogSql log;
//            log.RunInsert(type,YN);
        }
    });
    /*正在擦除*/
    connect(this->ui->erasingBtn,&QPushButton::pressed,this,[=]{
        {
            QPixmap pixmapwait(":/back/release/wait.png");
            this->ui->waitingBtn->setIcon(QIcon(pixmapwait));
            QPixmap pixmapearse(":/back/release/eraseCh.png");
            this->ui->erasingBtn->setIcon(QIcon(pixmapearse));
            QPixmap pixmapsuccess(":/back/release/success.png");
            this->ui->succrssBtn->setIcon(QIcon(pixmapsuccess));
            QPixmap pixmaplose(":/back/release/lose.png");
            this->ui->loseBtn->setIcon(QIcon(pixmaplose));
            QPixmap pixmaplog(":/back/release/logger.png");
            this->ui->loggerBtn->setIcon(QIcon(pixmaplog));
            QPixmap pixmapset(":/back/release/set.png");
            this->ui->settingBtn->setIcon(QIcon(pixmapset));
            this->ui->mainWidget->setCurrentIndex(1);
//            QString  type = "正在擦除界面";
//            QString  YN = "进入界面";
//            LogSql log;
//            log.RunInsert(type,YN);

        }
    });
    /*擦除成功*/
    connect(this->ui->succrssBtn,&QPushButton::pressed,this,[=]{
        {
            QPixmap pixmapwait(":/back/release/wait.png");
            this->ui->waitingBtn->setIcon(QIcon(pixmapwait));
            QPixmap pixmapearse(":/back/release/erase.png");
            this->ui->erasingBtn->setIcon(QIcon(pixmapearse));
            QPixmap pixmapsuccess(":/back/release/successCh.png");
            this->ui->succrssBtn->setIcon(QIcon(pixmapsuccess));
            QPixmap pixmaplose(":/back/release/lose.png");
            this->ui->loseBtn->setIcon(QIcon(pixmaplose));
            QPixmap pixmaplog(":/back/release/logger.png");
            this->ui->loggerBtn->setIcon(QIcon(pixmaplog));
            QPixmap pixmapset(":/back/release/set.png");
            this->ui->settingBtn->setIcon(QIcon(pixmapset));
            this->ui->mainWidget->setCurrentIndex(2);
//            QString  type = "擦除成功界面";
//            QString  YN = "进入界面";
//            LogSql log;
//            log.RunInsert(type,YN);
        }
    });
    /*擦除失败*/
    connect(this->ui->loseBtn,&QPushButton::pressed,this,[=]{
        {
            QPixmap pixmapwait(":/back/release/wait.png");
            this->ui->waitingBtn->setIcon(QIcon(pixmapwait));
            QPixmap pixmapearse(":/back/release/erase.png");
            this->ui->erasingBtn->setIcon(QIcon(pixmapearse));
            QPixmap pixmapsuccess(":/back/release/success.png");
            this->ui->succrssBtn->setIcon(QIcon(pixmapsuccess));
            QPixmap pixmaplose(":/back/release/loseCh.png");
            this->ui->loseBtn->setIcon(QIcon(pixmaplose));
            QPixmap pixmaplog(":/back/release/logger.png");
            this->ui->loggerBtn->setIcon(QIcon(pixmaplog));
            QPixmap pixmapset(":/back/release/set.png");
            this->ui->settingBtn->setIcon(QIcon(pixmapset));
            this->ui->mainWidget->setCurrentIndex(3);
//            QString  type = "擦除失败界面";
//            QString  YN = "进入界面";
//            LogSql log;
//            log.RunInsert(type,YN);
        }
    });
    /*日志*/
    connect(this->ui->loggerBtn,&QPushButton::pressed,[=]{
        {
            QPixmap pixmapwait(":/back/release/wait.png");
            this->ui->waitingBtn->setIcon(QIcon(pixmapwait));
            QPixmap pixmapearse(":/back/release/erase.png");
            this->ui->erasingBtn->setIcon(QIcon(pixmapearse));
            QPixmap pixmapsuccess(":/back/release/success.png");
            this->ui->succrssBtn->setIcon(QIcon(pixmapsuccess));
            QPixmap pixmaplose(":/back/release/lose.png");
            this->ui->loseBtn->setIcon(QIcon(pixmaplose));
            QPixmap pixmaplog(":/back/release/loggerCh.png");
            this->ui->loggerBtn->setIcon(QIcon(pixmaplog));
            QPixmap pixmapset(":/back/release/set.png");
            this->ui->settingBtn->setIcon(QIcon(pixmapset));
//            if(Login::PublicUserId == 0)
//            {
//                QMessageBox::warning(this,"警告","普通操作员无法查看日志！！！");
//                QString  type = "日志界面";
//                QString  YN = "查看日志失败";
//                LogSql log;
//                log.RunInsert(type,YN);
//                return;
//            }
            this->ui->mainWidget->setCurrentIndex(4);
            this->ui->loggerPage->CleanTable();
            this->ui->loggerPage->show_log();

        }
    });
    /*设置*/
    connect(this->ui->settingBtn,&QPushButton::pressed,[=]{
        {
            QPixmap pixmapwait(":/back/release/wait.png");
            this->ui->waitingBtn->setIcon(QIcon(pixmapwait));
            QPixmap pixmapearse(":/back/release/erase.png");
            this->ui->erasingBtn->setIcon(QIcon(pixmapearse));
            QPixmap pixmapsuccess(":/back/release/success.png");
            this->ui->succrssBtn->setIcon(QIcon(pixmapsuccess));
            QPixmap pixmaplose(":/back/release/lose.png");
            this->ui->loseBtn->setIcon(QIcon(pixmaplose));
            QPixmap pixmaplog(":/back/release/logger.png");
            this->ui->loggerBtn->setIcon(QIcon(pixmaplog));
            QPixmap pixmapset(":/back/release/setCh.png");
            this->ui->settingBtn->setIcon(QIcon(pixmapset));
            QPixmap pixmapwordcon(":/back/release/wordconCh.png");
            this->ui->rewordBtn->setIcon(QIcon(pixmapwordcon));
            QPixmap pixmaplogcon(":/back/release/logcon.png");
            this->ui->loggerConBtn->setIcon(QIcon(pixmaplogcon));
            this->ui->mainWidget->setCurrentIndex(6);
            ui->setWidget->setCurrentIndex(3);
            ui->rewordBtn->setChecked(true);

            this->ui->resetBtn->click();
//            QString  type = "设置界面";
//            QString  YN = "进入界面";
//            LogSql log;
//            log.RunInsert(type,YN);

        }
    });
    userlev = new UserLevel ();
    TempUserId = 0;
//    connect(userlev,SIGNAL(&UserLevel::hasData()),this,SLOT(getData()));
    connect(userlev,&UserLevel::hasData,this,[=](){

     this->getData();
    });
    /*修改密码*/
    connect(ui->rewordBtn,&QPushButton::pressed,[=]{
        {
            QPixmap pixmapSetlogin(":/back/release/loginSetFalse.png");
            this->ui->LoginSetBtn->setIcon(pixmapSetlogin);
            QPixmap pixmapwordcon(":/back/release/wordconCh.png");
            this->ui->rewordBtn->setIcon(QIcon(pixmapwordcon));
            QPixmap pixmaplogcon(":/back/release/logcon.png");
            this->ui->loggerConBtn->setIcon(QIcon(pixmaplogcon));

            userlev->show();
             userlev->setAttribute(Qt::WA_DeleteOnClose);
            //管理员修改操作员密码，隐藏就密码窗口
            if(Login::PublicUserId ==2 &&TempUserId == 0)
            {
                this->ui->oldpassword->hide();
                this->ui->label_2->hide();
            }
            TempUserId = userlev->radioId;
            int flag = Login::PublicUserId;
            if((flag <2&&TempUserId!=flag)||(flag==2&&TempUserId==1))
            {
                QMessageBox::warning(this,"警告","没有修改的权限！");
                return;
            }
            ui->setWidget->setCurrentIndex(0);
            this->ui->resetBtn->click();
        }
    });
    /*日志管理*/
    connect(this->ui->loggerConBtn,&QPushButton::pressed,[=]{
        {
            QPixmap pixmapSetlogin(":/back/release/loginSetFalse.png");
            this->ui->LoginSetBtn->setIcon(pixmapSetlogin);
            QPixmap pixmapwordcon(":/back/release/wordcon.png");
            this->ui->rewordBtn->setIcon(QIcon(pixmapwordcon));
            QPixmap pixmaplogcon(":/back/release/logconCh.png");
            this->ui->loggerConBtn->setIcon(QIcon(pixmaplogcon));
            QPixmap pixmapdetelog(":/back/release/detelog.png");
            ui->detelogBtn->setIcon(QIcon(pixmapdetelog));
            ui->setWidget->setCurrentIndex(1);

            ui->LogTimeBox->setDisabled(true);
            ui->LogOkBtn->setDisabled(true);
        }
    });

    ///输入密码次数
    connect(this->ui->LoginSetBtn,&QPushButton::pressed,[=]{
        QPixmap pixmapwordcon(":/back/release/wordcon.png");
        this->ui->rewordBtn->setIcon(QIcon(pixmapwordcon));
        QPixmap pixmaplogcon(":/back/release/logcon.png");
        this->ui->loggerConBtn->setIcon(QIcon(pixmaplogcon));
        QPixmap pixmapSetlogin(":/back/release/loginSetTrue.png");
        this->ui->LoginSetBtn->setIcon(pixmapSetlogin);
        ui->setWidget->setCurrentIndex(2);
    });

    /*删除日志*/
    connect(this->ui->detelogBtn,&QPushButton::pressed,[=]{
        {

            LogSql logClean;
            if(Login::PublicUserId<2)
            {
                QMessageBox::warning(this,"警告","没有权限清除日志！！！");
                logClean.RunInsert("删除日志","删除失败");
                return;
            }
            else {
                    firstDeleteLog();
                    QMessageBox::warning(this,"警告","完成！！！");
            }
//            if(!logClean.CleanLog())
//                logClean.RunInsert("删除日志","删除失败");
//            else {
//                QMessageBox::Ok;
//            }
        }
    });
    /*重置密码输入*/
    connect(this->ui->resetBtn,&QPushButton::pressed,[=]{
        {
            this->ui->oldpassword->setText("");
            this->ui->newpassword->setText("");
            this->ui->newpassword_2->setText("");
        }
    });
    /*确认修改密码*/

    connect(this->ui->trueBtn,&QPushButton::pressed,[=]{
        {
            LogSql log;

            QString exp="^(?=.*[A-Za-z])(?=.*\\d)(?=.*[$@$!%*#?&])[A-Za-z\\d$@$!%*#?&]{8,}$";
            QRegExp reg(exp);
            reg.setCaseSensitivity(Qt::CaseInsensitive);

            if(Login::PublicUserId !=2 ||TempUserId == Login::PublicUserId)
            {
                if(this->ui->newpassword->text()!=this->ui->newpassword_2->text())
                {
                   QMessageBox::warning(this,"提示","两次新密码输入不一致！");
                   log.RunInsert("修改密码","修改失败");
                }else if(this->ui->oldpassword->text()!="")
                {
                  QString *qsTemp;
                  qsTemp = getdatabase(TempUserId);
                  if(qsTemp[1] != this->ui->oldpassword->text())
                  {
                      log.RunInsert("修改密码","修改失败");
                      QMessageBox::warning(this,"警告","旧密码输入错误！");
                  }
                  else {
                      if(resetdatabase(this->ui->newpassword->text()))
                      {
                          log.RunInsert("修改密码","修改成功");
                          QMessageBox::warning(this,"提示","密码修改成功！");
                          this->hide();
                          this->m_login.show();
                      }
                      else {
                          log.RunInsert("修改密码","修改失败");
                          QMessageBox::warning(this,"提示","密码修改失败！");
                      }
                  }
                }else if(this->ui->oldpassword->text()=="")
                {
                  log.RunInsert("修改密码","修改失败");
                  QMessageBox::warning(this,"警告","旧密码不能为空！");
                }
                else if(reg.exactMatch(this->ui->newpassword->text())==false)
                {
                  log.RunInsert("修改密码","修改失败");
                  QMessageBox::warning(this,"警告","密码不符合规范！");
                }
            }else
            {
                resetdatabase(this->ui->newpassword->text());
                log.RunInsert("修改密码","修改成功");
                QMessageBox::warning(this,"提示","密码修改成功！");
            }
        }
    });

    memset(LonInTimes,0,sizeof(LonInTimes));

//    QSqlDatabase database;
//    if (QSqlDatabase::contains("qt_sql_default_connection"))
//    {
//        database = QSqlDatabase::database("qt_sql_default_connection");
//    }  qDebug("fdfd");
//    else
//    {
//        database = QSqlDatabase::addDatabase("QSQLITE");
//        database.setDatabaseName("MyDataBase.db");
//        database.setUserName("XingYeZhiXia");
//        database.setPassword("123456");
//    }

//    if (!database.open(waitingBtn))
//    {
//        qDebug() << "Error: Failed to connect database." << database.lastError();
//    }
//    else
//    {
//        //创建表格
//        QSqlQuery sql_query;
//        QString create_sql = "create table student (id int primary key, name varchar(30), age int)";
//        sql_query.prepare(create_sql);
//        if(!sql_query.exec())
//        {
//            qDebug() << "Error: Fail to create table." << sql_query.lastError();
//        }
//        else
//        {
//            qDebug() << "Table created!";
//        }

//        //插入数据
//        int max_id = 0;
//        QString insert_sql = "insert into student values (?, ?, ?)";
//        sql_query.prepare(insert_sql);
//        sql_query.addBindValue(max_id+1);
//        sql_query.addBindValue("Wang");
//        sql_query.addBindValue(25);
//        if(!sql_query.exec())
//        {
//            qDebug() << sql_query.lastError();
//        }
//        else
//        {
//            qDebug() << "inserted Wang!";
//        }
//        if(!sql_query.exec("INSERT INTO student VALUES(3, \"Li\", 23)"))
//        {
//            qDebug() << sql_query.lastError();
//        }
//        else
//        {
//            qDebug() << "inserted Li!";
//        }

//        //更新数据（修改数据）
//        QString update_sql = "update student set name = :name where id = :id";
//        sql_query.prepare(update_sql);
//        sql_query.bindValue(":name", "Qt");
//        sql_query.bindValue(":id", 1);
//        if(!sql_query.exec())
//        {
//            qDebug() << sql_query.lastError();
//        }
//        else
//        {
//            qDebug() << "updated!";
//        }
//        //查询数据
//        QString select_sql = "select id, name from student";
//        if(!sql_query.exec(select_sql))
//        {
//            qDebug()<<swaitingBtnql_query.lastError();
//        }
//        else
//        {
//            while(sql_query.next())
//            {
//                int id = sql_query.value(0).toInt();
//                QString name = sql_query.value(1).toString();
//                qDebug()<<QString("id:%1    name:%2").arg(id).arg(name);
//            }
//        }
//        //查询全部数据
//        QString select_all_sql = "select * from student";
//        sql_query.prepare(select_all_sql);
//        if(!sql_query.exec())
//        {
//            qDebug()<<sql_query.lastError();
//        }
//        else
//        {
//            while(sql_query.next())
//            {
//                int id = sql_query.value(0).toInt();
//                QString name = sql_query.value(1).toString();
//                int age = sql_query.value(2).toInt();
//                qDebug()<<QString("id:%1    name:%2    age:%3").arg(id).arg(name).arg(age);
//            }
//        }
//        //查询最大id
//        QString select_max_sql = "select max(id) from student";

//        sql_query.prepare(select_max_sql);
//        if(!sql_query.exec())
//        {
//            qDebug() << sql_query.lastError();
//        }
//        else
//        {
//            while(sql_query.next())
//            {
//                max_id = sql_query.value(0).toInt();
//                qDebug() << QString("max id:%1").arg(max_id);
//            }
//        }
//        //删除一条数据
//        QString delete_sql = "delete from student where id = ?";
//        sql_query.prepare(delete_sql);
//        sql_query.addBindValue(0);
//        if(!sql_query.exec())
//        {
//            qDebug()<<sql_query.lastError();
//        }
//        else
//        {
//            qDebug()<<"deleted!";
//        }
//        //清空表格
//        QString clear_sql = "delete from student";
//        sql_query.prepare(clear_sql);
//        if(!sql_query.exec())
//        {
//            qDebug() << sql_query.lastError();
//        }
//        else
//        {
//            qDebug() << "table cleared";
//        }
//        database.close();
//    }


    this->connect(this->ui->refreshCbox,&QCheckBox::stateChanged,this->ui->waitPage,&waittable::UpdateTimerState);


    qApp->installEventFilter(this);

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()),this,SLOT(onTimeOut()));
    m_timer->setInterval(100000);
    m_timer->start();


}

basegrinder::~basegrinder()
{
    delete ui;
}

void basegrinder::GoLogin()
{
    this->ui->waitPage->StartCheck();
    this->show();
    this->m_login.hide();

    successLogin = true;
}

bool basegrinder::resetdatabase(QString passwd)
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("DataBase.db");
//    database.setUserName("User");
//    database.setPassword("7410");
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
        return false;
    }
    else
    {
        QDateTime current_date_time =QDateTime::currentDateTime();
        QString current_time =current_date_time.toString("yyyy-MM-dd hh:mm:ss");
        QSqlQuery sql_query(database);
        //更新数据（修改数据）
        QString update_sql = "update User set passwd = :passwd ,date = :date where seq = :seq";
        sql_query.prepare(update_sql);
        sql_query.bindValue(":passwd",passwd);
        sql_query.bindValue(":seq", TempUserId);
        sql_query.bindValue(":date", current_time);
        if(!sql_query.exec())
        {
            qDebug() << sql_query.lastError();
            database.close();
            return false;
        }
        else
        {
            database.close();
            qDebug() << "updated!";
            return true;
        }

    }
}

void basegrinder::on_pushButton_pressed()
{
    LogSql log;
    log.WriteLogToText();
}

int basegrinder::getdataCount(QString pwd)
{
    int count = -1;
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
            while(sql_query.next())
            {
                count++;
                QString PWD = sql_query.value(1).toString();
                if(PWD.compare(pwd) == 0)
                {
                    database.close();
                    return count;
                }
            }
        }
        database.close();
    }
    return count;
}

QString* basegrinder::getdatabase(int num)
{
    QSqlDatabase database;
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("DataBase.db");
    if (!database.open())
    {
        qDebug() << "Error: Failed to connect database." << database.lastError();
        return nullptr;
    }
    else
    {
        QSqlQuery sql_query(database);
        QString select_sql = "select * from User";
        if(!sql_query.exec(select_sql))
        {
            qDebug()<<sql_query.lastError();
            return nullptr;
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
            qDebug() << " settable    qs[0] = "<<qs[0]<<"qs[1] ="<<qs[1] ;
            database.close();
            return qs;
        }
        database.close();
        return qs;
    }
}

void basegrinder::getData()
{
    TempUserId = userlev->radioId;
    int flag = Login::PublicUserId;
    if((flag <2&&TempUserId!=flag)||(flag==2&&TempUserId==1))
    {
        QMessageBox::warning(this,"警告","没有修改的权限！");
        return;
    }
    QPixmap pixmapwordcon(":/back/release/wordconCh.png");
    this->ui->rewordBtn->setIcon(QIcon(pixmapwordcon));
    QPixmap pixmaplogcon(":/back/release/logcon.png");
    this->ui->loggerConBtn->setIcon(QIcon(pixmaplogcon));
    ui->setWidget->setCurrentIndex(0);
    this->ui->resetBtn->click();

}

bool basegrinder::eventFilter(QObject *obj, QEvent *event)
{
   if(successLogin)
   {
       if(event->type() == QEvent::MouseButtonPress){
           qDebug()<<"mouse pressed";
           //return true;
           m_timer->stop();
           m_timer->start();
       }
   //    else {
   //        if(!m_timer->isActive())
   //        {
   //            m_timer->start();
   //            qDebug()<<"start";
   //        }

   //    }

   }

    return QWidget::eventFilter(obj,event);
}


void basegrinder::on_LogSaveBtn_pressed()
{
    if(Login::PublicUserId!=1)
    {
        QMessageBox::warning(this,"提示","仅安全保密管理员员有权限使用此功能！");
        return;
    }
    ui->LogTimeBox->setDisabled(false);
    ui->LogOkBtn->setDisabled(false);
}

void basegrinder::on_LogOkBtn_pressed()
{
    int num = ui->LogTimeBox->currentIndex();

    //指定文件路径，然后打开文件。
    QString path = QDir::currentPath() + "/LogMonth";
    QFile *file = new QFile(path);//此路径下没有就会自己创建一个
    while(!file->open(QIODevice::ReadWrite));//以读写切追加写入的方式操作文本
    //需要写入的数据
    QTextStream txtOutput(file);
    txtOutput<<QString::number(num+1)<<endl;

//    LogSql *sql = new LogSql;
//    sql->CleanGetIndex(num+1);

    ui->LogTimeBox->setDisabled(true);
    ui->LogOkBtn->setDisabled(true);
}

void basegrinder::firstDeleteLog()
{
    QString num;
    QString path = QDir::currentPath() + "/LogMonth";
    QFile *file = new QFile(path);//此路径下没有就会自己创建一个
    while(!file->open(QIODevice::ReadOnly));//以读写切追加写入的方式操作文本

    QTextStream txtOutput(file);
    txtOutput>>num<<endl;

    LogSql *sql = new LogSql;
    sql->CleanGetIndex(num.toInt());
}

void basegrinder::on_trueBtn_3_pressed()
{

    if(Login::PublicUserId == 2)
    {
        QString num = ui->SecretEdit->text();
        QString path = QDir::currentPath() + "/LogInNum";
        QFile *file = new QFile(path);//此路径下没有就会自己创建一个
        while(!file->open(QIODevice::WriteOnly));//以读写切追加写入的方式操作文本

        QTextStream txtOutput(file);
        txtOutput<<"/"<<num<<endl;
        QMessageBox::warning(this,"提示","设置完成！");
    }
    else {
        QMessageBox::warning(this,"提示","仅管理员有权限使用此功能！");
    }
}

void basegrinder::onTimeOut()
{
    m_timer->stop();
    this->hide();
    successLogin = false;
    m_rouseWidget.initPwd();
    m_rouseWidget.setUserName(m_login.getUserName());
    m_rouseWidget.show();
    connect(&this->m_rouseWidget,&RouseWidget::GoLogin,this,&basegrinder::rouseShow);

}

void basegrinder::rouseShow()
{
    successLogin = true;
    this->show();
}

