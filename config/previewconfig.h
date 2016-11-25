#ifndef PREVIEWCONFIG_H
#define PREVIEWCONFIG_H

#include "le.h"

class previewconfig : public QWidget
{
    Q_OBJECT

    QWidget *indexinit();
    QTextEdit *introindex;
    QTextEdit *introref;
    QTextEdit *introreel;
    project *p;
    QWidget *initform(bool ref);
    void formloadator(bool ref, group *g, QVBoxLayout *layout, QVBoxLayout *layoutgquestion = NULL);
public:
    previewconfig(project *p);
private slots:
    void *updateiindex();
    void *updateireel();
    void *updateiref();
};

#endif // PREVIEWCONFIG_H
