#include "grouptree.h"
#include "data/project.h"
#include "data/group.h"
#include "data/person.h"
#include "data/question.h"
#include "grouptreeitem.h"
#include "mainwindow.h"
#include "questiontreeitem.h"
#include "persontreeitem.h"
#include "tableclass/tableshow.h"
#include "config/infoquestion.h"

grouptree::grouptree(MainWindow *m, vector<group> & g, int i) : g(g), m(m), i(i)
{
	if (g.empty())
		this->addTopLevelItem(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("Aucun projet ouvert"))));
	this->addTopLevelItem(new grouptreeitem(QStringList(QString(g[0].getName())), &(m->current), 0, g[0].type, i, (QTreeWidget*)0));

	this->setCurrentItem(this->topLevelItem(0));

	// action sur clic droit
	this->setContextMenuPolicy(Qt::ActionsContextMenu);

	newg = new QAction(QString("Nouveaux"), this);
	this->addAction(newg);
	connect(newg, SIGNAL(triggered()), this, SLOT(addgroupintree()));

	newqg = new QAction(QString("Nouvelle question globale"), this);
	this->addAction(newqg);
	connect(newqg, SIGNAL(triggered()), this, SLOT(addquestglobintree()));

	supg = new QAction(QString("Suprimer"), this);
	this->addAction(supg);
	connect(supg, SIGNAL(triggered()), this, SLOT(supgroupintree()));

	modifdg = new QAction(QString("Modifier description"), this);
	this->addAction(modifdg);
	connect(modifdg, SIGNAL(triggered()), this, SLOT(modifdgroupintree()));

	newq = new QAction(QString("Nouvelle question"), this);
	this->addAction(newq);
	connect(newq, SIGNAL(triggered()), this, SLOT(addquestintree()));

	supq = new QAction(QString("Suprimer question"), this);
	this->addAction(supq);
	connect(supq, SIGNAL(triggered()), this, SLOT(supquestintree())); // pas fini

	newp = new QAction(QString("Nouvelle personne"), this);
	this->addAction(newp);
	connect(newp, SIGNAL(triggered()), this, SLOT(addpersonintree()));

	supp = new QAction(QString("Suprimer personne"), this);
	this->addAction(supp);
	connect(supp, SIGNAL(triggered()), this, SLOT(suppersonintree()));

	persinit = new QAction(QString("initialiser personne"), this);
	this->addAction(persinit);
	connect(persinit, SIGNAL(triggered()), this, SLOT(initpersonintree()));

    copie = new QAction(QString("copier"), this);
    this->addAction(copie);
    connect(copie, SIGNAL(triggered()), this, SLOT(copieintree()));

    paste = new QAction(QString("coller"), this);
    this->addAction(paste);
    connect(paste, SIGNAL(triggered()), this, SLOT(pastintree()));

    connect(this, SIGNAL(itemSelectionChanged()), this, SLOT(contextmenuselect()));
	contextmenuselect();
}

// void	grouptree::projectgroupshow(MainWindow *main, QTableWidget *gbox, int k, int id, int *i)
// new grouptreeitem(QStringList(QString(listgroup[*listpg].getName().c_str())), listgroup, *listpg, (QTreeWidget*)0)

void	grouptree::contextmenuselect()
{
	grouptreeitem *tmp = dynamic_cast<grouptreeitem*>(this->currentItem());
	questiontreeitem *tmp2 = dynamic_cast<questiontreeitem*>(this->currentItem());
	persontreeitem *tmp3 = dynamic_cast<persontreeitem*>(this->currentItem());

	newg->setVisible(false); // opti
	supg->setVisible(false);
	newq->setVisible(false);
	supq->setVisible(false);
	newp->setVisible(false);
	supp->setVisible(false);
	modifdg->setVisible(false);
	persinit->setVisible(false);
	newqg->setVisible(false);
	if (tmp)
	{
        emit selectgroupchange(tmp->getId());
		newg->setVisible(true);
		if (tmp->getId() > 0)
			supg->setVisible(true);
		modifdg->setVisible(true);
		if (g[0].type == 1 && i == 1)
		{
			newqg->setVisible(true);
			newq->setVisible(true);
		}
		else if (g[0].type == 0 && i == 1)
			newp->setVisible(true);
		return ;
	}
	else if (tmp2 && i == 1)
	{
		supq->setVisible(true);
		return ;
	}
	else if (tmp3 && i == 1)
	{
		persinit->setVisible(true);
		supp->setVisible(true);
		return ;
	}
}

void	grouptree::initpersonintree()
{
	char mdp[7];
	QSqlQuery qry;

	int id = (dynamic_cast<persontreeitem*>(this->currentItem())->id);
	QString email = m->current.listp[id].email;

	gen_random(mdp, 6);
	QString mdphash = "poke";
	mdphash += mdp;
	mdphash += "mon";

	qry.prepare(("UPDATE project_" + m->current.name + "_project Set password=? WHERE id=?;"));

	qry.addBindValue(QCryptographicHash::hash(mdphash.toUtf8(), QCryptographicHash::Sha384).toHex());
	qry.addBindValue(id);
	if (!qry.exec())
	{
		qDebug() << qry.lastError() << "grouptree::initpersonintree";
		return ;
	}
	sendmail(email, "Bonjour votre mot de passse tout au long de l'étude sera " + QString(mdp) + "\r\n");
	qry.prepare( ("INSERT INTO project_all_user (idperson, email, password, name_table) VALUES ( ? , ? , ? , ? );") );
	qry.addBindValue(id);
	qry.addBindValue(email);
	qry.addBindValue(QCryptographicHash::hash(mdphash.toUtf8(), QCryptographicHash::Sha384).toHex());
	qry.addBindValue(m->current.name);
	if (!qry.exec())
	{
		qDebug() << qry.lastError() << "grouptree::initpersonintree 2";
		return ;
	}
}

void grouptree::setcurrentgroup(int id, QTreeWidgetItem *dontgiveit)
{
	grouptreeitem *tmp;

	if (dontgiveit == NULL)
	{
		dontgiveit = this->topLevelItem(0);
	}
	tmp = dynamic_cast<grouptreeitem*>(dontgiveit);
	if (tmp && tmp->getId() == id)
		this->setCurrentItem(dontgiveit);
	for(int i = 0; i < dontgiveit->childCount(); ++i)
		setcurrentgroup(id, dontgiveit->child(i));
}

void	grouptree::setVisiblenongroup(bool v)
{
		dynamic_cast<grouptreeitem*>(this->topLevelItem(0))->setVisiblenongroup(v);
}

void	grouptree::addgroupintree()
{
	//QWidget *win = new QWidget();
	this->tmp = new QTreeWidgetItem((QTreeWidget*)0);
	this->currentItem()->addChild(this->tmp);
	this->openPersistentEditor(this->tmp);
	this->tmpid = dynamic_cast<grouptreeitem*>(this->currentItem())->getId();
	this->setCurrentItem(this->tmp);
	cotmp = connect(this, SIGNAL(itemChanged(QTreeWidgetItem *, int)), this, SLOT(addgroupintree2(QTreeWidgetItem *)), Qt::UniqueConnection);
	/*if (this->nametmp != NULL)
		delete this->nametmp;
	this->nametmp = new QLineEdit();

	connect(this->nametmp, SIGNAL(returnPressed()), this, SLOT(addgroupintree2()));
	connect(this->nametmp, SIGNAL(returnPressed()),  this->nametmp, SLOT(close()));
	this->nametmp->show();*/
}

void	grouptree::addgroupintree2(QTreeWidgetItem *item)
{
	disconnect(cotmp);
	qDebug() << item->text(0);
    int niark = sqlo::addgroup(&(m->current), m->namecurrent, item->text(0), tmpid, g[tmpid].type, item->text(0), 0);
	item->parent()->addChild(new grouptreeitem(QStringList(QString(g[niark].getName())), &(m->current), niark, g[niark].type, i, (QTreeWidget*)0));
	delete item;
	item = NULL;
	qDebug() << "upadte ?";
	m->updatetable();
	qDebug() << "upadte";
}

void	grouptree::addquestintree()
{
	//QWidget *win = new QWidget();
	this->tmp = new QTreeWidgetItem((QTreeWidget*)0);
	this->currentItem()->addChild(this->tmp);
	this->openPersistentEditor(this->tmp);
	this->tmpid = dynamic_cast<grouptreeitem*>(this->currentItem())->getId();
	this->setCurrentItem(this->tmp);
	cotmp = connect(this, SIGNAL(itemChanged(QTreeWidgetItem *, int)), this, SLOT(addquestintree2(QTreeWidgetItem *, int)), Qt::UniqueConnection);
	/*if (this->nametmp != NULL)
		delete this->nametmp;
	this->nametmp = new QLineEdit();

	connect(this->nametmp, SIGNAL(returnPressed()), this, SLOT(addgroupintree2()));
	connect(this->nametmp, SIGNAL(returnPressed()),  this->nametmp, SLOT(close()));
	this->nametmp->show();*/
}

void	grouptree::addquestintree2(QTreeWidgetItem *item, int column)
{
	Q_UNUSED(column);
	//qDebug() << item->text(0);
	disconnect(cotmp);
    int id = sqlo::addquestion(&(m->current), item->text(0), 0, "", 0, item->text(0), dynamic_cast<grouptreeitem*>(item->parent())->getId(), 0, 0, "", 1, 0, -1);
	item->parent()->addChild(new questiontreeitem(QStringList(item->text(0)) , id, (QTreeWidget*)0));

	m->updatetable();
	delete item;
	item = NULL;
}

void	grouptree::addquestglobintree()
{
    infoqtmp = new infoquestion(&(m->current), m, 0);
	infoqtmp->setquestionmod(dynamic_cast<grouptreeitem*>(this->currentItem())->getId());
    infoqtmp->setWindowModality(Qt::ApplicationModal);
	infoqtmp->show();

	connect(infoqtmp->b_update, SIGNAL(clicked(bool)), this, SLOT(addquestglobintree2()));
}

void	grouptree::addquestglobintree2()
{
	dynamic_cast<grouptreeitem*>(this->currentItem())->addquestglobinttree(infoqtmp->getquestioncopy());
    delete infoqtmp;
	m->updatetable();
}

void	grouptree::addpersonintree()
{
	//QWidget *win = new QWidget();
	this->tmp = new QTreeWidgetItem((QTreeWidget*)0);
	this->currentItem()->addChild(this->tmp);
	this->openPersistentEditor(this->tmp);
	this->tmpid = dynamic_cast<grouptreeitem*>(this->currentItem())->getId();
	this->setCurrentItem(this->tmp);
	cotmp = connect(this, SIGNAL(itemChanged(QTreeWidgetItem *, int)), this, SLOT(addpersonintree2(QTreeWidgetItem *, int)), Qt::UniqueConnection);
	/*if (this->nametmp != NULL)
		delete this->nametmp;
	this->nametmp = new QLineEdit();

	connect(this->nametmp, SIGNAL(returnPressed()), this, SLOT(addgroupintree2()));
	connect(this->nametmp, SIGNAL(returnPressed()),  this->nametmp, SLOT(close()));
	this->nametmp->show();*/
}

void	grouptree::addpersonintree2(QTreeWidgetItem *item, int column)
{
	qDebug() << item->text(0);

	disconnect(cotmp);
	int id = sqlo::addperson(&(m->current), item->text(0).section(" ", 0, 0), item->text(0).section(" ", 1, 1), "not defined", dynamic_cast<grouptreeitem*>(item->parent())->getId());
	item->parent()->addChild(new persontreeitem(QStringList(item->text(0)) , id, (QTreeWidget*)0));
	m->updatetable();
	delete item;
	item = NULL;
}

void	grouptree::supgroupintree()
{
	if (dynamic_cast<grouptreeitem*>(this->currentItem())->getId() < 1)
		return ;
	sqlo::supgroup(m->namecurrent, dynamic_cast<grouptreeitem*>(this->currentItem())->getId(), g);
	QTreeWidgetItem *item = this->currentItem();
	delete item;
	item = NULL;
	if (m->table)
	{
		m->table->reinit(&(m->current), m);
		m->table->showtable( m->currentgref, m->currentgqref);
	}
}

void	grouptree::modifdgroupintree()
{
	QWidget *win = new QWidget();
	QLabel *Labeldescription = new QLabel("Description");
	this->texttmp = new QPlainTextEdit(g[dynamic_cast<grouptreeitem*>(this->currentItem())->getId()].description, win);
	Labeldescription->setAlignment(Qt::AlignTop);

	//Boutons
	QPushButton *b_valider = new QPushButton("Valider");

	//Connexions aux slots
	connect(b_valider, SIGNAL(clicked()), this, SLOT(modifdgroupintree2()));
	connect(b_valider, SIGNAL(clicked()), win, SLOT(close()));

	QVBoxLayout *layoutFormulaire = new QVBoxLayout(this);
	layoutFormulaire->addWidget(Labeldescription);
	layoutFormulaire->addWidget(this->texttmp);
	layoutFormulaire->addWidget(b_valider);

	win->setLayout(layoutFormulaire);
	win->show();
}

void	grouptree::modifdgroupintree2()
{
	sqlo::sqlupdate(("project_" + m->current.name + "_groupe"), "description", texttmp->toPlainText(), dynamic_cast<grouptreeitem*>(this->currentItem())->getId());
	g[dynamic_cast<grouptreeitem*>(this->currentItem())->getId()].description = texttmp->toPlainText();
}

void	grouptree::supquestintree()
{
	sqlo::supquest(&(m->current), m->namecurrent, dynamic_cast<questiontreeitem*>(this->currentItem())->id);
	QTreeWidgetItem *item = this->currentItem();
	delete item;
	item = NULL;
	m->updatetable();
}

void	grouptree::suppersonintree()
{
	sqlo::supperson(&(m->current), m->namecurrent, dynamic_cast<persontreeitem*>(this->currentItem())->id);
	QTreeWidgetItem *item = this->currentItem();
	delete item;
	item = NULL;
	m->updatetable();
}

void    grouptree::copieintree()
{
    grouptreeitem *tmp = dynamic_cast<grouptreeitem*>(this->currentItem());
    questiontreeitem *tmp2 = dynamic_cast<questiontreeitem*>(this->currentItem());
    persontreeitem *tmp3 = dynamic_cast<persontreeitem*>(this->currentItem());
    copietype = -1;

    if (tmp)
    {
        copietype = 0;
        if (g[0].type == 1)
            copieg = m->current.listqgroup[tmp->getId()];
        else if (g[0].type == 0)
            copieg = m->current.listgroup[tmp->getId()];
    }
    else if (tmp2)
    {
        copietype = 2;
        copieq = m->current.listquestion[tmp2->id];
    }
    else if (tmp3)
    {
        copietype = 1;
        copiep = m->current.listp[tmp2->id];
    }
}

void    grouptree::pastintree()
{
    grouptreeitem *tmp = dynamic_cast<grouptreeitem*>(this->currentItem());

    if (!tmp)
        return ;
    if (copietype == 1)
    {
        int id = sqlo::addperson(&(m->current), copiep.firstname, copiep.lastname, copiep.email, tmp->getId());
        this->currentItem()->addChild(new persontreeitem(QStringList(copiep.firstname + " " + copiep.lastname) , id, (QTreeWidget*)0));
        m->updatetable();
    }
    else if (copietype == 0)
    {
        int id = sqlo::addgroup(&(m->current), m->namecurrent, copieg.name, tmp->getId(), copieg.type, copieg.description, copieg.gquestion);
        this->currentItem()->addChild(new grouptreeitem(QStringList(copieg.name), &(m->current), id));
        m->updatetable();
    }
    else if (copietype == 2)
    {
        int id = sqlo::addquestion(&(m->current), copieq.name, copieq.group, copieq.unit, copieq.note, copieq.sujet, tmp->getId(), copieq.type, copieq.ref_only, copieq.liststr.join("\n"), copieq.val, copieq.global);
        this->currentItem()->addChild(new questiontreeitem(QStringList(copieq.name) , tmp->getId(), (QTreeWidget*)0));
        m->updatetable();
    }

}

grouptree::~grouptree()
{

}
