#-------------------------------------------------
#
# Project created by QtCreator 2016-08-12T14:54:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets sql network

CONFIG += c++11

include(QtXlsx/qtxlsx.pri)

TARGET = muranoproject
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    data/fact.cpp \
    data/group.cpp \
    data/person.cpp \
    data/project.cpp \
    data/question.cpp \
    graph/bargraph.cpp \
    sql/sqldatatable.cpp \
    sql/sqloperation.cpp \
    sql/sqltableitem.cpp \
    tableclass/headertableitem.cpp \
    tableclass/itemtable.cpp \
    tableclass/tableshow.cpp \
    grouptree.cpp \
    grouptreeitem.cpp \
    misc.cpp \
    overview.cpp \
    questiontreeitem.cpp \
    smtp.cpp \
    table_common_operation.cpp \
    xlsx_common_operation.cpp \
    misc/listedit.cpp \
    config/infoquestion.cpp \
    config/menuconfigproject.cpp \
    config/menuconfigquestion.cpp \
    alltree.cpp \
    persontreeitem.cpp \
    config/menuconfigperson.cpp \
    config/infoperson.cpp \
    config/info.cpp \
    misc/tablistedit.cpp \
    misc/listeditwval.cpp

HEADERS  += mainwindow.h \
    data/fact.h \
    data/group.h \
    data/person.h \
    data/project.h \
    data/question.h \
    graph/bargraph.h \
    sql/sqldatatable.h \
    sql/sqltableitem.h \
    tableclass/headertableitem.h \
    tableclass/itemtable.h \
    tableclass/tableshow.h \
    define.h \
    grouptree.h \
    grouptreeitem.h \
    le.h \
    overview.h \
    questiontreeitem.h \
    smtp.h \
    misc/listedit.h \
    config/infoquestion.h \
    config/menuconfigproject.h \
    config/menuconfigquestion.h \
    alltree.h \
    persontreeitem.h \
    config/menuconfigperson.h \
    config/infoperson.h \
    config/info.h \
    misc/tablistedit.h \
    misc/listeditwval.h

FORMS    += mainwindow.ui

DISTFILES += \
    libmysql.lib \
    mysqlclient.lib \
    plugins/sqldrivers/qsqlite.dll \
    plugins/sqldrivers/qsqlited.dll \
    plugins/sqldrivers/qsqlmysql.dll \
    plugins/sqldrivers/qsqlmysqld.dll \
    plugins/sqldrivers/qsqlodbc.dll \
    plugins/sqldrivers/qsqlodbcd.dll \
    plugins/sqldrivers/qsqlpsql.dll \
    plugins/sqldrivers/qsqlpsqld.dll \
    plugins/qsqlite.dll \
    plugins/qsqlited.dll \
    plugins/qsqlmysql.dll \
    plugins/qsqlmysqld.dll \
    plugins/qsqlodbc.dll \
    plugins/qsqlodbcd.dll \
    plugins/qsqlpsql.dll \
    plugins/qsqlpsqld.dll \
    sqldrivers/qsqlite.dll \
    sqldrivers/qsqlited.dll \
    sqldrivers/qsqlmysql.dll \
    sqldrivers/qsqlmysqld.dll \
    sqldrivers/qsqlodbc.dll \
    sqldrivers/qsqlodbcd.dll \
    sqldrivers/qsqlpsql.dll \
    sqldrivers/qsqlpsqld.dll \
    libmysql.dll \
    qsqlite.dll \
    qsqlited.dll \
    qsqlmysql.dll \
    qsqlmysqld.dll \
    qsqlodbc.dll \
    qsqlodbcd.dll \
    qsqlpsql.dll \
    qsqlpsqld.dll
