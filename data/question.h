#pragma once
#include "le.h"

class question
{
public:
	question();
	question(string line);
    question(QString name, int groupcible, int id, int qgroupid, QString sujet, QString unit, int type, QString splitchar, int value, bool ref_only, bool global);
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
    bool global;
    bool ref_only;
    QString getnamereal(project *p);
};

ostream & operator<<(ostream &o, question const & rhs);
