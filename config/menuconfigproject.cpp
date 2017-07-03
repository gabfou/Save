#include "menuconfigproject.h"
#include "sql/sqldatatable.h"
#include "menuconfigquestion.h"
#include "menuconfigperson.h"
#include "data/project.h"
#include "data/group.h"
#include "data/question.h"
#include "data/person.h"
#include "tableclass/tableau_brut.h"
#include "previewconfig.h"

menuconfigproject::menuconfigproject(QString name, project *p, MainWindow *m) : name(name), p(p), m(m)
{
    this->setWindowModality(Qt::ApplicationModal);
	if (name.isEmpty())
		return ;
    this->resize(700, 500);
	this->configeneral();
    this->addTab(new menuconfigperson(p, m), "Personne");
    this->addTab(new menuconfigquestion(p, m), "Question");
    this->addTab(new previewconfig(m), "preview");
	this->show();
}

// onglet general

void menuconfigproject::configeneral()
{
    QWidget *win = new QWidget;
    QPushButton *tablesql = new QPushButton("Table sql");
    QPushButton *newtq = new QPushButton("Sauvegarder un template de question");
    QPushButton *addtq = new QPushButton("Ajouter des question a partir d'un template");
    QPushButton *newtp = new QPushButton("Sauvegarder un template de personne");
    QPushButton *addtp = new QPushButton("Ajouter des personne a partir d'un template");
    QCheckBox *afficheindex = new QCheckBox("Afficher l'index");
    afficheindex->setChecked(p->indexbool);


    //Connexions aux slots
    connect(tablesql, SIGNAL(clicked(bool)), this, SLOT(showsql()));
    connect(newtq, SIGNAL(clicked(bool)), this, SLOT(newtemplateq()));
    connect(addtq, SIGNAL(clicked(bool)), this, SLOT(addtemplateq()));
    connect(newtp, SIGNAL(clicked(bool)), this, SLOT(newtemplatep()));
    connect(addtp, SIGNAL(clicked(bool)), this, SLOT(addtemplatep()));
    connect(afficheindex, SIGNAL(clicked(bool)), this, SLOT(afficheindex(bool)));

	//Layout
	QGroupBox *groupbox = new QGroupBox("");

	QGridLayout *layoutFormulaire = new QGridLayout();

	groupbox->setLayout(layoutFormulaire);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignTop);
    layout->addWidget(tablesql);
    layout->addWidget(newtq);
    layout->addWidget(addtq);
    layout->addWidget(newtp);
    layout->addWidget(addtp);
    layout->addWidget(afficheindex);
    win->setLayout(layout);
	this->addTab(win, "general");
}

// option montrer les table sql

void menuconfigproject::showsql()
{
    QTabWidget *win = new QTabWidget();

    win->addTab(new sqldatatable(QString("groupname, groupparent, type"), "project_" + this->name + "_groupe", 3), "groupe");
    win->addTab(new sqldatatable(QString("lastname, firstname, email, groupid, refbool, questionbool"), "project_" + this->name + "_project", 6), "personne");
    win->addTab(new sqldatatable(QString("question, groupid, type, note, sujet, qgroupid, typef, ref_only, splitchar"), "project_" + this->name + "_question", 9), "question");
    win->setWindowModality(Qt::ApplicationModal);
    win->show();
}

// copier les noms des question dans les description (plus necessaire) 

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

// supression des retour chariot (plus necessaire)

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

// montrer le tableaux de donnée brute

void menuconfigproject::showtableau_brut()
{
    tableau_brut *tabb = new tableau_brut(p);
    tabb->show();
}

// creation d'un template de question a partir du set courant de question (manque de test) 

void menuconfigproject::newtemplateq()
{
    createquestiontemplate(m, p);
}

// integration d'un template de question a partir du set courant de question (manque de test) 

void menuconfigproject::addtemplateq()
{
    QString fichier = QFileDialog::getOpenFileName(0, "Open a file", "~", "Excell files (*.xlsx)");
    recupquestiontemplate(fichier, p);
}

// creation d'un template de personne a partir du set courant de personne (manque de test) 

void menuconfigproject::newtemplatep()
{
    createpersonnetemplate(m, p);
}

// integration d'un template de personne a partir du set courant de personne (manque de test) 

void menuconfigproject::addtemplatep()
{
    QString fichier = QFileDialog::getOpenFileName(0, "Open a file", "~", "Excell files (*.xlsx)");
    recuppersonnetemplate(fichier, p);
}

void menuconfigproject::afficheindex(bool checked)
{
    QSqlQuery qry;

    qry.prepare( "UPDATE all_config SET indexbool = " + QString::number(checked) + " WHERE project_name='" + p->name + "';");
    if(!qry.exec())
        qDebug() << "menuconfigproject::afficheindex fail" << qry.lastError();
}
