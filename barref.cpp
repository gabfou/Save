#include "barref.h"
#include "data/project.h"


barref::barref(QWidget *parent, project *p):
    QwtPlot( parent )
{
    setAutoFillBackground( true );

    setPalette( Qt::white );
    //canvas()->setPalette( QColor( "LemonChiffon" ) );

    setTitle( "Bar Chart" );

    //setAxisTitle( QwtPlot::yLeft, "Whatever" );
    setAxisTitle( QwtPlot::xBottom, "" );

    d_barrefItem = new QwtPlotMultiBarChart( "Bar Chart " );
    d_barrefItem->setLayoutPolicy( QwtPlotMultiBarChart::AutoAdjustSamples );
    //d_barrefItem->setSpacing( 20 );
    //d_barrefItem->
    d_barrefItem->setMargin( 3 );
    d_barrefItem->setStyle( QwtPlotMultiBarChart::Stacked );

    d_barrefItem->attach( this );

    insertLegend( new QwtLegend() );

    populate(p);
    setOrientation( 0 );

    setAutoReplot( true );
}

void barref::populate(project *p)
{
    static const char *colors[] = { "White", "Cyan"};

    t_groupref listg = syntheselistgroup(p->getgrouplist(0), p->getListquestion());
    //t_groupref listref = syntheselistgroup(p->getgrouplistref("ALL"), p->getListquestion());
    QList<QString>::iterator tmp;

    vector<question> listq = p->getListquestion();
    vector<question>::iterator tmp3;

    const int numSamples = listq.size() + 2;
    const int numBars = 2;

    QList<QwtText> titles;
    /*tmp3 = listq.begin();
    while (tmp3 != listq.end())
    {
        QString title(tmp3->name.c_str());
        titles += title;
        tmp3++;
    }*/
    titles += QString("reel");
    titles += QString("declaratif");
//    d_barrefItem->setBarTitles(titles);
    d_barrefItem->setLegendIconSize( QSize( 10, 14 ) );

    for ( int i = 0; i < numBars; i++ )
    {
        QwtColumnSymbol *symbol = new QwtColumnSymbol( QwtColumnSymbol::Box );
        symbol->setLineWidth( 2 );
        symbol->setFrameStyle( QwtColumnSymbol::Raised );
        symbol->setPalette( QPalette( colors[i] ) );

        d_barrefItem->setSymbol( i, symbol );
    }
    QVector< QVector<double> > series;
    tmp = listg.list.begin();
    tmp3 = listq.begin();
    int tmp37 = listg.total;
    while (tmp3 != listq.end())
    {
        QVector<double> values;
        tmp37 -= (*tmp).toInt();
        values += tmp37;
        values += (*tmp).toInt();
        series += values;
        qDebug() << (*tmp).toInt();
        tmp3++;
        tmp++;
    }

    d_barrefItem->setSamples( series );
}

void barref::setMode( int mode )
{
 //   if ( mode == 0 )
//    {
//        d_barrefItem->setStyle( QwtPlotMultiBarChart::Grouped );
//    }
//    else
//    {
        d_barrefItem->setStyle( QwtPlotMultiBarChart::Stacked );
//    }
}

void barref::setOrientation( int orientation )
{
    QwtPlot::Axis axis1, axis2;

    if ( orientation == 0 )
    {
        axis1 = QwtPlot::xBottom;
        axis2 = QwtPlot::yLeft;

        d_barrefItem->setOrientation( Qt::Vertical );
    }
    else
    {
        axis1 = QwtPlot::yLeft;
        axis2 = QwtPlot::xBottom;

        d_barrefItem->setOrientation( Qt::Horizontal );
    }

    setAxisScale( axis1, 0, d_barrefItem->dataSize() - 1, 1.0 );
    setAxisAutoScale( axis2 );

    QwtScaleDraw *scaleDraw1 = axisScaleDraw( axis1 );
    scaleDraw1->enableComponent( QwtScaleDraw::Backbone, false );
    scaleDraw1->enableComponent( QwtScaleDraw::Ticks, false );

    QwtScaleDraw *scaleDraw2 = axisScaleDraw( axis2 );
    scaleDraw2->enableComponent( QwtScaleDraw::Backbone, true );
    scaleDraw2->enableComponent( QwtScaleDraw::Ticks, true );

    plotLayout()->setAlignCanvasToScale( axis1, true );
    plotLayout()->setAlignCanvasToScale( axis2, false );

    plotLayout()->setCanvasMargin( 0 );
    updateCanvasMargins();

    replot();
}

void barref::exportChart()
{
    QwtPlotRenderer renderer;
    renderer.exportTo( this, "barref.pdf" );
}
