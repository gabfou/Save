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

    QString introref;
    QString introindex;
    QString introreel;
    int val = 0;
    int ref = 0;
    int gref = 0;
    int gqref = 0;
    int default_table = 0;
    int iterationmax = 0;
    int iterationmin = 0;
    bool sugestion = 1;
    void addquestion(QString name, int group, unsigned int id, int qgroupid, QString sujet, QString unit, int type, QString splitchar, int value, int ref_only, bool global);
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
    void addperson(QString name, QString lastname, QString email, int id, vector<question>* listquestion, int groupid, int questionbool, int refbool);
	QString postquestion(QString group);
	void addquestion(string name, string group);
    void addreponse(int id, string name, int time, int note, QString date, int iteration, int idquestion, QString timestr);
    QStringList sendproject(int group);
	void convert_to_xlsx();
    void addgroup(QString name, int parentid, unsigned int id, int type, QString description, bool gquestion);
	vector<group> getListgroup() const;
	void setListgroup(const vector<group> &value);
    QList<t_groupref> getgrouplist(int id, int qid = 0, int iterationmin = 1, int iterationmax = 2147483640);
	vector<question> getListquestion() const;
    QList<int> getlistallfils(int gid);
    vector<person> getListp() const;
	int getNbperson() const;
	int getNbfact() const;
	int getNbquestion() const;
	int getNbgroup() const;
	int getNbgeneration() const;
    void groupchild(unsigned int id, QList<int> &ret) const;
    void groupqchild(int id, QList<int> &ret, int gref = 0) const;
    void groupchild(unsigned int id, QList<int> & ret, vector<group> &g) const;
    question getquestion(int id);
    void questiongroupqchild(int id, QList<int> &ret, bool ref = 1) const;
    QList<question> questiongroupqchildnotopti(int id, bool ref = 1);
    person getperson(int id);
    int getNbqgroup() const;
    int getNbfactref() const;
    int getNbfactnref() const;
    int getNbpgeneration() const;
    int getNbqgeneration() const;
    group *groupsearch(QString name, group *g);
    int addqgroup(QString name, QString parrent);
    int mytypqinv(QString type);
    int addpgroup(QString name, QString parrent);
    QList<person> getListallpfils(int group);
};

#endif
