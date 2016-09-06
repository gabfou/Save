#ifndef INFOPERSON_H
#define INFOPERSON_H

#include "le.h"
#include "grouptree.h"
class listedit;
class person;

class infoperson : public QWidget
{
	Q_OBJECT
public:
    infoperson(project *p, MainWindow *m);

public slots:
	void updateib(QTreeWidgetItem *item);

private slots:
    void updatebdd();
private:
	QMetaObject::Connection cotmp;
	QLineEdit *name;
	QLineEdit *lastname;
	QLineEdit *email;
	project *p;
    person *pe = NULL;
	QPushButton *b_update;
    QLabel *infolabel;
	int init;
	int groupid;
    void prephide();
};

#endif // INFOPERSON_H