#ifndef LISTEDITWVAL_H
#define LISTEDITWVAL_H

#include "le.h"

class listedit;

class listeditwval : public QWidget
{
    Q_OBJECT

    listedit *listoption;
    QListWidget *listval;
    QPushButton *add;
    QPushButton *sup;
    QMetaObject::Connection conewval;
public:
    listeditwval();
    QStringList getlstr();
    void update(QStringList &l);
public slots:
    void supline();
private slots:
    void newval();
};

#endif // LISTEDITWVAL_H
