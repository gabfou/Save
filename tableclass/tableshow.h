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
    tableshow(project * p, MainWindow *mainp, int *showmode);

    void showtable(MainWindow *Mainp, int k, int id, int i, int qid);
	void sethorizontalheader(MainWindow *mainp);
	void updateall();
	void clearheader();
    void select(int gref, int gqref);
	void setverticalheader(vector<question> &q, int id);
	void setverticalheader(vector<group> &g, int id);
    tableshow(project *p, int ref, int *showmode);
	void reinit(project *p, MainWindow *mainp);
private:
	project * p;
    int *showmode;
	//const T & curentarg;
	int k;
	void populate();
};

#endif // TABLESHOW_H
