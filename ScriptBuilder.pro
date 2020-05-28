#-------------------------------------------------
#
# Project created by QtCreator 2020-05-28T08:45:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ScriptBuilder
TEMPLATE = app


SOURCES += main.cpp\
        ScriptBuilderMainWindow.cpp \
    Test1Properties_UI.cpp \
    Test2Properties_UI.cpp \
    Test3Properties_UI.cpp \
    Test1.cpp

HEADERS  += ScriptBuilderMainWindow.h \
    Theme.h \
    Test1Properties_UI.h \
    Test2Properties_UI.h \
    Test3Properties_UI.h \
    Test1.h

FORMS    += ScriptBuilderMainWindow.ui \
    Test1Properties_UI.ui \
    Test2Properties_UI.ui \
    Test3Properties_UI.ui

RESOURCES += \
    Resources.qrc
