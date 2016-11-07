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
	//	std::list<fact> listf;
	void showgroupauxi(QTableWidget *gbox, int *i, int *k, group gtmp, int ref, vector<question>::iterator tmp2);
	//QList<QString> showgroupauxi(QTableWidget *gbox, int *i, int k, group gtmp, int ref, vector<question>::iterator tmp2);
	void showgroupauxi(QTableWidget *gbox, int *i, int k, group gtmp, int ref, vector<question>::iterator tmp2);
	void showgroupauxi(QTableWidget *gbox, int *i, int k, group gtmp, int ref, string questionname);
public:
    int parentid;
	group();
	virtual ~group();

    group(QString name, int parentid, int id, vector<group> &listgroup, int type, QString description, bool gquestion);
	void addperson(person p);
    QString getName() const;
	void addqfils(int id);
	bool visible = true;
    QList<person> getListp();
    void debug();
	void addfils(int id);
	int getGeneration() const;
	int getParentid() const;
	void groupsetcolor(int i);
	QColor getColor() const;
	void setColor(const QColor &value);
    QList<int> getListfils() const;
    QList<float> grouprep(const vector<question> & questionlist, int ref, QList<int> listqchild);

    t_groupref groupnamerep(const vector<question> & questionlist, int ref, QList<int> listqchild);
    QString grouprep(question tmp2, int ref);
	int id;
    QString name;
    QString description;
    bool gquestion;
	int type = -1;
    QList<int> getListqfils() const;
	void addquestion(question q);
    QList<question> getListq() const;
    bool contain(person &p);
    bool contain(question &q);
    float grouprepall(question tmp2, vector<group> &g);
    int init = 0;
    void supquestion(int id);
    void supperson(int id);
    QString grouprepval(question tmp2, int ref);
    QString grouprep(group &groupp, QString tmp3, int ref, question *ret = NULL);
    QString grouprepvaltype2(question tmp2, int ref);
    void changegroupidallqchild(project *p, int groupid);
    void changequestion(int id, question &q);
    void changeperson(int id, person &p);
};

#endif // GROUP_H
