#ifndef BARGRAPH_H
#define BARGRAPH_H

#include "le.h"

class project;
class MainWindow;

class bargraph : public QWidget
{
public:
    bargraph(t_groupref g, project *q, MainWindow *m, QWidget *parent = 0);
    void updateg(t_groupref g, int qgroup);
	void redraw();
	QString getName() const;
	void setName(const QString &value);

public slots:
    void selectq(int gqref);
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
