#pragma once
#include "le.h"

class group;
class fact;
class question;
class Smtp;

class person
{
private:
    QList<fact> flist;
    QList<fact> freflist;
	std::vector<question> *questionlist;
    float personshowcase(question &qname, QList<fact> lf) const;
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
    QList<fact> getFlist() const;
	void personadd(QTableWidget *gbox, int i, group &g);
    float personshowcase(question &qname);
    float personrefshowcase(question & qname);
    QList<fact> getFreflist() const;
    float personshowcaseval(question &qname, QList<fact> lf) const;
    float personshowcaseval(question &qname);
    float personrefshowcaseval(question &qname);
    float personshowcaseval(question &qname, int ref);
    float personshowcase(question &qname, int ref);
    float personshowcasevaltype2(question &qname, QList<fact> lf, QVector<int> *nb) const;
    float personshowcasevaltype2(question &qname, int ref, QVector<int> *nb);
};
