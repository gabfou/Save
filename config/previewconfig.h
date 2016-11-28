#ifndef PREVIEWCONFIG_H
#define PREVIEWCONFIG_H

#include "le.h"

class grouptree;
class formloadator;

class previewconfig : public QWidget
{
    Q_OBJECT

    QWidget *indexinit();
    QTextEdit *introindex;
    QTextEdit *introref;
    QTextEdit *introreel;
    QTabWidget *preview;
    formloadator *refpreview;
    formloadator *reelpreview;
    project *p;
    QScrollArea *initform(bool ref);
    grouptree *groupboxtmp;
public:
    previewconfig(MainWindow *m);
private slots:
    void updateiindex();
    void updateireel();
    void updateiref();
};

#endif // PREVIEWCONFIG_H
