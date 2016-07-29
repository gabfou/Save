#include "grouptreeitem.h"
#include "group.h"

grouptreeitem::grouptreeitem()
{

}

grouptreeitem::grouptreeitem(QStringList str, vector<group> & listgroup, int id, QTreeWidget *parent) : QTreeWidgetItem(parent, str)
{
	list<int>::iterator listpg;
	list<int> listint = listgroup[id].getListfils();

	listpg = listint.begin();
	this->id = id;
	while (listpg != listint.end())
	{
		this->addChild(new grouptreeitem(QStringList(QString(listgroup[*listpg].getName().c_str())), listgroup, *listpg, (QTreeWidget*)0));
		listpg++;
	}
}

int grouptreeitem::getId() const
{
    return id;
}
