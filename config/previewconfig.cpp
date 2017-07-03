#include "previewconfig.h"
#include "data/project.h"
#include "data/group.h"
#include "data/question.h"
#include "grouptree.h"
#include "grouptreeitem.h"
#include "mainwindow.h"
#include "misc/formloadator.h"
#include "infoquestion.h"
#include "MRichTextEditor/mrichtextedit.h"

//initialiation

previewconfig::previewconfig(MainWindow *m) : p(&(m->current))
{
	QHBoxLayout *layout = new QHBoxLayout();
	preview = new QTabWidget();
    introindex = new MRichTextEdit();
    introindex->setText(p->introindex);

	formreel = new formloadator(0, 0, p);
	formref = new formloadator(1, 0, p);

	preview->addTab(this->indexinit(), "index");
	preview->addTab(formreel, "reel");
	preview->addTab(formref, "ref");

	groupboxtmp = new infoquestion(p, m);
	groupboxtmp->setquestionmod(0);
    changescope(groupboxtmp->groupbox->topLevelItem(0));
    layout->addWidget(groupboxtmp, 2);
	layout->addWidget(preview, 5);
	this->setLayout(layout);
	connect(groupboxtmp->groupbox, SIGNAL(itemClicked(QTreeWidgetItem *, int )), this, SLOT(changescope(QTreeWidgetItem *)));
	connect(formreel, SIGNAL(questionclicked(int)), groupboxtmp, SLOT(updatequestion(int)));
	connect(formref, SIGNAL(questionclicked(int)), groupboxtmp, SLOT(updatequestion(int)));
	connect(formreel, SIGNAL(groupclicked(int)), groupboxtmp, SLOT(updategroup(int)));
	connect(formref, SIGNAL(groupclicked(int)), groupboxtmp, SLOT(updategroup(int)));
}

//initialiation de l onglet index

QWidget *previewconfig::indexinit()
{
	QWidget *ret = new QWidget();
	QVBoxLayout *layout = new QVBoxLayout();
    QPushButton *pb = new QPushButton("Enregistrer", this);

	layout->addWidget(introindex);
    layout->addWidget(pb);
    layout->addWidget(new QLabel("estimate\nDay 1\n...\n"), 0,  Qt::AlignHCenter);
	if (p->sugestion)
	{
		layout->addWidget(new QLabel("your personal sugestion:\n"), 0,  Qt::AlignHCenter);
		layout->addWidget(new QTextEdit());
	}
	ret->setLayout(layout);
    connect(pb, SIGNAL(clicked(bool)), this, SLOT(updateiindex()));
    return (ret);
}

// changement du groupe de personne concernée

void previewconfig::changescope(QTreeWidgetItem *item)
{
	grouptreeitem *tmp;

	if ((tmp = dynamic_cast<grouptreeitem*>(item)) != NULL)
	{
		formreel->gidupdate(tmp->getId());
		formref->gidupdate(tmp->getId());
	}
}

// mise a jour de l intro coter base de donnée

void previewconfig::updateiindex()
{
	sqlo::sqlupdateintroindex(p->name, introindex->toHtml());
}
