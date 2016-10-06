#ifndef TABLEAU_BRUT_H
#define TABLEAU_BRUT_H

#include "le.h"

class person;
class fact;

class tableau_brut : public QTableWidget
{
public:
    tableau_brut(project *p);
private:
    void populate(project *p);
    void setrow(person &pe, fact &f, project *p, int k);
    void setheader(project *p);
};

#endif // TABLEAU_BRUT_H
