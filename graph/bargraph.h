#ifndef BARGRAPH_H
#define BARGRAPH_H

#include "le.h"
#include "data/question.h"

class project;
class question;
class MainWindow;

class bargraph : public QWidget
{
    Q_OBJECT
public:
    bargraph(t_groupref g, project *q, QWidget *parent = 0);
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
    QList<question> listqchild;
    void mousePressEvent(QMouseEvent *event);
signals:
     void isclicked();
};

#endif // BARGRAPH_H
