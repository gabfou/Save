#include "grouptreeitem.h"
#include "data/group.h"
#include "data/question.h"
#include "data/person.h"
#include "data/project.h"
#include "questiontreeitem.h"
#include "persontreeitem.h"

grouptreeitem::grouptreeitem()
{

}

// afficher ou pas les personne/ question (et pas juste les groupe de personne/question)

void grouptreeitem::setVisiblenongroup(bool v)
{
    int i = -1;
    grouptreeitem *tmpg;
    questiontreeitem *tmpq;
    persontreeitem *tmpp;

    while(++i < this->childCount())
    {
        if ((tmpg = dynamic_cast<grouptreeitem*>(this->child(i))))
            tmpg->setVisiblenongroup(v);
        else if((tmpq = dynamic_cast<questiontreeitem*>(this->child(i))))
            tmpq->setHidden((v) ? false : true);
        else if((tmpp = dynamic_cast<persontreeitem*>(this->child(i))))
            tmpp->setHidden((v) ? false : true);
    }
}

// initialistation

grouptreeitem::grouptreeitem(QStringList str, project * p, int id, int type, int mod, QTreeWidget *parent) : QTreeWidgetItem(parent, str), typeg(type), p(p)
{
	vector<group> &g = (type == 0) ? p->listgroup : p->listqgroup;
    QList<int>::iterator listpg;
    QList<int> listint =  g[id].getListfils();

	listpg = listint.begin();
	this->id = id;
	while (listpg != listint.end())
	{
        this->addChild(new grouptreeitem(QStringList(QString(g[*listpg].getName())), p, *listpg, type, mod, (QTreeWidget*)0));
        nbgchild++;
		listpg++;
	}
    if (mod > 0)
	{
		if (type == 1)
		{
            QList<question>::iterator listq;
            QList<question> listquestion = g[id].getListq();

			listq = listquestion.begin();
			while (listq != listquestion.end())
			{
                this->addChild(new questiontreeitem(QStringList(QString(listq->name)), listq->id, (QTreeWidget*)0));
				listq++;
			}
		}
        else if (type == 0)
        {
            QList<person>::iterator listp;
            QList<person> listperson = g[id].getListp();

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

// ajout de question globale voir grouptree::addquestglobintree2()

void    grouptreeitem::addquestglobinttree(const question &q)
{
    int i = -1;
    grouptreeitem *tmpg;

    if (nbgchild == 0)
    {
        this->addChild(new questiontreeitem(QStringList(q.name),
                                                        sqlo::addquestion(p, q.name, q.group, q.unit, q.note, q.sujet,
                                                                    this->getId(),
                                                                    q.type, q.ref_only, q.liststr.join("\n"), q.val, q.global),
                                                        (QTreeWidget*)0));
    }
    else
    {
        while (++i < this->childCount())
        {
            if ((tmpg = dynamic_cast<grouptreeitem*>(this->child(i))))
                tmpg->addquestglobinttree(q);
        }
    }
}

int grouptreeitem::getId() const
{
	return id;
}
