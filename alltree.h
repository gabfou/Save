#ifndef ALLTREE_H
#define ALLTREE_H

#include "le.h"

class MainWindow;

class Alltree : public QTabWidget
{
public:
    Alltree(MainWindow *m, project *current);
private:
    project *p;
};

#endif // ALLTREE_H
