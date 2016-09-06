#ifndef HEADERTABLEITEM_H
#define HEADERTABLEITEM_H

#include "le.h"

#include "data/group.h"
#include "data/person.h"
#include "data/question.h"

class headertableitem : public QObject, public QTableWidgetItem
{
    Q_OBJECT
public:
	//headertableitem();

	QString getFormule() const;
	void setFormule(const QString &value);

    headertableitem(project *p, QString str, QString form = "", int id = -1);
	QString formule = "";
	int groupe = 0;
	int id = -1;
    int type = -1;
	void *arg = NULL;
	group argg;
	person argp;
	question argq;
    project *p;
    headertableitem(project *p, QString str, group arg, QString form = "");
    headertableitem(project *p, QString str, person arg, QString form = "");
    headertableitem(project *p, QString str, question arg, QString form = "");
    bool is_in(vector<group> &g, vector<group> &gq, QList<int> listint, QList<int> listqint);
public slots:
    void changearg(QTreeWidgetItem *item);
};

#endif // HEADERTABLEITEM_H