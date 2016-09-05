#include "grouptreeitem.h"
#include "data/group.h"
#include "data/question.h"
#include "data/project.h"
#include "questiontreeitem.h"
#include "persontreeitem.h"

grouptreeitem::grouptreeitem()
{

}

grouptreeitem::grouptreeitem(QStringList str, project * p, int id, int type, int mod, QTreeWidget *parent) : QTreeWidgetItem(parent, str), typeg(type)
{
	vector<group> &g = (type == 0) ? p->listgroup : p->listqgroup;
	list<int>::iterator listpg;
	list<int> listint =  g[id].getListfils();

	listpg = listint.begin();
	this->id = id;
	while (listpg != listint.end())
	{
		this->addChild(new grouptreeitem(QStringList(QString(g[*listpg].getName().c_str())), p, *listpg, type, mod, (QTreeWidget*)0));
		listpg++;
	}
    if (mod > 0)
	{
		if (type == 1)
		{
			list<question>::iterator listq;
			list<question> listquestion = g[id].getListq();

			listq = listquestion.begin();
			while (listq != listquestion.end())
			{
                this->addChild(new questiontreeitem(QStringList(QString(listq->name)), listq->id, (QTreeWidget*)0));
				listq++;
			}
		}
        else if (type == 0)
        {
            list<person>::iterator listp;
            list<person> listperson = g[id].getListp();

            listp = listperson.begin();
            while (listp != listperson.end())
            {
                this->addChild(new persontreeitem(QStringList(QString(listp->name)), listp->id, (QTreeWidget*)0));
                listp++;
            }
        }
		else
			qDebug() << "groupitem group type =" << g[id].type;
	}
}

int grouptreeitem::getId() const
{
	return id;
}
