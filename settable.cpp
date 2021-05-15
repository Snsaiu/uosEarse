#include "settable.h"
#include "ui_settable.h"
#include <QMessageBox>
#include "LogSql.h"
#include "login.h"
#include "userlevel.h"

settable::settable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::settable)
{
    ui->setupUi(this);
    /*修改密码*/
    connect(ui->rewordBtn,&QPushButton::pressed,[=]{
        {
            QPixmap pixmapwordcon(":/back/release/wordconCh.png");
            this->ui->rewordBtn->setIcon(QIcon(pixmapwordcon));
            QPixmap pixmaplogcon(":/back/release/logcon.png");
            this->ui->loggerConBtn->setIcon(QIcon(pixmaplogcon));
            ui->setWidget->setCurrentIndex(0);
            this->ui->resetBtn->click();
        }
    });
    /*日志管理*/
    connect(this->ui->loggerConBtn,&QPushButton::pressed,[=]{
        {
            QPixmap pixmapwordcon(":/back/release/wordcon.png");
            this->ui->rewordBtn->setIcon(QIcon(pixmapwordcon));
            QPixmap pixmaplogcon(":/back/release/logconCh.png");
            this->ui->loggerConBtn->setIcon(QIcon(pixmaplogcon));
            QPixmap pixmapdetelog(":/back/release/detelog.png");
            ui->detelogBtn->setIcon(QIcon(pixmapdetelog));
            ui->setWidget->setCurrentIndex(1);
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
    /*清空日志*/
    connect(this->ui->detelogBtn,&QPushButton::pressed,[=]{
        {
            LogSql logClean;
            logClean.CleanLog();
        }
    });
    /*确认修改密码*/
    connect(this->ui->trueBtn,&QPushButton::pressed,[=]{
        {
            UserLevel userlev;
            userlev.show();
            int id = userlev.radioId;
            if(this->ui->newpassword->text()!=this->ui->newpassword_2->text())
            {
                 QMessageBox::warning(this,"提示","两次新密码输入不一致！");
            }else if(this->ui->oldpassword->text()!="")
            {
                int flag = Login::PublicUserId;
                int count = getdataCount(this->ui->oldpassword->text());

                QString *qsTemp;
                qsTemp = getdatabase(0);
                if(qsTemp[1] != this->ui->oldpassword->text())
                {
                    QMessageBox::warning(this,"警告","旧密码输入错误！");
                }
                else {
                    if(resetdatabase(this->ui->newpassword->text()))
                    {

                        QMessageBox::warning(this,"提示","密码修改成功！");
                    }
                    else {
                        QMessageBox::warning(this,"提示","密码修改失败！");
                    }
                }
            }else if(this->ui->oldpassword->text()=="")
            {
                QMessageBox::warning(this,"警告","旧密码不能为空！");
            }
        }
    });

}

settable::~settable()
{
    delete ui;
}

int settable::getdataCount(QString pwd)
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

QString* settable::getdatabase(int num)
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

bool settable::resetdatabase(QString passwd)
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
        QSqlQuery sql_query(database);
        //更新数据（修改数据）
        QString update_sql = "update User set passwd = :passwd where id = :id";
        sql_query.prepare(update_sql);
        sql_query.bindValue(":passwd",passwd);
        sql_query.bindValue(":id", 1);
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


