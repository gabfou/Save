#include "itemtable.h"
#include "headertableitem.h"
#include "data/person.h"
#include "data/question.h"
#include "tableshow.h"
#include "data/project.h"

itemtable::itemtable(QString placeholder, project *p, QString form, int itmin, int itmax) : placeholder(placeholder), form(form), p(p), itminprep(itmin), itmaxprep(itmax)
{
    this->setTextAlignment(Qt::AlignHCenter);
}

// mise a jour de la case en fonction de la colone et la ligne representer par des headertableitem

void itemtable::update()
{
	headertableitem *arg = dynamic_cast<headertableitem*>(this->tableWidget()->verticalHeaderItem(this->row()));
	headertableitem *head = dynamic_cast<headertableitem*>(this->tableWidget()->horizontalHeaderItem(this->column()));
	QString actform = "";

	if (form.compare(actform))
		actform = form;
	else if (head && form.compare(head->formule))
		actform = head->formule;

    int itmax;
    int itmin;
    if (p->ref == 1)
    {
        itmax = 0;
        itmin = 0;
    }
    else
    {
        itmax = p->iterationmax;
        itmin = p->iterationmin;
    }
    if (this->itmaxprep != -1)
        itmax = this->itmaxprep;
    if (this->itminprep != -1)
        itmin = this->itminprep;
    //le choix de la methode de calcul (update) depent des header de la cellule
    if (!head || !arg)
	{
		this->setBackgroundColor(Qt::white);
        return ;
    }
    else if (arg->type == 1 && head->type == 2)
        update(&(arg->argg), &(head->argq), itmin, itmax);
    else if (arg->type == 2 && head->type == 1)
        updateall(&(head->argg), &(arg->argq), itmin, itmax);
    else if (arg->type == 3 && head->type == 2)
        update(&(arg->argp), &(head->argq), itmin, itmax);
    else if (arg->type == 1  && head->type == 4)
        update(&(arg->argg), &(head->argstr), itmin, itmax);
    else if (arg->type == 1  && head->type == 5)
        update(&(arg->argg), (head->arglistq), itmin, itmax);
	else
	{
		this->setBackgroundColor(Qt::white);
	}
}

// mise a jour question group

void itemtable::update(group *arg, question *head, int itmin, int itmax, QString form) // opti passer question en vector
{
    (void)form;
	question *q = &(p->listquestion[head->id]); // opti verifier que ca sert a quelque chose (question deja en argument ?)
	QString val;


	if (q)
	{
        if (p->val)
        {
            if (q->val != -1)
                val = arg->grouprepval(*q, itmin, itmax);
        }
        else
            val = arg->grouprep(*q, itmin, itmax);
        //this->setBackgroundColor(arg->getColor()); //remettre les couleur
	}
    this->eval(val, *head);
}

// mise a jour question personne

void itemtable::update(person *arg, question *head, int itmin, int itmax, QString form) // opti passer question en vector
{
    (void)form;
    question *q = &(p->listquestion[head->id]); // opti verifier que ca sert a quelque chose (question deja en argument ?)
    QString val;

    if (q)
    {
        if (p->val)
            val = arg->personshowcasevalstr(*q, itmin, itmax);
        else
            val = arg->personshowcasestr(*q, itmin, itmax);
        //this->setBackgroundColor(arg->getColor()); //remettre les couleur
    }
    this->eval(val, *q);
}

// mise a jour liste question group

void itemtable::update(group *arg, QList<question> *head, int itmin, int itmax, QString form) // opti passer question en vector
{
    (void)form;
    if (arg->type != 1)
        return ;
    float valf = 0;
    int l;
    int lq = 0;
    QList<question>::iterator i  = head->begin();

    while (i != head->end())
    {
        if (i->qgroupid == arg->id)
        {
            l = 0;
            valf += p->listgroup[0].grouprepall(*i, p->listgroup, itmin, itmax, &l) / ((l != 0) ? (float)l : 1);
            qDebug() << l;
            lq++;
        }
        i++;
    }
    if (lq != 0)
        valf = valf / (float)lq;
    this->eval(QString::number(valf));
}

// mise a jour string group

void itemtable::update(group *arg, QString *head, int itmin, int itmax, QString form)
{
    (void)form;
    question tmp;
    QString val;
    val = arg->grouprep(p->listgroup[p->gref], *head, &tmp, itmin, itmax);
   this->eval(val, tmp);
}

// mise a jour group question

void itemtable::updateall(group *arg, question *head, int itmin, int itmax, QString form)
{
    (void)form;
    int l = 0;
    if (arg->type != 0)
        return ;
    QString val;
    question *q = &(p->listquestion[head->id]);
    int valtmp = arg->grouprepall(*q, p->listgroup, itmin, itmax, &l);
    val = QString::number(valtmp  / (float)l);
    this->eval(val, *head);
}

// eval qui affiche juste

void itemtable::eval(QString val)
{
    this->setText(val);
}

// eval qui formate un peu

void itemtable::eval(QString val, question &q)
{
    if (q.type == 0 || q.type == 2 || q.type == 3)
        this->setText(val);
    else if (q.type == 1 && val.compare("NA") != 0)
    {
        if (q.val)
            this->setText(val + "%");
        else
            this->setText(QString::number(val.toFloat() * 100) + "%");
    }
    else if (q.type == 1)
        this->setText(val);
    else
        this->setText("question non reconu");
}
