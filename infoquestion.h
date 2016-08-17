#ifndef INFOQUESTION_H
#define INFOQUESTION_H

#include "le.h"
#include "grouptree.h"

class infoquestion : public QWidget
{
	Q_OBJECT
public:
	infoquestion(project *p, MainWindow *m);

public slots:
	void updateib(QTreeWidgetItem *item);

private slots:
	void updatebdd();
private:
	QMetaObject::Connection cotmp;
	QLineEdit *name;
	grouptree *target;
	QLineEdit *description;
	QLineEdit *unit;
	QComboBox *type;
	QSpinBox *value;
	project *p;
	question *q = NULL;
	QPushButton *b_update;
	int init;
	int qgroupid;

};

#endif // INFOQUESTION_H
