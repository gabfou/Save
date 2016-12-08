#ifndef GROUPTREE_H
#define GROUPTREE_H

#include "le.h"
#include "data/group.h"
#include "data/person.h"
#include "data/question.h"
#include "data/fact.h"

// cette classe represente une aborecense coté question ou person

class project;
class MainWindow;
class grouptreeitem;
class infoquestion;

class grouptree : public QTreeWidget
{
	Q_OBJECT
	QLineEdit *nametmp = NULL;
	QTreeWidgetItem *tmp;
	int tmpid;
	vector<group> &g;
	QAction *newg;
	QAction *supg;
	QAction *newq;
	QAction *supq;
    QAction *newp;
    QAction *supp;
    QAction *newqg;
    QAction *persinit;
    QPlainTextEdit *texttmp;
    QAction *modifdg;
    QAction *copie;
    QAction *paste;
	QMetaObject::Connection cotmp;
	int i;
    infoquestion *infoqtmp;

    int copietype = -1;
    group copieg;
    question copieq;
    person copiep;
public:
	grouptree();
	~grouptree();
    MainWindow *m = NULL;
    grouptree(MainWindow *m, vector<group> &g, int i = 0);
    void setcurrentgroup(int id, QTreeWidgetItem *dontgiveit = NULL);
public slots:
	void supgroupintree();
	void contextmenuselect();
    void supquestintree();
    void modifdgroupintree();
    void setVisiblenongroup(bool v);
private slots:
	void addgroupintree();
    void addgroupintree2(QTreeWidgetItem *item);
	void addquestintree2(QTreeWidgetItem *item, int column);
    void addquestintree();
    void modifdgroupintree2();
    void addpersonintree();
    void addpersonintree2(QTreeWidgetItem *item, int column);
    void suppersonintree();
    void addquestglobintree();
    void addquestglobintree2();
    void initpersonintree();
    void pastintree();
    void copieintree();
signals:
    void selectgroupchange(int);
};

#endif // GROUPTREE_H
