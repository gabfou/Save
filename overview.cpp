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
    bar = new bargraph(syntheselistgroup(p->getgrouplist(group), p->getListquestion().size()), p);
    barref = new bargraph(syntheselistgroup(p->getgrouplistref(group), p->getListquestion().size()), p);
    bar->setName("Reel");
    barref->setName("Escompté");
    table = new tableshow(m, p, showmod);
    table->reinit();
    vector<question> listqchild =  p->questiongroupqchildnotopti(0);
    table->setverticalheader(listqchild, 0);
    table->sethorizontalheader(headertable, p->getNbgeneration());
    //table->showtable(0, 0);
    table->updateall();
    table->select(0,0);
    QHBoxLayout *hb = new QHBoxLayout(this);
    QGridLayout *gl = new QGridLayout(this);
    gl->addWidget(barref, 1, 0);
    gl->addWidget(bar, 0, 0);

    QSizePolicy sp(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sp.setHorizontalStretch(1);
    //table->setSizePolicy(sp);
    bar->setSizePolicy(sp);

    hb->addLayout(gl);
    hb->addWidget(table);
    setLayout(hb);
    //this->updateov(group);
    //this->show();
}

void overview::updateov(int group)
{
    if (*showmod == 2) // provisoire la meme au dessus
        group = 0;
	qDebug() << "updateov";
    bar->updateg(syntheselistgroup(p->getgrouplist(group), p->getListquestion().size()));
    barref->updateg(syntheselistgroup(p->getgrouplistref(group), p->getListquestion().size()));
    table->updateall();
    this->update();
}
