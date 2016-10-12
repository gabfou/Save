#include "alltree.h"
#include "data/group.h"
#include "data/project.h"
#include "grouptree.h"
#include "mainwindow.h"

Alltree::Alltree(MainWindow *m, project *current) : p(current)
{
    QTabWidget *tabgroup = new QTabWidget();
    QCheckBox *affichenongroup = new QCheckBox("Voir les non group");
    QVBoxLayout *layout = new QVBoxLayout();

    this->setLayout(layout);

    layout->addWidget(affichenongroup);

    groupboxtmp = new grouptree(m, p->listgroup, 1);
    groupboxtmp->setVisiblenongroup(0);
    groupboxtmp->resizeColumnToContents(0);
    tabgroup->addTab(groupboxtmp, "Participants");
    connect(this->groupboxtmp, SIGNAL(itemClicked(QTreeWidgetItem *, int )), m, SLOT(changescope2(QTreeWidgetItem *)));
    connect(affichenongroup, SIGNAL(toggled(bool)), groupboxtmp, SLOT(setVisiblenongroup(bool)));
    connect(affichenongroup, SIGNAL(toggled(bool)), this, SLOT(affichegroupp(bool)));

    groupboxtmp = new grouptree(m, p->listqgroup, 2);
    groupboxtmp->setVisiblenongroup(0);
    groupboxtmp->resizeColumnToContents(0);
    tabgroup->addTab(groupboxtmp, "Questionnaires");
    connect(this->groupboxtmp, SIGNAL(itemClicked(QTreeWidgetItem *, int )), m, SLOT(changescopeq2(QTreeWidgetItem *)));
    connect(affichenongroup, SIGNAL(toggled(bool)), groupboxtmp, SLOT(setVisiblenongroup(bool)));

    layout->addWidget(tabgroup);
}


void Alltree::affichegroupp(bool b)
{
    emit grouppmodechanged(b);
}
