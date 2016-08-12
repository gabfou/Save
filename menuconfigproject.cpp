#include "menuconfigproject.h"
#include "sql/sqldatatable.h"
#include "menuconfigquestion.h"
#include "data/project.h"

menuconfigproject::menuconfigproject(QString name, project *p, MainWindow *m) : name(name)
{
    //QLabel *Labelgroup = new QLabel("group :");
    //this->groupboxtmp = new grouptree(this->current);
    //Labelgroup->setAlignment(Qt::AlignTop);

    //Boutons
    //this->tab = new QTabWidget(this);
    if (name.isEmpty())
        return ;
    this->configeneral();
    this->addTab(new sqldatatable(QString("groupname, groupparent, type"), "project_" + this->name + "_groupe", 3), "groupe");
    this->addTab(new sqldatatable(QString("lastname, firstname, email, groupid"), "project_" + this->name + "_project", 4), "personne");
    this->addTab(new menuconfigquestion(p, m), "question");
    this->show();
}

// onglet general

void menuconfigproject::configeneral()
{
    QWidget *win = new QWidget;
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
    layout->addWidget(groupbox, 0, 0, 1, 3, Qt::AlignTop);
    //QGroupBox *gr = new QGroupBox("");
    layout->addWidget(b_annuler, 1, 0, Qt::AlignRight);
    layout->addWidget(b_actualiser, 1, 1, Qt::AlignRight);
    layout->addWidget(b_valider, 1, 2, Qt::AlignRight);
    //setLayout(layout);
    win->setLayout(layout);
    this->addTab(win, "general");
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
