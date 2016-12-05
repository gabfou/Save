#include "alltree.h"
#include "data/group.h"
#include "data/project.h"
#include "grouptree.h"
#include "mainwindow.h"

void Alltree::prephide()
{
	slidemax->hide();
	labelslidemax->hide();
	slidemin->hide();
	labelslidemin->hide();

	if (p->ref == 0)
	{
		slidemax->show();
		labelslidemax->show();
		slidemin->show();
		labelslidemin->show();
	}
}

Alltree::Alltree(MainWindow *m, project *current) : p(current)
{
	QTabWidget *tabgroup = new QTabWidget();
	QCheckBox *affichenongroup = new QCheckBox("Voir les non group");
	QCheckBox *afficheestim = new QCheckBox("afficher les estimation");
	if (p->ref)
		afficheestim->setChecked(1);
	QHBoxLayout *hbox = new QHBoxLayout();
	QVBoxLayout *layout = new QVBoxLayout();
	slidemax = new QSlider(Qt::Horizontal);
	labelslidemax = new QLabel("jour maximum");
	slidemin = new QSlider(Qt::Horizontal);
	labelslidemin = new QLabel("jour minimum");
    slidemin->setMinimum(0);
    slidemax->setMinimum(0);
	slidemin->setMaximum(m->current.iterationmax);
	slidemax->setMaximum(m->current.iterationmax);
	slidemax->setTracking(true);
    slidemin->setTracking(true);
    slidemin->setValue(0);
    slidemax->setValue(m->current.iterationmax);

	this->setLayout(layout);

	hbox->addWidget(affichenongroup);
	hbox->addWidget(afficheestim);
	layout->addLayout(hbox);
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
