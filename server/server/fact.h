#pragma once
#include "le.h"
#include <QGridLayout>
#include <QString>
typedef struct tm t_tm;

class fact
{
private:
    int		time = -1;
    QString timestr;
    int		note = -1;
    QString notestr;
	string	date;
    time_t	datesys = -1;
public:
    string	factname;

	fact();
	fact(string line);
	virtual ~fact();
    int showfact(QGridLayout *gbox, int i, int j);
    int checkfacttime(string name, int & counter) const;
    QString getTimestr() const;
    int getNote() const;
    void setNote(int value);
    int getTime() const;
    void setTime(int value);
    string getDate() const;
    void setDate(const string &value);
    string getFactname() const;
    void setFactname(const string &value);
    fact(string name, int time, int note, string date);
};

ostream & operator<<(ostream &o, fact const & rhs);
