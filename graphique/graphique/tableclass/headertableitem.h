#ifndef HEADERTABLEITEM_H
#define HEADERTABLEITEM_H

#include "le.h"

#include "data/group.h"
#include "data/person.h"
#include "data/question.h"

class headertableitem : public QTableWidgetItem
{
public:
    //headertableitem();

    QString getFormule() const;
    void setFormule(const QString &value);

    headertableitem(QString str, QString form = "", int id = -1);
    QString formule = "";
    int groupe = 0;
    int id = -1;
    int type = -1;
    void *arg = NULL;
    group argg;
    person argp;
    question argq;
    headertableitem(QString str, group arg, QString form = "");
    headertableitem(QString str, person arg, QString form = "");
    headertableitem(QString str, question arg, QString form = "");
};

#endif // HEADERTABLEITEM_H
