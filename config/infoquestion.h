#ifndef INFOQUESTION_H
#define INFOQUESTION_H

#include "le.h"
#include "grouptree.h"
class listedit;

class infoquestion : public QWidget
{
	Q_OBJECT
public:
    infoquestion(project *p, MainWindow *m);

public slots:
	void updateib(QTreeWidgetItem *item);

private slots:
    void updatebdd();
    void typeshow(int type);
private:
    grouptree *groupbox;
	QMetaObject::Connection cotmp;
	QLineEdit *name;
	grouptree *target;
	QLineEdit *description;
	QLineEdit *unit;
	QComboBox *type;
	QSpinBox *value;
	project *p;
    MainWindow *m;
	question *q = NULL;
	QPushButton *b_update;
    listedit *selectlist;
    QLabel *selectlistlabel;
    QLabel *unitlabel;
    QLabel *infolabel;
	int init;
	int qgroupid;
    QStringList listchar;
    QCheckBox *ref_only;

    void prephide();
};

#endif // INFOQUESTION_H
