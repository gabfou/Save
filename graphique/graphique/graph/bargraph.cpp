#include "bargraph.h"
#include "question.h"

bargraph::bargraph(t_groupref  g, vector<question> q, QWidget *parent) : QWidget(parent), g(g), q(q)
{
     setMinimumWidth(300);
}

void bargraph::paintEvent(QPaintEvent *event)
{
    QPainter qp(this);
    this->drawgraph(&qp);
}

//    t_groupref listg = syntheselistgroup(p->getgrouplist("ALL"), p->getListquestion());

void bargraph::drawgraph(QPainter *qp)
{
    float incr = this->width() / ((q.size() + 2) * 2);
    float x = incr;
    float d = this->g.total;
    float h120 = this->height() / 120;
    float tmp37 = 20;

    if (d == 0 || h120 == 0)
    {
        qDebug() << "drawgraph nop";
        return ;
    }
    d /= 100;
    qDebug() << "debut" << x <<  10 * h120 << incr << 100 * h120 << this->width() << this->height();
    qp->drawText(0, 0, this->width(), 10 * h120, Qt::AlignCenter, this->name);
    qp->setBrush(QBrush(Qt::cyan));
    qp->drawRect(x, tmp37 * h120 , incr, 100 * h120);
    QList<QString>::iterator tmp;
    vector<question> listq = q;
    vector<question>::iterator tmp3;

    tmp = g.list.begin();
    tmp3 = listq.begin();
    while (tmp3 != listq.end() && tmp != g.list.end())
    {
        if ((*tmp).compare("NA") == 0)
        {
            tmp3++;
            tmp++;
            continue ;
        }
        x +=  incr + incr;
        qDebug() << "boucle" << x <<  tmp37 << (*tmp).toFloat() / d;
        qp->drawRect(x, tmp37 * h120, incr, ((*tmp).toFloat() / d) * h120);
        tmp37 += ((*tmp).toInt() / d);
        tmp3++;
        tmp++;
    }
    this->show();
}
