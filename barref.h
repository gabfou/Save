/*#ifndef BARREF_H
#define BARREF_H

#include "le.h"

class QwtPlotMultiBarChart;
class QwtPlotHistogram;
class project;

class barref: public QwtPlot
{
    Q_OBJECT

public:
    barref(QWidget * = NULL , project *p = NULL);
public Q_SLOTS:
    void setMode( int );
    void setOrientation( int );
    void exportChart();

private:
    void populate(project *p);

     QwtPlotMultiBarChart *d_barrefItem;
};

#endif // BARREF_H
*/
