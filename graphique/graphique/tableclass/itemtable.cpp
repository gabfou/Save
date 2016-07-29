#include "itemtable.h"
#include "headertableitem.h"
#include "argtableitem.tpp"
#include "person.h"
#include "question.h"
#include "tableshow.h"
#include "project.h"

itemtable::itemtable(QString placeholder, project *p, QString form) : placeholder(placeholder), form(form), p(p)
{
    this->setText(placeholder);
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
        this->setText(this->placeholder);
        this->setBackgroundColor(Qt::white);
    }
    else if (arg->type = 1 && head->type == 2)
        update(&(arg->argg), &(head->argq));
    else
    {
        this->setText(this->placeholder);
        this->setBackgroundColor(Qt::white);
    }
}

void itemtable::update(group *arg, question *head, QString form) // opti passer question en vector
{
    vector<question>::iterator tmp = this->p->listquestion.begin();
    question *q = NULL;
    QString val;

    while(tmp != this->p->listquestion.end())
    {
       if ((*tmp).id == head->id)
       {
           q = &(*tmp);
           break ;
       }
       tmp++;
    }
    if (q)
    {
        val = arg->grouprep(*q, 0);
        this->setBackgroundColor(arg->getColor());
    }
   this->eval(val);
}

void itemtable::eval(QString val)
{
    this->setText(val);
}
