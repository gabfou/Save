#ifndef OVERVIEW_H
#define OVERVIEW_H


#include "le.h"

class project;
class bargraph;
class tableshow;

class overview : public QWidget
{
	project *p;
	bargraph *bar;
	bargraph *barref;
    int *showmod;
    tableshow *table;
public:
    overview(project *p, int group, int *showmod);
	void updateov(int group);
};

#endif // OVERVIEW_H
