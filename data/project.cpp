#include "project.h"
#include "question.h"
#include <stdio.h>
#include <string.h>
#include "barref.h"
#include "../mainwindow.h"
#include "le.h"

#include <QThread>

vector<group> project::getListgroup() const{return listgroup;}
vector<question> project::getListquestion() const{return listquestion;}
vector<person> project::getListp() const{return listp;}

int project::getNbperson() const
{
	return nbperson;
}

int project::getNbfact() const
{
	return nbfact;
}

int project::getNbquestion() const
{
	return nbquestion;
}

int project::getNbgroup() const
{
	return nbgroup;
}

int project::getNbgeneration() const
{
	return nbgeneration;
}

void project::checkmailcalendar()
{

}


// constructeur et destructeur

project::project()
{

}

project::project(QString fproject)
{
	this->initoroject(fproject);
}

void project::addperson(QString name, QString lastname, QString email)
{
	this->nbperson++;
	person ret(name, lastname, email);
	this->listp.push_back(ret);
}

inline void project::addperson(QString name, QString lastname, QString email, int id, vector<question> *listquestion, int groupid)
{
	this->nbperson++;
    qDebug() << name;
	person ret(name, lastname, email, id, listquestion, groupid);
    while (this->listp.size() < id)
        this->listp.push_back(person());
	this->listp.push_back(ret);
}

question project::getquestion(int id)
{
    vector<question> ql = this->listquestion;
	vector<question>::iterator q = ql.begin();

	while (q != ql.end())
	{
		if (q->id == id)
			return (*q);
		q++;
	}
	return(*(ql.begin()));
}

person project::getperson(int id)
{
    vector<person> pl = this->listp;
    vector<person>::iterator p = pl.begin();

    while (p != pl.end())
    {
        if (p->id == id)
            return (*p);
        p++;
    }
    return(*(pl.begin()));
}

inline void project::addquestion(QString name, int group, unsigned int id, int qgroupid, QString sujet,
                                 QString unit, int type, QString splitchar, int value, bool ref_only)
{
	this->nbquestion++;
    question ret(name, group, id, qgroupid, sujet, unit, type, splitchar, value, ref_only);
    while (this->listquestion.size() < id)
        this->listquestion.push_back(question());
	this->listquestion.push_back(ret);
}

void project::addreponse(int id, string name, int time, int note, string date, int iteration, int idquestion) // opti
{
    vector<person>::iterator tmp;

	tmp = listp.begin();
	while (tmp != listp.end())
	{
		if ((*tmp).compare(id) == 0)
		{
            (*tmp).add_fact(name, time, note, date, iteration, idquestion);
			return ;
		}
		tmp++;
	}
}

inline void project::addgroup(QString name, int parentid, unsigned int id, int type, QString description)
{
	if (type == 0)
	{
        group ret(name, parentid, id, (this->listgroup), type, description);
		if (ret.getGeneration() > this->nbgeneration)
			this->nbgeneration = ret.getGeneration();
		while (this->listgroup.size() < id)
			this->listgroup.push_back(group());
		this->listgroup.push_back(ret);
	}
	else if (type == 1)
	{
        group ret(name, parentid, id, (this->listqgroup), type, description);
		if (ret.getGeneration() > this->nbgeneration) // changer nbgenaration par nbqgeneration
			this->nbgeneration = ret.getGeneration();
		while (this->listqgroup.size() < id)
			this->listqgroup.push_back(group());
		this->listqgroup.push_back(ret);
	}
}

static int checkvalide(string line)
{
	int i = -1;

	while (line[++i])
	{
		if (line[i] == ' ' && i != 0 && isalnum(line[i - 1]) && isalnum(line[i + 1]))
			return (1);
	}
	return (0);
}

inline question newquestion(string line)
{
	question ret(line, 0);
	return(ret);
}

int listcompare(list<person> listp, QString line)
{
	list<person>::iterator tmp;

	tmp = listp.begin();
	while (tmp != listp.end())
	{
		if ((*tmp).compare(line) == 0)
		{
			return (1);
		}
		tmp++;
	}
	return (0);
}

void project::initoroject(QString fproject)
{
	this->name = fproject;
	QSqlQuery query;

    this->listgroup.clear();
    this->listp.clear();
    this->listqgroup.clear();
    this->listquestion.clear();
    this->addgroup("ALL", -1, 0, 0, "");
    this->addgroup("ALL", -1, 0, 1, "");
    if(query.exec(("SELECT groupname, groupparent, id, type, description FROM project_" + fproject + "_groupe")))
	{
		while(query.next())
		{
            this->addgroup(query.value(0).toString(),
						   query.value(1).toInt(),
						   query.value(2).toInt(),
                           query.value(3).toInt(),
                           query.value(4).toString());
		}
	}
	else
		qDebug() << "error get group :" << query.lastError();
    if(query.exec(("SELECT question,groupid,id,qgroupid,sujet,type,typef,splitchar,value,ref_only FROM project_" + fproject + "_question")))
	{
		while(query.next())
		{
            this->addquestion(query.value(0).toString(),
							  query.value(1).toInt(),
							  query.value(2).toInt(),
							  query.value(3).toInt(),
							  query.value(4).toString(),
                              query.value(5).toString(),
                              query.value(6).toInt(),
                              query.value(7).toString(),
                              query.value(8).toInt(),
                              query.value(9).toBool());
		}
	}
	else
		qDebug() << "error get question :" << query.lastError();
    if(query.exec(("SELECT id, firstname,lastname,email,groupid FROM project_" + fproject + "_project")))
	{
		while(query.next())
		{
            this->addperson(query.value(1).toString(),
                            query.value(2).toString(),
                            query.value(3).toString(),
							query.value(0).toInt(),
							&listquestion,
							query.value(4).toInt());
		}
	}
	else
		qDebug() << "error get user :" << query.lastError();
    if(query.exec(("SELECT idperson,name,time,note,date_info, iteration, idquestion FROM project_" + fproject + "_reponse")))
	{
		while(query.next())
		{
			this->addreponse(query.value(0).toInt(),
							 query.value(1).toString().toStdString(),
							 query.value(2).toInt(),
							 query.value(3).toInt(),
							 query.value(4).toString().toStdString(),
                             query.value(5).toInt(),
                             query.value(6).toInt());
		}
	}
	else
		qDebug() << "error get reponse :" << query.lastError();
    vector<person>::iterator tmp;
	tmp = this->listp.begin();
	while (tmp != this->listp.end())
	{
        if (tmp->groupid != -1)
            this->listgroup[tmp->getGroupid()].addperson(*tmp);
		tmp++;
	}
	vector<question>::iterator tmp2;
	tmp2 = this->listquestion.begin();
	while (tmp2 != this->listquestion.end())
	{
        if (tmp2->qgroupid != -1)
            this->listqgroup[tmp2->qgroupid].addquestion(*tmp2);
		tmp2++;
	}
}

void	project::groupchild(unsigned int id, QList<int> & ret) const
{
	list<int>::iterator listpg;
	list<int> listint;// = listgroup[id].getListfils();

    if (listgroup.empty())
    {
         qDebug() << "project->listgroup empty project pas init?";
         return ;
    }
    if (id >= listgroup.size() || listgroup[id].init == 0)
    {
         qDebug() << "group with id =" << id << " doesn't exist but is call in project::groupchild";
         return ;
    }
    ret << id;
	listint = this->listgroup[id].getListfils();
	listpg = listint.begin();
	while (listpg != listint.end())
	{
//		qDebug() << "number : " <<QString::number(*listpg);
			this->groupchild(*listpg, ret);
		listpg++;
	}
}

void	project::groupchild(unsigned int id, QList<int> & ret, vector<group> &g) const
{
	list<int>::iterator listpg;
    list<int> listint;// = listgroup[id].getListfils();

	ret << id;
    if (g[id].type == -1)
	{
		qDebug() << "groupchild bug id =" << id;
		return ;
	}
	listint = g[id].getListfils();
	listpg = listint.begin();
	while (listpg != listint.end())
	{
//		qDebug() << "number : " <<QString::number(*listpg);
			this->groupchild(*listpg, ret, g);
		listpg++;
	}
}

void	project::groupqchild(int id, QList<int> & ret) const
{
	list<int>::iterator listpg;
	list<int> listint = listqgroup[id].getListfils();

	ret << id;
	listint = this->listqgroup[id].getListfils();
	listpg = listint.begin();
	while (listpg != listint.end())
	{
        //qDebug() << "groupqchild number group: " << QString::number(*listpg);
		this->groupqchild(*listpg, ret);
		listpg++;
	}
}

vector<question> project::questiongroupqchildnotopti(int id)
{

	QList<int> listqchild;
	vector<question> ret;
    QList<int>::iterator tmp;
	questiongroupqchild(id, listqchild);

	tmp = listqchild.begin();
	while (tmp != listqchild.end())
	{
        qDebug() << listquestion[(*tmp)].name;
        ret.push_back(listquestion[(*tmp)]);
		tmp++;
	}
	return (ret);
}

void	project::questiongroupqchild(int id, QList<int> & ret) const
{
    list<int>::iterator listpg;
    list<question> listq = listqgroup[id].getListq();
    list<question>::iterator listqi;
    list<int> listint = listqgroup[id].getListfils();

    listqi = listq.begin();
    while (listqi != listq.end())
    {
        //qDebug() << "questiongroupchild : " << listqi->id;
        ret << listqi->id;
        listqi++;
    }
    listint = this->listqgroup[id].getListfils();
    listpg = listint.begin();
    while (listpg != listint.end())
    {
        //qDebug() << "questiongroupchild number group: " << QString::number(*listpg);
        this->questiongroupqchild(*listpg, ret);
        listpg++;
    }
}

QList<t_groupref> project::getgrouplist(int id, int qid)
{
	QList<t_groupref> ret;
	QList<int> listchild;
	QList<int>::iterator i;
    QList<int> listqchild;

	groupchild(id, listchild);
    questiongroupqchild(qid, listqchild);
    qDebug() << "machin" << listqchild;
	i = listchild.begin();
	while (i != listchild.end())
	{
        ret << this->listgroup[*i].groupnamerep(this->listquestion, 0, listqchild);
		i++;
	}
	return ret;
}

QList<t_groupref> project::getgrouplistref(int id, int qid)
{
    QList<t_groupref> ret;
    QList<int> listchild;
    QList<int>::iterator i;
    QList<int> listqchild;

    groupchild(id, listchild);
    questiongroupqchild(qid, listqchild);
    qDebug() << "machin" << listqchild;
    i = listchild.begin();
    while (i != listchild.end())
    {
        ret << this->listgroup[*i].groupnamerep(this->listquestion, 1, listqchild);
        i++;
    }
    return ret;
}

QStringList	project::sendproject(Smtp * smtp)
{
    vector<person>::iterator tmp;
    QStringList listmail;
    QString post = (this->name);
    post.append("&");
    post.append(this->postquestion("ALL"));

    tmp = this->listp.begin();
    while (tmp != this->listp.end())
    {
        listmail.push_back((*tmp).personsend(smtp, post));
        listmail.push_back(QString::number((*tmp).id));
        tmp++;
    }
    return (listmail);
}

QString	project::postquestion(QString group) //creation de l url
{(void)group;
	vector<question>::iterator tmp;
	QString ret = "";

	tmp = this->listquestion.begin();
	while (tmp != this->listquestion.end())
	{
        ret.append(((*tmp).name + "=0&"));
		tmp++;
	}
	return ret;
}

void project::convert_to_xlsx()
{

}

project::~project()
{

}
