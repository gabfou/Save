#ifndef FORMGROUPBOX_H
#define FORMGROUPBOX_H

#include "le.h"

// cette classe est un "QGroupBox" contenant une question ou un group elle essaye de simuler comment celle ci sera traiter coté web

class formgroupbox : public QGroupBox
{
    Q_OBJECT
    project *p;
public:
    formgroupbox(question *q, formgroupbox *parrent, project *p, QString text);
    formgroupbox(group *g, formgroupbox *parrent, project *p, QString text);
    question *argq = NULL;
    group *argg = NULL;
    int checkgid(int id, project *p);
    void addchild(formgroupbox *child);
    QList<formgroupbox*> listchild;
    QVBoxLayout *layout;
    QLabel *label;
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void dropEvent(QDropEvent *event);
public slots:
    void sihide();
    void sishow();
signals:
    void visibilychanged(int);
    void clicked(int);
    void updateneeded();
};

#endif // FORMGROUPBOX_H
