#ifndef INFOPERSON_H
#define INFOPERSON_H

#include "le.h"
#include "grouptree.h"
#include "info.h"

class listedit;
class person;

class infoperson : public info
{
	Q_OBJECT
public:
    infoperson(project *p, MainWindow *m);

public slots:
	void updateib(QTreeWidgetItem *item);

private slots:
    void updatebdd();
private:
    QWidget *contp;
	QMetaObject::Connection cotmp;
	QLineEdit *name;
	QLineEdit *lastname;
	QLineEdit *email;
    person *pe = NULL;
	QPushButton *b_update;
    QLabel *infolabel;
	int init;
	int groupid;
    QVBoxLayout *vbox;
    void prephide();
};

#endif // INFOPERSON_H
