#ifndef LISTEDIT_H
#define LISTEDIT_H

#include "le.h"

class listedit : public QWidget
{
    Q_OBJECT

    QPushButton *add;
    QPushButton *sup;
    int co = 1;
public:
    listedit(int co = 1);
    listedit(QStringList &str);
    QListWidget *list;
    void init(QStringList &str);
    void preinit(int co = 1);
    QStringList getlstr();
    void update(QStringList &l);
public slots:
    void edit(QListWidgetItem *item);
    void newitem();
    void supitem();
private slots:
    void closeedit(QListWidgetItem *item);
signals:
     void newitemcreated();
};

#endif // LISTEDIT_H
