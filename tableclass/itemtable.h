#ifndef ITEMTABLE_H
#define ITEMTABLE_H

#include "le.h"
template<typename T>
class argtableitem;
class group;
class project;
class headertableitem;

class itemtable : public QTableWidgetItem
{
public:
	itemtable(QString placeholder, project *p, QString form = "");
	void update(group *arg, question *head, QString form = "");
	void updategroup(headertableitem *arg, headertableitem *head);
	void update();
private:
	QString placeholder;
	QString form;
	project *p;
	void update2(argtableitem<group> *arg);
	void eval(QString val);
};

#endif // ITEMTABLE_H
