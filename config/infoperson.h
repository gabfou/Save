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
    infoperson(MainWindow *m, project *p);

public slots:
	void updateib(QTreeWidgetItem *item);

private slots:
    void updatebdd();
    void changegroupparent();
    void changegroupparent2(QTreeWidgetItem *item);
private:
    MainWindow *m;
    QWidget *contp;
	QMetaObject::Connection cotmp;
	QLineEdit *name;
	QLineEdit *lastname;
	QLineEdit *email;
    person *pe = NULL;
	QPushButton *b_update;
	int init;
	int groupid;
    QVBoxLayout *vbox;
    QPushButton *changegroup;
    void prephide();
};

#endif // INFOPERSON_H
