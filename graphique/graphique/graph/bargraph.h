#ifndef BARGRAPH_H
#define BARGRAPH_H

#include "le.h"

class bargraph : public QWidget
{
public:
    bargraph(t_groupref g, vector<question> q, QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *event);
    void drawgraph(t_groupref &g);
private:
    t_groupref g;
    vector<question> q;
};

#endif // BARGRAPH_H
