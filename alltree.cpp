#include "alltree.h"
#include "data/group.h"
#include "data/project.h"
#include "mainwindow.h"

Alltree::Alltree(MainWindow *m, project *current) : p(current)
{
    this->addTab(new grouptree(m, p->listgroup, 0), "groupe");
    this->addTab(new grouptree(m, p->listgroup, 1), "persone");
    this->addTab(new grouptree(m, p->listqgroup, 1), "question");
}
