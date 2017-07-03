
#include "fact.h"
#include <QLabel>
#include <QString>
#include <QDebug>

QString fact::getTimestr() const{return timestr;}
int fact::getNote() const{return note;}
void fact::setNote(int value){note = value;}
int fact::getTime() const{return time;}
void fact::setTime(int value){time = value;}
QString fact::getDate() const{return date;}
void fact::setDate(const QString &value){date = value;}
string fact::getFactname() const{return factname;}
void fact::setFactname(const string &value){factname = value;}

fact::fact()
{
}

fact::fact(string name, int time, int note, QString date, int idquestion, QString timestr, int iteration)
{
	this->factname = name;
	this->note = note;
	this->time = time;
	this->date = date;
    this->idquestion = idquestion;
    this->timestr = timestr;
    this->iteration = iteration;
}

fact::~fact()
{
}


// verifie si le fait est valide selon ces parametres

int fact::checkfacttime(int idquestion, int &counter, int iterationmin, int iterationmax) const
{
    if (this->idquestion == idquestion && iterationmin <= iteration && iterationmax >= iteration)
	{
		counter++;
		return (this->time);
	}
	return (0);
}

// verifie si le fait est valide selon ces parametre

void fact::checkfactstr(int idquestion, int &counter, QStringList &list, QVector<int> *nb, QVector<int> *nbl, int iterationmin, int iterationmax) const
{
    QStringList::iterator i;
    int j = -1;
    if (this->idquestion == idquestion)
    {
        counter++;
        i = list.begin();
        while (i != list.end())
        {
            ++j;
            if (i->compare(this->timestr) == 0)
            {
                (*nb)[j]++;
                (*nbl)[j]++;
                return ;
            }
            i++;
        }
    }
}

ostream & operator<<(ostream & o, fact const & rhs)
{
    (void)rhs;
	o << "placeholder";
	return o;
}
