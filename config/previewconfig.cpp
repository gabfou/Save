#include "previewconfig.h"
#include "data/project.h"
#include "data/group.h"
#include "data/question.h"
#include "grouptree.h"
#include "grouptreeitem.h"
#include "mainwindow.h"
#include "misc/formloadator.h"
#include "infoquestion.h"

previewconfig::previewconfig(MainWindow *m) : p(&(m->current))
{
    QHBoxLayout *layout = new QHBoxLayout();
    preview = new QTabWidget();
    introindex = new QTextEdit();

    formreel = new formloadator(0, 0, p);
    formref = new formloadator(1, 0, p);

    preview->addTab(this->indexinit(), "index");
    preview->addTab(formreel, "reel");
    preview->addTab(formref, "ref");

    groupboxtmp = new infoquestion(p, m);
    groupboxtmp->setquestionmod(0);
    layout->addWidget(groupboxtmp, 2);
    layout->addWidget(preview, 5);
    this->setLayout(layout);
    connect(introindex, SIGNAL(textChanged()), this, SLOT(updateiindex()));
    connect(groupboxtmp->groupbox, SIGNAL(itemClicked(QTreeWidgetItem *, int )), this, SLOT(changescope(QTreeWidgetItem *)));
    connect(formreel, SIGNAL(emitquestionclicked(int)), groupboxtmp, SLOT(updatequestion(id)));
    connect(formref, SIGNAL(emitquestionclicked(int)), groupboxtmp, SLOT(updatequestion(id)));
    connect(formreel, SIGNAL(emitgroupclicked(int)), groupboxtmp, SLOT(updategroup(id)));
}

QWidget *previewconfig::indexinit()
{
    QWidget *ret = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout();

    layout->addWidget(introindex);
    layout->addWidget(new QLabel("estimate\nDay 1\n...\n"), 0,  Qt::AlignHCenter);
    if (p->sugestion)
    {
        layout->addWidget(new QLabel("your personal sugestion:\n"), 0,  Qt::AlignHCenter);
        layout->addWidget(new QTextEdit());
    }
    ret->setLayout(layout);
    return (ret);
}

void previewconfig::changescope(QTreeWidgetItem *item)
{
    grouptreeitem *tmp;

    if ((tmp = dynamic_cast<grouptreeitem*>(item)) != NULL)
    {
        formreel->gidupdate(tmp->getId());
        formref->gidupdate(tmp->getId());
    }
}

void previewconfig::updateiindex()
{
    sqlo::sqlupdateintroindex(p->name, introindex->toHtml());
}
