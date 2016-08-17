#include "sqltableitem.h"

sqltableitem::sqltableitem(QString parparam, QString tablename, QString colname, int id)
	: tablename(tablename), colname(colname), id(QString::number(id)), QTableWidgetItem(parparam)
{

}

sqltableitem::sqltableitem(int parparam, QString tablename, QString colname, int id)
	: tablename(tablename), colname(colname), id(QString::number(id)), QTableWidgetItem(QString::number(parparam))
{

}

QString sqltableitem::getTablename() const{return tablename;}

QString sqltableitem::getColname() const{return colname;}

QString sqltableitem::getId() const{return id;}
