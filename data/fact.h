#pragma once
#include "le.h"
typedef struct tm t_tm;

class fact
{
private:
	int		note = -1;
	QString notestr;
    QString	date;
	time_t	datesys = -1;
public:
    int		time = -1;
    QString timestr;
    string	factname;
    int idquestion = -1;
    int iteration;

	fact();
	fact(string line);
	virtual ~fact();
	int showfact(QGridLayout *gbox, int i, int j);
    int checkfacttime(int idquestion, int &counter, int iterationmin = -1, int iterationmax = 2147483640) const;
	QString getTimestr() const;
	int getNote() const;
	void setNote(int value);
	int getTime() const;
	void setTime(int value);
    QString getDate() const;
    void setDate(const QString &value);
	string getFactname() const;
	void setFactname(const string &value);
    fact(string name, int time, int note, QString date, int idquestion, QString timestr, int iteration);
    void checkfactstr(int idquestion, int &counter, QStringList &list, QVector<int> *nb, QVector<int> *nbl, int iterationmin = -1, int iterationmax = 2147483640) const;
};

ostream & operator<<(ostream &o, fact const & rhs);
