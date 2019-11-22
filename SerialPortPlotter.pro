#-------------------------------------------------
#
# Project created by QtCreator 2014-12-22T14:53:33
#
#-------------------------------------------------

QT       += core gui
QT       += serialport
CONFIG += c++11

#greaterThan(QT_MAJOR_VERSION, 5): QT += widgets printsupport

QT += widgets printsupport

TARGET = serialportplotter
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
    #res/qdark_stylesheet/qdarkstyle/style.qrc      # don't exist

# The following line compiles on Release but not on Debug, so this workaroung is used:
RC_FILE = res/serial_port_plotter.rc
# Call the resource compiler
#win32:mkver_rc.target = serial_port_plotter_res.o
#win32:mkver_rc.commands = windres --use-temp-file -i serial_port_plotter.rc -o serial_port_plotter_res.o --include-dir=../res -DVERSION_H_INTERN $(DEFINES)
#win32:QMAKE_EXTRA_TARGETS += mkver_rc
#win32:PRE_TARGETDEPS += serial_port_plotter_res.o
#win32:LIBS += serial_port_plotter_res.o

unix:configfiles.extra = chmod +x scripts/*; make clean;
binfile.files += serial_port_plotter
binfile.path = /usr/bin/
#configfiles.files += data/config/*
configfiles.path = /usr/share/
docfiles.files += data/doc/*
docfiles.path = /usr/share/doc/
manfiles.files += data/man/*
manfiles.path = /usr/share/man/man1/
shortcutfiles.files += data/serialportplotter.desktop
shortcutfiles.path = /usr/share/applications/
INSTALLS += configfiles
INSTALLS += docfiles
INSTALLS += manfiles
INSTALLS += shortcutfiles
INSTALLS += binfile






