#include "itemtable.h"
#include "headertableitem.h"
#include "data/person.h"
#include "data/question.h"
#include "tableshow.h"
#include "data/project.h"

itemtable::itemtable(QString placeholder, project *p, QString form) : placeholder(placeholder), form(form), p(p)
{
    //this->setText(placeholder);
    //this->update();
	//conect(this->tableWidget()->verticalHeaderItem(int));
}

void itemtable::update()
{
	headertableitem *arg = dynamic_cast<headertableitem*>(this->tableWidget()->verticalHeaderItem(this->row()));
	headertableitem *head = dynamic_cast<headertableitem*>(this->tableWidget()->horizontalHeaderItem(this->column()));
	QString actform = "";
	if (form.compare(actform))
		actform = form;
	else if (head && form.compare(head->formule))
		actform = head->formule;
	if (!head || !arg)
	{
        //qDebug() << "fail dynamic cast tab col=" << this->column() << " tab row =" << this->row();
        //this->setText(this->placeholder);
		this->setBackgroundColor(Qt::white);
        return ;
    }
    else if (arg->type == 1 && head->type == 2)
		update(&(arg->argg), &(head->argq));
    else if (arg->type == 2 && head->type == 1)
        updateall(&(head->argg), &(arg->argq));
    else if (arg->type == 3 && head->type == 2)
        update(&(arg->argp), &(head->argq));
    else if (arg->type == 1  && head->type == 4)
    {
        update(&(arg->argg), &(head->argstr));
    }
	else
	{
//		this->setText(this->placeholder);
		this->setBackgroundColor(Qt::white);
	}
}

void itemtable::update(group *arg, question *head, QString form) // opti passer question en vector
{(void)form;
	// vector<question>::iterator tmp = this->p->listquestion.begin();
	question *q = &(p->listquestion[head->id]); // opti verifier que ca sert a quelque chose (question deja en argument ?)
	QString val;

	if (q)
	{
        if (p->val)
        {
            if (q->val != -1)
                val = arg->grouprepval(*q, p->ref);
        }
        else
            val = arg->grouprep(*q, p->ref);
        //this->setBackgroundColor(arg->getColor()); //remettre les couleur
	}
    this->eval(val, *head);
}

void itemtable::update(person *arg, question *head, QString form) // opti passer question en vector
{(void)form;
    // vector<question>::iterator tmp = this->p->listquestion.begin();
    question *q = &(p->listquestion[head->id]); // opti verifier que ca sert a quelque chose (question deja en argument ?)
    float   valfloat;
    QString val;

    if (q)
    {
        if (p->val)
        {
            if (q->val != -1)
                valfloat = arg->personshowcaseval(*q, p->ref);
        }
        else
            valfloat = arg->personshowcaseval(*q, p->ref);
        //this->setBackgroundColor(arg->getColor()); //remettre les couleur
    }
    val = (valfloat > -0.1) ? QString::number(valfloat) : "NA";
    this->eval(val, *head);
}

void itemtable::update(group *arg, QString *head, QString form)
{
    question tmp;
    QString val;
//        if (p->val)
//        {
//            if (q->val != -1)
//                val = arg->grouprepval(*q, p->ref);
//        }
//        else
    val = arg->grouprep(p->listgroup[p->gref], *head, p->ref, &tmp);
        //this->setBackgroundColor(arg->getColor()); //remettre les couleur
   this->eval(val, tmp);
}

void itemtable::updateall(group *arg, question *head, QString form)
{
    if (arg->type != 0)
    {
        qDebug("dafuq itemtable::updateall");
        return ;
    }
    QString val;
    question *q = &(p->listquestion[head->id]);
    val = QString::number(arg->grouprepall(*q, p->listgroup));
    //this->setBackgroundColor(arg->getColor());
    this->eval(val, *head);
}

void itemtable::eval(QString val)
{
    this->setText(val);
}

void itemtable::eval(QString val, question &q)
{
    if (q.type == 0 || q.type == 2 || q.type == 3)
        this->setText(val);
    else if (q.type == 1 && val.compare("NA") != 0)
    {
        if (q.val)
            this->setText(val);
        else
            this->setText(QString::number(val.toFloat() * 100) + "%");
    }
    else if (q.type == 1)
        this->setText(val);
    else
        this->setText("question non reconu");
}
