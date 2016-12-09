#include "menusondage.h"
#include "grouptree.h"
#include "mainwindow.h"
#include "config/menuconfigsondage.h"
#include "data/project.h"
#include "data/group.h"

menusondage::menusondage(MainWindow *m)
{
    this->setWindowModality(Qt::ApplicationModal);

    QHBoxLayout *hbox = new QHBoxLayout();

    grouptree *gt = new grouptree(m, m->current.listgroup, 2);
    menuconfigsondage *mcs = new menuconfigsondage(m, gt);

    hbox->addWidget(gt, 1);
    hbox->addWidget(mcs, 3);

    this->setLayout(hbox);
}
