#ifndef GROUPTREE_H
#define GROUPTREE_H

#include "le.h"

class project;
class MainWindow;
class group;

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
    int i;
public:
    grouptree();
    ~grouptree();
    MainWindow *m = NULL;
    grouptree(MainWindow *m, vector<group> &g, int i = 0);
public slots:
    void supgroupintree();
    void contextmenuselect();
    void supquestintree();
private slots:
    void addgroupintree();
    void addgroupintree2(QTreeWidgetItem *item, int column);
    void addquestintree2(QTreeWidgetItem *item, int column);
    void addquestintree();
};

#endif // GROUPTREE_H
