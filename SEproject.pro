#-------------------------------------------------
#
# Project created by QtCreator 2014-05-26T23:01:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SEproject
TEMPLATE = app


SOURCES += main.cpp\
        job.cpp \
    newjob.cpp \
    mymodel.cpp \
    mainwindow.cpp \
    user.cpp

HEADERS  += job.h \
    newjob.h \
    mymodel.h \
    mainwindow.h \
    user.h

FORMS    += job.ui \
    newjob.ui \
    mainwindow.ui \
    user.ui


DEFINES += BOOST_ALL_DYN_LINK
DEFINES += _CRT_SECURE_NO_WARNINGS
DEFINES += _SCL_SECURE_NO_WARNINGS
DEFINES += TRACE_APP
DEFINES += NOMINMAX

#lib settings for debug
LIBS += -LC:\cpp\DB_Libs -lmyUtilsD
LIBS += -LC:\cpp\DB_Libs -lSQLDatabaseD

LIBS += -LC:\cpp\boost\bin

INCLUDEPATH += C:\cpp\DB_Includes
INCLUDEPATH += C:\cpp\boost\include
