#ifndef INFOQUESTION_H
#define INFOQUESTION_H

#include "le.h"

class listedit;
class listeditwval;
class grouptree;
class textedit;
#include "info.h"

class infoquestion : public info
{
	Q_OBJECT
public:
    infoquestion(project *p, MainWindow *m, int con = 1);
    QPushButton *b_update;

    question getquestioncopy();
    void setquestionmod(int qgroupid);
    grouptree *groupbox;
public slots:
	void updateib(QTreeWidgetItem *item);
    void updategroup(int id);
    void updatequestion(int id);
private slots:
    void updatebdd();
    void typeshow(int type);
    void changegroupparent();
    void changegroupparent2(QTreeWidgetItem *item);
private:
    QWidget *contq;
    QHBoxLayout *hbox;
	QMetaObject::Connection cotmp;
	QLineEdit *name;
	grouptree *target;
    textedit *description;
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
