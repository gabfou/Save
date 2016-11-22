#ifndef INFOQUESTION_H
#define INFOQUESTION_H

#include "le.h"

class listedit;
class listeditwval;
#include "grouptree.h"
#include "info.h"

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
    void changegroupparent();
    void changegroupparent2(QTreeWidgetItem *item);
private:
    QWidget *contq;
    QHBoxLayout *hbox;
    grouptree *groupbox;
	QMetaObject::Connection cotmp;
	QLineEdit *name;
	grouptree *target;
    QTextEdit *description;
	QLineEdit *unit;
	QComboBox *type;
    QSpinBox *value;
	question *q = NULL;
    listedit *selectlist;
    listeditwval *selectlistval;
    QLabel *selectlistlabel;
    QLabel *unitlabel;
    QSpinBox *min;
    QSpinBox *max;
    QLabel *minlabel;
    QLabel *maxlabel;
    int init;
	int qgroupid;
    QStringList listchar;
    QComboBox *ref_only;
    QPushButton *changegroup;
    QLabel * changegrouplabel;
    QHBoxLayout *minmaxbox;
    QCheckBox *maxenabled;
    void prephide();
};

#endif // INFOQUESTION_H
