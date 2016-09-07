#pragma once
#include "le.h"
#include "person.h"
#include "group.h"
#include <QObject>
#include <QString>
#include "group.h"
//#include "../../graphique/graphique/mainwindow.h"

class MainWindow;

class project
{
 //   Q_OBJECT

private:
	int nbperson = 0;
	int nbfact = 0;
	int nbquestion = 0;
	int nbgroup = 0;
	int nbgeneration = 0;
    int val = 0;

public:
    int ref = 0;
    int gref = 0;
    int gqref = 0;
    void addquestion(QString name, int group, unsigned int id, int qgroupid, QString sujet, QString unit, int type, QString splitchar);
	string name;
    vector<person> listp;
	vector<question> listquestion;
	vector<group> listgroup;
	vector<group> listqgroup;

	void checkmailcalendar();
	project();
	project(string fproject);
	void initoroject(string fproject);
	~project();
//public slots:
    void addperson(QString name, QString lastname, QString email);
    void addperson(QString name, QString lastname, QString email, int id, vector<question>* listquestion, int groupid);
	QString postquestion(QString group);
	void addquestion(string name, string group);
    void addreponse(int id, string name, int time, int note, string date, int iteration, int idquestion);
    QStringList sendproject(Smtp *smtp);
	void convert_to_xlsx();
    void addgroup(string name, int parentid, unsigned int id, int type, QString description);
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
    vector<question> questiongroupqchildnotopti(int id);
    person getperson(int id);
};

