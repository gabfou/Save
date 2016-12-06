#include "formgroupbox.h"
#include "data/question.h"
#include "data/group.h"
#include "data/person.h"
#include "data/project.h"

formgroupbox::formgroupbox(question *q, formgroupbox *parrent, project *p) : argq(q), p(p)
{
    if (parrent)
        parrent->addchild(this);
    this->setAcceptDrops(1);
}

formgroupbox::formgroupbox(group *g, formgroupbox *parrent, project *p) : argg(g), p(p)
{
    if (parrent)
        parrent->addchild(this);
    this->setAcceptDrops(1);
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
    if (event->button() == Qt::LeftButton && (argq || argg))
    {

        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData;
        mimeData->setText((argg) ? argg->name + " " + QString::number(1) + " " + QString::number(argg->id)
                                 : argq->name + " " + QString::number(2) + " " + QString::number(argq->id));
        drag->setMimeData(mimeData);

        Qt::DropAction dropAction = drag->exec();
    }
}

void formgroupbox::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug() << "dsafdsfs 2";
}

void formgroupbox::dropEvent(QDropEvent *event)
{
    QStringList list = event->mimeData()->text().split(" ");
    group grouptmp;
    question questiontmp;

    qDebug() << "dsafdsfs";
    if (list.size() != 3)
        return ;
    int id = list.at(2).toInt();
    if (list.at(1).compare("1"))
    {
        grouptmp = p->listqgroup[id];
        if (argg)
        {
            sqlo::addgroup(p, p->name, argg->name, argg->parentid, argg->type, argg->description, argg->gquestion, id);
            sqlo::addgroup(p, p->name, grouptmp.name, grouptmp.parentid, grouptmp.type, grouptmp.description, grouptmp.gquestion, argg->id);
            emit updateneeded();
        }
        else if (argq)
            return ;
    }
    if (list.at(1).compare("2"))
    {
        questiontmp = p->listquestion[id];
        if (argg)
        {
            sqlo::addquestion(p, questiontmp.name, questiontmp.group, questiontmp.unit, -1, questiontmp.sujet, argg->id, questiontmp.type, questiontmp.ref_only, questiontmp.liststr.join(" "), questiontmp.val, questiontmp.global,questiontmp.id);
            emit updateneeded();
        }
        else if (argq)
        {
            sqlo::addquestion(p, argq->name, argq->group, argq->unit, -1, argq->sujet, argg->id, argq->type, argq->ref_only, argq->liststr.join(" "), argq->val, argq->global, questiontmp.id);
            sqlo::addquestion(p, questiontmp.name, questiontmp.group, questiontmp.unit, -1, argq->sujet, argg->id, questiontmp.type, questiontmp.ref_only, questiontmp.liststr.join(" "), questiontmp.val, questiontmp.global, argq->id);
            emit updateneeded();
        }
    }
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
