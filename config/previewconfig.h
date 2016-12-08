#ifndef PREVIEWCONFIG_H
#define PREVIEWCONFIG_H

#include "le.h"

class grouptree;
class formloadator;
class infoquestion;
class MRichTextEdit;

// cette classe represente l'onglet "preview" dans le menu configuration

class previewconfig : public QWidget
{
    Q_OBJECT

    QWidget *indexinit();
    MRichTextEdit *introindex;
    QTabWidget *preview;
    project *p;
    QScrollArea *initform(bool ref);
    infoquestion *groupboxtmp;
    formloadator *formref;
    formloadator *formreel;
public:
    previewconfig(MainWindow *m);
private slots:
    void updateiindex();
    void changescope(QTreeWidgetItem *item);
};

#endif // PREVIEWCONFIG_H
