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

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  mPlot(0),
  mTag1(0),
  mTag2(0)
{
  ui->setupUi(this);
  
  mPlot = new QCustomPlot(this);
  setCentralWidget(mPlot);
  
  // configure plot to have two right axes:
  mPlot->yAxis->setTickLabels(false);
  connect(mPlot->yAxis2, SIGNAL(rangeChanged(QCPRange)), mPlot->yAxis, SLOT(setRange(QCPRange))); // left axis only mirrors inner right axis
  mPlot->yAxis2->setVisible(true);
  mPlot->axisRect()->addAxis(QCPAxis::atRight);
  mPlot->axisRect()->axis(QCPAxis::atRight, 0)->setPadding(30); // add some padding to have space for tags
  mPlot->axisRect()->axis(QCPAxis::atRight, 1)->setPadding(30); // add some padding to have space for tags
  
  // create graphs:
  mGraph1 = mPlot->addGraph(mPlot->xAxis, mPlot->axisRect()->axis(QCPAxis::atRight, 0));
  mGraph2 = mPlot->addGraph(mPlot->xAxis, mPlot->axisRect()->axis(QCPAxis::atRight, 1));
  mGraph1->setPen(QPen(QColor(250, 120, 0)));
  mGraph2->setPen(QPen(QColor(0, 180, 60)));
  
  // create tags with newly introduced AxisTag class (see axistag.h/.cpp):
  mTag1 = new AxisTag(mGraph1->valueAxis());
  mTag1->setPen(mGraph1->pen());
  mTag2 = new AxisTag(mGraph2->valueAxis());
  mTag2->setPen(mGraph2->pen());
  
  connect(&mDataTimer, SIGNAL(timeout()), this, SLOT(timerSlot()));
  mDataTimer.start(40);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::timerSlot()
{
  // calculate and add a new data point to each graph:
  mGraph1->addData(mGraph1->dataCount(), qSin(mGraph1->dataCount()/50.0)+qSin(mGraph1->dataCount()/50.0/0.3843)*0.25);
  mGraph2->addData(mGraph2->dataCount(), qCos(mGraph2->dataCount()/50.0)+qSin(mGraph2->dataCount()/50.0/0.4364)*0.15);

  // make key axis range scroll with the data:
  mPlot->xAxis->rescale();
  mGraph1->rescaleValueAxis(false, true);
  mGraph2->rescaleValueAxis(false, true);
  mPlot->xAxis->setRange(mPlot->xAxis->range().upper, 100, Qt::AlignRight);
  
  // update the vertical axis tag positions and texts to match the rightmost data point of the graphs:
  double graph1Value = mGraph1->dataMainValue(mGraph1->dataCount()-1);
  double graph2Value = mGraph2->dataMainValue(mGraph2->dataCount()-1);
  mTag1->updatePosition(graph1Value);
  mTag2->updatePosition(graph2Value);
  mTag1->setText(QString::number(graph1Value, 'f', 2));
  mTag2->setText(QString::number(graph2Value, 'f', 2));
  
  mPlot->replot();
}
