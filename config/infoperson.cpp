#include "infoperson.h"
#include "data/person.h"
#include "data/project.h"
#include "persontreeitem.h"
#include "grouptreeitem.h"
#include "mainwindow.h"
#include "misc/listedit.h"

infoperson::infoperson(project *p, MainWindow *m) : p(p)
{
	QVBoxLayout *vbox = new QVBoxLayout();
	name = new QLineEdit();
	lastname = new QLineEdit();
	email = new QLineEdit();
	b_update = new QPushButton("Enregistrer");
    infolabel = new QLabel("");
    
    vbox->addWidget(infolabel);
	vbox->addWidget(new QLabel("Noms"));
	vbox->addWidget(name);
	vbox->addWidget(new QLabel("Noms de fammille"));
	vbox->addWidget(lastname);
	vbox->addWidget(new QLabel("Email"));
	vbox->addWidget(email);
    vbox->addWidget(b_update);
    this->setLayout(vbox);

	//slot

	cotmp = connect(b_update, SIGNAL(clicked(bool)), this, SLOT(updatebdd()));
}

void infoperson::updateib(QTreeWidgetItem * item)
{
	persontreeitem *tmp = dynamic_cast<persontreeitem*>(item);

    infolabel->setText("");
	disconnect(cotmp);
	cotmp = connect(b_update, SIGNAL(clicked(bool)), this, SLOT(updatebdd()));
	if (tmp == NULL)
	{
        grouptreeitem *tmp2 = dynamic_cast<grouptreeitem*>(item);
        if (tmp2)
        {
            groupid = tmp2->getId();
            infolabel->setText("Groupe");
        }
        else
        {
            infolabel->setText("Erreur: selection ilisible");
            qDebug() << "infoperson updateib dynamic cast 2 fail";
        }
		return ;
    }
    grouptreeitem *tmp2 = dynamic_cast<grouptreeitem*>(item->parent());
    infolabel->setText("Utilisateur");
    groupid = tmp2->getId();
	if (tmp->id == -1)
	{
		init = 0;
		return ;
	}
	else
	{
		init = 1;
        this->pe = new person(p->getperson(tmp->id));
	}
    name->setText(pe->firstname);
    lastname->setText(pe->lastname);
    email->setText(pe->email);
}

void infoperson::updatebdd()
{
    char mdp[7];
    QString mdphash;

    if (!pe && init)
	{
		QLabel *warning = new QLabel("Aucun objet selectioné");
		warning->show();
		return ;
	}
	QSqlQuery query;
	if (init)
        query.prepare(("UPDATE project_" + p->name + "_person Set firstname=?, lastname=?, email=?, groupid=? WHERE id=?;").c_str());
	else
	{
//        query.prepare( ("CREATE TABLE IF NOT EXISTS project_" + p->name + "_person (id INTEGER UNIQUE PRIMARY KEY NOT NULL AUTO_INCREMENT, person VARCHAR(30), groupid INTEGER, type VARCHAR(30), note BOOLEAN DEFAULT 1, sujet VARCHAR(300), qgroupid INT DEFAULT 0, typef INT DEFAULT 0)").c_str() );
//		if( !query.exec() )
//			qDebug() << query.lastError();
        query.prepare( ("INSERT INTO project_" + p->name + "_person (firstname, lastname, email, groupid, password) VALUES (?, ?, ?, ?, ?);").c_str() );
	}
	query.addBindValue(name->text());
	query.addBindValue(lastname->text());
	query.addBindValue(email->text());
	query.addBindValue(groupid);
	if (init)
        query.addBindValue(pe->id);
	else
	{
        gen_random(mdp, 6);
        mdphash = "poke";
        mdphash += mdp;
        mdphash += "mon";
        query.addBindValue(mdphash);
		// fonctione pas
        //p->addperson(name->text().toStdString(), 0, query.lastInsertId().toInt(), type->currentIndex(), description->text(), unit->text());
	}
	if (!(query.exec()))
    {
		qDebug() << query.lastError();
        infolabel->setText("Un problème est survenu");
    }
    else
    {
        if (init == 0)
        {
            QSqlQuery query2;
            query2.prepare( ("INSERT INTO project_all_user (email, password, idperson, name_table) VALUES (?, ?, ?, ?);") );
            query2.addBindValue(email->text());
            query2.addBindValue(mdphash);
            query2.addBindValue(query.lastInsertId());
            query2.addBindValue((p->name).c_str());
            if (!(query2.exec()))
            {
                qDebug() << query2.lastError() << "ajout de all user fail";
                infolabel->setText("Un problème est survenu");
            }
            sendmail(email->text(), "Bonjour votre mot de passse tout au long de l'étude sera " + QString(mdp) + "\r\n");
            init = 1;
        }
        infolabel->setText("Modification enregistrée");
    }
}
