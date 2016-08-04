#ifndef OVERVIEW_H
#define OVERVIEW_H


#include "le.h"

class project;

class overview : public QWidget
{
    project *p;
public:
    overview(project *p, int group);
    void updateov(int group);
};

#endif // OVERVIEW_H
