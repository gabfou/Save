#include "le.h"
#include "data/group.h"
#include "data/project.h"


int    addgroup(QString nameproject, QString name, int groupparent, int type, project *p)
{
    QSqlQuery qry;

    qry.prepare( "CREATE TABLE IF NOT EXISTS project_" + nameproject + "_groupe (id INTEGER UNIQUE PRIMARY KEY NOT NULL AUTO_INCREMENT, groupname VARCHAR(500), groupparent INTEGER DEFAULT 0, type BOOLEAN DEFAULT 0)" );
    if( !qry.exec() )
        qDebug() << qry.lastError();
    else
        qDebug() << "groupe Table created!";
    qry.prepare( "INSERT INTO project_" + nameproject + "_groupe (groupname ,groupparent ,type) VALUES ( ? , ? , ? );" );
    qry.addBindValue(name);
    qry.addBindValue(QString::number(groupparent));
    qry.addBindValue(QString::number(type));
    if( !qry.exec() )
        qDebug() << qry.lastError();
    else
        qDebug() << "groupe insert success!";
    p->addgroup(name.toStdString(), groupparent, qry.lastInsertId().toInt(), type);
    return (qry.lastInsertId().toInt());
}

void    supgroup(QString nameproject, int id, vector<group> & g)
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

int    addquestion(project *p, QString name, int groupid, QString type, int note, QString description, int qgroupid)
{
    QSqlQuery qry;

    qry.prepare( ("CREATE TABLE IF NOT EXISTS project_" + p->name + "_question (id INTEGER UNIQUE PRIMARY KEY NOT NULL AUTO_INCREMENT, question VARCHAR(30), groupid INTEGER, type VARCHAR(30), note BOOLEAN DEFAULT 1, sujet VARCHAR(30), qgroupid INT DEFAULT 0, typef INT DEFAULT 0)").c_str() );
    if( !qry.exec() )
        qDebug() << qry.lastError();
    qry.prepare( ("INSERT INTO project_" + p->name + "_question (question , groupid , type , note , sujet ) VALUES ( ? , ? , ? , ? , ? );").c_str() );
    qry.addBindValue(name);
    qry.addBindValue(groupid);
    qry.addBindValue(type);
    qry.addBindValue(note);
    qry.addBindValue(description);
    if( !qry.exec() )
        qDebug() << qry.lastError();
    else
        qDebug() << "question insert success!";
    p->addquestion(name.toStdString(), groupid, qry.lastInsertId().toInt(), qgroupid, description, type);
    return (qry.lastInsertId().toInt());
}

void    supquest(QString nameproject, int id)
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
}
