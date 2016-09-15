#ifndef TABLISTEDIT_H
#define TABLISTEDIT_H

#include "le.h"

class listedit;

class tablistedit : public QWidget
{
public:
    tablistedit(int colnb = 1);
private:
    QList<listedit*> list;
    QPushButton *add;
    QPushButton *sup;


};

#endif // TABLISTEDIT_H
