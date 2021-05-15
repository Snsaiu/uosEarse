#ifndef ROUSEWIDGET_H
#define ROUSEWIDGET_H

#include <QWidget>

namespace Ui {
class RouseWidget;
}

class RouseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RouseWidget(QWidget *parent = nullptr);
    ~RouseWidget();

    void initPwd();
    void setUserName(QString userName);

private slots:
    void on_loginBtn_clicked();

signals:
    void GoLogin();

private:
    Ui::RouseWidget *ui;
};

#endif // ROUSEWIDGET_H
