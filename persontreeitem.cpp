#include "persontreeitem.h"

persontreeitem::persontreeitem(QStringList str, int id, QTreeWidget *parent) : QTreeWidgetItem(parent, str), id(id)
{

}
