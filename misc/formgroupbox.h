#ifndef FORMGROUPBOX_H
#define FORMGROUPBOX_H

#include "le.h"

class formgroupbox : public QGroupBox
{
    Q_OBJECT
    void mousePressEvent(QMouseEvent *event);
    void dropEvent(QDropEvent *event);
    project *p;
public:
    formgroupbox(question *q, formgroupbox *parrent, project *p);
    formgroupbox(group *g, formgroupbox *parrent, project *p);
    question *argq = NULL;
    group *argg = NULL;
    int checkgid(int id, project *p);
    void addchild(formgroupbox *child);
    QList<formgroupbox*> listchild;
    void dragEnterEvent(QDragEnterEvent *event);
public slots:
    void sihide();
    void sishow();
signals:
    void visibilychanged(int);
    void clicked(int);
    void updateneeded();
};

#endif // FORMGROUPBOX_H
