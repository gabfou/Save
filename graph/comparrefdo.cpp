#include "comparrefdo.h"
#include "bargraph.h"
#include "mainwindow.h"

Comparrefdo::Comparrefdo(MainWindow *m, int group) : m(m), group(group)
{
    QGridLayout *gl = new QGridLayout(this);
    bar = new bargraph(syntheselistgroup(m->current.getgrouplist(group)),&(m->current));
    barref = new bargraph(syntheselistgroup(m->current.getgrouplistref(group)), &(m->current));
    bar->setName("Réel");
    barref->setName("Escompté");
    gl->addWidget(barref, 1, 0);
    gl->addWidget(bar, 0, 0);

    connect(bar, SIGNAL(isclicked()), this, SLOT(donshow()));
    connect(barref, SIGNAL(isclicked()), this, SLOT(refshow()));
    connect(m, SIGNAL(gqrefchange(int)), this, SLOT(autoupdateov()));
    connect(m, SIGNAL(grefchange(int)), this, SLOT(autoupdateov()));

    setLayout(gl);
}

void Comparrefdo::autoupdateov()
{
    bar->updateg(syntheselistgroup(m->current.getgrouplist(m->currentgref, m->currentgqref)), m->currentgqref);
    barref->updateg(syntheselistgroup(m->current.getgrouplistref(m->currentgref, m->currentgqref)), m->currentgqref);
    this->update();
}

void Comparrefdo::updateov(int group, int qgroup)
{
    bar->updateg(syntheselistgroup(m->current.getgrouplist(group, qgroup)), qgroup);
    barref->updateg(syntheselistgroup(m->current.getgrouplistref(group, qgroup)), qgroup);
    this->update();
}

void Comparrefdo::refshow()
{
    if (bar->isVisible() == 0)
    {
        allshow();
        return ;
    }
    bar->hide();
    barref->show();
}

void Comparrefdo::donshow()
{
    if (barref->isVisible() == 0)
    {
        allshow();
        return ;
    }
    barref->hide();
    bar->show();
}

void Comparrefdo::allshow()
{
    bar->show();
    barref->show();
}
