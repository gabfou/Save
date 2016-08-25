#include "sqltableitem.h"

sqltableitem::sqltableitem(QString parparam, QString tablename, QString colname, int id)
    : QTableWidgetItem(parparam), tablename(tablename), colname(colname), id(QString::number(id))
{

}

sqltableitem::sqltableitem(int parparam, QString tablename, QString colname, int id)
    : QTableWidgetItem(QString::number(parparam)), tablename(tablename), colname(colname), id(QString::number(id))
{

}

QString sqltableitem::getTablename() const{return tablename;}

QString sqltableitem::getColname() const{return colname;}

QString sqltableitem::getId() const{return id;}
