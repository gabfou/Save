#-------------------------------------------------
#
# Project created by QtCreator 2016-06-21T14:25:18
#
#-------------------------------------------------

greaterThan(QT_MAJOR_VERSION, 4):QT       += core gui sql widgets

greaterThan(QT_MAJOR_VERSION, 4)

QTPLUGIN += qsqlmysql

TARGET = graphique
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++0x
QT += network
CONFIG += qwt

include(QtXlsx/src/xlsx/qtxlsx.pri)

SOURCES += main.cpp\
        mainwindow.cpp \
    ../../server/server/fact.cpp \
    ../../server/server/misc.cpp \
    ../../server/server/person.cpp \
    ../../server/server/project.cpp \
    ../../server/server/question.cpp \
    smtp.cpp \
    xlsx_common_operation.cpp \
    ../../server/server/group.cpp \
    table_common_operation.cpp \
    barref.cpp \
    menuconfigproject.cpp \
    sqldatatable.cpp \
    sqltableitem.cpp \
    grouptree.cpp \
    grouptreeitem.cpp \
    tableclass/headertableitem.cpp \
    tableclass/tableshow.cpp \
    tableclass/itemtable.cpp \
    tableclass/argtableitem.tpp \
    tableclass/headeredit.cpp \
    sqloperation.cpp \
    dockgroup.cpp

HEADERS  += mainwindow.h \
    ../../server/server/fact.h \
    ../../server/server/person.h \
    ../../server/server/project.h \
    ../../server/server/question.h \
    ../../server/server/server.h \
    define.h \
    smtp.h \
    le.h \
    ../../server/server/group.h \
    barref.h \
    menuconfigproject.h \
    sqldatatable.h \
    sqltableitem.h \
    grouptree.h \
    grouptreeitem.h \
    tableclass/headertableitem.h \
    tableclass/tableshow.h \
    tableclass/itemtable.h \
    tableclass/headeredit.h \
    dockgroup.h
   
FORMS    += mainwindow.ui 
QT		+= network
QT       += webkit webkitwidgets

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../server/server/ -llibcurl
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../server/server/ -llibcurl
else:unix: LIBS += -L$$PWD/../../server/server/ -llibcurl

INCLUDEPATH += $$PWD/../../server/server
DEPENDPATH += $$PWD/../../server/server


