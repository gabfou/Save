
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

fact::fact(string line)
{
	int i = -1;
	
	while(line[++i] && line[i] != ' ')
		this->factname += line[i];
	if (line[i])
		i++;
	else
		return;
	//	this->time = -1;
	this->time = atoi(&line[i]);
	//this->timestr = this->time;
	while (line[i] && line[i] != ' ')
		i++;
	if (line[i])
		i++;
	else
		return;
	//	this->note = -1;
	this->note = atoi(&line[i]);
	//this->notestr = this->note;
	while (line[i] && line[i] != ' ')
		i++;
	if (line[i])
		i++;
	else
		return;
	//	this->date = -1;
	this->date = &line[i];
}

fact::fact(string name, int time, int note, string date)
{
	this->factname = name;
	this->note = note;
	this->time = time;
	this->date = date;
}

fact::~fact()
{
}

int fact::checkfacttime(string name, int & counter) const
{
	if (strcmp(name.c_str(), this->factname.c_str()) == 0)
	{
		counter++;
		return (this->time);
	}
	return (0);
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
