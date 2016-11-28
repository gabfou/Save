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
    QTabWidget *preview;
    project *p;
    QScrollArea *initform(bool ref);
    grouptree *groupboxtmp;
public:
    previewconfig(MainWindow *m);
private slots:
    void updateiindex();
    void changescope(QTreeWidgetItem *item);
};

#endif // PREVIEWCONFIG_H
