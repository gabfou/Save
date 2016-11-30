#include "formloadator.h"
#include "data/project.h"
#include "data/group.h"
#include "data/question.h"
#include "misc/formgroupbox.h"

formloadator::formloadator(bool ref, int gid, project *p): QScrollArea(), p(p)
{
    ret = new QWidget();
    layout = new QVBoxLayout();
    if (ref == 1)
        introref = new QTextEdit(p->introref);
    else
        introreel = new QTextEdit(p->introreel);

    layout->addWidget((ref == 1) ? new QTextEdit(p->introref) : new QTextEdit(p->introreel));

    formcreator(ref, &(p->listqgroup[0]), layout, gid);
    ret->setLayout(layout);
    this->setWidget(ret);
    if (ref == 1)
        connect(introref, SIGNAL(textChanged()), this, SLOT(updateiref()));
    else
        connect(introreel, SIGNAL(textChanged()), this, SLOT(updateireel()));
}

int formloadator::formcreator(bool ref, group *g, QVBoxLayout *layout, int gid, QVBoxLayout *layoutgquestion, formgroupbox *wgquestion)
{
    formgroupbox *w;

    if (wgquestion)
         w =  new formgroupbox(NULL, wgquestion);
    else
         w =  new formgroupbox(NULL, NULL);

    QVBoxLayout *layoutperso = new QVBoxLayout();
    QList<int> lg = g->getListfils();
    QList<question> lq = g->getListq();
    QList<int>::iterator      listg = lg.begin();
    QList<question>::iterator listq = lq.begin();
    QVBoxLayout *layoutq;
    int i = 0;

    layoutperso->addWidget(new QLabel(g->description), Qt::AlignCenter);
    if (layoutgquestion == NULL)
    {
        layout->addWidget(w);
        checklistparrent << w;
    }
    else
        layoutgquestion->addWidget(w);
    while (listg != lg.end())
    {
        if (p->listqgroup[*listg].gquestion)
            i += formcreator(ref, &(p->listqgroup[*listg]), layout, gid, layoutperso, w);
        else
            i += formcreator(ref, &(p->listqgroup[*listg]), layout, gid, NULL, NULL);
        listg++;
    }
    w->setLayout(layoutperso);
    while (listq != lq.end())
    {
        if (!((ref && listq->ref_only != 2) || (ref == 0 && listq->ref_only != 1)))
        {
            listq++;
            continue ;
        }
        formgroupbox *tmp = new formgroupbox(&(p->listquestion[(*listq).id]), w);
        connect(tmp, SIGNAL(clicked(int)), this, SLOT(emitquestionclicked(int)));
        layoutq = new QVBoxLayout();
        layoutq->addWidget(new QLabel(listq->sujet));
        tmp->setLayout(layoutq);
        layoutperso->addWidget(tmp);
        tmp->show();
        listq++;
        i++;
    }
    if (i != 0)
        w->show();
    else
        w->hide();
    return (i);
}

void formloadator::emitquestionclicked(int id)
{
    emit questionclicked(id);
}

void formloadator::emitgroupclicked(int id)
{
    emit groupclicked(id);
}


void formloadator::gidupdate(int gid)
{
    QList<formgroupbox*>::iterator i = checklistparrent.begin();

    while (i != checklistparrent.end())
    {
        (*i)->checkgid(gid, p);
        i++;
    }
    ret->adjustSize();
}

void formloadator::updateireel()
{
    sqlo::sqlupdateintroindex(p->name, introref->toHtml());
}

void formloadator::updateiref()
{
    sqlo::sqlupdateintroindex(p->name, introreel->toHtml());
}
