#include "grouptree.h"
#include "data/project.h"
#include "data/group.h"
#include "grouptreeitem.h"
#include "mainwindow.h"
#include "questiontreeitem.h"
#include "tableclass/tableshow.h"

grouptree::grouptree(MainWindow *m, vector<group> & g, int i) : m(m) , g(g), i(i)
{
	if (g.empty())
		this->addTopLevelItem(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("Aucun projet ouvert"))));
	this->addTopLevelItem(new grouptreeitem(QStringList(QString(g[0].getName().c_str())), m->current, 0, g[0].type, i, (QTreeWidget*)0));

	// action sur clic droit
	this->setContextMenuPolicy(Qt::ActionsContextMenu);

	newg = new QAction(QString("Nouveaux"), this);
	this->addAction(newg);
	connect(newg, SIGNAL(triggered()), this, SLOT(addgroupintree()));

	supg = new QAction(QString("Suprimer"), this);
	this->addAction(supg);
	connect(supg, SIGNAL(triggered()), this, SLOT(supgroupintree()));


	newq = new QAction(QString("Nouvelle question"), this);
	this->addAction(newq);
	connect(newq, SIGNAL(triggered()), this, SLOT(addquestintree()));


	supq = new QAction(QString("Suprimer question"), this);
	this->addAction(supq);
	connect(supq, SIGNAL(triggered()), this, SLOT(supquestintree())); // pas fini

	connect(this, SIGNAL(itemSelectionChanged()), this, SLOT(contextmenuselect()));
}

// void	grouptree::projectgroupshow(MainWindow *main, QTableWidget *gbox, int k, int id, int *i)
// new grouptreeitem(QStringList(QString(listgroup[*listpg].getName().c_str())), listgroup, *listpg, (QTreeWidget*)0)

void	grouptree::contextmenuselect()
{
	grouptreeitem *tmp = dynamic_cast<grouptreeitem*>(this->currentItem());
	questiontreeitem *tmp2 = dynamic_cast<questiontreeitem*>(this->currentItem());

	newg->setVisible(false); // opti
	supg->setVisible(false);
	newq->setVisible(false);
	supq->setVisible(false);
	if (tmp)
	{
		newg->setVisible(true);
		supg->setVisible(true);
		if (g[0].type == 1)
			newq->setVisible(true);
		return ;
	}
	if (tmp2)
	{
		supq->setVisible(true);
		return ;
	}
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
	disconnect(cotmp);
	qDebug() << item->text(0);
	int niark = addgroup(m->namecurrent, item->text(0), tmpid, g[tmpid].type, m->current);
	item->parent()->addChild(new grouptreeitem(QStringList(QString(g[niark].getName().c_str())), m->current, niark, g[niark].type, i, (QTreeWidget*)0));
	delete item;
	item = NULL;
	qDebug() << "upadte ?";
	m->table->reinit((m->current), m);
    m->table->showtable(m, 0, m->currentgref, 0, m->currentgqref);
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
	cotmp = connect(this, SIGNAL(itemChanged(QTreeWidgetItem *, int)), this, SLOT(addquestintree2(QTreeWidgetItem *, int)));
	/*if (this->nametmp != NULL)
		delete this->nametmp;
	this->nametmp = new QLineEdit();

	connect(this->nametmp, SIGNAL(returnPressed()), this, SLOT(addgroupintree2()));
	connect(this->nametmp, SIGNAL(returnPressed()),  this->nametmp, SLOT(close()));
	this->nametmp->show();*/
}

void	grouptree::addquestintree2(QTreeWidgetItem *item, int column)
{
	disconnect(cotmp);
	qDebug() << item->text(0);
	item->parent()->addChild(new questiontreeitem(QStringList(item->text(0)) , -1, (QTreeWidget*)0));
	delete item;
	item = NULL;

	m->table->reinit((m->current), m);
    m->table->showtable(m, 0, m->currentgref, 0, m->currentgqref);
}

void	grouptree::supgroupintree()
{
	supgroup(m->namecurrent, dynamic_cast<grouptreeitem*>(this->currentItem())->getId(), g);
	QTreeWidgetItem *item = this->currentItem();
	delete item;
	item = NULL;
	m->table->reinit((m->current), m);
    m->table->showtable(m, 0, m->currentgref, 0, m->currentgqref);
}

void	grouptree::supquestintree()
{
	supquest(m->namecurrent, dynamic_cast<questiontreeitem*>(this->currentItem())->id);
	QTreeWidgetItem *item = this->currentItem();
	delete item;
	item = NULL;
	m->table->reinit((m->current), m);
    m->table->showtable(m, 0, m->currentgref, 0, m->currentgqref);
}

grouptree::~grouptree()
{

}
