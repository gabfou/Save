#ifndef OVERVIEW_H
#define OVERVIEW_H

#include "le.h"

//obselete upadate avec comparefdo si util

class project;
class bargraph;
class tableshow;
class MainWindow;

class overview : public QWidget
{
	project *p;
	bargraph *bar;
	bargraph *barref;
    int *showmod;
    tableshow *table;
public:
    overview(MainWindow *m, project *p, int group, int *showmod);
    void updateov(int group, int qgroup);
};

#endif // OVERVIEW_H
