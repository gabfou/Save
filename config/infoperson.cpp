#include "infoperson.h"
#include "data/person.h"
#include "data/project.h"
#include "persontreeitem.h"
#include "grouptreeitem.h"
#include "mainwindow.h"
#include "misc/listedit.h"
#include "grouptree.h"

// initialisation

infoperson::infoperson(MainWindow *m, project *p) : info(m)
{
    vbox = new QVBoxLayout();
    contp = new QWidget();
	name = new QLineEdit();
	lastname = new QLineEdit();
	email = new QLineEdit();
    b_update = new QPushButton("Enregistrer");
    changegroup = new QPushButton("Modifier le groupe parrent");
    
    vbox->addWidget(new QLabel("Prenoms"));
	vbox->addWidget(name);
    vbox->addWidget(new QLabel("Noms de famille"));
	vbox->addWidget(lastname);
	vbox->addWidget(new QLabel("Email"));
    vbox->addWidget(email);
    vbox->addWidget(changegroup);
    vbox->addWidget(b_update);
    contp->setLayout(vbox);
    vboxinfo->addWidget(contp);

    contp->hide();

    //slot

	cotmp = connect(b_update, SIGNAL(clicked(bool)), this, SLOT(updatebdd()));
    connect(changegroup, SIGNAL(clicked(bool)), this, SLOT(changegroupparent()));
}

// changement du groupe parent de la person pointé menu

void infoperson::changegroupparent()
{
    grouptree *gt = new grouptree(m, p->listgroup, 0);

    gt->setWindowModality(Qt::ApplicationModal);
    connect(gt, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(changegroupparent2(QTreeWidgetItem*)));
    connect(gt, SIGNAL(itemClicked(QTreeWidgetItem*,int)), gt, SLOT(close()));
    gt->show();
}

// changement du groupe parent de la person pointé

void infoperson::changegroupparent2(QTreeWidgetItem *item)
{
    grouptreeitem* tmp =  dynamic_cast<grouptreeitem*>(item);

    if (tmp)
    {
        sqlo::addperson(p, pe->firstname, pe->lastname, pe->email, tmp->getId(),pe->refbool, pe->refbool, pe->jour, pe->id);
        p->listp[pe->id].groupid = tmp->getId();
        int i = pe->id;
        delete pe;
        this->pe = new person(p->getperson(i));
    }
}

// mise a jour du menu visible

void infoperson::updateib(QTreeWidgetItem * item)
{
	persontreeitem *tmp = dynamic_cast<persontreeitem*>(item);

    this->updateibg(-1, -1);
    infolabel->setText("");
	disconnect(cotmp);

    // si c est un groupe on appelle la classe parente qui represente un groupe

	if (tmp == NULL)
	{
        grouptreeitem *tmp2 = dynamic_cast<grouptreeitem*>(item);
        if (tmp2)
        {
            contp->hide();
            this->updateibg(tmp2->getId(), 0);
            groupid = tmp2->getId();
        }
        else
        {
            infolabel->setText("Erreur: selection ilisible");
            qDebug() << "infoperson updateib dynamic cast 2 fail";
        }
		return ;
    }

    // sinon

    cotmp = connect(b_update, SIGNAL(clicked(bool)), this, SLOT(updatebdd()));
    contg->hide();
    contp->show();
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
        if (pe)
            delete pe;
        this->pe = new person(p->getperson(tmp->id));
	}
    name->setText(pe->firstname);
    lastname->setText(pe->lastname);
    email->setText(pe->email);
}

// mise a jour de la base de donnée

void infoperson::updatebdd()
{
//    char mdp[7];
//    QString mdphash;

    if (!pe && init)
	{
		QLabel *warning = new QLabel("Aucun objet selectioné");
		warning->show();
		return ;
	}
    sqlo::addperson(p, name->text(), lastname->text(), email->text(), groupid, pe->refbool, pe->questionbool, pe->jour, ((init) ? pe->id : -1));
}
