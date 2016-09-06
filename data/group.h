#ifndef GROUP_H
#define GROUP_H

#include "le.h"

class person;
class question;

class group
{
private:
	int parentid;
	int generation = 0;
	std::list<person> listp;
	std::list<question> listq;
	std::list<int> listfils;
	QColor color;
	//	std::list<fact> listf;
	void showgroupauxi(QTableWidget *gbox, int *i, int *k, group gtmp, int ref, vector<question>::iterator tmp2);
	//QList<QString> showgroupauxi(QTableWidget *gbox, int *i, int k, group gtmp, int ref, vector<question>::iterator tmp2);
	void showgroupauxi(QTableWidget *gbox, int *i, int k, group gtmp, int ref, vector<question>::iterator tmp2);
	void showgroupauxi(QTableWidget *gbox, int *i, int k, group gtmp, int ref, string questionname);
public:
	group();
	virtual ~group();

    group(string name, int parentid, int id, vector<group> &listgroup, int type, QString description);
	void addperson(person p);
	string getName() const;
	void addqfils(int id);
	bool visible = true;
	list<person> getListp();
    void debug();
	void addfils(int id);
	int getGeneration() const;
	int getParentid() const;
	void groupsetcolor(int i);
	QColor getColor() const;
	void setColor(const QColor &value);
	std::list<int> getListfils() const;
    QList<float> grouprep(const vector<question> & questionlist, int ref, QList<int> listqchild);

    t_groupref groupnamerep(const vector<question> & questionlist, int ref, QList<int> listqchild);
    QString grouprep(question tmp2, int ref);
	int id;
	string name;
    QString description;
	int type = -1;
	std::list<int> getListqfils() const;
	void addquestion(question q);
    std::list<question> getListq() const;
    bool contain(person &p);
    bool contain(question &q);
    float grouprepall(question tmp2, vector<group> &g);
    int init = 0;
    void supquestion(int id);
    void supperson(int id);
};

#endif // GROUP_H