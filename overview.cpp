#include "overview.h"
#include "graph/bargraph.h"
#include "data/project.h"
#include "tableclass/tableshow.h"


overview::overview(project *p, int group) : p(p)
{    bar = new bargraph(syntheselistgroup(p->getgrouplist(group), p->getListquestion()), p);
     barref = new bargraph(syntheselistgroup(p->getgrouplistref(group), p->getListquestion()), p);
     bar->setName("Reel");
     barref->setName("Escompté");
     tableshow *table = new tableshow(p, group);
     QHBoxLayout *hb = new QHBoxLayout(this);
     QGridLayout *gl = new QGridLayout(this);
     gl->addWidget(barref, 1, 0);
     gl->addWidget(bar, 0, 0);

     QSizePolicy sp(QSizePolicy::Preferred, QSizePolicy::Preferred);
     sp.setHorizontalStretch(1);
     table->setSizePolicy(sp);
     bar->setSizePolicy(sp);

     hb->addLayout(gl);
     hb->addWidget(table);
     setLayout(hb);
    //this->updateov(group);
    //this->show();
}

void overview::updateov(int group)
{
    qDebug() << "updateov";
    bar->updateg(syntheselistgroup(p->getgrouplist(group), p->getListquestion()));
    barref->updateg(syntheselistgroup(p->getgrouplistref(group), p->getListquestion()));
    this->update();
}
