#ifndef ALLTREE_H
#define ALLTREE_H

#include "le.h"

class grouptree;

class MainWindow;

class Alltree : public QWidget
{
    Q_OBJECT
public:
    Alltree(MainWindow *m, project *current);
private slots:
    void affichegroupp(bool b);
private:
    project *p;
    grouptree *groupboxtmp;
    QSlider *slidemax;
    QLabel *labelslidemax;
    QSlider *slidemin;
    QLabel *labelslidemin;
    void prephide();
signals:
     void grouppmodechanged(bool gref);
};

#endif // ALLTREE_H
