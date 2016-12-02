#include "formgroupbox.h"
#include "data/question.h"
#include "data/group.h"
#include "data/project.h"

formgroupbox::formgroupbox(question *q, formgroupbox *parrent) : argq(q)
{
    if (parrent)
        parrent->addchild(this);
}

formgroupbox::formgroupbox(group *g, formgroupbox *parrent) : argg(g)
{
    if (parrent)
        parrent->addchild(this);
}

void formgroupbox::addchild(formgroupbox *child)
{
    listchild << child;
}

void formgroupbox::mousePressEvent ( QMouseEvent * event )
{
    if (argq)
        emit clicked(argq->id);
    else if (argg)
        emit clicked(argg->id);
}

int formgroupbox::checkgid(int id, project *p)
{
    int ret = 0;
    QList<formgroupbox*>::iterator i = listchild.begin();

    while (i != listchild.end())
    {
        ret += (*i)->checkgid(id, p);
        i++;
    }
    if (argq && argq->is_in(id, p))
        ret++;
    if (ret)
        this->sishow();
    else
        this->sihide();
    this->updateGeometry();
    this->adjustSize();
    return (ret);
}

void formgroupbox::sihide()
{
    this->hide();
    emit visibilychanged(0);
}

void formgroupbox::sishow()
{
    this->show();
    emit visibilychanged(1);
}
