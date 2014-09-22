#-------------------------------------------------
#
# Project created by QtCreator 2014-06-06T20:46:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PowerSS
TEMPLATE = app


SOURCES += main.cpp\
           powerss.cpp \
           catconsumer.cpp \
           catunit.cpp \
           catmotor.cpp \
           plamotor.cpp \
           plaunit.cpp \
           plaresistor.cpp \
           searchdialog.cpp \
           searchjobs.cpp \
           mymodel.cpp \
           newjob.cpp \
           selectjob.cpp \
           browse.cpp \
           messagebox.cpp \
           addcatpla.cpp \
    login.cpp

HEADERS  += powerss.h \
            catconsumer.h \
            catunit.h \
            catmotor.h \
            plamotor.h \
            plaunit.h \
            plaresistor.h \
            searchdialog.h \
            searchjobs.h \
            mymodel.h \
            newjob.h \
            selectjob.h \
            browse.h \
            messagebox.h \
            addcatpla.h \
    login.h

FORMS    += powerss.ui \
            catconsumer.ui \
            catunit.ui \
            catmotor.ui \
            plamotor.ui \
            plaunit.ui \
            plaresistor.ui \
            searchdialog.ui \
            searchjobs.ui \
            newjob.ui \
            selectjob.ui \
            browse.ui \
            messagebox.ui \
            addcatpla.ui \
    login.ui


DEFINES += BOOST_ALL_DYN_LINK
DEFINES += _CRT_SECURE_NO_WARNINGS
DEFINES += _SCL_SECURE_NO_WARNINGS
DEFINES += TRACE_APP
DEFINES += NOMINMAX

#lib settings for debug
LIBS += -LD:/cpp/DB_Libs -lmyUtilsD
LIBS += -LD:/cpp/DB_Libs -lSQLDatabaseD

LIBS += -LD:/cpp/boost/bin

INCLUDEPATH += D:/cpp/DB_Includes
INCLUDEPATH += D:/cpp/boost/include
