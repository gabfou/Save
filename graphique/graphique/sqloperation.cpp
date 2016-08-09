#include "le.h"
#include "group.h"

void    addgroup(QString nameproject, QString name, int groupparent, int type)
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
