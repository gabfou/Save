#ifndef FORMLOADATOR_H
#define FORMLOADATOR_H

#include "le.h"

class formloadator : public QScrollArea
{
    Q_OBJECT
public:
    formloadator(bool ref, int gid, project *p);
    int formcreator(bool ref, group *g, QVBoxLayout *layout, int gid = 0, QVBoxLayout *layoutgquestion = NULL);
private slots:
    void updateireel();
    void updateiref();
private:
    project *p;
    QTextEdit *introref;
    QTextEdit *introreel;
};

#endif // FORMLOADATOR_H
