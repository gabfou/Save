#include "previewconfig.h"
#include "data/project.h"
#include "data/group.h"
#include "data/question.h"
#include "grouptree.h"
#include "mainwindow.h"
#include "misc/formloadator.h"

previewconfig::previewconfig(MainWindow *m) : p(&(m->current))
{
    QHBoxLayout *layout = new QHBoxLayout();
    preview = new QTabWidget();
    introindex = new QTextEdit();
    introref = new QTextEdit();
    introreel = new QTextEdit();
    refpreview = new formcreator(0);
    reelpreview = new formcreator(1);

    preview->addTab(this->indexinit(), "index");
    preview->addTab(formcreator(0), "reel");
    preview->addTab(formcreator(1), "ref");

    grouptree *groupboxtmp = new grouptree(m, p->listgroup, 1);
    groupboxtmp->setVisiblenongroup(0);
    groupboxtmp->resizeColumnToContents(0);
    layout->addWidget(groupboxtmp, 1);
    groupboxtmp = new grouptree(m, p->listgroup, 1);
    groupboxtmp->setVisiblenongroup(0);
    groupboxtmp->resizeColumnToContents(0);
    layout->addWidget(preview, 3);
    this->setLayout(layout);
    connect(introindex, SIGNAL(textChanged()), this, SLOT(updateiindex()));
    connect(introref, SIGNAL(textChanged()), this, SLOT(updateiref()));
    connect(introreel, SIGNAL(textChanged()), this, SLOT(updateireel()));
    connect(this->groupboxtmp, SIGNAL(itemClicked(QTreeWidgetItem *, int )), this, SLOT(changescope(QTreeWidgetItem *)));
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



void previewconfig::updateiindex()
{
    sqlo::sqlupdateintroindex(p->name, introindex->toHtml());
}

void previewconfig::updateireel()
{
    sqlo::sqlupdateintroindex(p->name, introref->toHtml());
}

void previewconfig::updateiref()
{
    sqlo::sqlupdateintroindex(p->name, introreel->toHtml());
}
