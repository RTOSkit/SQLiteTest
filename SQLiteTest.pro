#-------------------------------------------------
#
# Project created by QtCreator 2012-11-10T13:28:35
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += webkit

TARGET = SQLiteTest
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sqlite.cpp \
    helpsetdialog.cpp \
    aboutdialog.cpp \
    resultdialog.cpp

HEADERS  += mainwindow.h \
    sqlite.h \
    helpsetdialog.h \
    aboutdialog.h \
    resultdialog.h

FORMS    += mainwindow.ui \
    helpsetdialog.ui \
    aboutdialog.ui \
    resultdialog.ui

OTHER_FILES +=


RESOURCES += \
    app.qrc
