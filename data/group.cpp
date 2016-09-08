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

void    group::supquestion(int id)
{
    list<question>::iterator tmp = listq.begin();

    while (tmp != listq.end())
    {
        if (tmp->id == id)
        {
            listq.erase(tmp);
            return ;
        }
        tmp++;
    }
}

void    group::supperson(int id)
{
    if (init == 0)
        return ;
    list<person>::iterator tmp = listp.begin();

    while (tmp != listp.end())
    {
        if (tmp->id == id)
        {
            listp.erase(tmp);
            return ;
        }
        tmp++;
    }
}

group::group(string name, int parentid, int id, vector<group> & listgroup, int type, QString description) : type(type)
{
    this->init = 1;
	this->name = name;
	this->parentid = parentid;
	this->id = id;
    this->description = description;
	this->groupsetcolor(id);
    if (parentid > -1 && (size_t)parentid < listgroup.size())
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
    qDebug() << p2.getName();
}

void group::addquestion(question q)
{
	question q2(q);
	this->listq.push_back(q2);
    qDebug() << q2.name;
}

void group::debug()
{
	list<person>::iterator tmp;
	tmp = this->listp.begin();
	while (tmp != this->listp.end())
	{
		//this->listgroup[tmp->getGroupid()].addperson(*tmp);
        qDebug() << tmp->getName();
		tmp++;
	}
}

std::list<int> group::getListfils() const
{
	return listfils;
}


t_groupref group::groupnamerep(const vector<question> &questionlist, int ref, QList<int> listqchild)
{
	t_groupref ret;

	ret.name = this->name.c_str();
    ret.list = this->grouprep(questionlist, ref, listqchild);

	return ret;
}

QString group::grouprepval(question tmp2, int ref)
{
    list<person>::iterator tmp;
    float nb;
    float l;
    float inttmp;

    if (tmp2.type == 2)
        return ("reponse non chiffrer");
    // int
    nb = 0;
    l = 0;
    tmp = this->listp.begin();
    while (tmp != this->listp.end())
    {
        if (ref == 0)
        {
            if ((inttmp = (*tmp).personshowcaseval(tmp2)) > -0.1)
            {
                l++;
                nb += inttmp;
            }
        }
        else
        {
            if ((inttmp = (*tmp).personrefshowcaseval(tmp2)) > -0.1)
            {
                l++;
                nb += inttmp;
            }
        }
        tmp++;
    }
    if (l != 0)
        return(QString::number(nb / l));
    else
        return ("NA");
}

QString group::grouprep(question tmp2, int ref)
{
    list<person>::iterator tmp;
    float nb;
    float l;
    float inttmp;

    if (tmp2.type == 2)
        return ("reponse non chiffrer");
    // int
    nb = 0;
    l = 0;
    tmp = this->listp.begin();
	while (tmp != this->listp.end())
	{
		if (ref == 0)
		{
            if ((inttmp = (*tmp).personshowcase(tmp2)) > -0.1)
            {
				l++;
                nb += inttmp;
            }
		}
		else
        {
            if ((inttmp = (*tmp).personrefshowcase(tmp2)) > -0.1)
            {
                l++;
                nb += inttmp;
            }
        }
		tmp++;
	}
	if (l != 0)
        return(QString::number(nb / l));
	else
        return ("NA");
}

float group::grouprepall(question tmp2, vector<group> &g) // opti qstring neccessaire
{
    list<int>::iterator tmp = listfils.begin();
    float val = 0;

    val += grouprep(tmp2, 0).toInt();
    while(tmp != listfils.end())
    {
        val += g[*tmp].grouprepall(tmp2, g);
        tmp++;
    }
    return (val);
}


QList<float> group::grouprep(const vector<question> & questionlist, int ref, QList<int> listqchild)
{
    QList<int>::iterator tmp2;
    QList<float> ret;
	//afficher reponse au question

    tmp2 = listqchild.begin();
    while (tmp2 != listqchild.end())
	{
        qDebug() << "truc :" << *tmp2;
        ret << grouprep(questionlist[*tmp2], ref).toFloat();
		tmp2++;
	}
	return ret;
}

void group::groupsetcolor(int i)
{
	this->color = panelgcolor[i % 5];
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
