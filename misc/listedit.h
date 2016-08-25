#ifndef LISTEDIT_H
#define LISTEDIT_H

#include "le.h"

class listedit : public QWidget
{
    Q_OBJECT

    QPushButton *add;
    QPushButton *sup;
public:
    listedit();
    listedit(QStringList &str);
    QListWidget *list;
    void init(QStringList &str);
    void preinit();
    QStringList getlstr();
public slots:
    void edit(QListWidgetItem *item);
    void newitem();
    void supitem();
private slots:
    void closeedit(QListWidgetItem *item);
};

#endif // LISTEDIT_H
