#include "group.h"
#include "person.h"
#include "question.h"
#include "fact.h"
#include "project.h"


QList<question> group::getListq() const{return listq;}

group::group()
{

}

QColor panelgcolor[5] = {Qt::cyan, Qt::magenta, Qt::yellow, Qt::blue, Qt::darkGreen};

QString group::getName() const{return this->name;}
QList<person> group::getListp() const {return this->listp;}
int group::getGeneration() const{return generation;}
int group::getParentid() const{return parentid;}
QColor group::getColor() const{return color;}
void group::setColor(const QColor &value){color = value;}


void	group::addfils(int id)
{
    this->listfils.push_back(id);
}

void    group::supquestion(int id)
{
    QList<question>::iterator tmp = listq.begin();

    while (tmp != listq.end())
    {
        if (tmp->id == id)
        {
            qDebug() << "question" << id << "supprimer";
            listq.erase(tmp);
            return ;
        }
        tmp++;
    }
}

void    group::supperson(int id)
{
    if (id < 0 || !this || init == 0)
        return ;
    QList<person>::iterator tmp = listp.begin();

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

void    group::changequestion(int id, question & q)
{
    QList<question>::iterator tmp = listq.begin();

    while (tmp != listq.end())
    {
        if (tmp->id == id)
        {
            qDebug() << "question" << id << "changer";
            *tmp = q;
            return ;
        }
        tmp++;
    }
}

void    group::changeperson(int id, person & p)
{
    if (id < 0 || init == 0)
        return ;
    QList<person>::iterator tmp = listp.begin();

    while (tmp != listp.end())
    {
        if (tmp->id == id)
        {
            *tmp = p;
            return ;
        }
        tmp++;
    }
}

group::group(QString name, int parentid, int id, vector<group> & listgroup, int type, QString description, int gquestion, project *p) : type(type), p(p)
{
    this->init = 1;
	this->name = name;
	this->parentid = parentid;
	this->id = id;
    this->description = description;
	this->groupsetcolor(id);
    this->gquestion = gquestion;
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

group::group(const group &g)
{
    this->init = g.init;
    this->name = g.name;
    this->parentid = g.parentid;
    this->id = g.id;
    this->description = g.description;
    this->gquestion = g.gquestion;
    this->generation = g.getGeneration();
    this->listfils = g.getListfils();
    this->listp = g.getListp();
    this->listq = g.getListq();
    this->p = g.p;
    this->type = g.type;
    this->color = g.getColor();
    this->visible = g.visible;
}

void group::addperson(person p)
{
	person p2(p);
    listp.push_back(p2);
}

void group::addquestion(question q)
{
	question q2(q);
    listq.push_back(q2);
}

void group::debug()
{
    QList<person>::iterator tmp;
	tmp = this->listp.begin();
	while (tmp != this->listp.end())
	{
        qDebug() << tmp->getName();
		tmp++;
	}
}

QList<int> group::getListfils() const
{
    return this->listfils;
}


t_groupref group::groupnamerep(const vector<question> &questionlist, QList<int> listqchild, int iterationmin, int iterationmax)
{
	t_groupref ret;

    ret.name = this->name;
    ret.list = this->grouprep(questionlist, listqchild, iterationmin, iterationmax);

	return ret;
}

t_groupref group::groupnameallrep(const vector<question> &questionlist, QList<int> listqchild, int iterationmin, int iterationmax)
{
    t_groupref ret;

    ret.name = this->name;
    ret.list = this->grouprepall(questionlist, listqchild, iterationmin, iterationmax);

    QList<float>::iterator it = ret.list.begin();
    while (it != ret.list.end())
    {
        ret.total += *it;
        it++;
    }
    return ret;
}

QString group::grouprepvaltype2(question tmp2, int iterationmin, int iterationmax)
{
    QList<person>::iterator tmp;
    QVector<int> nb(tmp2.liststr.size() + 1);
    float l;
    QString ret;

    l = 0;
    tmp = this->listp.begin();
    while (tmp != this->listp.end())
    {
        if (((*tmp).personshowcasevaltype2(tmp2, &nb, iterationmin, iterationmax)) > -0.1)
            l++;
        tmp++;
    }
    if (l == 0)
        return ("NA");
    int i = -1;
    while(++i < tmp2.liststr.size() + 1)
    {
        if (i != 0)
            ret += " | ";
        ret += QString::number(nb[i] * 100 / l) + "%";
    }
    return (ret);
}

QString group::grouprepval(question tmp2, int iterationmin, int iterationmax)
{
    QList<person>::iterator tmp;
    float nb;
    float l;
    float inttmp;

    if (tmp2.type == 2)
        return (grouprepvaltype2(tmp2, iterationmin, iterationmax));
    // int
    nb = 0;
    l = 0;
    tmp = this->listp.begin();
    while (tmp != this->listp.end())
    {
        if ((inttmp = (*tmp).personshowcaseval(tmp2, iterationmin, iterationmax)) > -0.1)
        {
            l++;
            nb += inttmp;
        }
        tmp++;
    }
    if (l != 0)
        return(QString::number(nb / l));
    else
        return ("NA");
}

QString group::grouprep(question tmp2, int iterationmin, int iterationmax)
{
    QList<person>::iterator tmp;
    float nb;
    float l;
    float inttmp;

    if (tmp2.type == 2)
        return (grouprepvaltype2(tmp2, iterationmin, iterationmax));
    nb = 0;
    l = 0;
    tmp = this->listp.begin();
	while (tmp != this->listp.end())
    {
        if ((inttmp = (*tmp).personshowcase(tmp2, iterationmin, iterationmax)) > -0.1)
        {
            l++;
            nb += inttmp;
        }
        tmp++;
	}
	if (l != 0)
        return(QString::number(nb / l));
	else
        return ("NA");
}

QString group::grouprep(group & groupp, QString tmp3, question *ret, int iterationmin, int iterationmax)
{
    QList<question>::iterator tmp = listq.begin();

    while (tmp != listq.end())
    {
        if (tmp3.compare(tmp->name) == 0)
        {
            if (ret != NULL)
                *ret = *tmp;
            return (groupp.grouprep(*tmp, iterationmin, iterationmax));
        }
        tmp++;
    }
    return ("NA");
}

float group::grouprepall(question tmp2, vector<group> &g, int iterationmin, int iterationmax) // opti qstring neccessaire
{
    QList<int>::iterator tmp = listfils.begin();
    float val = 0;

    val += grouprep(tmp2, iterationmin, iterationmax).toFloat();
    while(tmp != listfils.end())
    {
        val += g[*tmp].grouprepall(tmp2, g, iterationmin, iterationmax);
        tmp++;
    }
    return (val);
}

QList<float> group::grouprepall(const vector<question> & questionlist, QList<int> listqchild, int iterationmin, int iterationmax)
{
    QList<int>::iterator tmp2;
    QList<float> ret;
    vector<group> g;

    tmp2 = listqchild.begin();
    while (tmp2 != listqchild.end())
    {
        ret << grouprepall(questionlist[*tmp2], p->listgroup, iterationmin, iterationmax);
        tmp2++;
    }
    return ret;
}

QList<float> group::grouprep(const vector<question> & questionlist, QList<int> listqchild, int iterationmin, int iterationmax)
{
    QList<int>::iterator tmp2;
    QList<float> ret;

    tmp2 = listqchild.begin();
    while (tmp2 != listqchild.end())
    {
        ret << grouprep(questionlist[*tmp2], iterationmin, iterationmax).toFloat();
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
    QList<person>::iterator tmp = listp.begin();

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
    QList<question>::iterator tmp = listq.begin();

    while (tmp != listq.end())
    {
        if (tmp->id == q.id)
            return (1);
        tmp++;
    }
    return (0);
}

void group::changegroupidallqchild(project *p, int groupid)
{
    QList<question>::iterator tmp = listq.begin();

    while (tmp != listq.end())
    {
        sqlo::addquestion(p, tmp->name, groupid, tmp->unit, tmp->note, tmp->sujet, tmp->qgroupid,
                          tmp->type, tmp->ref_only,tmp->liststr.join("\n"), tmp->val, tmp->global, tmp->id);
        tmp++;
    }

    QList<int>::iterator tmp2 = listfils.begin();
    while (tmp2 != listfils.end())
    {
        p->listgroup[*tmp2].changegroupidallqchild(p, groupid);
        tmp2++;
    }
}
