#ifndef PROJECT_H
#define PROJECT_H

#include "le.h"
class person;

class MainWindow;

class project
{
 //   Q_OBJECT

private:
	int nbperson;
	int nbfact;
	int nbquestion;
	int nbgroup;
    int nbpgeneration;
    int nbqgeneration;
    int nbqgroup;
    int nbfactref;
    int nbfactnref;

    void initvar();
    void init();
public:

    QString mtypeq[4];

    int val = 0;
    int ref = 0;
    int gref = 0;
    int gqref = 0;
    void addquestion(QString name, int group, unsigned int id, int qgroupid, QString sujet, QString unit, int type, QString splitchar, int value, bool ref_only, bool global);
    QString name;
    vector<person> listp;
	vector<question> listquestion;
	vector<group> listgroup;
	vector<group> listqgroup;

	void checkmailcalendar();
	project();
    project(QString fproject);
    void initoroject(QString fproject);
	~project();
//public slots:
    void addperson(QString name, QString lastname, QString email);
    void addperson(QString name, QString lastname, QString email, int id, vector<question>* listquestion, int groupid);
	QString postquestion(QString group);
	void addquestion(string name, string group);
    void addreponse(int id, string name, int time, int note, string date, int iteration, int idquestion);
    QStringList sendproject();
	void convert_to_xlsx();
    void addgroup(QString name, int parentid, unsigned int id, int type, QString description, bool gquestion);
	vector<group> getListgroup() const;
	void setListgroup(const vector<group> &value);
	QList<t_groupref> getgrouplist(int id, int qid = 0);
    QList<t_groupref> getgrouplistref(int id, int qid = 0);
	vector<question> getListquestion() const;
    vector<person> getListp() const;
	int getNbperson() const;
	int getNbfact() const;
	int getNbquestion() const;
	int getNbgroup() const;
	int getNbgeneration() const;
    void groupchild(unsigned int id, QList<int> &ret) const;
	void groupqchild(int id, QList<int> &ret) const;
    void groupchild(unsigned int id, QList<int> & ret, vector<group> &g) const;
    question getquestion(int id);
    void questiongroupqchild(int id, QList<int> &ret) const;
    QList<question> questiongroupqchildnotopti(int id);
    person getperson(int id);
    int getNbqgroup() const;
    int getNbfactref() const;
    int getNbfactnref() const;
    int getNbpgeneration() const;
    int getNbqgeneration() const;
    group *groupsearch(QString name, group *g);
    int addqgroup(QString name, QString parrent);
    int mytypqinv(QString type);
};

#endif
