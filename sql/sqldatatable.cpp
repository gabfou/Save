#include "sqldatatable.h"
#include "sqltableitem.h"

sqldatatable::sqldatatable(QString column , QString table, int nbcolumn)
{
	QVariant tmpv; // opti & tmpv
	QSqlQuery query;
	query.prepare("SELECT id, " + column + " FROM " + table + ";");
	if (!(query.exec()))
		qDebug() << query.lastError();
	this->setRowCount(query.size());
	this->setColumnCount(nbcolumn);
	this->verticalHeader()->hide();
	int row = 0;
	this->strcolumn = column;
	this->tabcolumn = this->strcolumn.splitRef(", ");
	QTableWidgetItem *tmpItem;
	int col = -1;
	while (++col < nbcolumn)
		this->setHorizontalHeaderItem(col, new QTableWidgetItem(this->tabcolumn[col].toString()));
	while (query.next())
	{
		col = -1;
		int id = query.value(0).toInt();
		while (++col < nbcolumn)
		{
			tmpv = query.value(col + 1);
			tmpv.convert(QVariant::String);
	  //	  qDebug() << "niark" << tmpv.toString() << table << this->tabcolumn[col].toString() << id;
			tmpItem = new sqltableitem((tmpv.toString()), table, this->tabcolumn[col].toString(), id);
			this->setItem(row, col, tmpItem);
		}
		row++;
	}

	//formating table

	this->resizeColumnsToContents();
	this->resizeRowsToContents();
	this->setSortingEnabled(true);
	this->sortItems(1,Qt::AscendingOrder);

	//slot
	connect(this, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(sqlupdateitem(QTableWidgetItem*)));
}

void sqldatatable::sqlupdateitem(QTableWidgetItem* item)
{
	sqltableitem *tmp = dynamic_cast<sqltableitem *>(item);
	if (!tmp)
	{
		qDebug() << "dinamic cast fail sqlupdateitem";
		return ;
	}
    sqlupdate(tmp->getTablename(), tmp->getColname(), tmp->text(), tmp->getId().toInt());
}
