#ifndef FORMLOADATOR_H
#define FORMLOADATOR_H

#include "le.h"

#include "formgroupbox.h"
class MRichTextEdit;

// cette classe represente une preview d'un formulaire (2eme page du site web);

class formloadator : public QScrollArea
{
    Q_OBJECT
public:
    formloadator(bool ref, int gid, project *p);
    int formcreator(bool ref, group *g, QVBoxLayout *layout, int gid = 0, formgroupbox *wgquestion = NULL);
    void gidupdate(int gid);
public slots:
    int reformcreator();
private slots:
    void updateireel();
    void updateiref();
    void emitquestionclicked(int id);
    void emitgroupclicked(int id);
private:
    int gid;
    int ref;
    project *p;
    MRichTextEdit *introref;
    MRichTextEdit *introreel;
    QList<formgroupbox*> checklistparrent;
    QVBoxLayout *layout;
    QWidget *ret;
signals:
    void groupclicked(int);
    void questionclicked(int);
};

#endif // FORMLOADATOR_H
