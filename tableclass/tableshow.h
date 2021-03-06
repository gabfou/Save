#ifndef TABLESHOW_H
#define TABLESHOW_H

#include "le.h"

class project;
class person;
class group;
class question;
class MainWindow;
class headertableitem;

class tableshow : public QTableWidget
{
	// cette classe represente le tablaux afficher
	Q_OBJECT
public:
	tableshow(project * p, MainWindow *mainp, int showmode);

    void showtable(int id, int qid, int itmin, int itmax);
	void sethorizontalheader(MainWindow *mainp);
	void clearheader();
    void select(int gref, int gqref, int itmin, int itmax);
	void setverticalheader(vector<question> &q, int id);
	void setverticalheader(vector<group> &g, int id);
	void reinit(project *p, MainWindow *mainp);
	tableshow(MainWindow *m, project *p, int showmode);
	void sethorizontalheader(QList<headertableitem *> &list, int nc = 0);
	void setverticalheader(QList<headertableitem *> &listh, int nc = 0);
	void reinit(QList<headertableitem *> &listv, QList<headertableitem *> &listh);
	tableshow(MainWindow *m, QList<headertableitem *> &listv, QList<headertableitem *> &listh);
	void reinit();

	void setverticalheader(vector<person> &g);
public slots:
	void selectp(int gref);
	void selectq(int gqref);
	void updateall();
    void reselectm();
private slots:
	void saveqpoint(QPoint qpoint);
	void suphheader();
	void supvheader();
	void modifhheader();
	void modifvheader();
	void saveqpoint();
private:
	QMenu *menuhead;
	project * p;
	int showmode;
	MainWindow *m;
	//const T & curentarg;
	int k;
	QPoint lastqpoint;
	void populate();
	void preinit();
	void postinit();
	void prepostinit();
};

#endif // TABLESHOW_H
