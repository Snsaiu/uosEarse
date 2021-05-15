QT       += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11


QMAKE_CXXFLAGS += -std=c++0x

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
    checkerModule/filterharddiskproxy.cpp \
    userlevel.cpp \
    ForLogThread/logthread.cpp \
    Dialogs/disktypedialog.cpp \
    Services/pwdcomplexbase.cpp \
    Services/Impls/eightpwdcomplex.cpp \
    Models/usermodel.cpp \
    Services/userservicebase.cpp \
    Services/Impls/userservice.cpp \
    Services/commandservicebase.cpp \
    Services/exportlogservicebase.cpp \
    Services/Impls/pwdlogexportservice.cpp \
    Services/Impls/showwaittablecommand.cpp \
    Services/Impls/showearsingtablecommand.cpp \
    Services/Impls/showearsedsuccesstablecommand.cpp \
    Services/Impls/showearsederrortablecommand.cpp \
    DB/dbbase.cpp \
    DB/userdb.cpp \
    Services/Impls/showlogsettingcommand.cpp \
    Services/Impls/showpwdmodifycommand.cpp \
    Services/Impls/showusermanagercommand.cpp \
    Services/Impls/showlogsavecyclecommand.cpp \
    Services/Impls/setlogcyclecommand.cpp \
    Services/Impls/showlogspacecommand.cpp \
    Models/logspacemodel.cpp \
    Services/Impls/setlogspacecommand.cpp \
    Services/Impls/setlogsaveascommand.cpp \
    Services/Impls/logexportcommand.cpp \
    Models/logmodel.cpp \
    Enums/levelconst.cpp \
    DB/logdb.cpp \
    Services/logservicebase.cpp \
    Enums/opttypeconst.cpp \
    Models/settingmodel.cpp \
    DB/settingdb.cpp

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
    checkerModule/filterharddiskproxy.h \
    userlevel.h \
    ForLogThread/logthread.h \
    Dialogs/disktypedialog.h \
    Services/pwdcomplexbase.h \
    Services/Impls/eightpwdcomplex.h \
    Enums/permissiontype.h \
    Models/usermodel.h \
    Services/userservicebase.h \
    Services/Impls/userservice.h \
    Services/commandservicebase.h \
    Services/exportlogservicebase.h \
    Services/Impls/pwdlogexportservice.h \
    Services/Impls/showwaittablecommand.h \
    Services/Impls/showearsingtablecommand.h \
    Services/Impls/showearsedsuccesstablecommand.h \
    Services/Impls/showearsederrortablecommand.h \
    DB/dbbase.h \
    DB/userdb.h \
    Services/Impls/showlogsettingcommand.h \
    Services/Impls/showpwdmodifycommand.h \
    Services/Impls/showusermanagercommand.h \
    Services/Impls/showlogsavecyclecommand.h \
    Services/Impls/setlogcyclecommand.h \
    Services/Impls/showlogspacecommand.h \
    Models/logspacemodel.h \
    Services/Impls/setlogspacecommand.h \
    Services/Impls/setlogsaveascommand.h \
    Services/Impls/logexportcommand.h \
    Models/logmodel.h \
    Enums/levelconst.h \
    DB/logdb.h \
    Services/logservicebase.h \
    Enums/opttypeconst.h \
    Models/settingmodel.h \
    DB/settingdb.h

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
    stop.ui \
    userlevel.ui \
    Dialogs/disktypedialog.ui

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc

DISTFILES += \
    release/loginSetFalse.png \
    release/loginSetTrue.png

