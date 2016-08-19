#include "bargraph.h"
#include "data/question.h"
#include "data/project.h"

bargraph::bargraph(t_groupref  g, project *p, QWidget *parent) : QWidget(parent), g(g), p(p)
{
	setMinimumWidth(300);
	listqchild = p->questiongroupqchildnotopti(0);
}

void bargraph::updateg(t_groupref g)
{
	this->g = g;
	listqchild = p->questiongroupqchildnotopti(0);
}


void bargraph::paintEvent(QPaintEvent *event)
{
	QPainter qp(this);
	this->drawgraph(&qp);
}

//	t_groupref listg = syntheselistgroup(p->getgrouplist("ALL"), p->getListquestion());

void bargraph::drawgraph(QPainter *qp)
{

	float incr = this->width() / ((listqchild.size() + 2) * 2);
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
//	qDebug() << "debut" << x <<  10 * h120 << incr << 100 * h120 << this->width() << this->height();
    qp->drawText(0, 0, this->width(), 10 * h120, Qt::AlignCenter, this->name);
	qp->setBrush(QBrush(Qt::cyan));
	qp->drawRect(x, tmp37 * h120 , incr, 100 * h120);
	QList<QString>::iterator tmp;
	vector<question> listq = listqchild;
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
//		qDebug() << "boucle" << x <<  tmp37 << (*tmp).toFloat() / d;
        qp->drawRect(x, tmp37 * h120, incr, ((*tmp).toFloat() / d) * h120);
        qp->drawText(x, tmp37 * h120, incr, ((*tmp).toFloat() / d) , Qt::AlignCenter | Qt::TextWordWrap, tmp3->name.c_str());
		tmp37 += ((*tmp).toInt() / d);
		tmp3++;
		tmp++;
	}
	this->show();
}

QString bargraph::getName() const
{
	return name;
}

void bargraph::setName(const QString &value)
{
	name = value;
}
