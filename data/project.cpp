#include "project.h"
#include "question.h"
#include "barref.h"
#include "../mainwindow.h"
#include "person.h"
#include "group.h"
#include "fact.h"

#include <QThread>

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

// getter

vector<group> project::getListgroup() const{return listgroup;}
vector<question> project::getListquestion() const{return listquestion;}
vector<person> project::getListp() const{return listp;}
int project::getNbperson() const{return nbperson;}
int project::getNbfact() const{return nbfact;}
int project::getNbquestion() const{return nbquestion;}
int project::getNbgroup() const{return nbgroup;}
int project::getNbqgroup() const{return nbqgroup;}
int project::getNbfactref() const{return nbfactref;}
int project::getNbfactnref() const{return nbfactnref;}
int project::getNbpgeneration() const{return nbpgeneration;}
int project::getNbqgeneration() const{return nbqgeneration;}

// recuperation du bon type de question a partir d un String

int project::mytypqinv(QString type)
{
	if (type.compare("Nombre") == 0)
		return (0);
	if (type.compare("Oui/non") == 0)
		return (1);
	if (type.compare("Option") == 0)
		return (2);
	if (type.compare("Option avec valeur") == 0)
		return (3);
	return (-1);
}

// recuperation d une question a partir de son id

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

// recuperation d une person a partir de son id

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

void project::init()
{
	mtypeq[0] = "Nombre";
	mtypeq[1] = "Oui/non";
	mtypeq[2] = "Option";
	mtypeq[3] = "Option avec valeur";
}

// ajout d'une personne au projet

inline void project::addperson(QString name, QString lastname, QString email, int id, vector<question> *listquestion, int groupid, int questionbool, int refbool, int jour)
{
	if (id == -1)
        sqlo::addperson(this, name, lastname, email, groupid, refbool, questionbool, jour);
	if (questionbool > questionboolmax)
		questionboolmax = questionbool;
	this->nbperson++;
    person ret(name, lastname, email, id, listquestion, groupid, questionbool, refbool, jour);
	while ((int)(this->listp.size()) < id)
		this->listp.push_back(person());
	this->listp.push_back(ret);
}

// ajout d'une question au projet

inline void project::addquestion(QString name, int group, int id, int qgroupid, QString sujet,
								 QString unit, int type, QString splitchar, int value, int ref_only,
								 bool global)
{
	if (id == -1)
	{
		id = sqlo::addquestion(this, name, group, unit, 0, sujet, qgroupid, type, ref_only, splitchar, value, global);
	}
	this->nbquestion++;
	question ret(name, group, id, qgroupid, sujet, unit, type, splitchar, value, ref_only, global);
    while ((int)this->listquestion.size() < id)
		this->listquestion.push_back(question());
	this->listquestion.push_back(ret);
}

// ajout d'une reponse au projet

inline void project::addreponse(int id, string name, int time, int note, QString date, int iteration, int idquestion, QString timestr)
{
	if (iteration > iterationmax)
		iterationmax = iteration;
	if (iteration)
		nbfactnref++;
	else
		nbfactref++;
    if (id < (int)listp.size() && listp[id].id != -1)
		listp[id].add_fact(name, time, note, date, iteration, idquestion, timestr);
}

// ajout d'un groupe au projet

inline void project::addgroup(QString name, int parentid, unsigned int id, int type, QString description, int gquestion)
{
	if (type == 0)
	{
		this->nbgroup++;
		group ret(name, parentid, id, (this->listgroup), type, description, gquestion, this);
		if (ret.getGeneration() > this->nbpgeneration)
			this->nbpgeneration = ret.getGeneration();
		while (this->listgroup.size() < id)
			this->listgroup.push_back(group());
		this->listgroup.push_back(ret);
	}
	else if (type == 1)
	{
		this->nbqgroup++;
		group ret(name, parentid, id, (this->listqgroup), type, description, gquestion, this);
		if (ret.getGeneration() > this->nbqgeneration) // changer nbgenaration par nbqgeneration
			this->nbqgeneration = ret.getGeneration();
		while (this->listqgroup.size() < id)
			this->listqgroup.push_back(group());
		this->listqgroup.push_back(ret);
	}
}

inline question newquestion(string line)
{
	question ret(line, 0);
	return(ret);
}

// cherche line dans une list de personne

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

// initialization des variable

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
	default_table = 0;
	iterationmax = 0;
	iterationmin = 0;
	sugestion = 1;
	questionboolmax = 0;
	introindex.clear();
	introref.clear();
	introreel.clear();
    indexbool = 1;
}

// initialisation du projet recuperation des donnée sur le serveur

void project::initoroject(QString fproject)
{
	QElapsedTimer timerdebug;
	this->name = fproject;
	QSqlQuery query;

	initvar();
	this->addgroup("ALL", -1, 0, 0, "", 0);
	this->addgroup("ALL", -1, 0, 1, "", 0);

    if (query.exec("SELECT default_table, introindex, introref, introreel, indexbool FROM all_config WHERE project_name='" + fproject +"'"))
	{
		while(query.next())
		{
			default_table = (query.value(0).toInt());
			introindex = (query.value(1).toString());
			introref = (query.value(2).toString());
			introreel = (query.value(3).toString());
            indexbool = (query.value(4).toBool());
		}
	}
	else
		qDebug() << "error get info_project :" << query.lastError();
	qDebug() << "init groupe";timerdebug.start();
	if (query.exec("SELECT groupname, groupparent, id, type, description, gquestion FROM project_" + fproject + "_groupe"))
	{
		while(query.next())
		{
			this->addgroup(query.value(0).toString(),
						   query.value(1).toInt(),
						   query.value(2).toInt(),
						   query.value(3).toInt(),
						   query.value(4).toString(),
                           query.value(5).toInt());
		}
	}
	else
		qDebug() << "error get group :" << query.lastError();
	qDebug() << "init group time" << timerdebug.elapsed() << "milliseconds";

	qDebug() << "init question";timerdebug.start();
	if (query.exec("SELECT question,groupid,id,qgroupid,sujet,type,typef,splitchar,value,ref_only FROM project_" + fproject + "_question"))
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
							  query.value(9).toInt(),
							  0);
		}
	}
	else
		qDebug() << "error get question :" << query.lastError();
	qDebug() << "init question time" << timerdebug.elapsed() << "milliseconds";

	qDebug() << "init persone";timerdebug.start();
    if(query.exec("SELECT id, firstname,lastname,email,groupid,questionbool,refbool,jour FROM project_" + fproject + "_project"))
	{
		while(query.next())
		{
			this->addperson(query.value(1).toString(),
							query.value(2).toString(),
							query.value(3).toString(),
							query.value(0).toInt(),
							&listquestion,
							query.value(4).toInt(),
							query.value(5).toInt(),
                            query.value(6).toInt(),
                            query.value(7).toInt());
		}
	}
	else
		qDebug() << "error get user :" << query.lastError();
	qDebug() << "init persone time" << timerdebug.elapsed() << "milliseconds";

	qDebug() << "init fact";timerdebug.start();
	if(query.exec("SELECT idperson,name,time,note,date_info, iteration, idquestion, str FROM project_" + fproject + "_reponse"))
	{
		qDebug() << "query select reponse time" << timerdebug.elapsed() << "milliseconds";
		while(query.next())
		{
			this->addreponse(query.value(0).toInt(),
							 query.value(1).toString().toStdString(),
							 query.value(2).toInt(),
							 query.value(3).toInt(),
							 query.value(4).toDateTime().toString("dd/MM/yy hh:mm:ss"),
							 query.value(5).toInt(),
							 query.value(6).toInt(),
							 query.value(7).toString());
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
        if (tmp2->qgroupid > -1 && tmp2->qgroupid < (int)listqgroup.size())
			this->listqgroup[tmp2->qgroupid].addquestion(*tmp2);
		tmp2++;
	}
	qDebug() << "remplissage groupe question time" << timerdebug.elapsed() << "milliseconds";
}

// renvoi (par ret) d une list d'id tout les groupe fils au group d'id id ainsi que lui meme

void	project::groupchild(unsigned int id, QList<int> & ret) const
{
	QList<int>::iterator listpg;
	QList<int> listint;// = listgroup[id].getListfils();

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
		this->groupchild(*listpg, ret);
		listpg++;
	}
}

// pareil mais renvoi une liste de groupe de personne

void	project::groupchild(unsigned int id, vector<group> & ret) const
{
    QList<int>::iterator listpg;
    QList<int> listint;// = listgroup[id].getListfils();

    ret.push_back(listgroup[id]);
    listint = listgroup[id].getListfils();
    listpg = listint.begin();
    while (listpg != listint.end())
    {
        this->groupchild(*listpg, ret);
        listpg++;
    }
}

// pareil mais utilise g au lieux de this->listgroup

void	project::groupchild(unsigned int id, QList<int> & ret, vector<group> &g) const
{
	QList<int>::iterator listpg;
	QList<int> listint;

	ret << id;
	if (g[id].type == -1)
		return ;
	listint = g[id].getListfils();
	listpg = listint.begin();
	while (listpg != listint.end())
	{
		this->groupchild(*listpg, ret, g);
		listpg++;
	}
}

// obsolete

void	project::groupqchild(int id, QList<int> & ret, int gref) const
{
	QList<int>::iterator listpg;
	QList<int> listint = listqgroup[id].getListfils();

	ret << id;
	listint = this->listqgroup[id].getListfils();
	listpg = listint.begin();
	while (listpg != listint.end())
	{
		this->groupqchild(*listpg, ret, gref);
		listpg++;
	}
}

// recupere une liste de question fils du group avec pour id id

QList<question> project::questiongroupqchildnotopti(int id, bool ref)
{

	QList<int> listqchild;
	QList<question> ret;
	QList<int>::iterator tmp;
	questiongroupqchild(id, listqchild);

	tmp = listqchild.begin();
	while (tmp != listqchild.end())
	{
		//qDebug() << listquestion[(*tmp)].name;
		if (ref == 1 || listquestion[(*tmp)].ref_only == 0)
			ret.push_back(listquestion[(*tmp)]);
		tmp++;
	}
	return (ret);
}

// recupere une liste d'id des questions fils du groupe avec pour id id

void	project::questiongroupqchild(int id, QList<int> & ret, bool ref) const
{
	QList<int>::iterator listpg;
	QList<question> listq = listqgroup[id].getListq();
	QList<question>::iterator listqi;
	QList<int> listint = listqgroup[id].getListfils();

	listqi = listq.begin();
	while (listqi != listq.end())
	{
		if (ref == 1 || listqi->ref_only == 0)
			ret << listqi->id;
		listqi++;
	}
	listint = this->listqgroup[id].getListfils();
	listpg = listint.begin();
	while (listpg != listint.end())
	{
		this->questiongroupqchild(*listpg, ret, ref);
		listpg++;
	}
}

// renvoi toute ce dont a besoin bargraph pour fonctioner sous le bon formatage (id = groupe de personne concerné et qid = groupe de question concerné) 

QList<t_groupref> project::getgrouplist(int id, int qid, int iterationmin, int iterationmax)
{
	QList<t_groupref> ret;
	QList<int> listchild;
	QList<int>::iterator i;
	QList<int> listqchild;

	groupchild(id, listchild);
	questiongroupqchild(qid, listqchild);
	i = listchild.begin();
	while (i != listchild.end())
	{
		ret << this->listgroup[*i].groupnamerep(this->listquestion, listqchild, iterationmin, iterationmax);
		i++;
	}
	return ret;
}

// renvoi toute ce dont a besoin Comparrefdo pour fonctioner sous le bon formatage (id = groupe de personne concerné et qid = groupe de question concerné)

t_groupref project::getgroupalllist(int id, int qid, int iterationmin, int iterationmax)
{
    QList<int> listqchild;

    questiongroupqchild(qid, listqchild);
    return this->listgroup[id].groupnameallrep(this->listquestion, listqchild, iterationmin, iterationmax);
}

// cherche le groupe name dans les fils de g

group	*project::groupsearch(QString name, group *g)
{
	vector<group> & gv = (g->type) ? listqgroup : listgroup;
	QList<int> lf;
	QList<int>::iterator lfi;
	group *ret = NULL;

	if (name.compare(g->name) == 0)
		return (g);
//	if (g->getListfils().empty())
//		return (NULL);
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

// ajout d'un groupe de question

int project::addqgroup(QString name, QString parrent)
{
	if(name.isEmpty())
		return (-1);
	group *p = groupsearch(parrent, &listqgroup[0]);
	QList<int> lf;
	QList<int>::iterator lfi;

	if (p)
	{
		lf = p->getListfils();
		lfi = lf.begin();
		while(lfi != lf.end())
		{
			if (listqgroup[*lfi].name.compare(name) == 0)
				return (listqgroup[*lfi].id);
			lfi++;
		}
		return (sqlo::addgroup(this, this->name, name, p->id, p->type, name, 0));
	}
	return (-1);
}

// ajout d'un groupe de personne

int project::addpgroup(QString name, QString parrent)
{
	if (name.isEmpty())
		return (-1);
	group *p = groupsearch(parrent, &listgroup[0]);
	QList<int> lf;
	QList<int>::iterator lfi;

	if (p)
	{
		lf = p->getListfils();
		lfi = lf.begin();
		while(lfi != lf.end())
		{
			if (listgroup[*lfi].name.compare(name) == 0)
				return (listgroup[*lfi].id);
			lfi++;
		}
		return (sqlo::addgroup(this, this->name, name, p->id, p->type, name, 0));
	}
	return (-1);
}

// recuperer tout les personne descendant du groupe group

QList<person> project::getListallpfils(int group)
{
	QList<person> ret;
	QList<int> groupp = listgroup[group].getListfils();
	QList<int>::iterator i;

	ret += listgroup[group].getListp();

	i = groupp.begin();
	while(i != groupp.end())
	{
		ret += getListallpfils(*i);
		i++;
	}
	return (ret);
}


project::~project()
{

}

// ajout d'un groupe dans la base de donnée

int	sqlo::addgroup(project *p, QString nameproject, QString name, int groupparent, int type, QString description, int gquestion, int id)
{
	QSqlQuery qry;

	if (id != -1)
		qry.prepare(("UPDATE project_" + p->name + "_groupe Set groupname=?, groupparent=?, type=?, description=?, gquestion=? WHERE id=?;"));
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

// suppresion d'un groupe dans la base de donnée

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

// ajout d'une question dans la base de donnée

int	sqlo::addquestion(project *p, QString name, int groupid, QString type, int note, QString description, int qgroupid,
				int typef, int ref_only, QString splitchar, int val, bool global, int id) // global n'est pas integrer en sql
{
	QSqlQuery qry;

	if (id != -1)
		qry.prepare(("UPDATE project_" + p->name + "_question Set question=?, groupid=?, type=?, note=?, sujet=?, typef=?, qgroupid=?, ref_only=?, splitchar=?, value=? WHERE id=?;"));
	else
		qry.prepare( ("INSERT INTO project_" + p->name + "_question (question , groupid , type , note , sujet , typef, qgroupid, ref_only, splitchar, value ) VALUES ( ?, ?, ?, ?, ?, ?, ?, ?, ?, ? );") );
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
		p->listquestion[id].liststr = splitchar.split("\n");
		p->listquestion[id].val = val;
		p->listquestion[id].ref_only = ref_only;
		p->listquestion[id].global = global;
		p->listqgroup[qgroupid].changequestion(id, p->listquestion[id]);
	}
	return (qry.lastInsertId().toInt());
}

// suppression d'une question dans la base de donnée

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

// ajout d'une personne dans la base de donnée

int	 sqlo::addperson(project *p, QString firstname, QString lastname,
              QString email, int groupid, int refbool, int questionbool, int jour, int id)
{
	QSqlQuery qry;

	if (id != -1)
        qry.prepare(("UPDATE project_" + p->name + "_project Set firstname=?, lastname=?, email=?, groupid=?, refbool=?, questionbool=?, jour=? WHERE id=?;"));
	else
        qry.prepare( ("INSERT INTO project_" + p->name + "_project (firstname, lastname, email, groupid, refbool, questionbool, jour) VALUES ( ? , ? , ? , ? , ?, ?, ? );"));
	qry.addBindValue(firstname);
	qry.addBindValue(lastname);
	qry.addBindValue(email);
    qry.addBindValue(groupid);
    qry.addBindValue(refbool);
    qry.addBindValue(questionbool);
    qry.addBindValue(jour);
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
        p->addperson(firstname, lastname, email, qry.lastInsertId().toInt(), &(p->listquestion), groupid, 0, 0, 0);
		p->listgroup[groupid].addperson(p->listp[qry.lastInsertId().toInt()]);
	}
	else
	{
		p->listp[id].name = firstname + " " + lastname;
		p->listp[id].firstname = firstname;
		p->listp[id].lastname = lastname;
		p->listp[id].email = email;
		p->listp[id].groupid = groupid;
		p->listgroup[groupid].changeperson(id, p->listp[id]);
	}
	return (qry.lastInsertId().toInt());
}

// suppression d'une personne dans la base de donnée

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

// mise a jour de la table tablename en mettant str a la colone colname et a la ligne avec id id

void	sqlo::sqlupdate(QString tablename, QString colname, QString str, int id)
{
	QSqlQuery query;
	query.prepare("UPDATE " + tablename + " Set " + colname + "=? WHERE id=?;");
	query.addBindValue(str);
	query.addBindValue(id);
	if (!(query.exec()))
		qDebug() << query.lastError();
}

// mise a jour de l'introindex (l'into a la page ou le client choisit le formulaire a remplir) du projet projetname

void sqlo::sqlupdateintroindex(QString projetname, QString s)
{
	QSqlQuery query;
	query.prepare("UPDATE all_config Set introindex=? WHERE project_name=?;");
	query.addBindValue(s);
	query.addBindValue(projetname);
	if (!(query.exec()))
		qDebug() << query.lastError();
}

// mise a jour de l'introref (l'into a la page ou le client remplit le formulaire a l'iteration 0) du projet projetname

void sqlo::sqlupdateintroref(QString projetname, QString s)
{
	QSqlQuery query;
	query.prepare("UPDATE all_config Set introref=? WHERE project_name=?;");
	query.addBindValue(s);
	query.addBindValue(projetname);
	if (!(query.exec()))
		qDebug() << query.lastError();
}

// mise a jour de l'introreel (l'into a la page ou le client remplit le formulaire a partir de l'iteration 1) du projet projetname

void sqlo::sqlupdateintroreel(QString projetname, QString s)
{
	QSqlQuery query;
	query.prepare("UPDATE all_config Set introreel=? WHERE project_name=?;");
	query.addBindValue(s);
	query.addBindValue(projetname);
	if (!(query.exec()))
		qDebug() << query.lastError();
}

