#include "bargraph.h"

bargraph::bargraph(t_groupref  g, vector<question> q, QWidget *parent) : QWidget(parent), g(g), q(q)
{
}

bargraph::paintEvent(QPaintEvent *event)
{
    QPainter qp(this);
    drawgraph(&qp);
}

//    t_groupref listg = syntheselistgroup(p->getgrouplist("ALL"), p->getListquestion());


bargraph::drawgraph(QPainter *qp)
{
    int x = 10;
    int d = this->g.total;

    if (d == 0)
        return ;
    d /= 100;
    qp->setBrush(QBrush(Qt::cyan));
    qp->drawRect(x, 10, 10, 100);

    QList<QString>::iterator tmp;
    vector<question> listq = p->getListquestion();
    vector<question>::iterator tmp3;

    tmp = g.list.begin();
    tmp3 = listq.begin();
    int tmp37 = g.total;
    while (tmp3 != listq.end())
    {
        QVector<double> values;
        tmp37 -= (*tmp).toInt();
        qp->drawRect(x, 10 + g.total - tmp37, 10, (*tmp).toInt() / d);
        tmp3++;
        tmp++;
    }
}
