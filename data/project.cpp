#include "project.h"
#include "question.h"
#include "barref.h"
#include "../mainwindow.h"
#include "person.h"
#include "group.h"
#include "fact.h"

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

void project::checkmailcalendar()
{

}

void project::init()
{
    mtypeq[0] = "nombre";
    mtypeq[1] = "oui/non";
    mtypeq[2] = "question";
    mtypeq[3] = "nombre";
}

// constructeur et destructeur

project::project()
{
    init();
}

project::project(QString fproject)
{
    init();
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
	person ret(name, lastname, email, id, listquestion, groupid);
	while ((int)(this->listp.size()) < id)
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

int project::getNbqgroup() const
{
	return nbqgroup;
}

int project::getNbfactref() const
{
	return nbfactref;
}

int project::getNbfactnref() const
{
	return nbfactnref;
}

int project::getNbpgeneration() const
{
	return nbpgeneration;
}

int project::getNbqgeneration() const
{
	return nbqgeneration;
}

inline void project::addquestion(QString name, int group, unsigned int id, int qgroupid, QString sujet,
								 QString unit, int type, QString splitchar, int value, bool ref_only,
								 bool global)
{
	this->nbquestion++;
	question ret(name, group, id, qgroupid, sujet, unit, type, splitchar, value, ref_only, global);
	while (this->listquestion.size() < id)
		this->listquestion.push_back(question());
	this->listquestion.push_back(ret);
}

void project::addreponse(int id, string name, int time, int note, string date, int iteration, int idquestion) // opti
{
	if (iteration)
		nbfactnref++;
	else
		nbfactref++;
	listp[id].add_fact(name, time, note, date, iteration, idquestion);
}

inline void project::addgroup(QString name, int parentid, unsigned int id, int type, QString description, bool gquestion)
{
	if (type == 0)
	{
		this->nbgroup++;
		group ret(name, parentid, id, (this->listgroup), type, description, gquestion);
		if (ret.getGeneration() > this->nbpgeneration)
			this->nbpgeneration = ret.getGeneration();
		while (this->listgroup.size() < id)
			this->listgroup.push_back(group());
		this->listgroup.push_back(ret);
	}
	else if (type == 1)
	{
		this->nbqgroup++;
		group ret(name, parentid, id, (this->listqgroup), type, description, gquestion);
		if (ret.getGeneration() > this->nbqgeneration) // changer nbgenaration par nbqgeneration
			this->nbqgeneration = ret.getGeneration();
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

void project::initvar()
{
	nbperson = 0;
	nbfact = 0;
	nbquestion = 0;
	nbgroup = 0;
    nbpgeneration = 0;
    nbqgeneration = 0;
	nbqgroup = 0;
	nbfactref = 0;
	nbfactnref = 0;
	listgroup.clear();
	listp.clear();
	listqgroup.clear();
	listquestion.clear();
}

void project::initoroject(QString fproject)
{
	QElapsedTimer timerdebug;
	this->name = fproject;
	QSqlQuery query;

	initvar();
	this->addgroup("ALL", -1, 0, 0, "", 0);
	this->addgroup("ALL", -1, 0, 1, "", 0);

	qDebug() << "init groupe";timerdebug.start();
	if(query.exec(("SELECT groupname, groupparent, id, type, description, gquestion FROM project_" + fproject + "_groupe")))
	{
		while(query.next())
		{
			this->addgroup(query.value(0).toString(),
						   query.value(1).toInt(),
						   query.value(2).toInt(),
						   query.value(3).toInt(),
						   query.value(4).toString(),
						   query.value(5).toBool());
		}
	}
	else
		qDebug() << "error get group :" << query.lastError();
	qDebug() << "init group time" << timerdebug.elapsed() << "milliseconds";

	qDebug() << "init question";timerdebug.start();
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
							  query.value(9).toBool(),
							  0);
		}
	}
	else
		qDebug() << "error get question :" << query.lastError();
	qDebug() << "init question time" << timerdebug.elapsed() << "milliseconds";

	qDebug() << "init persone";timerdebug.start();
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
	qDebug() << "init persone time" << timerdebug.elapsed() << "milliseconds";

	qDebug() << "init fact";timerdebug.start();
	if(query.exec(("SELECT idperson,name,time,note,date_info, iteration, idquestion FROM project_" + fproject + "_reponse")))
	{
		qDebug() << "query select reponse time" << timerdebug.elapsed() << "milliseconds";
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
	qDebug() << "init all reponse time" << timerdebug.elapsed() << "milliseconds";

	qDebug() << "remplissage groupe persone";timerdebug.start();
	vector<person>::iterator tmp;
	tmp = this->listp.begin();
	while (tmp != this->listp.end())
	{
		if (tmp->groupid > -1 && tmp->groupid < (int)(listgroup.size()))
			this->listgroup[tmp->getGroupid()].addperson(*tmp);
		tmp++;
	}
	qDebug() << "remplissage groupe personne time" << timerdebug.elapsed() << "milliseconds";

	qDebug() << "remplissage groupe question";timerdebug.start();
	vector<question>::iterator tmp2;
	tmp2 = this->listquestion.begin();
	while (tmp2 != this->listquestion.end())
	{
		if (tmp2->qgroupid > -1 && tmp2->qgroupid < listqgroup.size())
			this->listqgroup[tmp2->qgroupid].addquestion(*tmp2);
		tmp2++;
	}
	qDebug() << "remplissage groupe question time" << timerdebug.elapsed() << "milliseconds";
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

QList<question> project::questiongroupqchildnotopti(int id)
{

	QList<int> listqchild;
	QList<question> ret;
	QList<int>::iterator tmp;
	questiongroupqchild(id, listqchild);

	tmp = listqchild.begin();
	while (tmp != listqchild.end())
	{
		//qDebug() << listquestion[(*tmp)].name;
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

group    *project::groupsearch(QString name, group *g)
{
    vector<group> gv = (g.type) ? listqgroup : listgroup;
    list<int> lf;
    list<int>::iterator lfi;
    group *ret;

    if (name.compare(g.name))
        return (g);
    if (g->getListfils().empty())
        return (NULL);
    lf = g->getListfils();
    lfi = lf.begin();
    while (lfi != lf.end())
    {
        ret = groupsearch(name, &gv[*lfi]);
        if (ret)
            return (ret);
        lfi++;
    }
    return (NULL);
}

void    project::addqgroup(QString name, QString parrent)
{
    group *p = groupsearch(parrent, &listqgroup[0]);
    list<int> lf;
    list<int>::iterator lfi;

    if (p)
    {
        lf = p->getListfils();
        lfi = lf.begin();
        while(lfi != lf.end())
        {
            if (listqgroup[*lfi].name.compare(name) == 0)
                return ;
            lfi++;
        }
        sqlo::addgroup(this, this->name, name, p->id, p->type, name, 0);
    }
}


QStringList	project::sendproject()
{
	list<person> listtmp = listgroup[0].getListp();
	list<person>::iterator tmp;
	QStringList listmail;
	QString post = (this->name);
	post.append("&");
	post.append(this->postquestion("ALL"));

	qDebug() << listtmp.size();
	tmp = listtmp.begin();
	while (tmp != listtmp.end())
	{
		listmail.push_back((*tmp).email);
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

int	sqlo::addgroup(project *p, QString nameproject, QString name, int groupparent, int type, QString description, bool gquestion, int id)
{
    QSqlQuery qry;

    if (id != -1)
        qry.prepare(("UPDATE project_" + p->name + "_groupe Set groupname=?, groupparrent=?, type=?, description=?, gquestion=? WHERE id=?;"));
    else
        qry.prepare( "INSERT INTO project_" + nameproject + "_groupe (groupname ,groupparent ,type, description, gquestion) VALUES ( ?, ?, ?, ?, ? );" );
    qry.addBindValue(name);
    qry.addBindValue(QString::number(groupparent));
    qry.addBindValue(QString::number(type));
    qry.addBindValue(description);
    qry.addBindValue(gquestion);
    if (id != -1)
        qry.addBindValue(id);
    if( !qry.exec() )
        qDebug() << qry.lastError();
    else
        qDebug() << "groupe insert success!";
    if (id == -1)
        p->addgroup(name, groupparent, qry.lastInsertId().toInt(), type, description, gquestion);
    else
    {
        vector<group> *tmp = (type == 0) ? &p->listgroup : &p->listqgroup;
        (*tmp)[id].parentid = groupparent;
        (*tmp)[id].type = type;
        (*tmp)[id].description = description;
        (*tmp)[id].name = name;
        (*tmp)[id].gquestion = gquestion;
    }
    return (qry.lastInsertId().toInt());
}

void	sqlo::supgroup(QString nameproject, int id, vector<group> & g)
{
    QSqlQuery qry;
    qry.prepare( "DELETE FROM project_" + nameproject + "_groupe WHERE id=?;" );
    qry.addBindValue(g[id].id);
    if( !qry.exec() )
        qDebug() << qry.lastError();
    else
    {
        qDebug() << "groupe delete success!";
    }
}

int	sqlo::addquestion(project *p, QString name, int groupid, QString type, int note, QString description, int qgroupid,
                int typef, bool ref_only, QString splitchar, int val, bool global, int id) // global n'est pas integrer en sql
{
    QSqlQuery qry;

    if (id != -1)
        qry.prepare(("UPDATE project_" + p->name + "_question Set question=?, groupid=?, type=?, note=?, sujet=?, typef=?, qgroupid=?, ref_only=?, splitchar=?, value=? WHERE id=?;"));
    else
    {
//		qry.prepare( ("CREATE TABLE IF NOT EXISTS project_" + p->name + "_question (id INTEGER UNIQUE PRIMARY KEY NOT NULL AUTO_INCREMENT, question VARCHAR(30), groupid INTEGER, type VARCHAR(30), note BOOLEAN DEFAULT 1, sujet VARCHAR(300), qgroupid INT DEFAULT 0, typef INT DEFAULT 0)") );
//		if( !qry.exec() )
//			qDebug() << qry.lastError();
        qry.prepare( ("INSERT INTO project_" + p->name + "_question (question , groupid , type , note , sujet , typef, qgroupid, ref_only, splitchar, value ) VALUES ( ?, ?, ?, ?, ?, ?, ?, ?, ?, ? );") );
    }
    qry.addBindValue(name);
    qry.addBindValue(groupid);
    qry.addBindValue(type);
    qry.addBindValue(note);
    qry.addBindValue(description);
    qry.addBindValue(typef);
    qry.addBindValue(qgroupid);
    qry.addBindValue(ref_only);
    qry.addBindValue(splitchar + " ");
    qry.addBindValue(val);
    //qry.addBindValue(global);
    if (id != -1)
        qry.addBindValue(id);
    if (!qry.exec())
        qDebug() << qry.lastError() << "addquestion";
    else
        qDebug() << "question insert success!";
    if (id == -1)
    {
        p->addquestion(name, groupid, qry.lastInsertId().toInt(), qgroupid, description, type, typef, splitchar + " ", val, ref_only, global);
        p->listqgroup[qgroupid].addquestion(p->listquestion[qry.lastInsertId().toInt()]);
    }
    else
    {
        p->listquestion[id].name = name;
        p->listquestion[id].group = groupid;
        p->listquestion[id].unit = type;
        p->listquestion[id].note = note;
        p->listquestion[id].sujet = description;
        p->listquestion[id].qgroupid = qgroupid;
        p->listquestion[id].type = typef;
        p->listquestion[id].liststr = splitchar.split(" ");
        p->listquestion[id].val = val;
        p->listquestion[id].ref_only = ref_only;
        p->listquestion[id].global = global;
    }
    return (qry.lastInsertId().toInt());
}

void	sqlo::supquest(project *p, QString nameproject, int id)
{
    QSqlQuery qry;
    qry.prepare( "DELETE FROM project_" + nameproject + "_question WHERE id=?;" );
    qry.addBindValue(id);
    if( !qry.exec() )
        qDebug() << qry.lastError();
    else
    {
        qDebug() << "question delete success!";
    }
    p->listqgroup[p->listquestion[id].qgroupid].supquestion(id);
    p->listquestion[id] = question();
}

int     sqlo::addperson(project *p, QString firstname, QString lastname,
              QString email, int groupid, int id)
{
    QSqlQuery qry;

    if (id != -1)
        qry.prepare(("UPDATE project_" + p->name + "_project Set firstname=?, lastname=?, email=?, groupid=? WHERE id=?;"));
    else
    {
//		qry.prepare( ("CREATE TABLE IF NOT EXISTS project_" + p->name + "_project (id INTEGER UNIQUE PRIMARY KEY NOT NULL AUTO_INCREMENT, person VARCHAR(30), groupid INTEGER, type VARCHAR(30), note BOOLEAN DEFAULT 1, sujet VARCHAR(300), qgroupid INT DEFAULT 0, typef INT DEFAULT 0)").c_str() );
//		if( !qry.exec() )
//			qDebug() << qry.lastError();
        qry.prepare( ("INSERT INTO project_" + p->name + "_project (firstname, lastname, email, groupid ) VALUES ( ? , ? , ? , ? );") );
    }
    qry.addBindValue(firstname);
    qry.addBindValue(lastname);
    qry.addBindValue(email);
    qry.addBindValue(groupid);
    if (id != -1)
    {
        qry.addBindValue(id);
    }
    if (!qry.exec())
        qDebug() << qry.lastError() << "addperson";
    else
        qDebug() << "person insert success!";
    if (id == -1)
    {
        p->addperson(firstname, lastname, email, qry.lastInsertId().toInt(), &(p->listquestion), groupid);
        p->listgroup[groupid].addperson(p->listp[qry.lastInsertId().toInt()]);
    }
    else
    {
        p->listp[id].name = firstname + " " + lastname;
        p->listp[id].firstname = firstname;
        p->listp[id].lastname = lastname;
        p->listp[id].email = email;
        p->listp[id].groupid = groupid;
    }
    return (qry.lastInsertId().toInt());
}

void	sqlo::supperson(project *p, QString nameproject, int id)
{
    qDebug() << id;
    if (id < 0)
        return ;
    QSqlQuery qry;
    qry.prepare( "DELETE FROM project_" + nameproject + "_project WHERE id=?;" );
    qry.addBindValue(id);
    if( !qry.exec() )
        qDebug() << qry.lastError();
    else
    {
        qDebug() << "person delete success!";
    }
    p->listgroup[p->listp[id].groupid].supperson(id);
    p->listp[id] = person();
}

void	sqlo::sqlupdate(QString tablename, QString colname, QString str, int id)
{
    QSqlQuery query;
    query.prepare("UPDATE " + tablename + " Set " + colname + "=? WHERE id=?;");
    query.addBindValue(str);
    query.addBindValue(id);
    if (!(query.exec()))
        qDebug() << query.lastError();
}
