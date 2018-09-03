#-------------------------------------------------
#
# Project created by QtCreator 2014-12-22T14:53:33
#
#-------------------------------------------------

QT       += core gui
QT       += serialport
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = serial_port_plotter
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

RESOURCES += \
    res/serial_port_plotter.qrc \
    res/qdark_stylesheet/qdarkstyle/style.qrc

# The following line compiles on Release but not on Debug, so this workaroung is used:
RC_FILE = res/serial_port_plotter.rc
# Call the resource compiler
#win32:mkver_rc.target = serial_port_plotter_res.o
#win32:mkver_rc.commands = windres --use-temp-file -i serial_port_plotter.rc -o serial_port_plotter_res.o --include-dir=../res -DVERSION_H_INTERN $(DEFINES)
#win32:QMAKE_EXTRA_TARGETS += mkver_rc
#win32:PRE_TARGETDEPS += serial_port_plotter_res.o
#win32:LIBS += serial_port_plotter_res.o
