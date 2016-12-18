#ifndef GROUP_H
#define GROUP_H

#include "le.h"

class person;
class question;

class group
{
private:
	int generation = 0;
    QList<person> listp;
    QList<question> listq;
    QList<int> listfils;
	QColor color;
    project *p;
	//	std::list<fact> listf;
	void showgroupauxi(QTableWidget *gbox, int *i, int *k, group gtmp, int ref, vector<question>::iterator tmp2);
	//QList<QString> showgroupauxi(QTableWidget *gbox, int *i, int k, group gtmp, int ref, vector<question>::iterator tmp2);
	void showgroupauxi(QTableWidget *gbox, int *i, int k, group gtmp, int ref, vector<question>::iterator tmp2);
	void showgroupauxi(QTableWidget *gbox, int *i, int k, group gtmp, int ref, string questionname);
public:
    int parentid;
	group();
	virtual ~group();

    group(QString name, int parentid, int id, vector<group> &listgroup, int type, QString description, int gquestion, project *p);
	void addperson(person p);
    QString getName() const;
	void addqfils(int id);
	bool visible = true;
    QList<person> getListp() const;
    void debug();
	void addfils(int id);
	int getGeneration() const;
	int getParentid() const;
	void groupsetcolor(int i);
	QColor getColor() const;
	void setColor(const QColor &value);
    QList<int> getListfils() const;
    QList<float> grouprep(const vector<question> & questionlist, QList<int> listqchild, int iterationmin = 0, int iterationmax = 2147483640);

    t_groupref groupnamerep(const vector<question> & questionlist, QList<int> listqchild, int iterationmin = 0, int iterationmax = 2147483640);
    QString grouprep(question tmp2, int iterationmin = 0, int iterationmax = 2147483640, int *nbp = NULL);
	int id;
    QString name;
    QString description;
    int gquestion;
	int type = -1;
    QList<int> getListqfils() const;
	void addquestion(question q);
    QList<question> getListq() const;
    bool contain(person &p);
    bool contain(question &q);
    float grouprepall(question tmp2, vector<group> &g, int iterationmin = 0, int iterationmax = 2147483640, int *nbp = NULL);
    int init = 0;
    void supquestion(int id);
    void supperson(int id);
    QString grouprepval(question tmp2, int iterationmin = 0, int iterationmax = 2147483640);
    QString grouprep(group &groupp, QString tmp3, question *ret = NULL, int iterationmin = 0, int iterationmax = 2147483640);
    QString grouprepvaltype2(question tmp2, int iterationmin = 0, int iterationmax = 2147483640);
    void changegroupidallqchild(project *p, int groupid);
    void changequestion(int id, question &q);
    void changeperson(int id, person &p);
    t_groupref groupnameallrep(const vector<question> &questionlist, QList<int> listqchild, int iterationmin, int iterationmax);
    QList<float> grouprepall(const vector<question> &questionlist, QList<int> listqchild, int iterationmin, int iterationmax);
    group(const group &g);
};

#endif // GROUP_H
