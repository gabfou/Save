#ifndef MENUGESTIONJOUR_H
#define MENUGESTIONJOUR_H

#include "le.h"

class menugestionjour : public QTableWidget
{
    Q_OBJECT
    MainWindow *m;
public:
    menugestionjour(MainWindow *m);
private slots:
    void updateitem(QTableWidgetItem *item);
};

#endif // MENUGESTIONJOUR_H
