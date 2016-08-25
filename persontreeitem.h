#ifndef PERSONTREEITEM_H
#define PERSONTREEITEM_H

#include "le.h"

class persontreeitem : public QTreeWidgetItem
{
public:
    persontreeitem(QStringList str, int id, QTreeWidget *parent);
    int id;
};

#endif // PERSONTREEITEM_H
