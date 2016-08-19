#ifndef BARGRAPH_H
#define BARGRAPH_H

#include "le.h"

class project;

class bargraph : public QWidget
{
public:
	bargraph(t_groupref g, project *q, QWidget *parent = 0);
	void updateg(t_groupref g);
	void redraw();
	QString getName() const;
	void setName(const QString &value);

protected:
	void paintEvent(QPaintEvent *event);
	void  drawgraph(QPainter *qp);
private:
	t_groupref g;
	project *p;
	QString name = "non défini";
	vector<question> listqchild;
};

#endif // BARGRAPH_H
