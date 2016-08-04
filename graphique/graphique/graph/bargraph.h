#ifndef BARGRAPH_H
#define BARGRAPH_H

#include "le.h"

class bargraph : public QWidget
{
public:
    bargraph(t_groupref g, vector<question> q, QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *event);
    void  drawgraph(QPainter *qp);
private:
    t_groupref g;
    vector<question> q;
    QString name = "non défini";
};

#endif // BARGRAPH_H
