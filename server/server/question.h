#pragma once
#include "le.h"

class question
{
private:
	int		note;
public:
	question();
	question(string line);
    question(string a, int b, int id, int qgroupid);
    question(string a, string b);
	virtual ~question();
	string questionrep(string personname, string var);
	string questionrep(string personname);
	string questionform(string personname);
    string name;
    string group = "ALL";
    int qgroupid = 0;
    int id = 0;
};

ostream & operator<<(ostream &o, question const & rhs);
