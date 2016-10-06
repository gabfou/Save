#include "menuconfigproject.h"
#include "sql/sqldatatable.h"
#include "menuconfigquestion.h"
#include "menuconfigperson.h"
#include "data/project.h"
#include "data/group.h"
#include "data/question.h"
#include "data/person.h"
#include "tableclass/tableau_brut.h"

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
    QPushButton *sup_retour_chariot = new QPushButton("suprimer retour chariot dans base de donnée");
    QPushButton *noms_to_description = new QPushButton("copier les noms vers les descriptions pour les questions");
    QPushButton *showtableau_brut = new QPushButton("generer tableaux brut");

	//Connexions aux slots
	//connect(b_valider, SIGNAL(clicked()), this, SLOT(changescope2()));
	connect(b_annuler, SIGNAL(clicked()), this, SLOT(close()));
    connect(tablesql, SIGNAL(clicked(bool)), this, SLOT(showsql()));
    connect(sup_retour_chariot, SIGNAL(clicked(bool)), this, SLOT(sup_retour_chariot()));
    connect(noms_to_description, SIGNAL(clicked(bool)), this, SLOT(noms_to_description()));
    connect(showtableau_brut, SIGNAL(clicked(bool)), this, SLOT(showtableau_brut()));

	//Layout
	QGroupBox *groupbox = new QGroupBox("");

	QGridLayout *layoutFormulaire = new QGridLayout();
	//layoutFormulaire->addWidget(Labelgroup, 1, 0);
	//layoutFormulaire->addWidget(this->groupboxtmp, 1, 1);

	groupbox->setLayout(layoutFormulaire);

    QVBoxLayout *layout = new QVBoxLayout();
	layout->setAlignment(Qt::AlignTop);
    //layout->addWidget(groupbox);
    layout->addWidget(tablesql);
    layout->addWidget(sup_retour_chariot);
    layout->addWidget(noms_to_description);
    layout->addWidget(showtableau_brut);
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

void menuconfigproject::showtableau_brut()
{
    tableau_brut *tabb = new tableau_brut(p);
    tabb->show();
}
