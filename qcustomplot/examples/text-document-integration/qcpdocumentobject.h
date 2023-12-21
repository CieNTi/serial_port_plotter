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

#ifndef QCPDOCUMENTOBJECT_H
#define QCPDOCUMENTOBJECT_H

#include <QObject>
#include <QTextObjectInterface>
#include <QPicture>
#include <QVariant>
#include <QPainter>
#include "../../qcustomplot.h"

class QCPDocumentObject : public QObject, public QTextObjectInterface
{
  Q_OBJECT
  Q_INTERFACES(QTextObjectInterface)
  
public:
  enum { PlotTextFormat = QTextFormat::UserObject + 3902 }; // if your application already uses the id (QTextFormat::UserObject + 3902), just change the id here
  enum { PicturePropertyId = 1 };
  
  explicit QCPDocumentObject(QObject *parent = 0);
  QSizeF intrinsicSize(QTextDocument *doc, int posInDocument, const QTextFormat &format);
  void drawObject(QPainter *painter, const QRectF &rect, QTextDocument *doc, int posInDocument, const QTextFormat &format);

  static QTextCharFormat generatePlotFormat(QCustomPlot *plot, int width=0, int height=0);

};
Q_DECLARE_METATYPE(QPicture)

#endif // QCPDOCUMENTOBJECT_H
