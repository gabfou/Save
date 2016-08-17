#ifndef OVERVIEW_H
#define OVERVIEW_H


#include "le.h"

class project;
class bargraph;

class overview : public QWidget
{
	project *p;
	bargraph *bar;
	bargraph *barref;
    int *showmod;
public:
    overview(project *p, int group, int *showmod);
	void updateov(int group);
};

#endif // OVERVIEW_H
