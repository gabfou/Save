#pragma once
#include "le.h"

class group;
class fact;
class question;
class Smtp;

class person
{
private:
	std::list<fact> flist;
	std::list<fact> freflist;
	std::vector<question> *questionlist;
    float personshowcase(question &qname, list<fact> lf) const;
public:
    QString name;
    QString lastname;
    QString firstname;
    QString email;
    int groupid = -1;
    int	id = -1;
	person();
	virtual ~person();
	void add_fact(string line);
    person(QString name, vector<question> *question);
    person(QString name, QString lastname, QString email);
    person(QString name, QString lastname, QString email, int id, vector<question> *listquestion, int groupid);
    int compare(QString name2);
//	person(string name);
	int getId() const;
	void setId(int value);
	int compare(int id);
    void add_fact(string name, int time, int note, string date, int iteration, int idquestion);
    QString personsend(Smtp *smtp, QString post);
	int getGroupid() const;
	person(const person &person);
    QString getEmail() const;
    QString getLastname() const;
    QString getName() const;
	std::vector<question> *getQuestionlist() const;
	std::list<fact> getFlist() const;
	void personadd(QTableWidget *gbox, int i, group &g);
    float personshowcase(question &qname);
    float personrefshowcase(question & qname);
    std::list<fact> getFreflist() const;
    float personshowcaseval(question &qname, list<fact> lf) const;
    float personshowcaseval(question &qname);
    float personrefshowcaseval(question &qname);
    float personshowcaseval(question &qname, int ref);
    float personshowcase(question &qname, int ref);
};
