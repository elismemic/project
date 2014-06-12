#-------------------------------------------------
#
# Project created by QtCreator 2014-05-30T13:50:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EdiniPRO
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    capacitor.cpp

HEADERS  += mainwindow.h \
    capacitor.h

FORMS    += mainwindow.ui \
    capacitor.ui
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
