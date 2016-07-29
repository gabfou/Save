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
public:
    grouptree();
    ~grouptree();
    MainWindow *m = NULL;
    grouptree(MainWindow *m, vector<group> &g);
private slots:
    void addgroupintree();
    void addgroupintree2(QTreeWidgetItem *item, int column);
};

#endif // GROUPTREE_H
