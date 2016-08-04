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
    string name;
    void addquestion(string name, int group, int id, int qgroupid);
public:
    list<person> listp;
    vector<question> listquestion;
    vector<group> listgroup;
    vector<group> listqgroup;

    void checkmailcalendar();
    project();
    project(string fproject);
    void send();
    void initoroject(string fproject);
    ~project();
//public slots:
    void	projectshow(MainWindow *main, QTableWidget *gbox, int grefid);
    void addperson(string name, string lastname, string email);
    void addperson(string name, string lastname, string email, int id, vector<question> listquestion, int groupid);
    QString postquestion(QString group);
    void addquestion(string name, string group);
    void addreponse(int id, string name, int time, int note, string date, int iteration);
    QStringList sendproject(Smtp *smtp);
    void convert_to_xlsx();
    void addgroup(string name, int parentid, int id, int type);
    vector<group> getListgroup() const;
    void setListgroup(const vector<group> &value);
    void projectgroupshow(MainWindow *qMain, QTableWidget *gbox, int k, int id, int *i);
    QList<t_groupref> getgrouplist(int id);
    QList<t_groupref> getgrouplistref(int id);
    vector<question> getListquestion() const;
    list<person> getListp() const;
    int getNbperson() const;
    int getNbfact() const;
    int getNbquestion() const;
    int getNbgroup() const;
    int getNbgeneration() const;
    void groupchild(int id, QList<int> &ret) const;
    void groupqchild(int id, QList<int> &ret) const;
};

