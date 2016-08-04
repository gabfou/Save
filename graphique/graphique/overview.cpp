#include "overview.h"
#include "graph/bargraph.h"
#include "project.h"
#include "tableclass/tableshow.h"


overview::overview(project *p, int group) : p(p)
{
    this->updateov(group);
    //this->show();
}

void overview::updateov(int group)
{
    bargraph *bar = new bargraph(syntheselistgroup(p->getgrouplist(group), p->getListquestion()), p->getListquestion());
    bargraph *barref = new bargraph(syntheselistgroup(p->getgrouplistref(group), p->getListquestion()), p->getListquestion());
    tableshow *table = new tableshow(p, group);
    QHBoxLayout *hb = new QHBoxLayout(this);
    QGridLayout *gl = new QGridLayout(this);
    gl->addWidget(barref, 1, 0);
    gl->addWidget(bar, 0, 0);
    hb->addLayout(gl);
    hb->addWidget(table);
    setLayout(hb);
}
