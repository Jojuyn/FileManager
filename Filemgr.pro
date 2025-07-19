QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17


SOURCES += \
    FileOperation/FileOperation.cpp \
    main.cpp \
    cell_main.cpp

HEADERS += \
    ../include.h \
    FileOperation/FileOperation.h \
    cell_main.h

FORMS += \
    cell_main.ui

DESTDIR = $$PWD/bin

RESOURCES += \
    res.qrc

RC_FILE = \
    filemgr.rc

