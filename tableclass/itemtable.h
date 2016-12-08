#ifndef ITEMTABLE_H
#define ITEMTABLE_H

#include "le.h"

// cette clase repredente une cellule d'un des 3 tableaux principaux

template<typename T>
class argtableitem;
class group;
class project;
class person;
class headertableitem;

class itemtable : public QTableWidgetItem
{
public:
    itemtable(QString placeholder, project *p, QString form = "", int itmin = -1, int itmax = -1);
    void update(group *arg, question *head, int itmin, int itmax, QString form = "");
	void updategroup(headertableitem *arg, headertableitem *head);
    void update();
private:
	QString placeholder;
	QString form;
	project *p;
    int itminprep;
    int itmaxprep;
	void update2(argtableitem<group> *arg);
    void eval(QString val, question &q);
    void eval(QString val);
    void updateall(group *arg, question *head, int itmin, int itmax, QString form = "");
    void update(group *arg, QString *head, int itmin, int itmax, QString form = "");
    void update(person *arg, question *head, int itmin, int itmax, QString form = "");
    void update(group *arg, QList<question> *head, int itmin, int itmax, QString form = "");
};

#endif // ITEMTABLE_H
