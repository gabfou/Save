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
list<person> project::getListp() const{return listp;}

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

project::project(string fproject)
{
	this->initoroject(fproject);
}

void project::addperson(string name, string lastname, string email)
{
	this->nbperson++;
	person ret(name, lastname, email);
	this->listp.push_back(ret);
}

inline void project::addperson(string name, string lastname, string email, int id, vector<question> *listquestion, int groupid)
{
	this->nbperson++;
	person ret(name, lastname, email, id, listquestion, groupid);
	this->listp.push_back(ret);
}

question project::getquestion(int id)
{
	vector<question> ql = this->listquestion;;
	vector<question>::iterator q = ql.begin();

	while (q != ql.end())
	{
		if (q->id == id)
			return (*q);
		q++;
	}
	return(*(ql.begin()));
}

inline void project::addquestion(string name, int group, int id, int qgroupid, QString sujet, QString unit)
{
	this->nbquestion++;
	question ret(name, group, id, qgroupid, sujet, unit);
    while (this->listquestion.size() < id)
        this->listquestion.push_back(question());
	this->listquestion.push_back(ret);
}

void project::addreponse(int id, string name, int time, int note, string date, int iteration)
{
	list<person>::iterator tmp;

	tmp = listp.begin();
	while (tmp != listp.end())
	{
		if ((*tmp).compare(id) == 0)
		{
			(*tmp).add_fact(name, time, note, date, iteration);
			return ;
		}
		tmp++;
	}
}

inline void project::addgroup(string name, int parentid, int id, int type)
{
	if (type == 0)
	{
		group ret(name, parentid, id, (this->listgroup), type);
		if (ret.getGeneration() > this->nbgeneration)
			this->nbgeneration = ret.getGeneration();
		while (this->listgroup.size() < id)
			this->listgroup.push_back(group());
		this->listgroup.push_back(ret);
	}
	else if (type == 1)
	{
		group ret(name, parentid, id, (this->listqgroup), type);
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

int listcompare(list<person> listp, string line)
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

void project::initoroject(string fproject)
{
	this->name = fproject;
	QSqlQuery query;

	this->addgroup("ALL", -1, 0, 0);
	this->addgroup("ALL", -1, 0, 1);
	if(query.exec(("SELECT groupname, groupparent, id, type FROM project_" + fproject + "_groupe").c_str()))
	{
		while(query.next())
		{
			this->addgroup(query.value(0).toString().toStdString(),
						   query.value(1).toInt(),
						   query.value(2).toInt(),
						   query.value(3).toInt());
		}
	}
	else
		qDebug() << "error get group :" << query.lastError();
	if(query.exec(("SELECT question,groupid,id,qgroupid,sujet,type FROM project_" + fproject + "_question").c_str()))
	{
		while(query.next())
		{
			this->addquestion(query.value(0).toString().toStdString(),
							  query.value(1).toInt(),
							  query.value(2).toInt(),
							  query.value(3).toInt(),
							  query.value(4).toString(),
							  query.value(5).toString());
		}
	}
	else
		qDebug() << "error get question :" << query.lastError();
	if(query.exec(("SELECT id, firstname,lastname,email,groupid FROM project_" + fproject + "_project").c_str()))
	{
		while(query.next())
		{
			this->addperson(query.value(1).toString().toStdString(),
							query.value(2).toString().toStdString(),
							query.value(3).toString().toStdString(),
							query.value(0).toInt(),
							&listquestion,
							query.value(4).toInt());
		}
	}
	else
		qDebug() << "error get user :" << query.lastError();
	if(query.exec(("SELECT idperson,name,time,note,date_info, iteration FROM project_" + fproject + "_reponse").c_str()))
	{
		while(query.next())
		{
			this->addreponse(query.value(0).toInt(),
							 query.value(1).toString().toStdString(),
							 query.value(2).toInt(),
							 query.value(3).toInt(),
							 query.value(4).toString().toStdString(),
							 query.value(5).toInt());
		}
	}
	else
		qDebug() << "error get reponse :" << query.lastError();
	list<person>::iterator tmp;
	tmp = this->listp.begin();
	while (tmp != this->listp.end())
	{
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

void	project::projectgroupshow(MainWindow *main, QTableWidget *gbox, int k, int id, int *i)
{
	list<int>::iterator listpg;
	list<int> listint = listgroup[id].getListfils();

	if (main->showmod == 1)
		this->listgroup[id].show(gbox, i, this->listgroup, k);
	else
		this->listgroup[id].showgroup(gbox, i, this->listquestion, this->listgroup, k);
	listint = this->listgroup[id].getListfils();
	listpg = listint.begin();
	while (listpg != listint.end())
	{
        //qDebug() << "number : " <<QString::number(*listpg);
			this->projectgroupshow(main, gbox, k, *listpg, i);
		listpg++;
	}
}

void	project::groupchild(int id, QList<int> & ret) const
{
	list<int>::iterator listpg;
	list<int> listint;// = listgroup[id].getListfils();

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

void	project::groupchild(int id, QList<int> & ret, vector<group> &g) const
{
	list<int>::iterator listpg;
	list<int> listint;// = listgroup[id].getListfils();

	ret << id;
	if (g[id].type = -1)
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
        qDebug() << "questiongroupchild : " << listqi->id;
        ret << listqi->id;
        listqi++;
    }
    listint = this->listqgroup[id].getListfils();
    listpg = listint.begin();
    while (listpg != listint.end())
    {
        qDebug() << "questiongroupchild number group: " << QString::number(*listpg);
        this->questiongroupqchild(*listpg, ret);
        listpg++;
    }
}

void	project::projectshow(MainWindow *main, QTableWidget *gbox, int grefid)
{
	list<person>::iterator tmp;
	vector<question>::iterator tmp2;
	int i = (main->showmod == 1) ? 1 : 0;
	i+= this->nbgeneration;
	int k = i;

	//gbox->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	if (this->listp.empty() || this->listquestion.empty())
		return ;
	gbox->clear();
	//if (g_ref)
	   gbox->setRowCount(this->nbperson * 2 + this->nbgroup * 2);
	//else
	  //  gbox->setRowCount(this->nbperson);
	gbox->setColumnCount(this->nbquestion + i /* 2*/);
	tmp2 = this->listquestion.begin();
	if (main->showmod == 0)
	{
		while (--k > -1)
			gbox->setHorizontalHeaderItem(k, new QTableWidgetItem("Sous groupe"));
	}
	else
	{
		gbox->setHorizontalHeaderItem(--k, new QTableWidgetItem("Noms"));
		while (--k > -1)
			gbox->setHorizontalHeaderItem(k, new QTableWidgetItem("Sous groupe"));
	}
	k = i;
	while (tmp2 != this->listquestion.end())
	{
		gbox->setHorizontalHeaderItem(i++, new QTableWidgetItem(("Moyenne " + tmp2->name + "").c_str()));
		//gbox->setHorizontalHeaderItem(i++, new QTableWidgetItem(("temps a " + tmp2->name + " reel").c_str()));
		tmp2++;
	}
	i = 0;
	this->projectgroupshow(main, gbox, k, grefid, &i);
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

QList<t_groupref> project::getgrouplistref(int id)
{
	QList<t_groupref> ret;
	QList<int> listchild;
    QList<int> listqchild;
	QList<int>::iterator i;


	groupchild(id, listchild);
	i = listchild.begin();
    questiongroupqchild(0, listqchild);
	while (i != listchild.end())
	{
        ret << this->listgroup[*i].groupnamerep(this->listquestion, 1, listqchild);
		i++;
	}
	return ret;
}

QStringList	project::sendproject(Smtp * smtp)
{
	list<person>::iterator tmp;
	QStringList listmail;
	QString post = (this->name.c_str());
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

// obsolete

void	project::send()
{
	list<person>::iterator tmp;

	tmp = this->listp.begin();
	while (tmp != this->listp.end())
	{
		(*tmp).personsend();
		tmp++;
	}
}

QString	project::postquestion(QString group) //creation de l url
{
	vector<question>::iterator tmp;
	QString ret = "";

	tmp = this->listquestion.begin();
	while (tmp != this->listquestion.end())
	{
		ret.append(((*tmp).name + "=0&").c_str());
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
