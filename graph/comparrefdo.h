#ifndef COMPARREFDO_H
#define COMPARREFDO_H

#include "le.h"

class bargraph;

class Comparrefdo : public QWidget
{
    Q_OBJECT
public:
    Comparrefdo(MainWindow *m, int group);
public slots:
    void updateov(int group, int qgroup);
    void autoupdateov();
    void refshow();
    void donshow();
    void allshow();
private:
    MainWindow *m;
    bargraph *bar;
    bargraph *barref;
    int group;
};

#endif // COMPARREFDO_H
