QT       += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Dialogs/earsecountdialog.cpp \
    EarseModuls/earseabstraction.cpp \
    EarseModuls/earseone.cpp \
    EarseModuls/earserandom.cpp \
    EarseModuls/earsestrategy.cpp \
    EarseModuls/earsezero.cpp \
    MessageMediator/messagemediator.cpp \
    MessageMediator/messagemodel.cpp \
    MessageMediator/messagesubject.cpp \
    basegrinder.cpp \
    login.cpp \
    main.cpp \
    waittable.cpp \
    earsetable.cpp \
    successtable.cpp \
    logtable.cpp \
    losetable.cpp \
    choose.cpp \
    stop.cpp \
    LogSql.cpp \
    settable.cpp \
    diskinfo.cpp \
    checkerModule/checkerdiskabstraction.cpp \
    checkerModule/harddiskmodel.cpp \
    checkerModule/harddiskchecker.cpp \
    checkerModule/usbchecker.cpp \
    checkerModule/checkerfactory.cpp \
    checkerModule/checkerstrategy.cpp \
    checkerModule/checkerfacade.cpp \
    checkerModule/filterharddiskproxy.cpp

HEADERS += \
    Dialogs/earsecountdialog.h \
    EarseModuls/earseabstraction.h \
    EarseModuls/earseone.h \
    EarseModuls/earserandom.h \
    EarseModuls/earsestrategy.h \
    EarseModuls/earsezero.h \
    MessageMediator/messagemediator.h \
    MessageMediator/messagemodel.h \
    MessageMediator/messagesubject.h \
    basegrinder.h \
    login.h \
    waittable.h \
    earsetable.h \
    successtable.h \
    logtable.h \
    losetable.h \
    choose.h \
    settable.h \
    stop.h \
    LogSql.h \
    diskinfo.h \
    publicuse.h \
    checkerModule/checkerdiskabstraction.h \
    checkerModule/harddiskmodel.h \
    checkerModule/harddiskchecker.h \
    checkerModule/usbchecker.h \
    checkerModule/checkerfactory.h \
    checkerModule/checkerstrategy.h \
    checkerModule/checkerfacade.h \
    checkerModule/filterharddiskproxy.h

FORMS += \
    Dialogs/earsecountdialog.ui \
    basegrinder.ui \
    login.ui \
    waittable.ui \
    earsetable.ui \
    successtable.ui \
    logtable.ui \
    losetable.ui \
    choose.ui \
    settable.ui \
    stop.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc

DISTFILES +=

