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
public:
    overview(project *p, int group);
    void updateov(int group);
};

#endif // OVERVIEW_H
