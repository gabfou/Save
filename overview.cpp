#include "overview.h"
#include "graph/bargraph.h"
#include "data/project.h"
#include "tableclass/tableshow.h"
#include "tableclass/headertableitem.h"

//obselete upadate avec comparefdo si util

overview::overview(MainWindow *m, project *p, int group, int *showmod) : p(p), showmod(showmod)
{
    QList<headertableitem*> headertable;
    headertable.push_back(new headertableitem(p, p->listgroup[group].name, p->listgroup[group]));
    bar = new bargraph(syntheselistgroup(p->getgrouplist(group, 0)), p);
    barref = new bargraph(syntheselistgroup(p->getgrouplist(group, 0, 0, 0)), p);
    bar->setName("Reel");
    barref->setName("Escompté");
    table = new tableshow(m, p, 0);
    table->reinit();
    //QList<question> listqchild =  p->questiongroupqchildnotopti(0);
    //table->setverticalheader(listqchild, 0);
    table->sethorizontalheader(headertable, p->getNbpgeneration());
    //table->showtable(0, 0);
    table->updateall();
    //table->select(0, 0);
    QHBoxLayout *hb = new QHBoxLayout(this);
    QGridLayout *gl = new QGridLayout(this);
    gl->addWidget(barref, 1, 0);
    gl->addWidget(bar, 0, 0);

    hb->addLayout(gl, 2);
    hb->addWidget(table, 1);
    setLayout(hb);
}

void overview::updateov(int group, int qgroup)
{
    bar->updateg(syntheselistgroup(p->getgrouplist(group, qgroup)), qgroup);
    barref->updateg(syntheselistgroup(p->getgrouplist(group, qgroup, 0, 0)), qgroup);
    table->updateall();
    this->update();
}
