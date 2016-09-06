#include "overview.h"
#include "graph/bargraph.h"
#include "data/project.h"
#include "tableclass/tableshow.h"
#include "tableclass/headertableitem.h"


overview::overview(MainWindow *m, project *p, int group, int *showmod) : p(p), showmod(showmod)
{
    if (*showmod == 2) // provisoire la meme en dessous
        group = 0;
    QList<headertableitem*> headertable;
    headertable.push_back(new headertableitem(p, p->listgroup[group].name.c_str(), p->listgroup[group]));
    bar = new bargraph(syntheselistgroup(p->getgrouplist(group)), p, m);
    barref = new bargraph(syntheselistgroup(p->getgrouplistref(group)), p, m);
    bar->setName("Reel");
    barref->setName("Escompté");
    table = new tableshow(m, p, showmod);
    table->reinit();
    vector<question> listqchild =  p->questiongroupqchildnotopti(0);
    table->setverticalheader(listqchild, 0);
    table->sethorizontalheader(headertable, p->getNbgeneration());
    //table->showtable(0, 0);
    table->updateall();
    table->select(0, 0);
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
//    if (*showmod == 2) // provisoire la meme au dessus
//        group = 0;
	qDebug() << "updateov";
    bar->updateg(syntheselistgroup(p->getgrouplist(group, qgroup)), qgroup);
    barref->updateg(syntheselistgroup(p->getgrouplistref(group, qgroup)), qgroup);
    table->updateall();
    this->update();
}
