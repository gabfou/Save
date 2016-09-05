#ifndef GROUPTREE_H
#define GROUPTREE_H

#include "le.h"

class project;
class MainWindow;
class group;
class grouptreeitem;

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
    QPlainTextEdit *texttmp;
    QAction *modifdg;
	QMetaObject::Connection cotmp;
	int i;
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
private slots:
	void addgroupintree();
	void addgroupintree2(QTreeWidgetItem *item, int column);
	void addquestintree2(QTreeWidgetItem *item, int column);
    void addquestintree();
    void modifdgroupintree2();
    void addpersonintree();
    void addpersonintree2(QTreeWidgetItem *item, int column);
    void suppersonintree();
};

#endif // GROUPTREE_H
