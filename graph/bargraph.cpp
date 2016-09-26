#include "bargraph.h"
#include "data/question.h"
#include "data/project.h"
#include "mainwindow.h"

bargraph::bargraph(t_groupref  g, project *p, MainWindow *m, QWidget *parent) : QWidget(parent), g(g), p(p)
{
    //setMinimumWidth(300);
	listqchild = p->questiongroupqchildnotopti(0);
//    connect(m, SIGNAL(gqrefchange(int)), this, SLOT(selectq(int)));
}

void bargraph::updateg(t_groupref g, int qgroup)
{
	this->g = g;
    listqchild = p->questiongroupqchildnotopti(qgroup);
    //this->g.total = total(g, listqchild);
}

void bargraph::selectq(int gqref)
{
//    qDebug() << "trucyhgsadjfhgsafdghasfd";
//    listqchild = p->questiongroupqchildnotopti(gqref);
}

void bargraph::paintEvent(QPaintEvent *event)
{
    (void)event;
	QPainter qp(this);
	this->drawgraph(&qp);
}

//	t_groupref listg = syntheselistgroup(p->getgrouplist("ALL"), p->getListquestion());

void bargraph::drawgraph(QPainter *qp)
{

	float incr = this->width() / ((listqchild.size() + 2) * 2);
	float x = incr;
    float width = incr * 1.5;
	float d = this->g.total;
    float h120 = this->height() / 140;
    float tmp37 = 40;
    float start = 30;

	if (d == 0 || h120 == 0)
	{
		qDebug() << "drawgraph nop";
		return ;
	}
	d /= 100;
//	qDebug() << "debut" << x <<  10 * h120 << incr << 100 * h120 << this->width() << this->height();
    qp->drawText(0, 0, this->width(), 10 * h120, Qt::AlignCenter, this->name);
	qp->setBrush(QBrush(Qt::cyan));
	qp->drawRect(x, tmp37 * h120 , width, 100 * h120);
    qp->drawText(x, tmp37 * h120 , width, 100 * h120, Qt::AlignCenter | Qt::TextWrapAnywhere, "100%");
    qp->translate(x, start * h120);
    qp->rotate(-45);
    qp->drawText(0, 0, 80, (width > 50) ? 50 : width, Qt::AlignCenter | Qt::TextWordWrap | Qt::TextDontClip, "total"); // pourrai peut etre simplifier
    qp->rotate(45);
    qp->translate(-x, -start * h120);
    QList<float>::iterator tmp;
    QList<question> listq = listqchild;
    QList<question>::iterator tmp3;

	tmp = g.list.begin();
	tmp3 = listq.begin();
	while (tmp3 != listq.end() && tmp != g.list.end())
	{
        /*if ((*tmp) == 0)
		{
			tmp3++;
			tmp++;
			continue ;
        }*/
        x +=  incr + incr;
//		qDebug() << "boucle" << x <<  tmp37 << (*tmp).toFloat() / d;
        qp->drawRect(x, tmp37 * h120, width, ((*tmp) / d) * h120);
        qp->drawText(x, tmp37 * h120, width, ((*tmp) / d) * h120, Qt::AlignCenter | Qt::TextWrapAnywhere, QString::number((int)((*tmp) / d)) + "%");
        qp->translate(x, start * h120);
        qp->rotate(-45);
        qp->drawText(0, 0, 80, (width > 50) ? 50 : width, Qt::AlignCenter | Qt::TextWordWrap | Qt::TextDontClip, tmp3->name); // pourrai peut etre simplifier
        qp->rotate(45);
        qp->translate(-x, -start * h120);
        tmp37 += ((*tmp) / d);
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
