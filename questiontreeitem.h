#ifndef QUESTIONTREEITEM_H
#define QUESTIONTREEITEM_H

// represente une question dans un groupetree

#include "le.h"

class questiontreeitem : public QTreeWidgetItem
{
public:
    questiontreeitem(QStringList str, int id, QTreeWidget *parent);
    int id;
};

#endif // QUESTIONTREEITEM_H
