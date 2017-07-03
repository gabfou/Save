#pragma once
#include "le.h"

class group;
class fact;
class question;
class Smtp;

// cette classe compile les donnée relatif a une personne;

class person
{
private:
    QList<fact> flist;
	std::vector<question> *questionlist;

public:
    QString name;
    QString lastname;
    QString firstname;
    QString email;
    int jour;
    int iteration = -1;
    int groupid = -1;
    int	id = -1;
    int questionbool;
    int refbool;
	person();
	virtual ~person();
    person(QString name, vector<question> *question);
    person(QString name, QString lastname, QString email, int id, vector<question> *listquestion, int groupid, int questionbool, int refbool, int jour);
    int compare(QString name2);
//	person(string name);
	int getId() const;
	void setId(int value);
	int compare(int id);
    void add_fact(string name, int time, int note, QString date, int iteration, int idquestion, QString timestr);
    QString personsend(Smtp *smtp, QString post);
	int getGroupid() const;
	person(const person &person);
    QString getEmail() const;
    QString getLastname() const;
    QString getName() const;
	std::vector<question> *getQuestionlist() const;
    QList<fact> getFlist() const;
	void personadd(QTableWidget *gbox, int i, group &g);
    QList<fact> getFreflist() const;
    float personshowcaseval(question &qname, int iterationmin = 0, int iterationmax = 2147483640);
    float personshowcasevaltype2(question &qname, QList<fact> lf, QVector<int> *nb, int iterationmin = 0, int iterationmax = 2147483640) const;
    float personshowcasevaltype2(question &qname, QVector<int> *nb, int iterationmin = 0, int iterationmax = 2147483640);
    QString personshowcasestr(question &qname, int iterationmin = 0, int iterationmax = 2147483640);
    QString personshowcasevalstr(question &qname, int iterationmin = 0, int iterationmax = 2147483640);
    float personshowcase(question &qname, int iterationmin = 0, int iterationmax = 2147483640);
    QString getrep(QVector<int> questionid, int iteration, project *p);
    QString time_rep_at_iteration(int it, int *counter, int *counter2);
};
