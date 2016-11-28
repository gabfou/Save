#include "previewconfig.h"
#include "data/project.h"
#include "data/group.h"
#include "data/question.h"
#include "grouptree.h"
#include "grouptreeitem.h"
#include "mainwindow.h"
#include "misc/formloadator.h"

previewconfig::previewconfig(MainWindow *m) : p(&(m->current))
{
    QHBoxLayout *layout = new QHBoxLayout();
    preview = new QTabWidget();
    introindex = new QTextEdit();

    preview->addTab(this->indexinit(), "index");
    preview->addTab(new formloadator(0, 0, p), "reel");
    preview->addTab(new formloadator(1, 0, p), "ref");

    groupboxtmp = new grouptree(m, p->listgroup, 1);
    groupboxtmp->setVisiblenongroup(0);
    groupboxtmp->resizeColumnToContents(0);
    layout->addWidget(groupboxtmp, 1);
    layout->addWidget(preview, 3);
    this->setLayout(layout);
    connect(introindex, SIGNAL(textChanged()), this, SLOT(updateiindex()));
    connect(groupboxtmp, SIGNAL(itemClicked(QTreeWidgetItem *, int )), this, SLOT(changescope(QTreeWidgetItem *)));
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

    qDebug() << "jksdgffs -1";
    if ((tmp = dynamic_cast<grouptreeitem*>(item)) != NULL)
    {
        qDebug() << "jksdgffs";
        preview->removeTab(2);
        preview->removeTab(1);
        preview->addTab(new formloadator(0, tmp->getId(), p), "reel");
        preview->addTab(new formloadator(1, tmp->getId(), p), "ref");
    }
}

void previewconfig::updateiindex()
{
    sqlo::sqlupdateintroindex(p->name, introindex->toHtml());
}
