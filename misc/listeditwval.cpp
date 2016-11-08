#include "listeditwval.h"
#include "listedit.h"

listeditwval::listeditwval()
{
    QVBoxLayout *vbox = new QVBoxLayout();
    QHBoxLayout *hbox = new QHBoxLayout();
    QHBoxLayout *hbox2 = new QHBoxLayout();
    int i = -1;


    add = new QPushButton("Nouveaux");
    sup = new QPushButton("Suprimer");
    hbox2->addWidget(add);
    hbox2->addWidget(sup);
    vbox->setMargin(0);
    vbox->setSpacing(0);
    vbox->setContentsMargins(0, 0, 0, 0);
    listoption = new listedit(0);
    listval = new QListWidget();
    hbox->addWidget(listoption);
    hbox->addWidget(listval);
    connect(add, SIGNAL(pressed()), listoption, SLOT(newitem()));
    conewval = connect(listoption, SIGNAL(newitemcreated()), this, SLOT(newval()));
    connect(sup, SIGNAL(pressed()), this, SLOT(supline()));
    vbox->addLayout(hbox);
    vbox->addLayout(hbox2);
    this->setLayout(vbox);
}

void listeditwval::supline()
{
    listoption->supitem();
    delete listval->item(listval->count() - 1);
}

void listeditwval::newval()
{

    QListWidgetItem* item;
    item = new QListWidgetItem(listval);
    listval->addItem(item);
    QSpinBox *val = new QSpinBox();
    item->setSizeHint(val->minimumSizeHint());
    listval->setItemWidget(item, val);
}

QStringList listeditwval::getlstr()
{
    QList<QListWidgetItem *> ltmp = listoption->list->findItems(QString("*"), Qt::MatchWrap | Qt::MatchWildcard);
    QStringList ret;
    QSpinBox *tmp;
    int row = 0;

    foreach(QListWidgetItem *item, ltmp)
    {
        tmp = dynamic_cast<QSpinBox*>(listval->itemWidget(listval->item(row++)));
        if (tmp)
        {
            ret << item->text();
            ret << tmp->text();
        }
    }
    return (ret);
}

void listeditwval::update(QStringList & l)
{
    QList<QString>::iterator i = l.begin();

    disconnect(conewval);

    listoption->list->clear();
    listval->clear();
    while(i != l.end() && i + 1 != l.end())
    {
        listoption->list->addItem(*i);
        i++;
        listval->addItem(*i);
        i++;
    }

    conewval = connect(listoption, SIGNAL(newitemcreated()), this, SLOT(newval()));
}
