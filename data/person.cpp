#include "person.h"
#include "group.h"
#include <Qlabel>
#include <QString>
#include "question.h"

int person::getId() const{return id;}
void person::setId(int value){id = value;}
int person::getGroupid() const{return groupid;}
QString person::getEmail() const{return email;}
QString person::getLastname() const{return lastname;}
QString person::getName() const{return name;}
std::vector<question> *person::getQuestionlist() const{return questionlist;}
std::list<fact> person::getFlist() const{return flist;}

std::list<fact> person::getFreflist() const
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

void person::add_fact(string line)
{
	(this->flist).push_back(newfact(line));
}

void person::add_fact(string name, int time, int note, string date, int iteration, int idquestion)
{
	if (iteration)
        (this->flist).push_back(newfact(name, time, note, date, idquestion));
	else
	{
        (this->freflist).push_back(newfact(name, time, note, date, idquestion));
	}
}

float person::personshowcase(question & qname, list<fact> lf) const
{
	list<fact>::iterator tmp;
    float j = 0;
    int l = 0;

	tmp = lf.begin();
	while (tmp != lf.end())
	{
		if (qname.type == 0 || qname.type == 1)
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

void	person::personrefshow(QTableWidget *gbox, int i, int k)
{
	list<fact>::iterator tmp;
	vector<question>::iterator tmp2;
	int nb = 0;

	tmp2 = this->questionlist->begin();
	while (tmp2 != this->questionlist->end())
	{
		nb = 0;
		nb = this->personrefshowcase(*tmp2);
		if (nb != 0)
			gbox->setItem(i, k, new QTableWidgetItem(QString::number(nb)));
		k++;
		tmp2++;
	}
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
