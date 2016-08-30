#include "alltree.h"
#include "data/group.h"
#include "data/project.h"
#include "grouptree.h"
#include "mainwindow.h"

Alltree::Alltree(MainWindow *m, project *current) : p(current)
{
    groupboxtmp = new grouptree(m, p->listgroup, 0);
    this->addTab(groupboxtmp, "groupe");
    connect(this->groupboxtmp, SIGNAL(itemClicked(QTreeWidgetItem *, int )), m, SLOT(changescope2(QTreeWidgetItem *)));

    this->addTab(new grouptree(m, p->listgroup, 2), "persone");

    groupboxtmp = new grouptree(m, p->listqgroup, 2);
    this->addTab(groupboxtmp, "question");
    connect(this->groupboxtmp, SIGNAL(itemClicked(QTreeWidgetItem *, int )), m, SLOT(changescopeq2(QTreeWidgetItem *)));
}
