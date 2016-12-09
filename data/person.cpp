#include "person.h"
#include "group.h"
#include "fact.h"
#include "question.h"
#include "project.h"

int person::getId() const{return id;}
void person::setId(int value){id = value;}
int person::getGroupid() const{return groupid;}
QString person::getEmail() const{return email;}
QString person::getLastname() const{return lastname;}
QString person::getName() const{return name;}
std::vector<question> *person::getQuestionlist() const{return questionlist;}
QList<fact> person::getFlist() const {return flist;}

person::person()
{
}

person::~person()
{
}

inline fact newfact(string name, int time, int note, QString date, int idquestion, QString timestr, int iteration)
{
    fact ret(name, time, note, date, idquestion, timestr, iteration);
	return(ret);
}

void person::add_fact(string name, int time, int note, QString date, int iteration, int idquestion, QString timestr)
{
    if (iteration > this->iteration)
        this->iteration = iteration;
    (this->flist).push_back(newfact(name, time, note, date, idquestion, timestr, iteration));
}


float person::personshowcaseval(question & qname, int iterationmin, int iterationmax)
{
    QList<fact>::iterator tmp;
    float j = 0;
    int l = 0;

    tmp = flist.begin();
    while (tmp != flist.end())
    {
        if ((qname.type == 0 || qname.type == 1 || qname.type == 3) && qname.val != -1)
        {
            j += (*tmp).checkfacttime(qname.id ,l, iterationmin, iterationmax) * qname.val;
        }
        tmp++;
    }
    if (l != 0)
        return(j / (float)l);
    return -1;
}



QString	person::personshowcasevalstr(question &qname, int iterationmin, int iterationmax)
{
    float tmp;

    if (qname.type == 2)
    {
        QVector<int> nb(qname.liststr.size() + 1);
        personshowcasevaltype2(qname, &nb, iterationmin, iterationmax);
        int i = -1;
        while(++i < qname.liststr.size() + 1)
        {
            if (nb[i] > 0)
                return (qname.liststr.at(i));
        }
        return ("NA");
    }
    tmp = personshowcaseval(qname, iterationmin, iterationmax);
    return ((tmp > -0.1) ? QString::number(tmp) : "NA");
}


float person::personshowcasevaltype2(question & qname, QVector<int> *nb, int iterationmin, int iterationmax)
{
    QList<fact>::iterator tmp;
    int j;
    int l = 0;
    QVector<int> nbl(qname.liststr.size() + 1);

    tmp = flist.begin();
    while (tmp != flist.end())
    {
        (*tmp).checkfactstr(qname.id , l, qname.liststr, nb, &nbl, iterationmin, iterationmax);
        tmp++;
    }
    if (l != 0)
    {
        j = -1;
        while (++j < qname.liststr.size() + 1)
        {
            if (nbl[j] != 0)
                (*nb)[j] = (*nb)[j] / nbl[j];
            else
                (*nb)[j] = 0;
        }
        return (1);
    }
    return -1;
}


float person::personshowcase(question & qname, int iterationmin, int iterationmax)
{
    QList<fact>::iterator tmp;
    float j = 0;
    int l = 0;

    tmp = this->flist.begin();
    while (tmp != flist.end())
	{
        if (qname.type == 0 || qname.type == 1 || qname.type == 3)
        {
            j += (*tmp).checkfacttime(qname.id ,l, iterationmin, iterationmax);
        }
		tmp++;
	}
	if (qname.type == 1)
        j = j * 100.0;
	if (l != 0)
        return(j / (float)l);
    return -1;
}


QString	person::personshowcasestr(question &qname, int iterationmin, int iterationmax)
{
    float tmp;
    if (qname.type == 2)
    {
        QVector<int> nb(qname.liststr.size() + 1);
        personshowcasevaltype2(qname, &nb, iterationmin, iterationmax);
        int i = -1;
        while(++i < qname.liststr.size() + 1)
        {
            if (nb[i] > 0)
                return (qname.liststr.at(i));
        }
        return ("NA");
    }
    tmp = personshowcase(qname, iterationmin, iterationmax);
    return ((tmp > -0.1) ? QString::number(tmp) : "NA");
}


QString	person::personsend(Smtp * smtp, QString post)
{
	(void)smtp;
	(void)post;
    return (this->email);
}

person::person(QString name, vector<question> *question)
{
	this->name = name;
	this->questionlist = question;
}


person::person(QString name, QString lastname, QString email, int id, vector<question> *listquestion, int groupid, int questionbool, int refbool, int jour)
{
	this->name = name + " " + lastname;
	this->firstname = name;
	this->lastname = lastname;
	this->id  = id;
	this->email = email;
	this->questionlist = listquestion;
	this->groupid = groupid;
    this->questionbool = questionbool;
    this->refbool = refbool;
    this->jour = jour;
}

person::person(const person & person)
{
	this->name = person.getName();
	this->id  = person.getId();
	this->email = person.getEmail();
	this->questionlist = person.getQuestionlist();
	this->groupid = person.getGroupid();
	this->flist = person.getFlist();
	this->firstname = person.firstname;
	this->lastname = person.lastname;
    this->questionbool = person.questionbool;
    this->refbool = person.refbool;
    this->jour = person.jour;
}


int person::compare(QString name2)
{
	return (name2.compare(this->name));
}

int person::compare(int id)
{
	if (this->id == id)
		return 0;
	return 1;
}

QString person::getrep(QVector<int> questionid, int iteration, project *p)
{
    QVector<int>::iterator it;

    it = questionid.begin();
    while (it != questionid.end())
    {
        QList<fact>::iterator tmp;

        tmp = this->flist.begin();
        while (tmp != flist.end())
        {
            if (tmp->idquestion == *it && tmp->iteration == iteration)
            {
                if (p->listquestion[*it].type == 2)
                    return (tmp->timestr);
                else
                    return (QString::number(tmp->time));
            }
            tmp++;
        }
        it++;
    }
    return ("NA");
}



QString person::time_rep_at_iteration(int it, int *counter, int *counter2)
{
    QList<fact>::iterator tmp;

    if (this->questionbool < it)
        return("non demandé");
    tmp = this->flist.begin();
    while (tmp != flist.end())
    {
        if (tmp->iteration == it)
        {
            if (counter)
                (*counter)++;
            if (counter2)
                (*counter2)++;
            return (tmp->getDate());
        }
        tmp++;
    }
    return("non rempli");
}

QString person::time_rep_at_iteration(int it)
{
    QList<fact>::iterator tmp;

    if (this->questionbool < it)
        return("non demandé");
    tmp = this->flist.begin();
    while (tmp != flist.end())
    {
        if (tmp->iteration == it)
        {
            return (tmp->getDate());
        }
        tmp++;
    }
    return("non rempli");
}
