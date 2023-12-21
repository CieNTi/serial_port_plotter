/***************************************************************************
**                                                                        **
**  QCustomPlot, an easy to use, modern plotting widget for Qt            **
**  Copyright (C) 2011-2022 Emanuel Eichhammer                            **
**                                                                        **
**  This program is free software: you can redistribute it and/or modify  **
**  it under the terms of the GNU General Public License as published by  **
**  the Free Software Foundation, either version 3 of the License, or     **
**  (at your option) any later version.                                   **
**                                                                        **
**  This program is distributed in the hope that it will be useful,       **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of        **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         **
**  GNU General Public License for more details.                          **
**                                                                        **
**  You should have received a copy of the GNU General Public License     **
**  along with this program.  If not, see http://www.gnu.org/licenses/.   **
**                                                                        **
****************************************************************************
**           Author: Emanuel Eichhammer                                   **
**  Website/Contact: https://www.qcustomplot.com/                         **
**             Date: 06.11.22                                             **
**          Version: 2.1.1                                                **
****************************************************************************/

/************************************************************************************************************
**                                                                                                         **
**  This is the example code for QCustomPlot.                                                              **
**                                                                                                         **
**  It demonstrates basic and some advanced capabilities of the widget. The interesting code is inside     **
**  the "setup(...)Demo" functions of MainWindow.                                                          **
**                                                                                                         **
**  In order to see a demo in action, call the respective "setup(...)Demo" function inside the             **
**  MainWindow constructor. Alternatively you may call setupDemo(i) where i is the index of the demo       **
**  you want (for those, see MainWindow constructor comments). All other functions here are merely a       **
**  way to easily create screenshots of all demos for the website. I.e. a timer is set to successively     **
**  setup all the demos and make a screenshot of the window area and save it in the ./screenshots          **
**  directory.                                                                                             **
**                                                                                                         **
*************************************************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
#  include <QDesktopWidget>
#endif
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  setGeometry(400, 250, 542, 390);
  
  setupDemo(0);
  //setupPlayground(ui->customPlot);
  // 0:  setupQuadraticDemo(ui->customPlot);
  // 1:  setupSimpleDemo(ui->customPlot);
  // 2:  setupSincScatterDemo(ui->customPlot);
  // 3:  setupScatterStyleDemo(ui->customPlot);
  // 4:  setupScatterPixmapDemo(ui->customPlot);
  // 5:  setupLineStyleDemo(ui->customPlot);
  // 6:  setupDateDemo(ui->customPlot);
  // 7:  setupTextureBrushDemo(ui->customPlot);
  // 8:  setupMultiAxisDemo(ui->customPlot);
  // 9:  setupLogarithmicDemo(ui->customPlot);
  // 10: setupRealtimeDataDemo(ui->customPlot);
  // 11: setupParametricCurveDemo(ui->customPlot);
  // 12: setupBarChartDemo(ui->customPlot);
  // 13: setupStatisticalDemo(ui->customPlot);
  // 14: setupSimpleItemDemo(ui->customPlot);
  // 15: setupItemDemo(ui->customPlot);
  // 16: setupStyledDemo(ui->customPlot);
  // 17: setupAdvancedAxesDemo(ui->customPlot);
  // 18: setupColorMapDemo(ui->customPlot);
  // 19: setupFinancialDemo(ui->customPlot);
  // 20: setupPolarPlotDemo(ui->customPlot);
    
  // for making screenshots of the current demo or all demos (for website screenshots):
  //QTimer::singleShot(1500, this, SLOT(allScreenShots()));
  //QTimer::singleShot(4000, this, SLOT(screenShot()));
}

void MainWindow::setupDemo(int demoIndex)
{
  switch (demoIndex)
  {
    case 0:  setupQuadraticDemo(ui->customPlot); break;
    case 1:  setupSimpleDemo(ui->customPlot); break;
    case 2:  setupSincScatterDemo(ui->customPlot); break;
    case 3:  setupScatterStyleDemo(ui->customPlot); break;
    case 4:  setupScatterPixmapDemo(ui->customPlot); break;
    case 5:  setupLineStyleDemo(ui->customPlot); break;
    case 6:  setupDateDemo(ui->customPlot); break;
    case 7:  setupTextureBrushDemo(ui->customPlot); break;
    case 8:  setupMultiAxisDemo(ui->customPlot); break;
    case 9:  setupLogarithmicDemo(ui->customPlot); break;
    case 10: setupRealtimeDataDemo(ui->customPlot); break;
    case 11: setupParametricCurveDemo(ui->customPlot); break;
    case 12: setupBarChartDemo(ui->customPlot); break;
    case 13: setupStatisticalDemo(ui->customPlot); break;
    case 14: setupSimpleItemDemo(ui->customPlot); break;
    case 15: setupItemDemo(ui->customPlot); break;
    case 16: setupStyledDemo(ui->customPlot); break;
    case 17: setupAdvancedAxesDemo(ui->customPlot); break;
    case 18: setupColorMapDemo(ui->customPlot); break;
    case 19: setupFinancialDemo(ui->customPlot); break;
    case 20: setupPolarPlotDemo(ui->customPlot); break;
  }
  setWindowTitle("QCustomPlot: "+demoName);
  statusBar()->clearMessage();
  currentDemoIndex = demoIndex;
  ui->customPlot->replot();
}

void MainWindow::setupQuadraticDemo(QCustomPlot *customPlot)
{
  demoName = "Quadratic Demo";
  // generate some data:
  QVector<double> x(101), y(101); // initialize with entries 0..100
  for (int i=0; i<101; ++i)
  {
    x[i] = i/50.0 - 1; // x goes from -1 to 1
    y[i] = x[i]*x[i];  // let's plot a quadratic function
  }
  // create graph and assign data to it:
  customPlot->addGraph();
  customPlot->graph(0)->setData(x, y);
  // give the axes some labels:
  customPlot->xAxis->setLabel("x");
  customPlot->yAxis->setLabel("y");
  // set axes ranges, so we see all data:
  customPlot->xAxis->setRange(-1, 1);
  customPlot->yAxis->setRange(0, 1);
}

void MainWindow::setupSimpleDemo(QCustomPlot *customPlot)
{
  demoName = "Simple Demo";
  
  // add two new graphs and set their look:
  customPlot->addGraph();
  customPlot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
  customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue
  customPlot->addGraph();
  customPlot->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph
  // generate some points of data (y0 for first, y1 for second graph):
  QVector<double> x(251), y0(251), y1(251);
  for (int i=0; i<251; ++i)
  {
    x[i] = i;
    y0[i] = qExp(-i/150.0)*qCos(i/10.0); // exponentially decaying cosine
    y1[i] = qExp(-i/150.0);              // exponential envelope
  }
  // configure right and top axis to show ticks but no labels:
  // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
  customPlot->xAxis2->setVisible(true);
  customPlot->xAxis2->setTickLabels(false);
  customPlot->yAxis2->setVisible(true);
  customPlot->yAxis2->setTickLabels(false);
  // make left and bottom axes always transfer their ranges to right and top axes:
  connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
  connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
  // pass data points to graphs:
  customPlot->graph(0)->setData(x, y0);
  customPlot->graph(1)->setData(x, y1);
  // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
  customPlot->graph(0)->rescaleAxes();
  // same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
  customPlot->graph(1)->rescaleAxes(true);
  // Note: we could have also just called customPlot->rescaleAxes(); instead
  // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
  customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

void MainWindow::setupSincScatterDemo(QCustomPlot *customPlot)
{
  demoName = "Sinc Scatter Demo";
  customPlot->legend->setVisible(true);
  customPlot->legend->setFont(QFont("Helvetica",9));
  // set locale to english, so we get english decimal separator:
  customPlot->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
  // add confidence band graphs:
  customPlot->addGraph();
  QPen pen;
  pen.setStyle(Qt::DotLine);
  pen.setWidth(1);
  pen.setColor(QColor(180,180,180));
  customPlot->graph(0)->setName("Confidence Band 68%");
  customPlot->graph(0)->setPen(pen);
  customPlot->graph(0)->setBrush(QBrush(QColor(255,50,30,20)));
  customPlot->addGraph();
  customPlot->legend->removeItem(customPlot->legend->itemCount()-1); // don't show two confidence band graphs in legend
  customPlot->graph(1)->setPen(pen);
  customPlot->graph(0)->setChannelFillGraph(customPlot->graph(1));
  // add theory curve graph:
  customPlot->addGraph();
  pen.setStyle(Qt::DashLine);
  pen.setWidth(2);
  pen.setColor(Qt::red);
  customPlot->graph(2)->setPen(pen);
  customPlot->graph(2)->setName("Theory Curve");
  // add data point graph:
  customPlot->addGraph();
  customPlot->graph(3)->setPen(QPen(Qt::blue));
  customPlot->graph(3)->setName("Measurement");
  customPlot->graph(3)->setLineStyle(QCPGraph::lsNone);
  customPlot->graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 4));
  // add error bars:
  QCPErrorBars *errorBars = new QCPErrorBars(customPlot->xAxis, customPlot->yAxis);
  errorBars->removeFromLegend();
  errorBars->setAntialiased(false);
  errorBars->setDataPlottable(customPlot->graph(3));
  errorBars->setPen(QPen(QColor(180,180,180)));

  // generate ideal sinc curve data and some randomly perturbed data for scatter plot:
  QVector<double> x0(250), y0(250);
  QVector<double> yConfUpper(250), yConfLower(250);
  for (int i=0; i<250; ++i)
  {
    x0[i] = (i/249.0-0.5)*30+0.01; // by adding a small offset we make sure not do divide by zero in next code line
    y0[i] = qSin(x0[i])/x0[i]; // sinc function
    yConfUpper[i] = y0[i]+0.15;
    yConfLower[i] = y0[i]-0.15;
    x0[i] *= 1000;
  }
  QVector<double> x1(50), y1(50), y1err(50);
  for (int i=0; i<50; ++i)
  {
    // generate a gaussian distributed random number:
    double tmp1 = rand()/(double)RAND_MAX;
    double tmp2 = rand()/(double)RAND_MAX;
    double r = qSqrt(-2*qLn(tmp1))*qCos(2*M_PI*tmp2); // box-muller transform for gaussian distribution
    // set y1 to value of y0 plus a random gaussian pertubation:
    x1[i] = (i/50.0-0.5)*30+0.25;
    y1[i] = qSin(x1[i])/x1[i]+r*0.15;
    x1[i] *= 1000;
    y1err[i] = 0.15;
  }
  // pass data to graphs and let QCustomPlot determine the axes ranges so the whole thing is visible:
  customPlot->graph(0)->setData(x0, yConfUpper);
  customPlot->graph(1)->setData(x0, yConfLower);
  customPlot->graph(2)->setData(x0, y0);
  customPlot->graph(3)->setData(x1, y1);
  errorBars->setData(y1err);
  customPlot->graph(2)->rescaleAxes();
  customPlot->graph(3)->rescaleAxes(true);
  // setup look of bottom tick labels:
  customPlot->xAxis->setTickLabelRotation(30);
  customPlot->xAxis->ticker()->setTickCount(9);
  customPlot->xAxis->setNumberFormat("ebc");
  customPlot->xAxis->setNumberPrecision(1);
  customPlot->xAxis->moveRange(-10);
  // make top right axes clones of bottom left axes. Looks prettier:
  customPlot->axisRect()->setupFullAxesBox();
}

void MainWindow::setupScatterStyleDemo(QCustomPlot *customPlot)
{
  demoName = "Scatter Style Demo";
  customPlot->legend->setVisible(true);
  customPlot->legend->setFont(QFont("Helvetica", 9));
  customPlot->legend->setRowSpacing(-3);
  QVector<QCPScatterStyle::ScatterShape> shapes;
  shapes << QCPScatterStyle::ssCross;
  shapes << QCPScatterStyle::ssPlus;
  shapes << QCPScatterStyle::ssCircle;
  shapes << QCPScatterStyle::ssDisc;
  shapes << QCPScatterStyle::ssSquare;
  shapes << QCPScatterStyle::ssDiamond;
  shapes << QCPScatterStyle::ssStar;
  shapes << QCPScatterStyle::ssTriangle;
  shapes << QCPScatterStyle::ssTriangleInverted;
  shapes << QCPScatterStyle::ssCrossSquare;
  shapes << QCPScatterStyle::ssPlusSquare;
  shapes << QCPScatterStyle::ssCrossCircle;
  shapes << QCPScatterStyle::ssPlusCircle;
  shapes << QCPScatterStyle::ssPeace;
  shapes << QCPScatterStyle::ssCustom;

  QPen pen;
  // add graphs with different scatter styles:
  for (int i=0; i<shapes.size(); ++i)
  {
    customPlot->addGraph();
    pen.setColor(QColor(qSin(i*0.3)*100+100, qSin(i*0.6+0.7)*100+100, qSin(i*0.4+0.6)*100+100));
    // generate data:
    QVector<double> x(10), y(10);
    for (int k=0; k<10; ++k)
    {
      x[k] = k/10.0 * 4*3.14 + 0.01;
      y[k] = 7*qSin(x[k])/x[k] + (shapes.size()-i)*5;
    }
    customPlot->graph()->setData(x, y);
    customPlot->graph()->rescaleAxes(true);
    customPlot->graph()->setPen(pen);
    customPlot->graph()->setName(QCPScatterStyle::staticMetaObject.enumerator(QCPScatterStyle::staticMetaObject.indexOfEnumerator("ScatterShape")).valueToKey(shapes.at(i)));
    customPlot->graph()->setLineStyle(QCPGraph::lsLine);
    // set scatter style:
    if (shapes.at(i) != QCPScatterStyle::ssCustom)
    {
      customPlot->graph()->setScatterStyle(QCPScatterStyle(shapes.at(i), 10));
    }
    else
    {
      QPainterPath customScatterPath;
      for (int i=0; i<3; ++i)
        customScatterPath.cubicTo(qCos(2*M_PI*i/3.0)*9, qSin(2*M_PI*i/3.0)*9, qCos(2*M_PI*(i+0.9)/3.0)*9, qSin(2*M_PI*(i+0.9)/3.0)*9, 0, 0);
      customPlot->graph()->setScatterStyle(QCPScatterStyle(customScatterPath, QPen(Qt::black, 0), QColor(40, 70, 255, 50), 10));
    }
  }
  // set blank axis lines:
  customPlot->rescaleAxes();
  customPlot->xAxis->setTicks(false);
  customPlot->yAxis->setTicks(false);
  customPlot->xAxis->setTickLabels(false);
  customPlot->yAxis->setTickLabels(false);
  // make top right axes clones of bottom left axes:
  customPlot->axisRect()->setupFullAxesBox();
}

void MainWindow::setupLineStyleDemo(QCustomPlot *customPlot)
{
  demoName = "Line Style Demo";
  customPlot->legend->setVisible(true);
  customPlot->legend->setFont(QFont("Helvetica", 9));
  QPen pen;
  QStringList lineNames;
  lineNames << "lsNone" << "lsLine" << "lsStepLeft" << "lsStepRight" << "lsStepCenter" << "lsImpulse";
  // add graphs with different line styles:
  for (int i=QCPGraph::lsNone; i<=QCPGraph::lsImpulse; ++i)
  {
    customPlot->addGraph();
    pen.setColor(QColor(qSin(i*1+1.2)*80+80, qSin(i*0.3+0)*80+80, qSin(i*0.3+1.5)*80+80));
    customPlot->graph()->setPen(pen);
    customPlot->graph()->setName(lineNames.at(i-QCPGraph::lsNone));
    customPlot->graph()->setLineStyle((QCPGraph::LineStyle)i);
    customPlot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
    // generate data:
    QVector<double> x(15), y(15);
    for (int j=0; j<15; ++j)
    {
      x[j] = j/15.0 * 5*3.14 + 0.01;
      y[j] = 7*qSin(x[j])/x[j] - (i-QCPGraph::lsNone)*5 + (QCPGraph::lsImpulse)*5 + 2;
    }
    customPlot->graph()->setData(x, y);
    customPlot->graph()->rescaleAxes(true);
  }
  // zoom out a bit:
  customPlot->yAxis->scaleRange(1.1, customPlot->yAxis->range().center());
  customPlot->xAxis->scaleRange(1.1, customPlot->xAxis->range().center());
  // set blank axis lines:
  customPlot->xAxis->setTicks(false);
  customPlot->yAxis->setTicks(true);
  customPlot->xAxis->setTickLabels(false);
  customPlot->yAxis->setTickLabels(true);
  // make top right axes clones of bottom left axes:
  customPlot->axisRect()->setupFullAxesBox();
}

void MainWindow::setupScatterPixmapDemo(QCustomPlot *customPlot)
{
  demoName = "Scatter Pixmap Demo";
  customPlot->axisRect()->setBackground(QPixmap("./solarpanels.jpg"));
  customPlot->addGraph();
  customPlot->graph()->setLineStyle(QCPGraph::lsLine);
  QPen pen;
  pen.setColor(QColor(255, 200, 20, 200));
  pen.setStyle(Qt::DashLine);
  pen.setWidthF(2.5);
  customPlot->graph()->setPen(pen);
  customPlot->graph()->setBrush(QBrush(QColor(255,200,20,70)));
  customPlot->graph()->setScatterStyle(QCPScatterStyle(QPixmap("./sun.png")));
  // set graph name, will show up in legend next to icon:
  customPlot->graph()->setName("Data from Photovoltaic\nenergy barometer 2011");
  // set data:
  QVector<double> year, value;
  year  << 2005 << 2006 << 2007 << 2008  << 2009  << 2010 << 2011;
  value << 2.17 << 3.42 << 4.94 << 10.38 << 15.86 << 29.33 << 52.1;
  customPlot->graph()->setData(year, value);

  // set title of plot:
  customPlot->plotLayout()->insertRow(0);
  customPlot->plotLayout()->addElement(0, 0, new QCPTextElement(customPlot, "Regenerative Energies", QFont("sans", 12, QFont::Bold)));
  // axis configurations:
  customPlot->xAxis->setLabel("Year");
  customPlot->yAxis->setLabel("Installed Gigawatts of\nphotovoltaic in the European Union");
  customPlot->xAxis2->setVisible(true);
  customPlot->yAxis2->setVisible(true);
  customPlot->xAxis2->setTickLabels(false);
  customPlot->yAxis2->setTickLabels(false);
  customPlot->xAxis2->setTicks(false);
  customPlot->yAxis2->setTicks(false);
  customPlot->xAxis2->setSubTicks(false);
  customPlot->yAxis2->setSubTicks(false);
  customPlot->xAxis->setRange(2004.5, 2011.5);
  customPlot->yAxis->setRange(0, 52);
  // setup legend:
  customPlot->legend->setFont(QFont(font().family(), 7));
  customPlot->legend->setIconSize(50, 20);
  customPlot->legend->setVisible(true);
  customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft | Qt::AlignTop);
}

void MainWindow::setupDateDemo(QCustomPlot *customPlot)
{
  demoName = "Date Demo";
  // set locale to english, so we get english month names:
  customPlot->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
  // seconds of current time, we'll use it as starting point in time for data:
  double now = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
  srand(8); // set the random seed, so we always get the same random data
  // create multiple graphs:
  for (int gi=0; gi<5; ++gi)
  {
    customPlot->addGraph();
    QColor color(20+200/4.0*gi,70*(1.6-gi/4.0), 150, 150);
    customPlot->graph()->setLineStyle(QCPGraph::lsLine);
    customPlot->graph()->setPen(QPen(color.lighter(200)));
    customPlot->graph()->setBrush(QBrush(color));
    // generate random walk data:
    QVector<QCPGraphData> timeData(250);
    for (int i=0; i<250; ++i)
    {
      timeData[i].key = now + 24*3600*i;
      if (i == 0)
        timeData[i].value = (i/50.0+1)*(rand()/(double)RAND_MAX-0.5);
      else
        timeData[i].value = qFabs(timeData[i-1].value)*(1+0.02/4.0*(4-gi)) + (i/50.0+1)*(rand()/(double)RAND_MAX-0.5);
    }
    customPlot->graph()->data()->set(timeData);
  }
  // configure bottom axis to show date instead of number:
  QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
  dateTicker->setDateTimeFormat("d. MMMM\nyyyy");
  customPlot->xAxis->setTicker(dateTicker);
  // configure left axis text labels:
  QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
  textTicker->addTick(10, "a bit\nlow");
  textTicker->addTick(50, "quite\nhigh");
  customPlot->yAxis->setTicker(textTicker);
  // set a more compact font size for bottom and left axis tick labels:
  customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
  customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));
  // set axis labels:
  customPlot->xAxis->setLabel("Date");
  customPlot->yAxis->setLabel("Random wobbly lines value");
  // make top and right axes visible but without ticks and labels:
  customPlot->xAxis2->setVisible(true);
  customPlot->yAxis2->setVisible(true);
  customPlot->xAxis2->setTicks(false);
  customPlot->yAxis2->setTicks(false);
  customPlot->xAxis2->setTickLabels(false);
  customPlot->yAxis2->setTickLabels(false);
  // set axis ranges to show all data:
  customPlot->xAxis->setRange(now, now+24*3600*249);
  customPlot->yAxis->setRange(0, 60);
  // show legend with slightly transparent background brush:
  customPlot->legend->setVisible(true);
  customPlot->legend->setBrush(QColor(255, 255, 255, 150));
}

void MainWindow::setupTextureBrushDemo(QCustomPlot *customPlot)
{
  demoName = "Texture Brush Demo";
  // add two graphs with a textured fill:
  customPlot->addGraph();
  QPen redDotPen;
  redDotPen.setStyle(Qt::DotLine);
  redDotPen.setColor(QColor(170, 100, 100, 180));
  redDotPen.setWidthF(2);
  customPlot->graph(0)->setPen(redDotPen);
  customPlot->graph(0)->setBrush(QBrush(QPixmap("./balboa.jpg"))); // fill with texture of specified image
  
  customPlot->addGraph();
  customPlot->graph(1)->setPen(QPen(Qt::red));
  
  // activate channel fill for graph 0 towards graph 1:
  customPlot->graph(0)->setChannelFillGraph(customPlot->graph(1));
  
  // generate data:
  QVector<double> x(250);
  QVector<double> y0(250), y1(250);
  for (int i=0; i<250; ++i)
  {
    // just playing with numbers, not much to learn here
    x[i] = 3*i/250.0;
    y0[i] = 1+qExp(-x[i]*x[i]*0.8)*(x[i]*x[i]+x[i]);
    y1[i] = 1-qExp(-x[i]*x[i]*0.4)*(x[i]*x[i])*0.1;
  }
  
  // pass data points to graphs:
  customPlot->graph(0)->setData(x, y0);
  customPlot->graph(1)->setData(x, y1);
  // activate top and right axes, which are invisible by default:
  customPlot->xAxis2->setVisible(true);
  customPlot->yAxis2->setVisible(true);
  // make tick labels invisible on top and right axis:
  customPlot->xAxis2->setTickLabels(false);
  customPlot->yAxis2->setTickLabels(false);
  // set ranges:
  customPlot->xAxis->setRange(0, 2.5);
  customPlot->yAxis->setRange(0.9, 1.6);
  // assign top/right axes same properties as bottom/left:
  customPlot->axisRect()->setupFullAxesBox();
}

void MainWindow::setupMultiAxisDemo(QCustomPlot *customPlot)
{
  customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
  demoName = "Multi Axis Demo";
  
  customPlot->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom)); // period as decimal separator and comma as thousand separator
  customPlot->legend->setVisible(true);
  QFont legendFont = font();  // start out with MainWindow's font..
  legendFont.setPointSize(9); // and make a bit smaller for legend
  customPlot->legend->setFont(legendFont);
  customPlot->legend->setBrush(QBrush(QColor(255,255,255,230)));
  // by default, the legend is in the inset layout of the main axis rect. So this is how we access it to change legend placement:
  customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignBottom|Qt::AlignRight);
  
  // setup for graph 0: key axis left, value axis bottom
  // will contain left maxwell-like function
  customPlot->addGraph(customPlot->yAxis, customPlot->xAxis);
  customPlot->graph(0)->setPen(QPen(QColor(255, 100, 0)));
  customPlot->graph(0)->setBrush(QBrush(QPixmap("./balboa.jpg"))); // fill with texture of specified image
  customPlot->graph(0)->setLineStyle(QCPGraph::lsLine);
  customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));
  customPlot->graph(0)->setName("Left maxwell function");
  
  // setup for graph 1: key axis bottom, value axis left (those are the default axes)
  // will contain bottom maxwell-like function with error bars
  customPlot->addGraph();
  customPlot->graph(1)->setPen(QPen(Qt::red));
  customPlot->graph(1)->setBrush(QBrush(QPixmap("./balboa.jpg"))); // same fill as we used for graph 0
  customPlot->graph(1)->setLineStyle(QCPGraph::lsStepCenter);
  customPlot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, Qt::red, Qt::white, 7));
  customPlot->graph(1)->setName("Bottom maxwell function");
  QCPErrorBars *errorBars = new QCPErrorBars(customPlot->xAxis, customPlot->yAxis);
  errorBars->removeFromLegend();
  errorBars->setDataPlottable(customPlot->graph(1));
  
  // setup for graph 2: key axis top, value axis right
  // will contain high frequency sine with low frequency beating:
  customPlot->addGraph(customPlot->xAxis2, customPlot->yAxis2);
  customPlot->graph(2)->setPen(QPen(Qt::blue));
  customPlot->graph(2)->setName("High frequency sine");
  
  // setup for graph 3: same axes as graph 2
  // will contain low frequency beating envelope of graph 2
  customPlot->addGraph(customPlot->xAxis2, customPlot->yAxis2);
  QPen blueDotPen;
  blueDotPen.setColor(QColor(30, 40, 255, 150));
  blueDotPen.setStyle(Qt::DotLine);
  blueDotPen.setWidthF(4);
  customPlot->graph(3)->setPen(blueDotPen);
  customPlot->graph(3)->setName("Sine envelope");
  
  // setup for graph 4: key axis right, value axis top
  // will contain parabolically distributed data points with some random perturbance
  customPlot->addGraph(customPlot->yAxis2, customPlot->xAxis2);
  customPlot->graph(4)->setPen(QColor(50, 50, 50, 255));
  customPlot->graph(4)->setLineStyle(QCPGraph::lsNone);
  customPlot->graph(4)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
  customPlot->graph(4)->setName("Some random data around\na quadratic function");
  
  // generate data, just playing with numbers, not much to learn here:
  QVector<double> x0(25), y0(25);
  QVector<double> x1(15), y1(15), y1err(15);
  QVector<double> x2(250), y2(250);
  QVector<double> x3(250), y3(250);
  QVector<double> x4(250), y4(250);
  for (int i=0; i<25; ++i) // data for graph 0
  {
    x0[i] = 3*i/25.0;
    y0[i] = qExp(-x0[i]*x0[i]*0.8)*(x0[i]*x0[i]+x0[i]);
  }
  for (int i=0; i<15; ++i) // data for graph 1
  {
    x1[i] = 3*i/15.0;;
    y1[i] = qExp(-x1[i]*x1[i])*(x1[i]*x1[i])*2.6;
    y1err[i] = y1[i]*0.25;
  }
  for (int i=0; i<250; ++i) // data for graphs 2, 3 and 4
  {
    x2[i] = i/250.0*3*M_PI;
    x3[i] = x2[i];
    x4[i] = i/250.0*100-50;
    y2[i] = qSin(x2[i]*12)*qCos(x2[i])*10;
    y3[i] = qCos(x3[i])*10;
    y4[i] = 0.01*x4[i]*x4[i] + 1.5*(rand()/(double)RAND_MAX-0.5) + 1.5*M_PI;
  }
  
  // pass data points to graphs:
  customPlot->graph(0)->setData(x0, y0);
  customPlot->graph(1)->setData(x1, y1);
  errorBars->setData(y1err);
  customPlot->graph(2)->setData(x2, y2);
  customPlot->graph(3)->setData(x3, y3);
  customPlot->graph(4)->setData(x4, y4);
  // activate top and right axes, which are invisible by default:
  customPlot->xAxis2->setVisible(true);
  customPlot->yAxis2->setVisible(true);
  // set ranges appropriate to show data:
  customPlot->xAxis->setRange(0, 2.7);
  customPlot->yAxis->setRange(0, 2.6);
  customPlot->xAxis2->setRange(0, 3.0*M_PI);
  customPlot->yAxis2->setRange(-70, 35);
  // set pi ticks on top axis:
  customPlot->xAxis2->setTicker(QSharedPointer<QCPAxisTickerPi>(new QCPAxisTickerPi));
  // add title layout element:
  customPlot->plotLayout()->insertRow(0);
  customPlot->plotLayout()->addElement(0, 0, new QCPTextElement(customPlot, "Way too many graphs in one plot", QFont("sans", 12, QFont::Bold)));
  // set labels:
  customPlot->xAxis->setLabel("Bottom axis with outward ticks");
  customPlot->yAxis->setLabel("Left axis label");
  customPlot->xAxis2->setLabel("Top axis label");
  customPlot->yAxis2->setLabel("Right axis label");
  // make ticks on bottom axis go outward:
  customPlot->xAxis->setTickLength(0, 5);
  customPlot->xAxis->setSubTickLength(0, 3);
  // make ticks on right axis go inward and outward:
  customPlot->yAxis2->setTickLength(3, 3);
  customPlot->yAxis2->setSubTickLength(1, 1);
}

void MainWindow::setupLogarithmicDemo(QCustomPlot *customPlot)
{
  demoName = "Logarithmic Demo";
  customPlot->setNoAntialiasingOnDrag(true); // more performance/responsiveness during dragging
  customPlot->addGraph();
  QPen pen;
  pen.setColor(QColor(255,170,100));
  pen.setWidth(2);
  pen.setStyle(Qt::DotLine);
  customPlot->graph(0)->setPen(pen);
  customPlot->graph(0)->setName("x");
  
  customPlot->addGraph();
  customPlot->graph(1)->setPen(QPen(Qt::red));
  customPlot->graph(1)->setBrush(QBrush(QColor(255, 0, 0, 20)));
  customPlot->graph(1)->setName("-sin(x)exp(x)");
  
  customPlot->addGraph();
  customPlot->graph(2)->setPen(QPen(Qt::blue));
  customPlot->graph(2)->setBrush(QBrush(QColor(0, 0, 255, 20)));
  customPlot->graph(2)->setName(" sin(x)exp(x)");
  
  customPlot->addGraph();
  pen.setColor(QColor(0,0,0));
  pen.setWidth(1);
  pen.setStyle(Qt::DashLine);
  customPlot->graph(3)->setPen(pen);
  customPlot->graph(3)->setBrush(QBrush(QColor(0,0,0,15)));
  customPlot->graph(3)->setLineStyle(QCPGraph::lsStepCenter);
  customPlot->graph(3)->setName("x!");
  
  const int dataCount = 200;
  const int dataFactorialCount = 21;
  QVector<QCPGraphData> dataLinear(dataCount), dataMinusSinExp(dataCount), dataPlusSinExp(dataCount), dataFactorial(dataFactorialCount);
  for (int i=0; i<dataCount; ++i)
  {
    dataLinear[i].key = i/10.0;
    dataLinear[i].value = dataLinear[i].key;
    dataMinusSinExp[i].key = i/10.0;
    dataMinusSinExp[i].value = -qSin(dataMinusSinExp[i].key)*qExp(dataMinusSinExp[i].key);
    dataPlusSinExp[i].key = i/10.0;
    dataPlusSinExp[i].value = qSin(dataPlusSinExp[i].key)*qExp(dataPlusSinExp[i].key);
  }
  for (int i=0; i<dataFactorialCount; ++i)
  {
    dataFactorial[i].key = i;
    dataFactorial[i].value = 1.0;
    for (int k=1; k<=i; ++k) dataFactorial[i].value *= k; // factorial
  }
  customPlot->graph(0)->data()->set(dataLinear);
  customPlot->graph(1)->data()->set(dataMinusSinExp);
  customPlot->graph(2)->data()->set(dataPlusSinExp);
  customPlot->graph(3)->data()->set(dataFactorial);

  customPlot->yAxis->grid()->setSubGridVisible(true);
  customPlot->xAxis->grid()->setSubGridVisible(true);
  customPlot->yAxis->setScaleType(QCPAxis::stLogarithmic);
  customPlot->yAxis2->setScaleType(QCPAxis::stLogarithmic);
  QSharedPointer<QCPAxisTickerLog> logTicker(new QCPAxisTickerLog);
  customPlot->yAxis->setTicker(logTicker);
  customPlot->yAxis2->setTicker(logTicker);
  customPlot->yAxis->setNumberFormat("eb"); // e = exponential, b = beautiful decimal powers
  customPlot->yAxis->setNumberPrecision(0); // makes sure "1*10^4" is displayed only as "10^4"
  customPlot->xAxis->setRange(0, 19.9);
  customPlot->yAxis->setRange(1e-2, 1e10);
  // make range draggable and zoomable:
  customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
  
  // make top right axes clones of bottom left axes:
  customPlot->axisRect()->setupFullAxesBox();
  // connect signals so top and right axes move in sync with bottom and left axes:
  connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
  connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
  
  customPlot->legend->setVisible(true);
  customPlot->legend->setBrush(QBrush(QColor(255,255,255,150)));
  customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop); // make legend align in top left corner or axis rect
}

void MainWindow::setupRealtimeDataDemo(QCustomPlot *customPlot)
{
  demoName = "Real Time Data Demo";
  
  // include this section to fully disable antialiasing for higher performance:
  /*
  customPlot->setNotAntialiasedElements(QCP::aeAll);
  QFont font;
  font.setStyleStrategy(QFont::NoAntialias);
  customPlot->xAxis->setTickLabelFont(font);
  customPlot->yAxis->setTickLabelFont(font);
  customPlot->legend->setFont(font);
  */
  customPlot->addGraph(); // blue line
  customPlot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
  customPlot->addGraph(); // red line
  customPlot->graph(1)->setPen(QPen(QColor(255, 110, 40)));

  QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
  timeTicker->setTimeFormat("%h:%m:%s");
  customPlot->xAxis->setTicker(timeTicker);
  customPlot->axisRect()->setupFullAxesBox();
  customPlot->yAxis->setRange(-1.2, 1.2);
  
  // make left and bottom axes transfer their ranges to right and top axes:
  connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
  connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
  
  // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
  connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
  dataTimer.start(0); // Interval 0 means to refresh as fast as possible
}

void MainWindow::setupParametricCurveDemo(QCustomPlot *customPlot)
{
  demoName = "Parametric Curves Demo";
  
  // create empty curve objects:
  QCPCurve *fermatSpiral1 = new QCPCurve(customPlot->xAxis, customPlot->yAxis);
  QCPCurve *fermatSpiral2 = new QCPCurve(customPlot->xAxis, customPlot->yAxis);
  QCPCurve *deltoidRadial = new QCPCurve(customPlot->xAxis, customPlot->yAxis);
  // generate the curve data points:
  const int pointCount = 500;
  QVector<QCPCurveData> dataSpiral1(pointCount), dataSpiral2(pointCount), dataDeltoid(pointCount);
  for (int i=0; i<pointCount; ++i)
  {
    double phi = i/(double)(pointCount-1)*8*M_PI;
    double theta = i/(double)(pointCount-1)*2*M_PI;
    dataSpiral1[i] = QCPCurveData(i, qSqrt(phi)*qCos(phi), qSqrt(phi)*qSin(phi));
    dataSpiral2[i] = QCPCurveData(i, -dataSpiral1[i].key, -dataSpiral1[i].value);
    dataDeltoid[i] = QCPCurveData(i, 2*qCos(2*theta)+qCos(1*theta)+2*qSin(theta), 2*qSin(2*theta)-qSin(1*theta));
  }
  // pass the data to the curves; we know t (i in loop above) is ascending, so set alreadySorted=true (saves an extra internal sort):
  fermatSpiral1->data()->set(dataSpiral1, true);
  fermatSpiral2->data()->set(dataSpiral2, true);
  deltoidRadial->data()->set(dataDeltoid, true);
  // color the curves:
  fermatSpiral1->setPen(QPen(Qt::blue));
  fermatSpiral1->setBrush(QBrush(QColor(0, 0, 255, 20)));
  fermatSpiral2->setPen(QPen(QColor(255, 120, 0)));
  fermatSpiral2->setBrush(QBrush(QColor(255, 120, 0, 30)));
  QRadialGradient radialGrad(QPointF(310, 180), 200);
  radialGrad.setColorAt(0, QColor(170, 20, 240, 100));
  radialGrad.setColorAt(0.5, QColor(20, 10, 255, 40));
  radialGrad.setColorAt(1,QColor(120, 20, 240, 10));
  deltoidRadial->setPen(QPen(QColor(170, 20, 240)));
  deltoidRadial->setBrush(QBrush(radialGrad));
  // set some basic customPlot config:
  customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
  customPlot->axisRect()->setupFullAxesBox();
  customPlot->rescaleAxes();
}

void MainWindow::setupBarChartDemo(QCustomPlot *customPlot)
{
  demoName = "Bar Chart Demo";
  // set dark background gradient:
  QLinearGradient gradient(0, 0, 0, 400);
  gradient.setColorAt(0, QColor(90, 90, 90));
  gradient.setColorAt(0.38, QColor(105, 105, 105));
  gradient.setColorAt(1, QColor(70, 70, 70));
  customPlot->setBackground(QBrush(gradient));
  
  // create empty bar chart objects:
  QCPBars *regen = new QCPBars(customPlot->xAxis, customPlot->yAxis);
  QCPBars *nuclear = new QCPBars(customPlot->xAxis, customPlot->yAxis);
  QCPBars *fossil = new QCPBars(customPlot->xAxis, customPlot->yAxis);
  regen->setAntialiased(false); // gives more crisp, pixel aligned bar borders
  nuclear->setAntialiased(false);
  fossil->setAntialiased(false);
  regen->setStackingGap(1);
  nuclear->setStackingGap(1);
  fossil->setStackingGap(1);
  // set names and colors:
  fossil->setName("Fossil fuels");
  fossil->setPen(QPen(QColor(111, 9, 176).lighter(170)));
  fossil->setBrush(QColor(111, 9, 176));
  nuclear->setName("Nuclear");
  nuclear->setPen(QPen(QColor(250, 170, 20).lighter(150)));
  nuclear->setBrush(QColor(250, 170, 20));
  regen->setName("Regenerative");
  regen->setPen(QPen(QColor(0, 168, 140).lighter(130)));
  regen->setBrush(QColor(0, 168, 140));
  // stack bars on top of each other:
  nuclear->moveAbove(fossil);
  regen->moveAbove(nuclear);
  
  // prepare x axis with country labels:
  QVector<double> ticks;
  QVector<QString> labels;
  ticks << 1 << 2 << 3 << 4 << 5 << 6 << 7;
  labels << "USA" << "Japan" << "Germany" << "France" << "UK" << "Italy" << "Canada";
  QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
  textTicker->addTicks(ticks, labels);
  customPlot->xAxis->setTicker(textTicker);
  customPlot->xAxis->setTickLabelRotation(60);
  customPlot->xAxis->setSubTicks(false);
  customPlot->xAxis->setTickLength(0, 4);
  customPlot->xAxis->setRange(0, 8);
  customPlot->xAxis->setBasePen(QPen(Qt::white));
  customPlot->xAxis->setTickPen(QPen(Qt::white));
  customPlot->xAxis->grid()->setVisible(true);
  customPlot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
  customPlot->xAxis->setTickLabelColor(Qt::white);
  customPlot->xAxis->setLabelColor(Qt::white);
  
  // prepare y axis:
  customPlot->yAxis->setRange(0, 12.1);
  customPlot->yAxis->setPadding(5); // a bit more space to the left border
  customPlot->yAxis->setLabel("Power Consumption in\nKilowatts per Capita (2007)");
  customPlot->yAxis->setBasePen(QPen(Qt::white));
  customPlot->yAxis->setTickPen(QPen(Qt::white));
  customPlot->yAxis->setSubTickPen(QPen(Qt::white));
  customPlot->yAxis->grid()->setSubGridVisible(true);
  customPlot->yAxis->setTickLabelColor(Qt::white);
  customPlot->yAxis->setLabelColor(Qt::white);
  customPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
  customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
  
  // Add data:
  QVector<double> fossilData, nuclearData, regenData;
  fossilData  << 0.86*10.5 << 0.83*5.5 << 0.84*5.5 << 0.52*5.8 << 0.89*5.2 << 0.90*4.2 << 0.67*11.2;
  nuclearData << 0.08*10.5 << 0.12*5.5 << 0.12*5.5 << 0.40*5.8 << 0.09*5.2 << 0.00*4.2 << 0.07*11.2;
  regenData   << 0.06*10.5 << 0.05*5.5 << 0.04*5.5 << 0.06*5.8 << 0.02*5.2 << 0.07*4.2 << 0.25*11.2;
  fossil->setData(ticks, fossilData);
  nuclear->setData(ticks, nuclearData);
  regen->setData(ticks, regenData);
  
  // setup legend:
  customPlot->legend->setVisible(true);
  customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
  customPlot->legend->setBrush(QColor(255, 255, 255, 100));
  customPlot->legend->setBorderPen(Qt::NoPen);
  QFont legendFont = font();
  legendFont.setPointSize(10);
  customPlot->legend->setFont(legendFont);
  customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

void MainWindow::setupStatisticalDemo(QCustomPlot *customPlot)
{
  demoName = "Statistical Demo";
  QCPStatisticalBox *statistical = new QCPStatisticalBox(customPlot->xAxis, customPlot->yAxis);
  QBrush boxBrush(QColor(60, 60, 255, 100));
  boxBrush.setStyle(Qt::Dense6Pattern); // make it look oldschool
  statistical->setBrush(boxBrush);
  
  // specify data:
  statistical->addData(1, 1.1, 1.9, 2.25, 2.7, 4.2);
  statistical->addData(2, 0.8, 1.6, 2.2, 3.2, 4.9, QVector<double>() << 0.7 << 0.34 << 0.45 << 6.2 << 5.84); // provide some outliers as QVector
  statistical->addData(3, 0.2, 0.7, 1.1, 1.6, 2.9);
  
  // prepare manual x axis labels:
  customPlot->xAxis->setSubTicks(false);
  customPlot->xAxis->setTickLength(0, 4);
  customPlot->xAxis->setTickLabelRotation(20);
  QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
  textTicker->addTick(1, "Sample 1");
  textTicker->addTick(2, "Sample 2");
  textTicker->addTick(3, "Control Group");
  customPlot->xAxis->setTicker(textTicker);
  
  // prepare axes:
  customPlot->yAxis->setLabel(QString::fromUtf8("O₂ Absorption [mg]"));
  customPlot->rescaleAxes();
  customPlot->xAxis->scaleRange(1.7, customPlot->xAxis->range().center());
  customPlot->yAxis->setRange(0, 7);
  customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

void MainWindow::setupSimpleItemDemo(QCustomPlot *customPlot)
{
  demoName = "Simple Item Demo";
  customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
  
  // add the text label at the top:
  QCPItemText *textLabel = new QCPItemText(customPlot);
  textLabel->setPositionAlignment(Qt::AlignTop|Qt::AlignHCenter);
  textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
  textLabel->position->setCoords(0.5, 0); // place position at center/top of axis rect
  textLabel->setText("Text Item Demo");
  textLabel->setFont(QFont(font().family(), 16)); // make font a bit larger
  textLabel->setPen(QPen(Qt::black)); // show black border around text
  
  // add the arrow:
  QCPItemLine *arrow = new QCPItemLine(customPlot);
  arrow->start->setParentAnchor(textLabel->bottom);
  arrow->end->setCoords(4, 1.6); // point to (4, 1.6) in x-y-plot coordinates
  arrow->setHead(QCPLineEnding::esSpikeArrow);
}

void MainWindow::setupItemDemo(QCustomPlot *customPlot)
{
  demoName = "Item Demo";
  
  customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
  QCPGraph *graph = customPlot->addGraph();
  int n = 500;
  double phase = 0;
  double k = 3;
  QVector<double> x(n), y(n);
  for (int i=0; i<n; ++i)
  {
    x[i] = i/(double)(n-1)*34 - 17;
    y[i] = qExp(-x[i]*x[i]/20.0)*qSin(k*x[i]+phase);
  }
  graph->setData(x, y);
  graph->setPen(QPen(Qt::blue));
  graph->rescaleKeyAxis();
  customPlot->yAxis->setRange(-1.45, 1.65);
  customPlot->xAxis->grid()->setZeroLinePen(Qt::NoPen);
  
  // add the bracket at the top:
  QCPItemBracket *bracket = new QCPItemBracket(customPlot);
  bracket->left->setCoords(-8, 1.1);
  bracket->right->setCoords(8, 1.1);
  bracket->setLength(13);
  
  // add the text label at the top:
  QCPItemText *wavePacketText = new QCPItemText(customPlot);
  wavePacketText->position->setParentAnchor(bracket->center);
  wavePacketText->position->setCoords(0, -10); // move 10 pixels to the top from bracket center anchor
  wavePacketText->setPositionAlignment(Qt::AlignBottom|Qt::AlignHCenter);
  wavePacketText->setText("Wavepacket");
  wavePacketText->setFont(QFont(font().family(), 10));
  
  // add the phase tracer (red circle) which sticks to the graph data (and gets updated in bracketDataSlot by timer event):
  QCPItemTracer *phaseTracer = new QCPItemTracer(customPlot);
  itemDemoPhaseTracer = phaseTracer; // so we can access it later in the bracketDataSlot for animation
  phaseTracer->setGraph(graph);
  phaseTracer->setGraphKey((M_PI*1.5-phase)/k);
  phaseTracer->setInterpolating(true);
  phaseTracer->setStyle(QCPItemTracer::tsCircle);
  phaseTracer->setPen(QPen(Qt::red));
  phaseTracer->setBrush(Qt::red);
  phaseTracer->setSize(7);
  
  // add label for phase tracer:
  QCPItemText *phaseTracerText = new QCPItemText(customPlot);
  phaseTracerText->position->setType(QCPItemPosition::ptAxisRectRatio);
  phaseTracerText->setPositionAlignment(Qt::AlignRight|Qt::AlignBottom);
  phaseTracerText->position->setCoords(1.0, 0.95); // lower right corner of axis rect
  phaseTracerText->setText("Points of fixed\nphase define\nphase velocity vp");
  phaseTracerText->setTextAlignment(Qt::AlignLeft);
  phaseTracerText->setFont(QFont(font().family(), 9));
  phaseTracerText->setPadding(QMargins(8, 0, 0, 0));
  
  // add arrow pointing at phase tracer, coming from label:
  QCPItemCurve *phaseTracerArrow = new QCPItemCurve(customPlot);
  phaseTracerArrow->start->setParentAnchor(phaseTracerText->left);
  phaseTracerArrow->startDir->setParentAnchor(phaseTracerArrow->start);
  phaseTracerArrow->startDir->setCoords(-40, 0); // direction 30 pixels to the left of parent anchor (tracerArrow->start)
  phaseTracerArrow->end->setParentAnchor(phaseTracer->position);
  phaseTracerArrow->end->setCoords(10, 10);
  phaseTracerArrow->endDir->setParentAnchor(phaseTracerArrow->end);
  phaseTracerArrow->endDir->setCoords(30, 30);
  phaseTracerArrow->setHead(QCPLineEnding::esSpikeArrow);
  phaseTracerArrow->setTail(QCPLineEnding(QCPLineEnding::esBar, (phaseTracerText->bottom->pixelPosition().y()-phaseTracerText->top->pixelPosition().y())*0.85));
  
  // add the group velocity tracer (green circle):
  QCPItemTracer *groupTracer = new QCPItemTracer(customPlot);
  groupTracer->setGraph(graph);
  groupTracer->setGraphKey(5.5);
  groupTracer->setInterpolating(true);
  groupTracer->setStyle(QCPItemTracer::tsCircle);
  groupTracer->setPen(QPen(Qt::green));
  groupTracer->setBrush(Qt::green);
  groupTracer->setSize(7);
  
  // add label for group tracer:
  QCPItemText *groupTracerText = new QCPItemText(customPlot);
  groupTracerText->position->setType(QCPItemPosition::ptAxisRectRatio);
  groupTracerText->setPositionAlignment(Qt::AlignRight|Qt::AlignTop);
  groupTracerText->position->setCoords(1.0, 0.20); // lower right corner of axis rect
  groupTracerText->setText("Fixed positions in\nwave packet define\ngroup velocity vg");
  groupTracerText->setTextAlignment(Qt::AlignLeft);
  groupTracerText->setFont(QFont(font().family(), 9));
  groupTracerText->setPadding(QMargins(8, 0, 0, 0));
  
  // add arrow pointing at group tracer, coming from label:
  QCPItemCurve *groupTracerArrow = new QCPItemCurve(customPlot);
  groupTracerArrow->start->setParentAnchor(groupTracerText->left);
  groupTracerArrow->startDir->setParentAnchor(groupTracerArrow->start);
  groupTracerArrow->startDir->setCoords(-40, 0); // direction 30 pixels to the left of parent anchor (tracerArrow->start)
  groupTracerArrow->end->setCoords(5.5, 0.4);
  groupTracerArrow->endDir->setParentAnchor(groupTracerArrow->end);
  groupTracerArrow->endDir->setCoords(0, -40);
  groupTracerArrow->setHead(QCPLineEnding::esSpikeArrow);
  groupTracerArrow->setTail(QCPLineEnding(QCPLineEnding::esBar, (groupTracerText->bottom->pixelPosition().y()-groupTracerText->top->pixelPosition().y())*0.85));
  
  // add dispersion arrow:
  QCPItemCurve *arrow = new QCPItemCurve(customPlot);
  arrow->start->setCoords(1, -1.1);
  arrow->startDir->setCoords(-1, -1.3);
  arrow->endDir->setCoords(-5, -0.3);
  arrow->end->setCoords(-10, -0.2);
  arrow->setHead(QCPLineEnding::esSpikeArrow);
  
  // add the dispersion arrow label:
  QCPItemText *dispersionText = new QCPItemText(customPlot);
  dispersionText->position->setCoords(-6, -0.9);
  dispersionText->setRotation(40);
  dispersionText->setText("Dispersion with\nvp < vg");
  dispersionText->setFont(QFont(font().family(), 10));
  
  // setup a timer that repeatedly calls MainWindow::bracketDataSlot:
  connect(&dataTimer, SIGNAL(timeout()), this, SLOT(bracketDataSlot()));
  dataTimer.start(0); // Interval 0 means to refresh as fast as possible
}

void MainWindow::setupStyledDemo(QCustomPlot *customPlot)
{
  demoName = "Styled Demo";
  
  // prepare data:
  QVector<double> x1(20), y1(20);
  QVector<double> x2(100), y2(100);
  QVector<double> x3(20), y3(20);
  QVector<double> x4(20), y4(20);
  for (int i=0; i<x1.size(); ++i)
  {
    x1[i] = i/(double)(x1.size()-1)*10;
    y1[i] = qCos(x1[i]*0.8+qSin(x1[i]*0.16+1.0))*qSin(x1[i]*0.54)+1.4;
  }
  for (int i=0; i<x2.size(); ++i)
  {
    x2[i] = i/(double)(x2.size()-1)*10;
    y2[i] = qCos(x2[i]*0.85+qSin(x2[i]*0.165+1.1))*qSin(x2[i]*0.50)+1.7;
  }
  for (int i=0; i<x3.size(); ++i)
  {
    x3[i] = i/(double)(x3.size()-1)*10;
    y3[i] = 0.05+3*(0.5+qCos(x3[i]*x3[i]*0.2+2)*0.5)/(double)(x3[i]+0.7)+std::rand()/(double)RAND_MAX*0.01;
  }
  for (int i=0; i<x4.size(); ++i)
  {
    x4[i] = x3[i];
    y4[i] = (0.5-y3[i])+((x4[i]-2)*(x4[i]-2)*0.02);
  }
  
  // create and configure plottables:
  QCPGraph *graph1 = customPlot->addGraph();
  graph1->setData(x1, y1);
  graph1->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1.5), QBrush(Qt::white), 9));
  graph1->setPen(QPen(QColor(120, 120, 120), 2));

  QCPGraph *graph2 = customPlot->addGraph();
  graph2->setData(x2, y2);
  graph2->setPen(Qt::NoPen);
  graph2->setBrush(QColor(200, 200, 200, 20));
  graph2->setChannelFillGraph(graph1);
  
  QCPBars *bars1 = new QCPBars(customPlot->xAxis, customPlot->yAxis);
  bars1->setWidth(9/(double)x3.size());
  bars1->setData(x3, y3);
  bars1->setPen(Qt::NoPen);
  bars1->setBrush(QColor(10, 140, 70, 160));
  
  QCPBars *bars2 = new QCPBars(customPlot->xAxis, customPlot->yAxis);
  bars2->setWidth(9/(double)x4.size());
  bars2->setData(x4, y4);
  bars2->setPen(Qt::NoPen);
  bars2->setBrush(QColor(10, 100, 50, 70));
  bars2->moveAbove(bars1);
  
  // move bars above graphs and grid below bars:
  customPlot->addLayer("abovemain", customPlot->layer("main"), QCustomPlot::limAbove);
  customPlot->addLayer("belowmain", customPlot->layer("main"), QCustomPlot::limBelow);
  graph1->setLayer("abovemain");
  customPlot->xAxis->grid()->setLayer("belowmain");
  customPlot->yAxis->grid()->setLayer("belowmain");

  // set some pens, brushes and backgrounds:
  customPlot->xAxis->setBasePen(QPen(Qt::white, 1));
  customPlot->yAxis->setBasePen(QPen(Qt::white, 1));
  customPlot->xAxis->setTickPen(QPen(Qt::white, 1));
  customPlot->yAxis->setTickPen(QPen(Qt::white, 1));
  customPlot->xAxis->setSubTickPen(QPen(Qt::white, 1));
  customPlot->yAxis->setSubTickPen(QPen(Qt::white, 1));
  customPlot->xAxis->setTickLabelColor(Qt::white);
  customPlot->yAxis->setTickLabelColor(Qt::white);
  customPlot->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
  customPlot->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
  customPlot->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
  customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
  customPlot->xAxis->grid()->setSubGridVisible(true);
  customPlot->yAxis->grid()->setSubGridVisible(true);
  customPlot->xAxis->grid()->setZeroLinePen(Qt::NoPen);
  customPlot->yAxis->grid()->setZeroLinePen(Qt::NoPen);
  customPlot->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
  customPlot->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
  QLinearGradient plotGradient;
  plotGradient.setStart(0, 0);
  plotGradient.setFinalStop(0, 350);
  plotGradient.setColorAt(0, QColor(80, 80, 80));
  plotGradient.setColorAt(1, QColor(50, 50, 50));
  customPlot->setBackground(plotGradient);
  QLinearGradient axisRectGradient;
  axisRectGradient.setStart(0, 0);
  axisRectGradient.setFinalStop(0, 350);
  axisRectGradient.setColorAt(0, QColor(80, 80, 80));
  axisRectGradient.setColorAt(1, QColor(30, 30, 30));
  customPlot->axisRect()->setBackground(axisRectGradient);
  
  customPlot->rescaleAxes();
  customPlot->yAxis->setRange(0, 2);
}

void MainWindow::setupAdvancedAxesDemo(QCustomPlot *customPlot)
{
  demoName = "Advanced Axes Demo";
  
  // configure axis rect:
  customPlot->plotLayout()->clear(); // clear default axis rect so we can start from scratch
  QCPAxisRect *wideAxisRect = new QCPAxisRect(customPlot);
  wideAxisRect->setupFullAxesBox(true);
  wideAxisRect->axis(QCPAxis::atRight, 0)->setTickLabels(true);
  wideAxisRect->addAxis(QCPAxis::atLeft)->setTickLabelColor(QColor("#6050F8")); // add an extra axis on the left and color its numbers
  QCPLayoutGrid *subLayout = new QCPLayoutGrid;
  customPlot->plotLayout()->addElement(0, 0, wideAxisRect); // insert axis rect in first row
  customPlot->plotLayout()->addElement(1, 0, subLayout); // sub layout in second row (grid layout will grow accordingly)
  //customPlot->plotLayout()->setRowStretchFactor(1, 2);
  // prepare axis rects that will be placed in the sublayout:
  QCPAxisRect *subRectLeft = new QCPAxisRect(customPlot, false); // false means to not setup default axes
  QCPAxisRect *subRectRight = new QCPAxisRect(customPlot, false);
  subLayout->addElement(0, 0, subRectLeft);
  subLayout->addElement(0, 1, subRectRight);
  subRectRight->setMaximumSize(100, 100); // make bottom right axis rect size fixed 100x100
  subRectRight->setMinimumSize(100, 100); // make bottom right axis rect size fixed 100x100
  // setup axes in sub layout axis rects:
  subRectLeft->addAxes(QCPAxis::atBottom | QCPAxis::atLeft);
  subRectRight->addAxes(QCPAxis::atBottom | QCPAxis::atRight);
  subRectLeft->axis(QCPAxis::atLeft)->ticker()->setTickCount(2);
  subRectRight->axis(QCPAxis::atRight)->ticker()->setTickCount(2);
  subRectRight->axis(QCPAxis::atBottom)->ticker()->setTickCount(2);
  subRectLeft->axis(QCPAxis::atBottom)->grid()->setVisible(true);
  // synchronize the left and right margins of the top and bottom axis rects:
  QCPMarginGroup *marginGroup = new QCPMarginGroup(customPlot);
  subRectLeft->setMarginGroup(QCP::msLeft, marginGroup);
  subRectRight->setMarginGroup(QCP::msRight, marginGroup);
  wideAxisRect->setMarginGroup(QCP::msLeft | QCP::msRight, marginGroup);
  // move newly created axes on "axes" layer and grids on "grid" layer:
  foreach (QCPAxisRect *rect, customPlot->axisRects())
  {
    foreach (QCPAxis *axis, rect->axes())
    {
      axis->setLayer("axes");
      axis->grid()->setLayer("grid");
    }
  }
  
  // prepare data:
  QVector<QCPGraphData> dataCos(21), dataGauss(50), dataRandom(100);
  QVector<double> x3, y3;
  std::srand(3);
  for (int i=0; i<dataCos.size(); ++i)
  {
    dataCos[i].key = i/(double)(dataCos.size()-1)*10-5.0;
    dataCos[i].value = qCos(dataCos[i].key);
  }
  for (int i=0; i<dataGauss.size(); ++i)
  {
    dataGauss[i].key = i/(double)dataGauss.size()*10-5.0;
    dataGauss[i].value = qExp(-dataGauss[i].key*dataGauss[i].key*0.2)*1000;
  }
  for (int i=0; i<dataRandom.size(); ++i)
  {
    dataRandom[i].key = i/(double)dataRandom.size()*10;
    dataRandom[i].value = std::rand()/(double)RAND_MAX-0.5+dataRandom[qMax(0, i-1)].value;
  }
  x3 << 1 << 2 << 3 << 4;
  y3 << 2 << 2.5 << 4 << 1.5;
  
  // create and configure plottables:
  QCPGraph *mainGraphCos = customPlot->addGraph(wideAxisRect->axis(QCPAxis::atBottom), wideAxisRect->axis(QCPAxis::atLeft));
  mainGraphCos->data()->set(dataCos);
  mainGraphCos->valueAxis()->setRange(-1, 1);
  mainGraphCos->rescaleKeyAxis();
  mainGraphCos->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black), QBrush(Qt::white), 6));
  mainGraphCos->setPen(QPen(QColor(120, 120, 120), 2));
  QCPGraph *mainGraphGauss = customPlot->addGraph(wideAxisRect->axis(QCPAxis::atBottom), wideAxisRect->axis(QCPAxis::atLeft, 1));
  mainGraphGauss->data()->set(dataGauss);
  mainGraphGauss->setPen(QPen(QColor("#8070B8"), 2));
  mainGraphGauss->setBrush(QColor(110, 170, 110, 30));
  mainGraphCos->setChannelFillGraph(mainGraphGauss);
  mainGraphCos->setBrush(QColor(255, 161, 0, 50));
  mainGraphGauss->valueAxis()->setRange(0, 1000);
  mainGraphGauss->rescaleKeyAxis();
  
  QCPGraph *subGraphRandom = customPlot->addGraph(subRectLeft->axis(QCPAxis::atBottom), subRectLeft->axis(QCPAxis::atLeft));
  subGraphRandom->data()->set(dataRandom);
  subGraphRandom->setLineStyle(QCPGraph::lsImpulse);
  subGraphRandom->setPen(QPen(QColor("#FFA100"), 1.5));
  subGraphRandom->rescaleAxes();
  
  QCPBars *subBars = new QCPBars(subRectRight->axis(QCPAxis::atBottom), subRectRight->axis(QCPAxis::atRight));
  subBars->setWidth(3/(double)x3.size());
  subBars->setData(x3, y3);
  subBars->setPen(QPen(Qt::black));
  subBars->setAntialiased(false);
  subBars->setAntialiasedFill(false);
  subBars->setBrush(QColor("#705BE8"));
  subBars->keyAxis()->setSubTicks(false);
  subBars->rescaleAxes();
  // setup a ticker for subBars key axis that only gives integer ticks:
  QSharedPointer<QCPAxisTickerFixed> intTicker(new QCPAxisTickerFixed);
  intTicker->setTickStep(1.0);
  intTicker->setScaleStrategy(QCPAxisTickerFixed::ssMultiples);
  subBars->keyAxis()->setTicker(intTicker);
}

void MainWindow::setupColorMapDemo(QCustomPlot *customPlot)
{
  demoName = "Color Map Demo";
  
  // configure axis rect:
  customPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
  customPlot->axisRect()->setupFullAxesBox(true);
  customPlot->xAxis->setLabel("x");
  customPlot->yAxis->setLabel("y");

  // set up the QCPColorMap:
  QCPColorMap *colorMap = new QCPColorMap(customPlot->xAxis, customPlot->yAxis);
  int nx = 200;
  int ny = 200;
  colorMap->data()->setSize(nx, ny); // we want the color map to have nx * ny data points
  colorMap->data()->setRange(QCPRange(-4, 4), QCPRange(-4, 4)); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions
  // now we assign some data, by accessing the QCPColorMapData instance of the color map:
  double x, y, z;
  for (int xIndex=0; xIndex<nx; ++xIndex)
  {
    for (int yIndex=0; yIndex<ny; ++yIndex)
    {
      colorMap->data()->cellToCoord(xIndex, yIndex, &x, &y);
      double r = 3*qSqrt(x*x+y*y)+1e-2;
      z = 2*x*(qCos(r+2)/r-qSin(r+2)/r); // the B field strength of dipole radiation (modulo physical constants)
      colorMap->data()->setCell(xIndex, yIndex, z);
    }
  }
  
  // add a color scale:
  QCPColorScale *colorScale = new QCPColorScale(customPlot);
  customPlot->plotLayout()->addElement(0, 1, colorScale); // add it to the right of the main axis rect
  colorScale->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)
  colorMap->setColorScale(colorScale); // associate the color map with the color scale
  colorScale->axis()->setLabel("Magnetic Field Strength");
  
  // set the color gradient of the color map to one of the presets:
  colorMap->setGradient(QCPColorGradient::gpPolar);
  // we could have also created a QCPColorGradient instance and added own colors to
  // the gradient, see the documentation of QCPColorGradient for what's possible.
  
  // rescale the data dimension (color) such that all data points lie in the span visualized by the color gradient:
  colorMap->rescaleDataRange();
  
  // make sure the axis rect and color scale synchronize their bottom and top margins (so they line up):
  QCPMarginGroup *marginGroup = new QCPMarginGroup(customPlot);
  customPlot->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
  colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
  
  // rescale the key (x) and value (y) axes so the whole color map is visible:
  customPlot->rescaleAxes();
}

void MainWindow::setupFinancialDemo(QCustomPlot *customPlot)
{
  demoName = "Financial Charts Demo";
  customPlot->legend->setVisible(true);
  
  // generate two sets of random walk data (one for candlestick and one for ohlc chart):
  int n = 500;
  QVector<double> time(n), value1(n), value2(n);
  QDateTime start(QDate(2014, 6, 11), QTime(0, 0));
  start.setTimeSpec(Qt::UTC);
  double startTime = start.toMSecsSinceEpoch()/1000.0;
  double binSize = 3600*24; // bin data in 1 day intervals
  time[0] = startTime;
  value1[0] = 60;
  value2[0] = 20;
  std::srand(9);
  for (int i=1; i<n; ++i)
  {
    time[i] = startTime + 3600*i;
    value1[i] = value1[i-1] + (std::rand()/(double)RAND_MAX-0.5)*10;
    value2[i] = value2[i-1] + (std::rand()/(double)RAND_MAX-0.5)*3;
  }
  
  // create candlestick chart:
  QCPFinancial *candlesticks = new QCPFinancial(customPlot->xAxis, customPlot->yAxis);
  candlesticks->setName("Candlestick");
  candlesticks->setChartStyle(QCPFinancial::csCandlestick);
  candlesticks->data()->set(QCPFinancial::timeSeriesToOhlc(time, value1, binSize, startTime));
  candlesticks->setWidth(binSize*0.9);
  candlesticks->setTwoColored(true);
  candlesticks->setBrushPositive(QColor(245, 245, 245));
  candlesticks->setBrushNegative(QColor(40, 40, 40));
  candlesticks->setPenPositive(QPen(QColor(0, 0, 0)));
  candlesticks->setPenNegative(QPen(QColor(0, 0, 0)));
  
  // create ohlc chart:
  QCPFinancial *ohlc = new QCPFinancial(customPlot->xAxis, customPlot->yAxis);
  ohlc->setName("OHLC");
  ohlc->setChartStyle(QCPFinancial::csOhlc);
  ohlc->data()->set(QCPFinancial::timeSeriesToOhlc(time, value2, binSize/3.0, startTime)); // divide binSize by 3 just to make the ohlc bars a bit denser
  ohlc->setWidth(binSize*0.2);
  ohlc->setTwoColored(true);
  
  // create bottom axis rect for volume bar chart:
  QCPAxisRect *volumeAxisRect = new QCPAxisRect(customPlot);
  customPlot->plotLayout()->addElement(1, 0, volumeAxisRect);
  volumeAxisRect->setMaximumSize(QSize(QWIDGETSIZE_MAX, 100));
  volumeAxisRect->axis(QCPAxis::atBottom)->setLayer("axes");
  volumeAxisRect->axis(QCPAxis::atBottom)->grid()->setLayer("grid");
  // bring bottom and main axis rect closer together:
  customPlot->plotLayout()->setRowSpacing(0);
  volumeAxisRect->setAutoMargins(QCP::msLeft|QCP::msRight|QCP::msBottom);
  volumeAxisRect->setMargins(QMargins(0, 0, 0, 0));
  // create two bar plottables, for positive (green) and negative (red) volume bars:
  customPlot->setAutoAddPlottableToLegend(false);
  QCPBars *volumePos = new QCPBars(volumeAxisRect->axis(QCPAxis::atBottom), volumeAxisRect->axis(QCPAxis::atLeft));
  QCPBars *volumeNeg = new QCPBars(volumeAxisRect->axis(QCPAxis::atBottom), volumeAxisRect->axis(QCPAxis::atLeft));
  for (int i=0; i<n/5; ++i)
  {
    int v = std::rand()%20000+std::rand()%20000+std::rand()%20000-10000*3;
    (v < 0 ? volumeNeg : volumePos)->addData(startTime+3600*5.0*i, qAbs(v)); // add data to either volumeNeg or volumePos, depending on sign of v
  }
  volumePos->setWidth(3600*4);
  volumePos->setPen(Qt::NoPen);
  volumePos->setBrush(QColor(100, 180, 110));
  volumeNeg->setWidth(3600*4);
  volumeNeg->setPen(Qt::NoPen);
  volumeNeg->setBrush(QColor(180, 90, 90));
  
  // interconnect x axis ranges of main and bottom axis rects:
  connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), volumeAxisRect->axis(QCPAxis::atBottom), SLOT(setRange(QCPRange)));
  connect(volumeAxisRect->axis(QCPAxis::atBottom), SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis, SLOT(setRange(QCPRange)));
  // configure axes of both main and bottom axis rect:
  QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
  dateTimeTicker->setDateTimeSpec(Qt::UTC);
  dateTimeTicker->setDateTimeFormat("dd. MMMM");
  volumeAxisRect->axis(QCPAxis::atBottom)->setTicker(dateTimeTicker);
  volumeAxisRect->axis(QCPAxis::atBottom)->setTickLabelRotation(15);
  customPlot->xAxis->setBasePen(Qt::NoPen);
  customPlot->xAxis->setTickLabels(false);
  customPlot->xAxis->setTicks(false); // only want vertical grid in main axis rect, so hide xAxis backbone, ticks, and labels
  customPlot->xAxis->setTicker(dateTimeTicker);
  customPlot->rescaleAxes();
  customPlot->xAxis->scaleRange(1.025, customPlot->xAxis->range().center());
  customPlot->yAxis->scaleRange(1.1, customPlot->yAxis->range().center());
  
  // make axis rects' left side line up:
  QCPMarginGroup *group = new QCPMarginGroup(customPlot);
  customPlot->axisRect()->setMarginGroup(QCP::msLeft|QCP::msRight, group);
  volumeAxisRect->setMarginGroup(QCP::msLeft|QCP::msRight, group);
}

void MainWindow::setupPolarPlotDemo(QCustomPlot *customPlot)
{
  // Warning: Polar plots are a still a tech preview
  
  customPlot->plotLayout()->clear();
  QCPPolarAxisAngular *angularAxis = new QCPPolarAxisAngular(customPlot);
  customPlot->plotLayout()->addElement(0, 0, angularAxis);
  /* This is how we could set the angular axis to show pi symbols instead of degree numbers:
  QSharedPointer<QCPAxisTickerPi> ticker(new QCPAxisTickerPi);
  ticker->setPiValue(180);
  ticker->setTickCount(8);
  polarAxis->setTicker(ticker);
  */
  customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
  angularAxis->setRangeDrag(false);
  angularAxis->setTickLabelMode(QCPPolarAxisAngular::lmUpright);
  
  angularAxis->radialAxis()->setTickLabelMode(QCPPolarAxisRadial::lmUpright);
  angularAxis->radialAxis()->setTickLabelRotation(0);
  angularAxis->radialAxis()->setAngle(45);
  
  angularAxis->grid()->setAngularPen(QPen(QColor(200, 200, 200), 0, Qt::SolidLine));
  angularAxis->grid()->setSubGridType(QCPPolarGrid::gtAll);
  
  QCPPolarGraph *g1 = new QCPPolarGraph(angularAxis, angularAxis->radialAxis());
  QCPPolarGraph *g2 = new QCPPolarGraph(angularAxis, angularAxis->radialAxis());
  g2->setPen(QPen(QColor(255, 150, 20)));
  g2->setBrush(QColor(255, 150, 20, 50));
  g1->setScatterStyle(QCPScatterStyle::ssDisc);
  for (int i=0; i<100; ++i)
  {
    g1->addData(i/100.0*360.0, qSin(i/100.0*M_PI*8)*8+1);
    g2->addData(i/100.0*360.0, qSin(i/100.0*M_PI*6)*2);
  }
  angularAxis->setRange(0, 360);
  angularAxis->radialAxis()->setRange(-10, 10);
}

void MainWindow::realtimeDataSlot()
{
  static QTime timeStart = QTime::currentTime();
  // calculate two new data points:
  double key = timeStart.msecsTo(QTime::currentTime())/1000.0; // time elapsed since start of demo, in seconds
  static double lastPointKey = 0;
  if (key-lastPointKey > 0.002) // at most add point every 2 ms
  {
    // add data to lines:
    ui->customPlot->graph(0)->addData(key, qSin(key)+std::rand()/(double)RAND_MAX*1*qSin(key/0.3843));
    ui->customPlot->graph(1)->addData(key, qCos(key)+std::rand()/(double)RAND_MAX*0.5*qSin(key/0.4364));
    // rescale value (vertical) axis to fit the current data:
    //ui->customPlot->graph(0)->rescaleValueAxis();
    //ui->customPlot->graph(1)->rescaleValueAxis(true);
    lastPointKey = key;
  }
  // make key axis range scroll with the data (at a constant range size of 8):
  ui->customPlot->xAxis->setRange(key, 8, Qt::AlignRight);
  ui->customPlot->replot();
  
  // calculate frames per second:
  static double lastFpsKey;
  static int frameCount;
  ++frameCount;
  if (key-lastFpsKey > 2) // average fps over 2 seconds
  {
    ui->statusBar->showMessage(
          QString("%1 FPS, Total Data points: %2")
          .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
          .arg(ui->customPlot->graph(0)->data()->size()+ui->customPlot->graph(1)->data()->size())
          , 0);
    lastFpsKey = key;
    frameCount = 0;
  }
}

void MainWindow::bracketDataSlot()
{
  double secs = QCPAxisTickerDateTime::dateTimeToKey(QDateTime::currentDateTime());
  
  // update data to make phase move:
  int n = 500;
  double phase = secs*5;
  double k = 3;
  QVector<double> x(n), y(n);
  for (int i=0; i<n; ++i)
  {
    x[i] = i/(double)(n-1)*34 - 17;
    y[i] = qExp(-x[i]*x[i]/20.0)*qSin(k*x[i]+phase);
  }
  ui->customPlot->graph()->setData(x, y);
  
  itemDemoPhaseTracer->setGraphKey((8*M_PI+fmod(M_PI*1.5-phase, 6*M_PI))/k);
  
  ui->customPlot->replot();
  
  // calculate frames per second:
  double key = secs;
  static double lastFpsKey;
  static int frameCount;
  ++frameCount;
  if (key-lastFpsKey > 2) // average fps over 2 seconds
  {
    ui->statusBar->showMessage(
          QString("%1 FPS, Total Data points: %2")
          .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
          .arg(ui->customPlot->graph(0)->data()->size())
          , 0);
    lastFpsKey = key;
    frameCount = 0;
  }
}

void MainWindow::setupPlayground(QCustomPlot *customPlot)
{
  Q_UNUSED(customPlot)
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::screenShot()
{
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
  QPixmap pm = QPixmap::grabWindow(qApp->desktop()->winId(), this->x()+2, this->y()+2, this->frameGeometry().width()-4, this->frameGeometry().height()-4);
#elif QT_VERSION < QT_VERSION_CHECK(5, 5, 0)
  QPixmap pm = qApp->primaryScreen()->grabWindow(qApp->desktop()->winId(), this->x()+2, this->y()+2, this->frameGeometry().width()-4, this->frameGeometry().height()-4);
#elif QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
  QPixmap pm = qApp->primaryScreen()->grabWindow(qApp->desktop()->winId(), this->x()-7, this->y()-7, this->frameGeometry().width()+14, this->frameGeometry().height()+14);
#else
  QPixmap pm = qApp->primaryScreen()->grabWindow(0, this->x()-7, this->y()-7, this->frameGeometry().width()+14, this->frameGeometry().height()+14);
#endif
  QString fileName = demoName.toLower()+".png";
  fileName.replace(" ", "");
  pm.save("./screenshots/"+fileName);
  qApp->quit();
}

void MainWindow::allScreenShots()
{
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
  QPixmap pm = QPixmap::grabWindow(qApp->desktop()->winId(), this->x()+2, this->y()+2, this->frameGeometry().width()-4, this->frameGeometry().height()-4);
#elif QT_VERSION < QT_VERSION_CHECK(5, 5, 0)
  QPixmap pm = qApp->primaryScreen()->grabWindow(qApp->desktop()->winId(), this->x()+2, this->y()+2, this->frameGeometry().width()-4, this->frameGeometry().height()-4);
#elif QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
  QPixmap pm = qApp->primaryScreen()->grabWindow(qApp->desktop()->winId(), this->x()-7, this->y()-7, this->frameGeometry().width()+14, this->frameGeometry().height()+14);
#else
  QPixmap pm = qApp->primaryScreen()->grabWindow(0, this->x()-7, this->y()-7, this->frameGeometry().width()+14, this->frameGeometry().height()+14);
#endif
  QString fileName = demoName.toLower()+".png";
  fileName.replace(" ", "");
  pm.save("./screenshots/"+fileName);
  
  if (currentDemoIndex < 19)
  {
    if (dataTimer.isActive())
      dataTimer.stop();
    dataTimer.disconnect();
    delete ui->customPlot;
    ui->customPlot = new QCustomPlot(ui->centralWidget);
    ui->verticalLayout->addWidget(ui->customPlot);
    setupDemo(currentDemoIndex+1);
    // setup delay for demos that need time to develop proper look:
    int delay = 250;
    if (currentDemoIndex == 10) // Next is Realtime data demo
      delay = 12000;
    else if (currentDemoIndex == 15) // Next is Item demo
      delay = 5000;
    QTimer::singleShot(delay, this, SLOT(allScreenShots()));
  } else
  {
    qApp->quit();
  }
}







































