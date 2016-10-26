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
    QCalendarWidget *calendar;
    QDateTimeEdit *timecalendar;
    QRadioButton *listday[7] = {new QRadioButton("Lundi"), new QRadioButton("Mardi"),
                             new QRadioButton("Mercredi"), new QRadioButton("Jeudi"),
                             new QRadioButton("Vendredi"), new QRadioButton("Samedi"),
                             new QRadioButton("Dimanche")};
public:
    menuconfigsondage(MainWindow *m);
private slots:
    void supsondage();
    void newsondage();
    void updatecurrent();};

#endif // MENUCONFIGSONDAGE_H
