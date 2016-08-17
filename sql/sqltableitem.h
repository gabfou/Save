#ifndef SQLTABLEITEM_H
#define SQLTABLEITEM_H

#include "le.h"

class sqltableitem : public QTableWidgetItem
{
public:
	sqltableitem(QString parparam, QString tablename, QString colname, int id);
	sqltableitem(int parparam, QString tablename, QString colname, int id);
	QString getTablename() const;
	QString getColname() const;
	QString getId() const;

private:
	QString tablename;
	QString colname;
	QString id;
};

#endif // SQLTABLEITEM_H
