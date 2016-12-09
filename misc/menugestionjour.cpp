#include "menugestionjour.h"
#include "mainwindow.h"
#include "sql/sqltableitem.h"
#include "data/person.h"

menugestionjour::menugestionjour(MainWindow *m) : m(m)
{


    this->setRowCount(m->current.getNbperson());
    this->setColumnCount(6);

    vector<person>::iterator it = m->current.listp.begin();
    int y = -1;
    this->setHorizontalHeaderItem(0, new QTableWidgetItem("Prenoms"));
    this->setHorizontalHeaderItem(1, new QTableWidgetItem("Noms"));
    this->setHorizontalHeaderItem(2, new QTableWidgetItem("Estimation a remplir?"));
    this->setHorizontalHeaderItem(3, new QTableWidgetItem("Nombre de jour a remplir"));
    this->setHorizontalHeaderItem(4, new QTableWidgetItem("Nombre de jour remplis"));
    this->setHorizontalHeaderItem(5, new QTableWidgetItem("Id"));
    while (it != m->current.listp.end())
    {
        if (it->id == -1)
        {
            it++;
            continue ;
        }
        this->setItem(++y, 0, new QTableWidgetItem(it->firstname));
        this->setItem(y, 1, new QTableWidgetItem(it->lastname));
        this->setItem(y, 2, new QTableWidgetItem((it->refbool) ? "oui": "non"));
        this->setItem(y, 3, new QTableWidgetItem(QString::number(it->questionbool)));
        this->setItem(y, 4, new QTableWidgetItem(QString::number(it->jour)));
        this->setItem(y, 5, new QTableWidgetItem(QString::number(it->id)));
        it++;
    }

    //formating table

    this->hideColumn(5);
    this->resizeColumnsToContents();
    this->resizeRowsToContents();

    //slot
    connect(this, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(updateitem(QTableWidgetItem*)));
}


void menugestionjour::updateitem(QTableWidgetItem* item)
{
    int row = item->row();
    person *p = &(m->current.listp[this->item(row, 5)->text().toInt()]);
    sqlo::addperson(&(m->current), this->item(row, 0)->text(), this->item(row, 1)->text(), p->email, p->groupid, this->item(row, 2)->text().compare("non"), this->item(row, 3)->text().toInt(), this->item(row, 4)->text().toInt(), p->id);
}
