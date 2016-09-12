#ifndef INFOQUESTION_H
#define INFOQUESTION_H

#include "le.h"
#include "grouptree.h"
#include "info.h"

class listedit;

class infoquestion : public info
{
	Q_OBJECT
public:
    infoquestion(project *p, MainWindow *m, int con = 1);
    QPushButton *b_update;

    question getquestioncopy();
    void setquestionmod(int qgroupid);
public slots:
	void updateib(QTreeWidgetItem *item);

private slots:
    void updatebdd();
    void typeshow(int type);
private:
    QWidget *contq;
    QHBoxLayout *hbox;
    grouptree *groupbox;
	QMetaObject::Connection cotmp;
	QLineEdit *name;
	grouptree *target;
	QLineEdit *description;
	QLineEdit *unit;
	QComboBox *type;
    QSpinBox *value;
    MainWindow *m;
	question *q = NULL;
    listedit *selectlist;
    QLabel *selectlistlabel;
    QLabel *unitlabel;
	int init;
	int qgroupid;
    QStringList listchar;
    QCheckBox *ref_only;

    void prephide();
};

#endif // INFOQUESTION_H
