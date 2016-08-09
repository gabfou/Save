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
    //    std::list<fact> listf;
    void showgroupauxi(QTableWidget *gbox, int *i, int *k, group gtmp, int ref, vector<question>::iterator tmp2);
    //QList<QString> showgroupauxi(QTableWidget *gbox, int *i, int k, group gtmp, int ref, vector<question>::iterator tmp2);
    void showgroupauxi(QTableWidget *gbox, int *i, int k, group gtmp, int ref, vector<question>::iterator tmp2);
    void showgroupauxi(QTableWidget *gbox, int *i, int k, group gtmp, int ref, string questionname);
public:
    group();
    virtual ~group();

    group(string name, int parentid, int id, vector<group> &listgroup, int type);
    void addperson(person p);
    string getName() const;
    void addqfils(int id);
    bool visible = true;
    list<person> getListp();
    void debug();
    void show(QTableWidget *gbox, int *i, const vector<group> & listgroup, int k) const;
    void showgroup(QTableWidget *gbox, int *i, const vector<question> & question, const vector<group> & listgroup, int k) const;
    void addfils(int id);
    int getGeneration() const;
    int getParentid() const;
    void groupsetcolor(int i);
    QColor getColor() const;
    void setColor(const QColor &value);
    std::list<int> getListfils() const;
    QList<QString> grouprep(const vector<question> & questionlist, int ref) const;

    t_groupref groupnamerep(const vector<question> & questionlist, int ref) const;
    QString grouprep(question tmp2, int ref) const;
    int id;
    string name;
    int type = -1;
    std::list<int> getListqfils() const;
    void addquestion(question q);
    std::list<question> getListq() const;
};

#endif // GROUP_H
