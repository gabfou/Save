#include "formgroupbox.h"
#include "data/question.h"
#include "data/group.h"
#include "data/person.h"
#include "data/project.h"

// cette classe est un "QGroupBox" contenant une question ou un group elle essaye de simuler comment celle ci sera traiter coté web

formgroupbox::formgroupbox(question *q, formgroupbox *parrent, project *p, QString text) : argq(q), p(p)
{
    layout = new QVBoxLayout();
    label = new QLabel(text);
    layout->addWidget(label);
    this->setLayout(layout);
    if (parrent)
        parrent->addchild(this);
    this->setAcceptDrops(1);
}

formgroupbox::formgroupbox(group *g, formgroupbox *parrent, project *p, QString text) : argg(g), p(p)
{
    layout = new QVBoxLayout();
    label = new QLabel(text);
    layout->addWidget(label);
    this->setLayout(layout);
    if (parrent)
        parrent->addchild(this);
    this->setAcceptDrops(1);
}

void formgroupbox::addchild(formgroupbox *child)
{
    listchild << child;
}

// verifie si elle est visible en function de l'id du group de personne id

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

// la fin du fichier essaye de gerer le drag and drop pour pouvoir intervertir des question antre les groupe

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
    event->acceptProposedAction();
}

void formgroupbox::dropEvent(QDropEvent *event)
{
    formgroupbox *src = dynamic_cast<formgroupbox*>(event->source());
    if (src == NULL)
        return ;
    group grouptmp;
    question questiontmp;
    int id;

    if (src->argg)
    {
        id = src->argg->id;
        grouptmp = group(p->listqgroup[id]);
        if (argg)
        {
            qDebug() << "dropEvent 1";
            sqlo::addgroup(p, p->name, argg->name, argg->parentid, argg->type, argg->description, argg->gquestion, id);
            sqlo::addgroup(p, p->name, grouptmp.name, grouptmp.parentid, grouptmp.type, grouptmp.description, grouptmp.gquestion, argg->id);
            this->label->setText(argg->description);
            src->label->setText(src->argg->description);
        }
        else if (argq)
        {
            qDebug() << "dropEvent 2";
            return ;
        }
    }
    if (src->argq)
    {
        id = src->argq->id;
        questiontmp = question(p->listquestion[id]);
        if (argg)
        {
//            qDebug() << "dropEvent 3"; // il manque la mise a jour
//            sqlo::addquestion(p, questiontmp.name, questiontmp.group, questiontmp.unit, -1, questiontmp.sujet, argg->id, questiontmp.type, questiontmp.ref_only, questiontmp.liststr.join(" "), questiontmp.val, questiontmp.global,questiontmp.id);
//            emit updateneeded();
        }
        else if (argq)
        {
            qDebug() << "dropEvent 4";
            sqlo::addquestion(p, argq->name, argq->group, argq->unit, -1, argq->sujet, argq->qgroupid, argq->type, argq->ref_only, argq->liststr.join(" "), argq->val, argq->global, questiontmp.id);
            sqlo::addquestion(p, questiontmp.name, questiontmp.group, questiontmp.unit, -1, questiontmp.sujet, questiontmp.qgroupid, questiontmp.type, questiontmp.ref_only, questiontmp.liststr.join(" "), questiontmp.val, questiontmp.global, argq->id);
            this->label->setText(argq->sujet);
            src->label->setText(src->argq->sujet);
        }
    }
}
