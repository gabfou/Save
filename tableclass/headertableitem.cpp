#include "headertableitem.h"
#include "grouptree.h"
#include "grouptreeitem.h"
#include "persontreeitem.h"
#include "questiontreeitem.h"
#include "data/project.h"
#include "tableshow.h"

QString headertableitem::getFormule() const{return formule;}
void headertableitem::setFormule(const QString &value){formule = value;}

headertableitem::headertableitem(project *p, QString str, QString form, int id) : QTableWidgetItem(str), formule(form), id(id), p(p), type(-1)
{
}

headertableitem::headertableitem(project *p, QString str, group arg, QString form)
    : QTableWidgetItem(str), type(1), argg(arg), id(arg.id), formule(form), p(p)
{
}

headertableitem::headertableitem(project *p, QString str, person arg, QString form)
    : QTableWidgetItem(str), type(3), argp(arg), id(arg.id), formule(form), p(p)
{
}

headertableitem::headertableitem(project *p, QString str, question arg, QString form)
    : QTableWidgetItem(str), type(2), argq(arg), id(arg.id), formule(form), p(p)
{
}

headertableitem::headertableitem(project *p, QString str, QString arg, QString form)
    : QTableWidgetItem(str), type(4), argstr(arg), id(-1), formule(form), p(p)
{
}

void headertableitem::changearg(QTreeWidgetItem *item)
{
    grouptreeitem *gcast = dynamic_cast<grouptreeitem*>(item);
    questiontreeitem *qcast = dynamic_cast<questiontreeitem*>(item);
    persontreeitem *pcast = dynamic_cast<persontreeitem*>(item);

    if (gcast)
    {
        if (gcast->typeg == 0)
            argg = p->listgroup[gcast->getId()];
        else
            argg = p->listqgroup[gcast->getId()];
        id = argg.id;
        type = 1;
//            QTableWidgetItem(), type(1), argg(arg), id(arg.id), formule(form)
    }
    else if (qcast)
    {
        argq = p->listquestion[qcast->id];
        id = argq.id;
        type = 2;
    }
    else if (pcast)
    {
        argp = p->listp[pcast->id];
        id = argp.id;
        type = 3;
    }
    dynamic_cast<tableshow*>(this->tableWidget())->updateall(); // opti
}

bool headertableitem::is_in(vector<group> &g, vector<group> &gq, QList<int> listint, QList<int> listqint)
{
    QList<int>::iterator tmp;

    if (type == -1 || type == 4)
    {
        return (1);
    }
    if (type == 1)
    {
        qDebug() << "is_in" << argg.type << argg.getListp().empty() << argg.getListq().empty();
        if ((argg.type == 0 && argg.getListp().empty()) || (argg.type == 1 && argg.getListq().empty()))
            return (0);
        if (g[0].type != this->argg.type) // a enlever si en dessous finie
            return (1);
        if ((listint.contains(id)) || (listqint.contains(id))) // a finir
            return (1);
        return (0);
    }
    if (type == 3)
    {
        if (g[0].type != 0)
            return (1);
        else
        {
            tmp = listint.begin();
            while (tmp != listint.end())
            {
                if (g[(*tmp)].contain(this->argp))
                    return (1);
                tmp++;
            }
            return (0);
        }
    }
    if (type == 2)
    {
        if (gq[0].type != 1)
        {
            return (1);
        }
        else if (p->ref == 0 && argq.ref_only)
            return (0);
        else
        {
            tmp = listqint.begin();
            while (tmp != listqint.end())
            {
                gq[*tmp].getListq();
                if (gq[*tmp].contain(this->argq))
                    return (1);
                tmp++;
            }
            return (0);
        }
    }
    return (false);
}
