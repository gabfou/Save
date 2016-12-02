#ifndef FORMGROUPBOX_H
#define FORMGROUPBOX_H

#include "le.h"

class formgroupbox : public QGroupBox
{
    Q_OBJECT
    void mousePressEvent(QMouseEvent *event);
public:
    formgroupbox(question *q, formgroupbox *parrent);
    formgroupbox(group *g, formgroupbox *parrent);
    question *argq = NULL;
    group *argg = NULL;
    int checkgid(int id, project *p);
    void addchild(formgroupbox *child);
    QList<formgroupbox*> listchild;
public slots:
    void sihide();
    void sishow();
signals:
    void visibilychanged(int);
    void clicked(int);
};

#endif // FORMGROUPBOX_H
