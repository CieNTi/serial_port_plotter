#-------------------------------------------------
#
# Project created by QtCreator 2014-12-22T14:53:33
#
#-------------------------------------------------

QT       += core gui
QT       += serialport
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = SerialPortPlotter
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
        qcustomplot/qcustomplot.cpp \
    helpwindow.cpp

HEADERS  += mainwindow.hpp \
                qcustomplot/qcustomplot.h \
    helpwindow.hpp


FORMS    += mainwindow.ui \
    helpwindow.ui

RC_FILE = res/serial_port_plotter.rc

RESOURCES += \
    res/serial_port_plotter.qrc \
    res/qdark_stylesheet/qdarkstyle/style.qrc
