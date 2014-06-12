#-------------------------------------------------
#
# Project created by QtCreator 2014-05-22T18:55:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Capacitor
TEMPLATE = app


SOURCES += main.cpp\
        capacitor.cpp

HEADERS  += capacitor.h

FORMS    += capacitor.ui


DEFINES += BOOST_ALL_DYN_LINK
DEFINES += _CRT_SECURE_NO_WARNINGS
DEFINES += _SCL_SECURE_NO_WARNINGS
DEFINES += TRACE_APP

#lib settings for debug
LIBS += -LC:/Users/User/Documents/PROJECT/cpp/DB_Libs -lmyUtilsD
LIBS += -LC:/Users/User/Documents/PROJECT/cpp/DB_Libs -lSQLDatabaseD

LIBS += -LC:/Users/User/Documents/PROJECT/cpp/boost/bin

INCLUDEPATH += C:/Users/User/Documents/PROJECT/cpp/DB_Includes
INCLUDEPATH += C:/Users/User/Documents/PROJECT/cpp/boost/include
