#ifndef MENUCONFIGPROJECT_H
#define MENUCONFIGPROJECT_H

#include "le.h"

class menuconfigproject : public QTabWidget
{
public:
    menuconfigproject(QString name);
private:
    QTabWidget *tab;
    void configeneral();
    void configgroupe();
    QString name;
};

#endif // MENUCONFIGPROJECT_H
