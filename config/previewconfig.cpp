#include "previewconfig.h"
#include "data/project.h"
#include "data/group.h"
#include "data/question.h"

previewconfig::previewconfig(project *p) : p(p)
{
    QHBoxLayout *layout = new QHBoxLayout();
    QTabWidget *preview = new QTabWidget();
    introindex = new QTextEdit();
    introref = new QTextEdit();
    introreel = new QTextEdit();

    preview->addTab(this->indexinit(), "index");
    preview->addTab(this->initform(0), "reel");
    preview->addTab(this->initform(1), "ref");
    //preview->addWidget(ref, "ref");
    //preview->addWidget(reel, "reel");
//    introref->
    layout->addWidget(preview);
    this->setLayout(layout);
    connect(introindex, SIGNAL(textChanged()), this, SLOT(updateiindex()));
    connect(introref, SIGNAL(textChanged()), this, SLOT(updateiref()));
    connect(introreel, SIGNAL(textChanged()), this, SLOT(updateireel()));
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


void previewconfig::formloadator(bool ref, group *g, QVBoxLayout *layout, QVBoxLayout *layoutgquestion)
{
    QWidget *w =  new QWidget();
    QVBoxLayout *layoutperso = new QVBoxLayout();
    QList<int> lg = g->getListfils();
    QList<question> lq = g->getListq();
    QList<int>::iterator      listg = lg.begin();
    QList<question>::iterator listq = lq.begin();
    QVBoxLayout *layoutq;

    if (layoutgquestion == NULL)
        layout->addWidget(w);
    else
        layoutgquestion->addWidget(w);
    while (listg != lg.end())
    {
        if (p->listqgroup[*listg].gquestion)
            formloadator(ref, &(p->listqgroup[*listg]), layout, layoutperso);
        else
            formloadator(ref, &(p->listqgroup[*listg]), layout, NULL);
        listg++;
    }
    while (listq != lq.end())
    {
        layoutq = new QVBoxLayout();
        layoutq->addWidget(new QLabel(listq->sujet));
        layoutperso->addLayout(layoutq);
        listq++;
    }
    w->setLayout(layoutperso);
    w->show();
}

QWidget *previewconfig::initform(bool ref)
{
    QWidget *ret = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout();

    layout->addWidget((ref == 1) ? introref : introreel);

    formloadator(ref, &(p->listqgroup[0]), layout);
    ret->setLayout(layout);
    return (ret);
}


void *previewconfig::updateiindex()
{
    sqlo::sqlupdateintroindex(p->name, introindex->toHtml());
}

void *previewconfig::updateireel()
{
    sqlo::sqlupdateintroindex(p->name, introref->toHtml());
}

void *previewconfig::updateiref()
{
    sqlo::sqlupdateintroindex(p->name, introreel->toHtml());
}
