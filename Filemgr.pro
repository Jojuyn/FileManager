QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17


SOURCES += \
    FileOperation/FileOperation.cpp \
    main.cpp \
    cell_main.cpp \
    themechoose.cpp \
    settingdialog.cpp \
    configmanager.cpp

HEADERS += \
    FileOperation/FileOperation.h \
    cell_main.h \
    configmanager.h \
    themechoose.h \
    settingdialog.h

FORMS += \
    cell_main.ui \
    themechoose.ui \
    settingdialog.ui

DESTDIR = $$PWD/bin

RESOURCES += \
    res.qrc \
    resources.qrc

RC_FILE = \
    #filemgr.rc
INCLUDEPATH += $$PWD/thirdparty/json/include/
