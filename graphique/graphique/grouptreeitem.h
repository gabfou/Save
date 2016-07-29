#ifndef GROUPTREEITEM_H
#define GROUPTREEITEM_H

#include "le.h"

class group;

class grouptreeitem : public QTreeWidgetItem
{
public:
	grouptreeitem();
    grouptreeitem(QStringList str, vector<group> & listgroup, int id, QTreeWidget *parent = 0);
    int getId() const;

private:
    int id;
};

#endif // GROUPTREEITEM_H
