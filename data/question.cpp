#include "question.h"
#include "project.h"
#include "group.h"


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
    this->liststr = splitchar.split("\n");
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

QString question::getnamereal(project *p)
{
    QString rep;
    int gtmp = qgroupid;

    while (p->listqgroup[gtmp].gquestion)
    {
        rep += p->listqgroup[gtmp].name + ": ";
        gtmp = p->listqgroup[gtmp].parentid;
    }
    rep += name;
    return (rep);
}

ostream & operator<<(ostream & o, question const & rhs)
{
    (void)rhs;
	o << "placeholder";
	return o;
}
