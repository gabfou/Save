#include "menuconfigproject.h"
#include "sql/sqldatatable.h"
#include "menuconfigquestion.h"
#include "menuconfigperson.h"
#include "data/project.h"
#include "data/group.h"
#include "data/question.h"
#include "data/person.h"

menuconfigproject::menuconfigproject(QString name, project *p, MainWindow *m) : name(name), p(p)
{
	//QLabel *Labelgroup = new QLabel("group :");
	//this->groupboxtmp = new grouptree(this->current);
	//Labelgroup->setAlignment(Qt::AlignTop);

	//Boutons
	//this->tab = new QTabWidget(this);
	if (name.isEmpty())
		return ;
    this->resize(700, 500);
	this->configeneral();
    this->addTab(new menuconfigperson(p, m), "Personne");
    this->addTab(new menuconfigquestion(p, m), "Question");
	this->show();
}

// onglet general

void menuconfigproject::configeneral()
{
	QWidget *win = new QWidget;
	QPushButton *b_valider = new QPushButton("Valider");
	QPushButton *b_actualiser = new QPushButton("Actualiser");
	QPushButton *b_annuler = new QPushButton("Fermer");
    QPushButton *tablesql = new QPushButton("table sql");
    QPushButton *sup_retour_chariot = new QPushButton("suprimer retour chariot");
    QPushButton *noms_to_description = new QPushButton("noms to description");

	//Connexions aux slots
	//connect(b_valider, SIGNAL(clicked()), this, SLOT(changescope2()));
	connect(b_annuler, SIGNAL(clicked()), this, SLOT(close()));
    connect(tablesql, SIGNAL(clicked(bool)), this, SLOT(showsql()));
    connect(sup_retour_chariot, SIGNAL(clicked(bool)), this, SLOT(sup_retour_chariot()));
    connect(noms_to_description, SIGNAL(clicked(bool)), this, SLOT(noms_to_description()));

	//Layout
	QGroupBox *groupbox = new QGroupBox("");

	QGridLayout *layoutFormulaire = new QGridLayout();
	//layoutFormulaire->addWidget(Labelgroup, 1, 0);
	//layoutFormulaire->addWidget(this->groupboxtmp, 1, 1);

	groupbox->setLayout(layoutFormulaire);

	QGridLayout *layout = new QGridLayout();
	layout->setAlignment(Qt::AlignTop);
    layout->addWidget(groupbox, 0, 0, 3, 3, Qt::AlignTop);
	//QGroupBox *gr = new QGroupBox("");
  //  layout->addWidget(b_annuler, 1, 0, Qt::AlignRight);
  //  layout->addWidget(b_actualiser, 1, 1, Qt::AlignRight);
  //  layout->addWidget(b_valider, 1, 2, Qt::AlignRight);
    layout->addWidget(tablesql, 2, 2, Qt::AlignCenter);
    layout->addWidget(sup_retour_chariot, 3, 2, Qt::AlignCenter);
    layout->addWidget(noms_to_description, 1, 1, Qt::AlignCenter);
	//setLayout(layout);
	win->setLayout(layout);
	this->addTab(win, "general");
}

void menuconfigproject::showsql()
{
    QTabWidget *win = new QTabWidget();

    win->addTab(new sqldatatable(QString("groupname, groupparent, type"), "project_" + this->name + "_groupe", 3), "groupe");
    win->addTab(new sqldatatable(QString("lastname, firstname, email, groupid, refbool, questionbool"), "project_" + this->name + "_project", 6), "personne");
    win->addTab(new sqldatatable(QString("question, groupid, type, note, sujet, qgroupid, typef, ref_only, splitchar"), "project_" + this->name + "_question", 9), "question");
    win->show();
}

// onglet groupe

void menuconfigproject::configgroupe()
{
	/*QWidget *win = new QWidget;
	QPushButton *b_valider = new QPushButton("Valider");
	QPushButton *b_actualiser = new QPushButton("Actualiser");
	QPushButton *b_annuler = new QPushButton("Fermer");

	//Connexions aux slots
	//connect(b_valider, SIGNAL(clicked()), this, SLOT(changescope2()));
	connect(b_annuler, SIGNAL(clicked()), this, SLOT(close()));

	//Layout
	QGroupBox *groupbox = new QGroupBox("");

	QGridLayout *layoutFormulaire = new QGridLayout();
	//layoutFormulaire->addWidget(Labelgroup, 1, 0);
	//layoutFormulaire->addWidget(this->groupboxtmp, 1, 1);

	groupbox->setLayout(layoutFormulaire);
	QGridLayout *layout = new QGridLayout();
	layout->setAlignment(Qt::AlignTop);
	layout->addWidget(new sqldatatable(QString("groupname, parrent"), "project_" + this->name + "_groupe", 2), 0, 0, 1, 2, Qt::AlignTop);
	layout->addWidget(b_annuler, 1, 0, Qt::AlignLeft);
	layout->addWidget(b_actualiser, 1, 1, Qt::AlignRight);
	layout->addWidget(b_valider, 1, 2, Qt::AlignRight);
	//setLayout(layout);
	win->setLayout(layout);*/
	this->addTab(new sqldatatable(QString("groupname, groupparent"), "project_" + this->name + "_groupe", 2), "groupe");
}

void menuconfigproject::noms_to_description()
{
    QSqlQuery query;
    QSqlQuery query2;

    if(query.exec(("SELECT groupname, id FROM project_" + p->name + "_groupe")))
    {
        while(query.next())
        {
            query2.prepare("UPDATE project_" + p->name + "_groupe Set description=? WHERE id=?;");
            query2.addBindValue(query.value(0).toString());
            query2.addBindValue(query.value(1).toInt());
            query2.exec();
        }
    }
    else
        qDebug() << "error menuconfigproject::noms_to_description :" << query.lastError();
}

void menuconfigproject::sup_retour_chariot()
{
    int i = -1;
    QSqlQuery qry;

    while (++i < p->listgroup.size())
    {
        if (p->listgroup[i].init)
        {
            p->listgroup[i].name.remove('\n');
            qry.prepare("UPDATE project_" + p->name + "_groupe Set groupname=? WHERE id=?;");
            qry.addBindValue(p->listgroup[i].name);
            qry.addBindValue(i);
            if (!(qry.exec()))
                qDebug() << qry.lastError();
        }
    }
    i = -1;
    while (++i < p->listqgroup.size())
    {
        if (p->listqgroup[i].init)
        {
            p->listqgroup[i].name.remove('\n');
            qry.prepare("UPDATE project_" + p->name + "_groupe Set groupname=? WHERE id=?;");
            qry.addBindValue(p->listqgroup[i].name);
            qry.addBindValue(i);
            if (!(qry.exec()))
                qDebug() << qry.lastError();
        }
    }
}
