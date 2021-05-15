#include "basegrinder.h"
#include <QApplication>
#include <QLibrary>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    basegrinder w;
//    w.show();
    QApplication::addLibraryPath("./plugins");
    return a.exec();
}
