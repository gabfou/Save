#pragma once
#include "le.h"

class question
{
public:
	question();
	question(string line);
    question(QString a, int b, int id, int qgroupid, QString sujet, QString unit, int type, QString splitchar, int value, bool ref_only);
	question(string a, string b);
	question(const question &q);
	virtual ~question();
    QString questionrep(string personname, string var);


    QString name;
	QString sujet;
    int group = 0;
    int qgroupid = -1;
    int id = -1;
	int	note;
	int type = 0;
	bool bnote;
    QStringList liststr;
	QString unit;
    int val = -1;
    bool ref_only;
};

ostream & operator<<(ostream &o, question const & rhs);
