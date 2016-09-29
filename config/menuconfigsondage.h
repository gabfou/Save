#ifndef MENUCONFIGSONDAGE_H
#define MENUCONFIGSONDAGE_H

#include "le.h"

class MainWindow;

class menuconfigsondage : public QWidget
{
    Q_OBJECT

    QListWidget *listWidget;
    QVector<int> listid;
    QCheckBox *refcheck;
    QSpinBox *nbiteration;
    MainWindow *m;
public:
    menuconfigsondage(MainWindow *m);
private slots:
    void supsondage();
    void newsondage();
};

#endif // MENUCONFIGSONDAGE_H
