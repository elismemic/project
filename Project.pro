#-------------------------------------------------
#
# Project created by QtCreator 2014-06-08T16:33:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Project
TEMPLATE = app


SOURCES += main.cpp\
        project.cpp \
    resistorcatalog.cpp \
    reactorcatalog.cpp \
    reactorbankplacement.cpp \
    resistorplacement.cpp \
    mymodel.cpp \
    searchwindowresistorcatalog.cpp \
    searchwindowreactorcatalog.cpp \
    searchwindowreactorbankplacement.cpp \
    searchwindowresistorplacement.cpp

HEADERS  += project.h \
    resistorcatalog.h \
    reactorcatalog.h \
    reactorbankplacement.h \
    resistorplacement.h \
    mymodel.h \
    searchwindowresistorcatalog.h \
    searchwindowreactorcatalog.h \
    searchwindowreactorbankplacement.h \
    searchwindowresistorplacement.h

FORMS    += project.ui \
    resistorcatalog.ui \
    reactorcatalog.ui \
    reactorbankplacement.ui \
    resistorplacement.ui \
    searchwindowresistorcatalog.ui \
    searchwindowreactorcatalog.ui \
    searchwindowreactorbankplacement.ui \
    searchwindowresistorplacement.ui


DEFINES += BOOST_ALL_DYN_LINK
DEFINES += _CRT_SECURE_NO_WARNINGS
DEFINES += _SCL_SECURE_NO_WARNINGS
DEFINES += TRACE_APP
DEFINES += NOMINMAX

#lib settings for debug
LIBS += -LC:\Users\Lady\Desktop\cpp\DB_Libs -lmyUtilsD
LIBS += -LC:\Users\Lady\Desktop\cpp\DB_Libs -lSQLDatabaseD

LIBS += -LC:\Users\Lady\Desktop\cpp\boost\bin

INCLUDEPATH += C:\Users\Lady\Desktop\cpp\DB_Includes
INCLUDEPATH += C:\Users\Lady\Desktop\cpp\boost\include
