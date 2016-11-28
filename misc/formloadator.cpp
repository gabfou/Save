#include "formloadator.h"

formloadator::formloadator(bool ref)
{
    QWidget *ret = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout();

    layout->addWidget((ref == 1) ? introref : introreel);

    formcreator(ref, &(p->listqgroup[0]), layout);
    ret->setLayout(layout);
    this->setWidget(ret);
}

int formloadator::formcreator(bool ref, group *g, QVBoxLayout *layout, int gid, QVBoxLayout *layoutgquestion)
{
    QGroupBox *w =  new QGroupBox();
    QVBoxLayout *layoutperso = new QVBoxLayout();
    QList<int> lg = g->getListfils();
    QList<question> lq = g->getListq();
    QList<int>::iterator      listg = lg.begin();
    QList<question>::iterator listq = lq.begin();
    QVBoxLayout *layoutq;
    int i = 0;

    layoutperso->addWidget(new QLabel(g->description), Qt::AlignCenter);
    if (layoutgquestion == NULL)
        layout->addWidget(w);
    else
        layoutgquestion->addWidget(w);
    while (listg != lg.end())
    {
        if (p->listqgroup[*listg].gquestion)
            i += formcreator(ref, &(p->listqgroup[*listg]), layout, gid, layoutperso);
        else
            i += formcreator(ref, &(p->listqgroup[*listg]), layout, gid, NULL);
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
        QGroupBox *tmp = new QGroupBox();
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
