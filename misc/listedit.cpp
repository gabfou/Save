#include "listedit.h"

listedit::listedit()
{
    this->preinit();
}

listedit::listedit(QStringList &str)
{
    this->preinit();
    this->init(str);
}

void listedit::preinit()
{
    list = new QListWidget();
    add = new QPushButton("Nouveaux");
    sup = new QPushButton("Suprimer");
    QHBoxLayout *hbox = new QHBoxLayout();
    hbox->addWidget(sup);
    hbox->addWidget(add);
    QVBoxLayout *vbox = new QVBoxLayout();
    vbox->addWidget(list);
    vbox->addLayout(hbox);
    connect(list, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(edit(QListWidgetItem*)));
    connect(add, SIGNAL(pressed()), this, SLOT(newitem()));
    connect(sup, SIGNAL(pressed()), this, SLOT(supitem()));
    this->setLayout(vbox);
}

void listedit::init(QStringList &str)
{
    list->clear();
    list->insertItems(0, str);
}


void listedit::edit(QListWidgetItem *item)
{
    list->openPersistentEditor(item);
    list->setCurrentItem(item);
    connect(list, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(closeedit(QListWidgetItem*)), Qt::UniqueConnection);
}

void listedit::closeedit(QListWidgetItem *item)
{
    list->closePersistentEditor(item);
}

void listedit::newitem()
{
    QListWidgetItem *newitem = new QListWidgetItem("");
    list->addItem(newitem);
    this->edit(newitem);
}

QStringList listedit::getlstr()
{
    QList<QListWidgetItem *> ltmp = list->findItems(QString("*"), Qt::MatchWrap | Qt::MatchWildcard);
    QStringList ret;

    foreach(QListWidgetItem *item, ltmp)
        ret << item->text();
    return (ret);
}

void listedit::supitem()
{
    delete list->currentItem();
}

