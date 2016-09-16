#include "question.h"


question::question()
{
}


question::question(QString name, int groupcible, int id, int qgroupid, QString sujet, QString unit, int type, QString splitchar, int value, bool ref_only, bool global)
{
    this->name = name;
    this->group = groupcible;
	this->id = id;
    this->qgroupid = qgroupid;
	this->sujet = sujet;
	this->unit = unit;
    this->type = type;
    this->liststr = splitchar.split(" ");
    this->val = value;
    this->ref_only = ref_only;
    this->global = global;
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
    this->val = q.val;
    this->ref_only = q.ref_only;
    this->global = q.global;
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
