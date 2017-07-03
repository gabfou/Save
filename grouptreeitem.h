#ifndef GROUPTREEITEM_H
#define GROUPTREEITEM_H

#include "le.h"

class project;

// cette classe represente un groupe dans un grouptree

class grouptreeitem : public QTreeWidgetItem
{
public:
	grouptreeitem();
	grouptreeitem(QStringList str, project *p, int id, int type = 0, int mod = 0, QTreeWidget *parent = 0);
	int getId() const;
    int typeg = 0;
    int nbgchild = 0;

    void addquestglobinttree(const question &q);
public slots:
    void setVisiblenongroup(bool v);
private:
	int id;
    project *p;
};

#endif // GROUPTREEITEM_H
