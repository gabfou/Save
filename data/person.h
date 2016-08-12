#pragma once
#include "le.h"
#include "fact.h"
#include "question.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include "smtp.h"

class group;

class person
{
private:
    std::list<fact> flist;
    std::list<fact> freflist;
    std::vector<question> *questionlist;
	string name;
    string lastname;
    string email;
    int groupid = 0;
public:
    int    id;
	person();
	virtual ~person();
	void add_fact(string line);
    void personshow(QTableWidget *gbox, int i, int k, group parent, int ref) const;
	void personsend();
    person(string name, vector<question> *question);
    person(string name, string lastname, string email);
    person(string name, string lastname, string email, int id, vector<question> *listquestion, int groupid);
	int compare(string name2);
//	person(string name);
    int getId() const;
    void setId(int value);
    int compare(int id);
    void add_fact(string name, int time, int note, string date, int iteration);
    QString personsend(Smtp *smtp, QString post);
    int getGroupid() const;
    person(const person &person);
    string getEmail() const;
    string getLastname() const;
    string getName() const;
    std::vector<question> *getQuestionlist() const;
    std::list<fact> getFlist() const;
    void personadd(QTableWidget *gbox, int i, group &g);
    int personshowcase(string qname) const;
    void personrefshow(QTableWidget *gbox, int i, int k) const;
    int personrefshowcase(string qname) const;
    std::list<fact> getFreflist() const;
};
