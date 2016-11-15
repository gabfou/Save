#-------------------------------------------------
#
# Project created by QtCreator 2016-08-12T14:54:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets sql network
QMAKE_MAC_SDK = macosx10.12
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
    misc/listeditwval.cpp \
    config/menuconfigsondage.cpp \
    sql/sqloperation.cpp \
    tableclass/tableau_brut.cpp \
    template/template.cpp \
    misc/uploader.cpp \
    graph/comparrefdo.cpp \
    misc/menusondage.cpp \
    misc/emailvalidator.cpp

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
    misc/listeditwval.h \
    config/menuconfigsondage.h \
    tableclass/tableau_brut.h \
    misc/uploader.h \
    graph/comparrefdo.h \
    misc/menusondage.h \
    misc/emailvalidator.h

FORMS    += mainwindow.ui

DISTFILES += \
    libmysql.lib \
    mysqlclient.lib \
    plugins/sqldrivers/qsqlmysql.dll \
    plugins/sqldrivers/qsqlmysqld.dll \
    plugins/qsqlmysql.dll \
    plugins/qsqlmysqld.dll \
    sqldrivers/qsqlmysql.dll \
    sqldrivers/qsqlmysqld.dll \
    libmysql.dll \
    qsqlmysql.dll \
    qsqlmysqld.dll \
    template/test \
    misc/ssh.py
