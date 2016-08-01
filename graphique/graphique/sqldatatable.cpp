#include "sqldatatable.h"
#include "sqltableitem.h"

sqldatatable::sqldatatable(QString column , QString table, int nbcolumn)
{
    nbcolumn;
    QVariant tmpv; // opti & tmpv
    QSqlQuery query;
    query.prepare("SELECT id, " + column + " FROM " + table + ";");
    if (!(query.exec()))
        qDebug() << query.lastError();
    this->setRowCount(query.numRowsAffected());
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
    QSqlQuery query;
    query.prepare("UPDATE " + tmp->getTablename() + " Set " + tmp->getColname() + "=? WHERE id=?;");
    query.addBindValue(tmp->text());
    query.addBindValue(tmp->getId());
    if (!(query.exec()))
        qDebug() << query.lastError();
}
