#ifndef STOP_H
#define STOP_H

#include <QDialog>
#include <QWidget>

namespace Ui {
class stop;
}

class stop : public QDialog
{
    Q_OBJECT

public:
    explicit stop(QWidget *parent = 0);
    ~stop();
    QString Index;
    QString getIndex() const;
    void setIndex(QString value);

private:
    Ui::stop *ui;

signals:
    void CancelEarseSignal(QString index);
};

#endif // STOP_H
