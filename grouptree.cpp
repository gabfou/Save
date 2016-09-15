#include "grouptree.h"
#include "data/project.h"
#include "data/group.h"
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
    newqg->setVisible(false);
	if (tmp)
	{
		newg->setVisible(true);
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
		supp->setVisible(true);
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

void    grouptree::setVisiblenongroup(bool v)
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
	cotmp = connect(this, SIGNAL(itemChanged(QTreeWidgetItem *, int)), this, SLOT(addgroupintree2(QTreeWidgetItem *, int)));
	/*if (this->nametmp != NULL)
		delete this->nametmp;
	this->nametmp = new QLineEdit();

	connect(this->nametmp, SIGNAL(returnPressed()), this, SLOT(addgroupintree2()));
	connect(this->nametmp, SIGNAL(returnPressed()),  this->nametmp, SLOT(close()));
	this->nametmp->show();*/
}

void	grouptree::addgroupintree2(QTreeWidgetItem *item, int column)
{
	(void)column;
	disconnect(cotmp);
	qDebug() << item->text(0);
    int niark = addgroup(&(m->current), m->namecurrent, item->text(0), tmpid, g[tmpid].type, "");
    item->parent()->addChild(new grouptreeitem(QStringList(QString(g[niark].getName())), &(m->current), niark, g[niark].type, i, (QTreeWidget*)0));
	delete item;
	item = NULL;
	qDebug() << "upadte ?";
	m->table->reinit(&(m->current), m);
	m->table->showtable(m->currentgref, m->currentgqref);
	//m->updateproject();// actualisation necessaire mais detruit cette classe
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
    //qDebug() << item->text(0);
    int id = addquestion(&(m->current), item->text(0), 0, "", 0, "", 0, 0, 0, "", -1);
    item->parent()->addChild(new questiontreeitem(QStringList(item->text(0)) , id, (QTreeWidget*)0));

	m->table->reinit(&(m->current), m);
	m->table->showtable(m->currentgref, m->currentgqref);
	delete item;
	item = NULL;
}

void	grouptree::addquestglobintree()
{
    infoqtmp = new infoquestion(&(m->current), m, 0);
    infoqtmp->setquestionmod(dynamic_cast<grouptreeitem*>(this->currentItem())->getId());
    infoqtmp->show();

    connect(infoqtmp->b_update, SIGNAL(clicked(bool)), this, SLOT(addquestglobintree2()));
}

void	grouptree::addquestglobintree2()
{
    dynamic_cast<grouptreeitem*>(this->currentItem())->addquestglobinttree(infoqtmp->getquestioncopy());
    m->table->reinit(&(m->current), m);
    m->table->showtable(m->currentgref, m->currentgqref);
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
//	qDebug() << item->text(0);

    int id = addperson(&(m->current), item->text(0).section(" ", 0, 0), item->text(0).section(" ", 1, 1), "not defined", 0);
    item->parent()->addChild(new persontreeitem(QStringList(item->text(0)) , id, (QTreeWidget*)0));
	m->table->reinit(&(m->current), m);
	m->table->showtable(m->currentgref, m->currentgqref);
	delete item;
	item = NULL;
}

void	grouptree::supgroupintree()
{
	supgroup(m->namecurrent, dynamic_cast<grouptreeitem*>(this->currentItem())->getId(), g);
	QTreeWidgetItem *item = this->currentItem();
	delete item;
	item = NULL;
	m->table->reinit(&(m->current), m);
	m->table->showtable( m->currentgref, m->currentgqref);
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
    sqlupdate(("project_" + m->current.name + "_groupe"), "description", texttmp->toPlainText(), dynamic_cast<grouptreeitem*>(this->currentItem())->getId());
	g[dynamic_cast<grouptreeitem*>(this->currentItem())->getId()].description = texttmp->toPlainText();
}

void	grouptree::supquestintree()
{
	supquest(&(m->current), m->namecurrent, dynamic_cast<questiontreeitem*>(this->currentItem())->id);
	QTreeWidgetItem *item = this->currentItem();
	delete item;
	item = NULL;
	m->table->reinit(&(m->current), m);
	m->table->showtable(m->currentgref, m->currentgqref);
}

void	grouptree::suppersonintree()
{
	supperson(&(m->current), m->namecurrent, dynamic_cast<persontreeitem*>(this->currentItem())->id);
	QTreeWidgetItem *item = this->currentItem();
	delete item;
	item = NULL;
	m->table->reinit(&(m->current), m);
	m->table->showtable(m->currentgref, m->currentgqref);
}

grouptree::~grouptree()
{

}
