#include "tablistedit.h"
#include "listedit.h"

tablistedit::tablistedit(int colnb)
{
    QVBoxLayout *vbox = new QVBoxLayout();
    QHBoxLayout *hbox = new QHBoxLayout();
    QHBoxLayout *hbox2 = new QHBoxLayout();
    listedit *tmp2;
    int i = -1;


    add = new QPushButton("Nouveaux");
    sup = new QPushButton("Suprimer");
    hbox2->addWidget(add);
    hbox2->addWidget(sup);
    vbox->setMargin(0);
    vbox->setSpacing(0);
    vbox->setContentsMargins(0, 0, 0, 0);
    while (++i < colnb)
    {
        listedit *tmp = new listedit(0);
        list.push_back(tmp);
        hbox->addWidget(tmp);
        if (i == 0)
            connect(add, SIGNAL(pressed()), tmp, SLOT(newitem()));
        else
            connect(tmp2, SIGNAL(newitemcreated()), tmp, SLOT(newitem()));
        connect(sup, SIGNAL(pressed()), tmp, SLOT(supitem()));
        tmp2 = tmp;
    }
    vbox->addLayout(hbox);
    vbox->addLayout(hbox2);
    this->setLayout(vbox);
}

QStringList tablistedit::getlstr() // segfault
{
    QList<QListWidgetItem *>::iterator *ltmp = new QList<QListWidgetItem *>::iterator[list.size()];
    QList<listedit*>::iterator listle;
    int size = 0;
    QStringList ret;

    int i = 0;

    listle = list.begin();
    i = -1;
    while(listle != list.end())
    {
        ltmp[++i] = (*listle)->list->findItems(QString("*"), Qt::MatchWrap | Qt::MatchWildcard).begin();
        listle++;
        size++;
    }
    while (size-- > 0)
    {
        i = -1;
        while(++i < list.size())
        {
            ret << (*(ltmp[i]))->text();
            ltmp[i]++;
        }
    }
    delete ltmp;
    return (ret);
}
