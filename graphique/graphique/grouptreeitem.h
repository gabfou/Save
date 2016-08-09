#ifndef GROUPTREEITEM_H
#define GROUPTREEITEM_H

#include "le.h"

class project;

class grouptreeitem : public QTreeWidgetItem
{
public:
	grouptreeitem();
    grouptreeitem(QStringList str, project *p, int id, int type = 0, int mod = 0, QTreeWidget *parent = 0);
    int getId() const;

private:
    int id;
};

#endif // GROUPTREEITEM_H
