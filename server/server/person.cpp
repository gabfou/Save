#include "person.h"
#include "group.h"
#include <Qlabel>
#include <QString>

int person::getId() const{return id;}
void person::setId(int value){id = value;}
int person::getGroupid() const{return groupid;}
string person::getEmail() const{return email;}
string person::getLastname() const{return lastname;}
string person::getName() const{return name;}
std::vector<question> person::getQuestionlist() const{return questionlist;}
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

inline fact newfact(string name, int time, int note, string date)
{
	fact ret(name, time, note, date);
	return(ret);
}

void person::add_fact(string line)
{
	(this->flist).push_back(newfact(line));
}

void person::add_fact(string name, int time, int note, string date, int iteration)
{
    if (iteration)
        (this->flist).push_back(newfact(name, time, note, date));
    else
    {
        (this->freflist).push_back(newfact(name, time, note, date));
    }
}

int	person::personshowcase(string qname) const
{
    list<fact>::const_iterator tmp;
	int j = 0;
	int l = 0;


    tmp = this->flist.begin();
    while (tmp != this->flist.end())
    {
        j += (*tmp).checkfacttime(qname ,l);
        tmp++;
    }
    if (l != 0)
        return(j / l);
    return 0;
}

void	person::personshow(QTableWidget *gbox, int i, int k, group parent, int ref) const
{
	list<fact>::iterator tmp;
    vector<question>::const_iterator tmp2;
	int nb = 0;
    int k2 = k;

	tmp2 = this->questionlist.begin();
	while (tmp2 != this->questionlist.end())
	{
		nb = 0;
        nb = (ref) ? this->personrefshowcase(tmp2->name) : this->personshowcase(tmp2->name);
		if (nb != 0)
        {
            gbox->setItem(i, k, new QTableWidgetItem(QString::number(nb)));
            gbox->item(i, k)->setBackgroundColor(parent.getColor());
        }
        else
        {
            gbox->setItem(i, k, new QTableWidgetItem("NA"));
            gbox->item(i, k)->setBackgroundColor(parent.getColor());
        }
		k++;
		tmp2++;
	}
    while (k2 > -1)
    {
        if (!(gbox->item(i, k2)))
            gbox->setItem(i, k2, new QTableWidgetItem(""));
        gbox->item(i, k2--)->setBackgroundColor(parent.getColor());
    }
}

int	person::personrefshowcase(string qname) const
{
    list<fact>::const_iterator tmp;
    int j = 0;
    int l = 0;

    tmp = this->freflist.begin();
    while (tmp != this->freflist.end())
    {
        j += (*tmp).checkfacttime(qname ,l);
        tmp++;
    }
    if (l != 0)
        return(j / l);
    return 0;
}

void	person::personrefshow(QTableWidget *gbox, int i, int k) const
{
    list<fact>::iterator tmp;
    vector<question>::const_iterator tmp2;
    int nb = 0;

    tmp2 = this->questionlist.begin();
    while (tmp2 != this->questionlist.end())
    {
        nb = 0;
        nb = this->personrefshowcase(tmp2->name);
        if (nb != 0)
            gbox->setItem(i, k, new QTableWidgetItem(QString::number(nb)));
        k++;
        tmp2++;
    }
}

QString	person::personsend(Smtp * smtp, QString post)
{
	//smtp->sendMail("etudes@muranoconseil.com", "gabfou95@gmail.com" , "Etude muranoconseil",  body + post);
	return (this->email.c_str());
}

void	person::personsend()
{
	vector<question>::iterator tmp;
	ofstream file;
	ofstream file2;
	string bidon = "../../www/";
	string var;

	
	file.open(bidon + this->name + "form.php");
	file2.open(bidon + this->name + "rep.php");
	tmp = this->questionlist.begin();
	file << "INTRO";
	file << "<form action = \"";
	file << this->name + "rep.php";
	file << "\" method = \"POST\">\n";
	file2 << "<p>Merci!<\\p>";
	file2 << "<?php\n";
	while (tmp != this->questionlist.end())
	{
		var = "$file";
		file2 << var + " = fopen('../server/server/" + PATH + "', 'a+');\n";
		file2 << "fputs(" + var + ", \"\\n\".'person" + this->name + "');\n";
		file << (*tmp).questionform(this->name);
		file2 << (*tmp).questionrep(this->name, var);
		tmp++;
	}
	file << "<p><input type = \"submit\" value = \"OK\"></p>\n";
	file << "</form>\n";
	file2 << "?>";
	file.close();
	file2.close();

}

person::person(string name, vector<question> question)
{
	this->name = name;
	this->questionlist = question;
}

person::person(string name, string lastname, string email)
{
	this->name = name + " " + lastname;
	this->email = email;
}

person::person(string name, string lastname, string email, int id, vector<question> listquestion, int groupid)
{
	this->name = name + " " + lastname;
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
}


int person::compare(string name2)
{
	return (name2.compare(this->name));
}

int person::compare(int id)
{
	if (this->id == id)
		return 0;
	return 1;
}
