#include "grouptree.h"
#include "project.h"
#include "group.h"
#include "grouptreeitem.h"
#include "mainwindow.h"

grouptree::grouptree()
{

}

grouptree::grouptree(MainWindow *m, vector<group> & g) : m(m)
{
	int i = -1;
	if (g.empty())
		this->addTopLevelItem(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("aucun projet ouvertt"))));
	this->addTopLevelItem(new grouptreeitem(QStringList(QString(g[0].getName().c_str())), g, 0, (QTreeWidget*)0));
    this->setContextMenuPolicy(Qt::ActionsContextMenu);
    QAction *newg = new QAction(QString("nouveaux groupe"), this);
    this->addAction(newg);
    connect(newg, SIGNAL(triggered()), this, SLOT(addgroupintree()));
}

// void	grouptree::projectgroupshow(MainWindow *main, QTableWidget *gbox, int k, int id, int *i)
// new grouptreeitem(QStringList(QString(listgroup[*listpg].getName().c_str())), listgroup, *listpg, (QTreeWidget*)0)


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
    addgroup(m->namecurrent, item->text(0), tmpid);
//    delete item;
//    item = NULL;
    qDebug() << "upadte ?";
//    m->updateproject(); actualisation necessaire mais detruit cette classe
    qDebug() << "upadte";
}


grouptree::~grouptree()
{

}
