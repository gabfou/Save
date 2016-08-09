#ifndef INFOQUESTION_H
#define INFOQUESTION_H

#include "le.h"
#include "grouptree.h"

class infoquestion : public QWidget
{
    Q_OBJECT
public:
    infoquestion(project *p);

public slots:
    void updateib(QTreeWidgetItem *item);

private slots:
    void updatebdd();
private:
    QLineEdit *name;
    grouptree *target;
    QLineEdit *description;
    QLineEdit *unit;
    QComboBox *type;
    QSpinBox *value;
    project *p;
    question *q = NULL;

};

#endif // INFOQUESTION_H
