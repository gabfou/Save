#ifndef SQLDATATABLE_H
#define SQLDATATABLE_H

#include "le.h"

class sqltableitem;

class sqldatatable : public QTableWidget
{
	Q_OBJECT
public:
	sqldatatable(QString column, QString table, int nbcolumn);
private slots:
	void sqlupdateitem(QTableWidgetItem *item);
private:
	QVector<QStringRef> tabcolumn;
	QString strcolumn;
};

#endif // SQLDATATABLE_H
