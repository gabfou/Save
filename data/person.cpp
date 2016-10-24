#include "person.h"
#include "group.h"
#include "fact.h"
#include "question.h"

int person::getId() const{return id;}
void person::setId(int value){id = value;}
int person::getGroupid() const{return groupid;}
QString person::getEmail() const{return email;}
QString person::getLastname() const{return lastname;}
QString person::getName() const{return name;}
std::vector<question> *person::getQuestionlist() const{return questionlist;}
QList<fact> person::getFlist() const{return flist;}

QList<fact> person::getFreflist() const
{
	return freflist;
}

person::person()
{
}

person::~person()
{
}

inline fact newfact(string line)
{
	fact ret(line);
	return(ret);
}

inline fact newfact(string name, int time, int note, string date, int idquestion)
{
    fact ret(name, time, note, date, idquestion);
	return(ret);
}

void person::add_fact(string name, int time, int note, string date, int iteration, int idquestion)
{
	if (iteration)
        (this->flist).push_back(newfact(name, time, note, date, idquestion));
	else
        (this->freflist).push_back(newfact(name, time, note, date, idquestion));
}



float person::personshowcaseval(question & qname, QList<fact> lf) const
{
    QList<fact>::iterator tmp;
    float j = 0;
    int l = 0;

    tmp = lf.begin();
    while (tmp != lf.end())
    {
        if ((qname.type == 0 || qname.type == 1 || qname.type == 3) && qname.val != -1)
        {
            j += (*tmp).checkfacttime(qname.id ,l) * qname.val;
        }
        tmp++;
    }
    if (l != 0)
        return(j / (float)l);
    return -1;
}

float	person::personshowcaseval(question & qname)
{
    return (this->personshowcaseval(qname, this->flist));
}

float	person::personrefshowcaseval(question &qname)
{
    return (this->personshowcaseval(qname, this->freflist));
}

float	person::personshowcaseval(question &qname, int ref)
{
    if (ref)
       return (this->personshowcaseval(qname, this->freflist));
    else
       return (this->personshowcaseval(qname, this->flist));
}

float person::personshowcasevaltype2(question & qname, QList<fact> lf, QVector<int> *nb) const
{
    QList<fact>::iterator tmp;
    int j;
    int l = 0;
    QVector<int> nbl(qname.liststr.size() + 1);

    tmp = lf.begin();
    while (tmp != lf.end())
    {
        (*tmp).checkfactstr(qname.id , l, qname.liststr, nb, &nbl);
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

float	person::personshowcasevaltype2(question &qname, int ref, QVector<int> *nb)
{
    if (ref)
       return (this->personshowcasevaltype2(qname, this->freflist, nb));
    else
       return (this->personshowcasevaltype2(qname, this->flist, nb));
}

float person::personshowcase(question & qname, QList<fact> lf) const
{
    QList<fact>::iterator tmp;
    float j = 0;
    int l = 0;

	tmp = lf.begin();
	while (tmp != lf.end())
	{
        if (qname.type == 0 || qname.type == 1 || qname.type == 3)
        {
            j += (*tmp).checkfacttime(qname.id ,l);
        }
		tmp++;
	}
	if (qname.type == 1)
        j = j * 100.0;
	if (l != 0)
        return(j / (float)l);
    return -1;
}

float	person::personshowcase(question & qname)
{
	return (this->personshowcase(qname, this->flist));
}

float	person::personrefshowcase(question &qname)
{
	return (this->personshowcase(qname, this->freflist));
}

float	person::personshowcase(question &qname, int ref)
{
    if (ref)
       return (this->personshowcase(qname, this->freflist));
    else
       return (this->personshowcase(qname, this->flist));
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

person::person(QString name, QString lastname, QString email)
{
	this->name = name + " " + lastname;
	this->email = email;
}

person::person(QString name, QString lastname, QString email, int id, vector<question> *listquestion, int groupid)
{
	this->name = name + " " + lastname;
	this->firstname = name;
	this->lastname = lastname;
	this->id  = id;
	this->email = email;
	this->questionlist = listquestion;
	this->groupid = groupid;
}

person::person(const person & person)
{
	this->name = person.getName();
	this->id  = person.getId();
	this->email = person.getEmail();
	this->questionlist = person.getQuestionlist();
	this->groupid = person.getGroupid();
	this->flist = person.getFlist();
	this->freflist = person.getFreflist();
	this->firstname = person.firstname;
	this->lastname = person.lastname;
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
