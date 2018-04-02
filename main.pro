#-------------------------------------------------
#
# Project created by QtCreator 2017-07-28T20:58:13
#
#-------------------------------------------------

QT       += core gui
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = main
TEMPLATE = app


SOURCES += main.cpp\
        Dialog.cpp \
    data.cpp \
    taskthread.cpp \
    dateutilsutils.cpp \
    readcvsutils.cpp \
    MainWindow.cpp \
    qcustomplot.cpp \
    MainWindow2.cpp \
    MainWindow3.cpp \
    MainWindow4.cpp \
    MainWindow5.cpp \
    Point.cpp

HEADERS  += Dialog.h \
    dateutils.h \
    data.h \
    taskthread.h \
    readcvsutils.h \
    MainWindow.h \
    qcustomplot.h \
    MainWindow2.h \
    MainWindow3.h \
    MainWindow4.h \
    MainWindow5.h \
    Point.h

FORMS    += Dialog.ui \
    MainWindow.ui \
    MainWindow2.ui \
    MainWindow3.ui \
    MainWindow4.ui \
    MainWindow5.ui
