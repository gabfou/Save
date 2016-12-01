#ifndef FORMLOADATOR_H
#define FORMLOADATOR_H

#include "le.h"

#include "formgroupbox.h"

class formloadator : public QScrollArea
{
    Q_OBJECT
public:
    formloadator(bool ref, int gid, project *p);
    int formcreator(bool ref, group *g, QVBoxLayout *layout, int gid = 0, QVBoxLayout *layoutgquestion = NULL, formgroupbox *wgquestion = NULL);
    void gidupdate(int gid);
private slots:
    void updateireel();
    void updateiref();
    void emitquestionclicked(int id);
    void emitgroupclicked(int id);
private:
    project *p;
    QTextEdit *introref;
    QTextEdit *introreel;
    QList<formgroupbox*> checklistparrent;
    QVBoxLayout *layout;
    QWidget *ret;
signals:
    void groupclicked(int);
    void questionclicked(int);
};

#endif // FORMLOADATOR_H
