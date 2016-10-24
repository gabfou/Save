
#include "fact.h"
#include <QLabel>
#include <QString>
#include <QDebug>

QString fact::getTimestr() const{return timestr;}
int fact::getNote() const{return note;}
void fact::setNote(int value){note = value;}
int fact::getTime() const{return time;}
void fact::setTime(int value){time = value;}
string fact::getDate() const{return date;}
void fact::setDate(const string &value){date = value;}
string fact::getFactname() const{return factname;}
void fact::setFactname(const string &value){factname = value;}

fact::fact()
{
}

fact::fact(string name, int time, int note, string date, int idquestion)
{
	this->factname = name;
	this->note = note;
	this->time = time;
	this->date = date;
    this->idquestion = idquestion;
}

fact::~fact()
{
}


int fact::checkfacttime(int idquestion, int &counter) const
{
    if (this->idquestion == idquestion)
	{
		counter++;
		return (this->time);
	}
	return (0);
}

void fact::checkfactstr(int idquestion, int &counter, QStringList &list, QVector<int> *nb, QVector<int> *nbl) const
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

int fact::showfact(QGridLayout *gbox, int i, int j)
{
	QLabel *time = new QLabel();
	time->setText(QString::number(this->time));
	time->setStyleSheet("border: 2px solid grey");
	gbox->addWidget(time, i, j++);
	QLabel *note = new QLabel();
	note->setText(QString::number(this->note));
	note->setStyleSheet("border: 2px solid grey");
	gbox->addWidget(note, i, j++);
	cout << this->factname << " " << this->time << "min " << this->note << " / 5\n";
	return (j);
}

ostream & operator<<(ostream & o, fact const & rhs)
{
    (void)rhs;
	o << "placeholder";
	return o;
}
