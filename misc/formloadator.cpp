#include "formloadator.h"
#include "data/project.h"
#include "data/group.h"
#include "data/question.h"
#include "misc/formgroupbox.h"
#include "MRichTextEditor/mrichtextedit.h"

formloadator::formloadator(bool ref, int gid, project *p): QScrollArea(), p(p), ref(ref), gid(gid)
{
    ret = new QWidget();
    layout = new QVBoxLayout();
    QPushButton *pb = new QPushButton("Enregistrer", this);
    if (ref == 1)
    {
        introref = new MRichTextEdit();
        introref->setText(p->introref);
    }
    else
    {
        introreel = new MRichTextEdit();
        introreel->setText(p->introreel);
    }

    layout->addWidget((ref == 1) ? introref : introreel);
    layout->addWidget(pb);

    formcreator(ref, &(p->listqgroup[0]), layout, gid);
    ret->setLayout(layout);
    this->setWidget(ret);
    if (ref == 1)
        connect(pb, SIGNAL(clicked(bool)), this, SLOT(updateiref()));
    else
        connect(pb, SIGNAL(clicked(bool)), this, SLOT(updateireel()));
}

int formloadator::reformcreator()
{
    formcreator(ref, &(p->listqgroup[0]), layout, gid);
}

int formloadator::formcreator(bool ref, group *g, QVBoxLayout *layout, int gid, formgroupbox *wgquestion)
{
    formgroupbox *w;

    if (wgquestion)
         w =  new formgroupbox(g, wgquestion, p, g->description);
    else
         w =  new formgroupbox(g, NULL, p, g->description);
    connect(w, SIGNAL(clicked(int)), this, SLOT(emitgroupclicked(int)));

    QList<int> lg = g->getListfils();
    QList<question> lq = g->getListq();
    QList<int>::iterator      listg = lg.begin();
    QList<question>::iterator listq = lq.begin();
    int i = 0;

//    w->layout->addWidget(new QLabel(g->description), Qt::AlignCenter);
    if (wgquestion == NULL)
    {
        layout->addWidget(w);
        checklistparrent << w;
    }
    else
        wgquestion->layout->addWidget(w);
    while (listg != lg.end())
    {
        if (p->listqgroup[*listg].gquestion)
            i += formcreator(ref, &(p->listqgroup[*listg]), layout, gid, w);
        else
            i += formcreator(ref, &(p->listqgroup[*listg]), layout, gid, w);
        listg++;
    }
//    w->setLayout(w->layout);
    while (listq != lq.end())
    {
        if (!((ref && listq->ref_only != 2) || (ref == 0 && listq->ref_only != 1)))
        {
            listq++;
            continue ;
        }
        formgroupbox *tmp = new formgroupbox(&(p->listquestion[(*listq).id]), w, p, listq->sujet);
        connect(tmp, SIGNAL(clicked(int)), this, SLOT(emitquestionclicked(int)));
        //layoutq = new QVBoxLayout();
        //layoutq->addWidget(new QLabel(listq->sujet));
        //tmp->setLayout(layoutq);
        w->layout->addWidget(tmp);
        listq++;
        i++;
    }
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
    this->gid = gid;
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
    sqlo::sqlupdateintroindex(p->name, introreel->toHtml());
}

void formloadator::updateiref()
{
    sqlo::sqlupdateintroindex(p->name, introref->toHtml());
}
