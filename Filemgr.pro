QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17


SOURCES += \
    main.cpp \
    cell_main.cpp \
    settingdialog.cpp \
    recyclebinwindow.cpp \
    configmanager.cpp

HEADERS += \
    cell_main.h \
    configmanager.h \
    recyclebinwindow.h \
    settingdialog.h

FORMS += \
    cell_main.ui \
    settingdialog.ui
    recyclebinwindow.ui \

DESTDIR = $$PWD/bin

RESOURCES += \
    res.qrc \
    resources.qrc

RC_FILE = \
    filemgr.rc
INCLUDEPATH += $$PWD/thirdparty/json/include/
