#include "question.h"


question::question()
{
}

question::question(string line)
{

}

question::question(string a, int b, int id, int qgroupid)
{
    this->name = a;
    this->group = b;
    this->id = id;
    this->qgroupid = qgroupid;
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
	o << "placeholder";
	return o;
}
