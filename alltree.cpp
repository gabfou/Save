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
    QSlider *slidemax = new QSlider(Qt::Horizontal);
    QLabel *labelslidemax = new QLabel("jour maximum");
    QSlider *slidemin = new QSlider(Qt::Horizontal);
    QLabel *labelslidemin = new QLabel("jour minimum");
    slidemin->setMinimum(0);
    slidemax->setMinimum(0);
    slidemin->setMaximum(m->current.iterationmax);
    slidemax->setMaximum(m->current.iterationmax);
    slidemax->setTracking(true);
    slidemin->setTracking(true);
    qDebug() << m->current.iterationmax;
    //slidemin->setValue(0);
    //slidemax->setValue(m->current.iterationmax);

    this->setLayout(layout);

    layout->addWidget(affichenongroup);
    layout->addWidget(labelslidemax);
    layout->addWidget(slidemax);
    layout->addWidget(labelslidemin);
    layout->addWidget(slidemin);

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
    connect(slidemax, SIGNAL(valueChanged(int)), m, SLOT(maxiterationchange(int)));
    connect(slidemin, SIGNAL(valueChanged(int)), m, SLOT(miniterationchange(int)));

    layout->addWidget(tabgroup);
}


void Alltree::affichegroupp(bool b)
{
    emit grouppmodechanged(b);
}
