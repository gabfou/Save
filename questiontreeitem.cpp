#include "questiontreeitem.h"

questiontreeitem::questiontreeitem(QStringList str, int id, QTreeWidget *parent) : QTreeWidgetItem(parent, str), id(id)
{
}
