#include "question.h"


question::question()
{
}


question::question(QString a, int b, int id, int qgroupid, QString sujet, QString unit, int type, QString splitchar)
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

ostream & operator<<(ostream & o, question const & rhs)
{
    (void)rhs;
	o << "placeholder";
	return o;
}
