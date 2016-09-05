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
	//group *argg = dynamic_cast<argtableitem<group>*>(this->tableWidget()->verticalHeaderItem(this->row()));
	//person *argp = dynamic_cast<argtableitem<person>*>(this->tableWidget()->verticalHeaderItem(this->row()));
	//question *argq = dynamic_cast<argtableitem<question>*>(this->tableWidget()->verticalHeaderItem(this->row()));
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
        val = arg->grouprep(*q, p->ref);
        //this->setBackgroundColor(arg->getColor()); //remettre les couleur
	}
    this->eval(val, *head);
}

void itemtable::updateall(group *arg, question *head, QString form) // opti passer question en vector
{
    if (arg->type != 0)
    {
        qDebug("dafuq itemtable::updateall");
        return ;
    }
    QString val;
    question *q = &(p->listquestion[head->id]);
    val = arg->grouprepall(*q, p->listgroup);
    this->setBackgroundColor(arg->getColor());
    this->eval(val, *head);
}

void itemtable::eval(QString val, question &q)
{
    if (q.type == 0 || q.type == 2)
        this->setText(val);
    if (q.type == 1 && val.compare("NA") != 0)
        this->setText(val + "%");
    else if (q.type == 1)
        this->setText(val);
}
