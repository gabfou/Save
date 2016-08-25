#pragma once
#include "le.h"

class question
{
public:
	question();
	question(string line);
    question(string a, int b, int id, int qgroupid, QString sujet, QString unit, int type, QString splitchar);
	question(string a, string b);
	question(const question &q);
	virtual ~question();
	string questionrep(string personname, string var);
	string questionrep(string personname);
	string questionform(string personname);
	string name;
	QString sujet;
	string group = "ALL";
    int qgroupid = -1;
    int id = -1;
	int	note;
	int type = 0;
	bool bnote;
    QStringList liststr;
	QString unit;
};

ostream & operator<<(ostream &o, question const & rhs);
