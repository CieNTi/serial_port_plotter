QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

greaterThan(QT_MAJOR_VERSION, 4): CONFIG += c++11
lessThan(QT_MAJOR_VERSION, 5): QMAKE_CXXFLAGS += -std=c++11

TARGET = axis-tags-example
TEMPLATE = app

INCLUDEPATH += ../../
SOURCES += \
        main.cpp \
        mainwindow.cpp \
    ../../qcustomplot.cpp \
    axistag.cpp

HEADERS += \
        mainwindow.h \
    ../../qcustomplot.h \
    axistag.h

FORMS += \
        mainwindow.ui
