#include "question.h"


question::question()
{
}


question::question(string a, int b, int id, int qgroupid, QString sujet, QString unit, int type, QString splitchar)
{
	this->name = a;
	this->group = b;
	this->id = id;
	this->qgroupid = qgroupid;
	this->sujet = sujet;
	this->unit = unit;
    this->type = type;
    this->liststr = splitchar.split(" ");
}

question::question(const question &q)
{
	this->group = q.group;
	this->id = q.id;
	this->name = q.name;
	this->qgroupid = q.qgroupid;
	this->note = q.note;
	this->unit = q.unit;
    this->type = q.type;
    this->liststr = q.liststr;
	this->sujet = q.sujet;
}

question::~question()
{
}

string question::questionrep(string personname, string var)
{
	string ret;

	ret += "fputs(" + var + ", \"\\n\".'" + this->name + " '.$_POST[\"" + personname + this->name + "temps\"].'" + " '.$_POST[\"" + personname + this->name + "note\"]);\n";
	return (ret);
}

string question::questionform(string personname)
{
	string ret;

	ret += "<p>intro question; ";
	ret += this->name;
	ret +=	" </p>";
	ret += "<p>temps : <input type = \"text\" name = \"";
	ret += personname;
	ret += this->name;
	ret += "temps\" / ></p>\n";
	ret += "<p>note : <input type = \"text\" name = \"";
	ret += personname;
	ret += this->name;
	ret += "note\" / ></p>\n";
	return (ret);
}

ostream & operator<<(ostream & o, question const & rhs)
{
    (void)rhs;
	o << "placeholder";
	return o;
}
