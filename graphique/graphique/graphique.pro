#-------------------------------------------------
#
# Project created by QtCreator 2016-06-21T14:25:18
#
#-------------------------------------------------

greaterThan(QT_MAJOR_VERSION, 4):QT       += core gui sql widgets

greaterThan(QT_MAJOR_VERSION, 4)

#QTPLUGIN += qsqlmysql

TARGET = graphique
CONFIG += c++11
#QMAKE_CXXFLAGS += -std=c++0x
QT += network
#LIBS+= -L. libmysql.lib #mysqlclient.lib
#include(./libmysql.dll)

include(QtXlsx/src/xlsx/qtxlsx.pri)

SOURCES += main.cpp\
        mainwindow.cpp \
    smtp.cpp \
    xlsx_common_operation.cpp \
    table_common_operation.cpp \
    menuconfigproject.cpp \
    grouptree.cpp \
    grouptreeitem.cpp \
    tableclass/headertableitem.cpp \
    tableclass/tableshow.cpp \
    tableclass/itemtable.cpp \
    tableclass/argtableitem.tpp \
    tableclass/headeredit.cpp \
    dockgroup.cpp \
    graph/bargraph.cpp \
    overview.cpp \
    menuconfigquestion.cpp \
    questiontreeitem.cpp \
    infoquestion.cpp \
    sql/sqldatatable.cpp \
    sql/sqloperation.cpp \
    sql/sqltableitem.cpp \
    data/fact.cpp \
    data/group.cpp \
    data/person.cpp \
    data/project.cpp \
    data/question.cpp \
    misc.cpp

HEADERS  += mainwindow.h \
    define.h \
    smtp.h \
    le.h \
    ../../server/server/group.h \
    menuconfigproject.h \
    grouptree.h \
    grouptreeitem.h \
    tableclass/headertableitem.h \
    tableclass/tableshow.h \
    tableclass/itemtable.h \
    tableclass/headeredit.h \
    dockgroup.h \
    graph/bargraph.h \
    overview.h \
    menuconfigquestion.h \
    questiontreeitem.h \
    infoquestion.h \
    sql/sqldatatable.h \
    sql/sqltableitem.h \
    data/fact.h \
    data/group.h \
    data/person.h \
    data/project.h \
    data/question.h
   
FORMS    += mainwindow.ui 
QT		+= network
#QT       += webkit webkitwidgets

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../server/server/ #-llibcurl
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../server/server/ #-llibcurl
else:unix: LIBS += -L$$PWD/../../server/server/ #-llibcurl

INCLUDEPATH += $$PWD/../../server/server
DEPENDPATH += $$PWD/../../server/server


