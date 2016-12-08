#ifndef HEADERTABLEITEM_H
#define HEADERTABLEITEM_H

#include "le.h"

#include "data/fact.h"
#include "data/group.h"
#include "data/person.h"
#include "data/question.h"

// cette clase repredente un header d'un des 3 tableaux principaux

class headertableitem : public QObject, public QTableWidgetItem
{
    Q_OBJECT
public:
	//headertableitem();

	QString getFormule() const;
	void setFormule(const QString &value);

    headertableitem(project *p, QString str, QString form = "", int id = -1);
    virtual ~headertableitem();
    project *p;
    int type = -1;
	int groupe = 0;
	void *arg = NULL;
    group argg;
    person argp;
    question argq;
    QString argstr;
    QList<question> *arglistq = NULL;
    int id = -1;
    QString formule = "";
    headertableitem(project *p, QString str, group arg, QString form = "");
    headertableitem(project *p, QString str, person arg, QString form = "");
    headertableitem(project *p, QString str, question arg, QString form = "");
    bool is_in(vector<group> &g, vector<group> &gq, QList<int> listint, QList<int> listqint, int itmin, int itmax);
    headertableitem(project *p, QString str, QString arg, QString form);
    headertableitem(project *p, QString str, QList<question> *arg, QString form);
public slots:
    void changearg(QTreeWidgetItem *item);
};

#endif // HEADERTABLEITEM_H
