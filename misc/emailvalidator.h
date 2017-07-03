#ifndef EMAILVALIDATOR_H
#define EMAILVALIDATOR_H

#include "le.h"
#include "listedit.h"
#include "data/person.h"

// menu d'envoi d'email pas fonctionel

class emailvalidator : public QWidget
{
    Q_OBJECT
    QList<person> listp;
    QListWidget *listmail;
    MainWindow *m;
    int groupid = 0;
    bool ref;
public:
    emailvalidator(MainWindow *m, int ref);
private slots:
    void init(int group);
    void send();
};

#endif // EMAILVALIDATOR_H
