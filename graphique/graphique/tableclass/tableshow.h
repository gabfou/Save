#ifndef TABLESHOW_H
#define TABLESHOW_H

#include "le.h"

class project;
class person;
class group;
class question;
class MainWindow;

class tableshow : public QTableWidget
{
    Q_OBJECT
public:
    tableshow(project * p, MainWindow *Main);

    void showtable(MainWindow *Main, int k, int id, int i);
    void sethorizontalheader(MainWindow *main);
    void updateall();
    void clearheader();
    void select(int gref);
    void setverticalheader(vector<question> &q, int id);
    void setverticalheader(vector<group> &g, int id);
private:
    project * p;
    //const T & curentarg;
    int k;
    void populate();
};

#endif // TABLESHOW_H
