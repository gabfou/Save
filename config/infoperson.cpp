#include "infoperson.h"
#include "data/person.h"
#include "data/project.h"
#include "persontreeitem.h"
#include "grouptreeitem.h"
#include "mainwindow.h"
#include "misc/listedit.h"

infoperson::infoperson(project *p, MainWindow *m) : info(p)
{
    vbox = new QVBoxLayout();
    contp = new QWidget();
	name = new QLineEdit();
	lastname = new QLineEdit();
	email = new QLineEdit();
    b_update = new QPushButton("Enregistrer");
    
    vbox->addWidget(new QLabel("Noms"));
	vbox->addWidget(name);
	vbox->addWidget(new QLabel("Noms de fammille"));
	vbox->addWidget(lastname);
	vbox->addWidget(new QLabel("Email"));
	vbox->addWidget(email);
    vbox->addWidget(b_update);
    contp->setLayout(vbox);
    vboxinfo->addWidget(contp);

	//slot

	cotmp = connect(b_update, SIGNAL(clicked(bool)), this, SLOT(updatebdd()));
}

void infoperson::updateib(QTreeWidgetItem * item)
{
	persontreeitem *tmp = dynamic_cast<persontreeitem*>(item);

    this->updateibg(-1, -1);
    infolabel->setText("");
	disconnect(cotmp);
	if (tmp == NULL)
	{
        grouptreeitem *tmp2 = dynamic_cast<grouptreeitem*>(item);
        if (tmp2)
        {
            contp->hide();
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
    addperson(p, name->text(), lastname->text(), email->text(), groupid, ((init) ? pe->id : -1));
}
