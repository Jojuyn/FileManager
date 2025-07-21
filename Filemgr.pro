QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17


SOURCES += \
    main.cpp \
    cell_main.cpp

HEADERS += \
    cell_main.h \
    include.h

FORMS += \
    cell_main.ui


DESTDIR = $$PWD/bin

RESOURCES += \
    res.qrc

RC_FILE = \
    filemgr.rc

