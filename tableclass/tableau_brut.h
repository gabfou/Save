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
    QStringList checklist;
    QVector<QVector<int>> checklistreal;
    void populate(project *p);
    void setrow(person &pe, project *p, int k, int it);
    void setheader(project *p);
};

#endif // TABLEAU_BRUT_H
