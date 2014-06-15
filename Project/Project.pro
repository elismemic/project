#-------------------------------------------------
#
# Project created by QtCreator 2014-05-26T14:51:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Project
TEMPLATE = app


SOURCES += main.cpp\
        project.cpp \
    conductor.cpp \
    capacitor.cpp \
    capacitorbankplacement.cpp \
    mymodel.cpp \
    searchwindowcapacitor.cpp \
    searchwindowbankplacement.cpp \
    searchwindowconductor.cpp

HEADERS  += project.h \
    conductor.h \
    capacitor.h \
    capacitorbankplacement.h \
    mymodel.h \
    searchwindowcapacitor.h \
    searchwindowbankplacement.h \
    searchwindowconductor.h

FORMS    += project.ui \
    conductor.ui \
    capacitor.ui \
    capacitorbankplacement.ui \
    searchwindowcapacitor.ui \
    searchwindowbankplacement.ui \
    searchwindowconductor.ui


DEFINES += BOOST_ALL_DYN_LINK
DEFINES += _CRT_SECURE_NO_WARNINGS
DEFINES += _SCL_SECURE_NO_WARNINGS
DEFINES += TRACE_APP

#lib settings for debug
LIBS += -LC:\cpp\DB_Libs -lmyUtilsD
LIBS += -LC:\cpp\DB_Libs -lSQLDatabaseD

LIBS += -LC:\cpp\boost\bin

INCLUDEPATH += C:\cpp\DB_Includes
INCLUDEPATH += C:\cpp\boost\include
