#-------------------------------------------------
#
# Project created by QtCreator 2014-05-28T19:58:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Cat_and_Place
TEMPLATE = app

DEFINES += BOOST_ALL_DYN_LINK
DEFINES += _CRT_SECURE_NO_WARNINGS
DEFINES += _SCL_SECURE_NO_WARNINGS
DEFINES += TRACE_APP

TRANSLATIONS += translation.ts
TRANSLATIONS += translationEn.ts

CODECFORTR = UTF-8

LIBS += -LC:/Users/darko/Desktop/SEPRO/cpp/DB_Libs -lmyUtilsD
LIBS += -LC:/Users/darko/Desktop/SEPRO/cpp/DB_Libs -lSQLDatabaseD
LIBS += -LC:/Users/darko/Desktop/SEPRO/cpp/boost/bin


INCLUDEPATH += C:/Users/darko/Desktop/SEPRO/cpp/DB_Includes
INCLUDEPATH += C:/Users/darko/Desktop/SEPRO/cpp/boost/include



SOURCES += main.cpp\
        mainwindow.cpp \
    busbar.cpp \
    mymodel.cpp \
    busbarsearch.cpp \
    cablehead.cpp \
    busbarplacement.cpp \
    searchplacements.cpp \
    cableheadplacement.cpp \
    junction.cpp \
    junctionplacement.cpp

HEADERS  += mainwindow.h \
    busbar.h \
    mymodel.h \
    busbarsearch.h \
    cablehead.h \
    junction.h \
    busbarplacement.h \
    searchplacements.h \
    cableheadplacement.h \
    junctionplacement.h

FORMS    += mainwindow.ui \
    busbar.ui \
    busbarsearch.ui \
    cablehead.ui \
    junction.ui \
    busbarplacement.ui \
    searchplacements.ui \
    cableheadplacement.ui \
    junctionplacement.ui
