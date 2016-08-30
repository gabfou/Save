#ifndef ALLTREE_H
#define ALLTREE_H

#include "le.h"

class grouptree;

class MainWindow;

class Alltree : public QTabWidget
{
public:
    Alltree(MainWindow *m, project *current);
private:
    project *p;
    grouptree *groupboxtmp;
};

#endif // ALLTREE_H
