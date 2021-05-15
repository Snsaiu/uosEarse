#ifndef CHOOSE_H
#define CHOOSE_H
#include <QWidget>

namespace Ui {
class choose;
}

class choose : public QWidget
{
    Q_OBJECT



public:
    explicit choose(QWidget *parent = nullptr);
    ~choose();

private:
    Ui::choose *ui;
    void GoChoose();
};

#endif // CHOOSE_H
