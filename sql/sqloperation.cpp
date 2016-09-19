#include "le.h"
#include "data/group.h"
#include "data/project.h"


int	addgroup(project *p, QString nameproject, QString name, int groupparent, int type, QString description, bool gquestion, int id)
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

void	supgroup(QString nameproject, int id, vector<group> & g)
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

int	addquestion(project *p, QString name, int groupid, QString type, int note, QString description, int qgroupid,
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

void	supquest(project *p, QString nameproject, int id)
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

int	addperson(project *p, QString firstname, QString lastname,
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

void	supperson(project *p, QString nameproject, int id)
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

void	sqlupdate(QString tablename, QString colname, QString str, int id)
{
	QSqlQuery query;
	query.prepare("UPDATE " + tablename + " Set " + colname + "=? WHERE id=?;");
	query.addBindValue(str);
	query.addBindValue(id);
	if (!(query.exec()))
		qDebug() << query.lastError();
}
