#include "bargraph.h"
#include "data/question.h"
//#include "data/project.h"
#include "data/group.h"
#include "mainwindow.h"

// pas utilise tentative de graphique

bargraph::bargraph(t_groupref  g, project *p, QWidget *parent) : QWidget(parent), g(g), p(p)
{
    //setMinimumWidth(300);
    listqchild = p->questiongroupqchildnotopti(p->gqref, 0);
//    connect(m, SIGNAL(gqrefchange(int)), this, SLOT(selectq(int)));
}

void bargraph::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        emit isclicked();
}

void bargraph::updateg(t_groupref g, int qgroup)
{
	this->g = g;
    listqchild = p->questiongroupqchildnotopti(qgroup, 0);
    //this->g.total = total(g, listqchild);
}


void bargraph::paintEvent(QPaintEvent *event)
{
    (void)event;
	QPainter qp(this);
	this->drawgraph(&qp);
}

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
        qDebug() << "drawgraph nop d =" << d << " h120=" << h120;
		return ;
	}
    d /= 100;
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
        x +=  incr + incr;
        qp->drawRect(x, tmp37 * h120, width, ((*tmp) / d) * h120);
        qp->drawText(x, tmp37 * h120, width, ((*tmp) / d) * h120, Qt::AlignCenter | Qt::TextWrapAnywhere, QString::number((int)((*tmp) / d)) + "%");
        qp->translate(x, start * h120);
        qp->rotate(-45);
        if (p->listqgroup[tmp3->qgroupid].gquestion)
            qp->drawText(0, 0, 80, (width > 50) ? 50 : width, Qt::AlignCenter | Qt::TextWordWrap | Qt::TextDontClip,
                         p->listqgroup[tmp3->qgroupid].name + ":\n" + tmp3->name); // pourrai peut etre simplifier
        else
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
