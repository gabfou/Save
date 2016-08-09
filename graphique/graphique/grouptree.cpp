#include "grouptree.h"
#include "project.h"
#include "group.h"
#include "grouptreeitem.h"
#include "mainwindow.h"

grouptree::grouptree(MainWindow *m, vector<group> & g, int i) : m(m) , g(g)
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

    connect(this, SIGNAL(itemSelectionChanged()), this, SLOT(contextmenuselect()));
}

// void	grouptree::projectgroupshow(MainWindow *main, QTableWidget *gbox, int k, int id, int *i)
// new grouptreeitem(QStringList(QString(listgroup[*listpg].getName().c_str())), listgroup, *listpg, (QTreeWidget*)0)

void    grouptree::contextmenuselect()
{
    grouptreeitem *tmp = dynamic_cast<grouptreeitem*>(this->currentItem());

    newg->setVisible(false); // opti
    supg->setVisible(false);
    if (tmp)
    {
        newg->setVisible(true);
        supg->setVisible(true);
        return ;
    }
}

void    grouptree::addgroupintree()
{
    //QWidget *win = new QWidget();
    this->tmp = new QTreeWidgetItem((QTreeWidget*)0);
    this->currentItem()->addChild(this->tmp);
    this->openPersistentEditor(this->tmp);
    this->tmpid = dynamic_cast<grouptreeitem*>(this->currentItem())->getId();
    this->setCurrentItem(this->tmp);
    connect(this, SIGNAL(itemChanged(QTreeWidgetItem *, int)), this, SLOT(addgroupintree2(QTreeWidgetItem *, int)));
    /*if (this->nametmp != NULL)
        delete this->nametmp;
    this->nametmp = new QLineEdit();

    connect(this->nametmp, SIGNAL(returnPressed()), this, SLOT(addgroupintree2()));
    connect(this->nametmp, SIGNAL(returnPressed()),  this->nametmp, SLOT(close()));
    this->nametmp->show();*/
}

void    grouptree::addgroupintree2(QTreeWidgetItem *item, int column)
{
    qDebug() << item->text(0);
    addgroup(m->namecurrent, item->text(0), tmpid, g[tmpid].type);
    delete item;
    item = NULL;
    qDebug() << "upadte ?";
    //m->updateproject();// actualisation necessaire mais detruit cette classe
    qDebug() << "upadte";
}

void    grouptree::supgroupintree()
{
    supgroup(m->namecurrent, dynamic_cast<grouptreeitem*>(this->currentItem())->getId(), g);
    QTreeWidgetItem *item = this->currentItem();
    delete item;
    item = NULL;
}

grouptree::~grouptree()
{

}
