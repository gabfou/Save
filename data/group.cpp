#include "group.h"
#include "person.h"
#include "question.h"


std::list<question> group::getListq() const{return listq;}

group::group()
{

}

QColor panelgcolor[5] = {Qt::cyan, Qt::magenta, Qt::yellow, Qt::blue, Qt::darkGreen};

string group::getName() const{return this->name;}
list<person> group::getListp(){return this->listp;}
int group::getGeneration() const{return generation;}
int group::getParentid() const{return parentid;}
QColor group::getColor() const{return color;}
void group::setColor(const QColor &value){color = value;}


void	group::addfils(int id)
{
	qDebug() << this->name.c_str() << " addfils: " << QString::number(id) << QString::number((long int)this);
	int dafuq = id;
	if (this->listfils.empty())
		qDebug() << "emptyfils";
	this->listfils.push_back(dafuq);
}


group::group(string name, int parentid, int id, vector<group> & listgroup, int type) : type(type)
{
	this->name = name;
	this->parentid = parentid;
	this->id = id;
	this->groupsetcolor(id);
	if (parentid > -1 && parentid < listgroup.size())
	{
		listgroup[parentid].addfils(id);
		this->generation = listgroup[parentid].getGeneration() + 1;
	}
	else if (parentid == -1)
	   this->generation = -1;
	else
	{
		this->generation = 0;
		warning("probleme de base de donnée: groupe pere eronée ou placer apres group fils");
	}
}

void group::addperson(person p)
{
	person p2(p);
	this->listp.push_back(p2);
	qDebug() << p2.getName().c_str();
}

void group::addquestion(question q)
{
	question q2(q);
	this->listq.push_back(q2);
	qDebug() << q2.name.c_str();
}

void group::debug()
{
	list<person>::iterator tmp;
	tmp = this->listp.begin();
	while (tmp != this->listp.end())
	{
		//this->listgroup[tmp->getGroupid()].addperson(*tmp);
		qDebug() << tmp->getName().c_str();
		tmp++;
	}
}

std::list<int> group::getListfils() const
{
	return listfils;
}


t_groupref group::groupnamerep(const vector<question> &questionlist, int ref, QList<int> listqchild) const
{
	t_groupref ret;

	ret.name = this->name.c_str();
    ret.list = this->grouprep(questionlist, ref, listqchild);

	return ret;
}

QString group::grouprep(question tmp2, int ref) const
{
	list<person>::const_iterator tmp;
	int nb;
	int l;

	nb = 0;
	l = 0;
	tmp = this->listp.begin();
	while (tmp != this->listp.end())
	{
		if (ref == 0)
		{
			if ((nb += (*tmp).personshowcase(tmp2.name)) != 0)
				l++;
		}
		else
			if ((nb += (*tmp).personrefshowcase(tmp2.name)) != 0)
				l++;
		tmp++;
	}
	if (l != 0)
		return(QString::number(nb / l));
	else
		return ("NA");
}

QList<QString> group::grouprep(const vector<question> & questionlist, int ref, QList<int> listqchild) const
{
    QList<int>::const_iterator tmp2;
	QList<QString> ret;
	//afficher reponse au question

    tmp2 = listqchild.begin();
    while (tmp2 != listqchild.end())
	{
        qDebug() << "truc :" << *tmp2;
        ret << grouprep(questionlist[*tmp2], ref);
		tmp2++;
	}
	return ret;
}

void group::showgroup(QTableWidget *gbox, int *i, const vector<question> & questionlist, const vector<group> & listgroup, int k)  const
{
/*	vector<question>::iterator tmp2;
	group gtmp = *this;

	//afficher les groupe

	if (listp.empty() == true)
		return ;
	while (gtmp.getGeneration() > 0)
	{
		gbox->setItem(*i, gtmp.getGeneration() - 1, new QTableWidgetItem(gtmp.getName().c_str()));
		//gbox->item(*i, gtmp.getGeneration() - 1)->setBackgroundColor(Qt::red);
		if (g_ref)
			gbox->setItem(*i + 1, gtmp.getGeneration() - 1, new QTableWidgetItem(gtmp.getName().c_str()));
		gtmp = listgroup[gtmp.getParentid()];
	}
	gbox->setVerticalHeaderItem(*i, new QTableWidgetItem(gtmp.getName().c_str()));
	gbox->verticalHeaderItem(*i)->setBackgroundColor(gtmp.getColor());
	if (g_ref)
	{
		gbox->setVerticalHeaderItem(*i + 1, new QTableWidgetItem((gtmp.getName() + " ref").c_str()));
		gbox->verticalHeaderItem(*i + 1)->setBackgroundColor(gtmp.getColor());
	}

	//afficher reponse au question

    QList<QString> listrep = this->grouprep(questionlist, 0);
	QList<QString>::iterator tmp = listrep.begin();
	int x = k;

	while (tmp  != listrep.end())
	{
		gbox->setItem(*i, x, new QTableWidgetItem(*tmp));
		gbox->item(*i, (x)++)->setBackgroundColor(gtmp.getColor());
		tmp++;
	}
	x = k;
	while (x > -1)
	{
		if (!(gbox->item(*i, x)))
			gbox->setItem(*i, x, new QTableWidgetItem(""));
		gbox->item(*i, (x)--)->setBackgroundColor(gtmp.getColor());
	}
	(*i)++;
	if (g_ref)
	{
		QList<QString> listrepref = this->grouprep(questionlist, 1);
		x = k;
		tmp = listrepref.begin();

		while (tmp != listrepref.end())
		{
			gbox->setItem(*i, x, new QTableWidgetItem(*tmp));
			gbox->item(*i, (x)++)->setBackgroundColor(gtmp.getColor());
			tmp++;
		}
		x = k;
		while (x > -1)
		{
			if (!(gbox->item(*i, x)))
				gbox->setItem(*i, x, new QTableWidgetItem(""));
			gbox->item(*i, (x)--)->setBackgroundColor(gtmp.getColor());
		}
		(*i)++;
    }*/
}

void group::groupsetcolor(int i)
{
	this->color = panelgcolor[i % 5];
}

void group::show(QTableWidget *gbox, int *i, const vector<group> & listgroup, int k) const
{
	list<person>::const_iterator tmp;
	group gtmp = *this;

	tmp = this->listp.begin();
	while (tmp != this->listp.end())
	{
		while (gtmp.getGeneration() > 0)
		{
			gbox->setItem(*i, gtmp.getGeneration() - 1, new QTableWidgetItem(gtmp.getName().c_str()));
			if (g_ref)
				gbox->setItem(*i + 1, gtmp.getGeneration() - 1, new QTableWidgetItem(gtmp.getName().c_str()));
			gtmp = listgroup[gtmp.getParentid()];
		}
		gbox->setVerticalHeaderItem(*i, new QTableWidgetItem(gtmp.getName().c_str()));
		gbox->setItem(*i, k - 1, new QTableWidgetItem((*tmp).getName().c_str()));
		(*tmp).personshow(gbox, (*i)++, k, gtmp, 0);
		if (g_ref)
		{
			gbox->setVerticalHeaderItem(*i, new QTableWidgetItem(gtmp.getName().c_str()));
			gbox->setItem(*i, k - 1, new QTableWidgetItem((*tmp).getName().c_str()));
			(*tmp).personshow(gbox, (*i)++, k, gtmp, 1);
		}
		tmp++;
	}
}

group::~group()
{

}

bool group::contain(person &p)
{
    list<person>::iterator tmp = listp.begin();

    while (tmp != listp.end())
    {
        if (tmp->id == p.id)
            return (1);
        tmp++;
    }
    return (0);
}

bool group::contain(question &q)
{
    list<question>::iterator tmp = listq.begin();

    while (tmp != listq.end())
    {
        if (tmp->id == q.id)
            return (1);
        tmp++;
    }
    return (0);
}
