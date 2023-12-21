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

#include "qcpdocumentobject.h"

QCPDocumentObject::QCPDocumentObject(QObject *parent) :
  QObject(parent)
{
}

QSizeF QCPDocumentObject::intrinsicSize(QTextDocument *doc, int posInDocument, const QTextFormat &format)
{
  Q_UNUSED(doc)
  Q_UNUSED(posInDocument)
  QPicture pic = qvariant_cast<QPicture>(format.property(PicturePropertyId));
  if (pic.isNull())
  {
    qDebug() << Q_FUNC_INFO << "Plot object is empty";
    return QSizeF(10, 10);
  } else
    return QSizeF(pic.boundingRect().size());
}

void QCPDocumentObject::drawObject(QPainter *painter, const QRectF &rect, QTextDocument *doc, int posInDocument, const QTextFormat &format)
{
  Q_UNUSED(doc)
  Q_UNUSED(posInDocument)
  QPicture pic = qvariant_cast<QPicture>(format.property(PicturePropertyId));
  if (pic.isNull())
    return;
  
  QSize finalSize = pic.boundingRect().size();
  finalSize.scale(rect.size().toSize(), Qt::KeepAspectRatio);
  double scaleFactor = finalSize.width()/(double)pic.boundingRect().size().width();
  painter->save();
  painter->scale(scaleFactor, scaleFactor);
  painter->setClipRect(rect);
  painter->drawPicture(rect.topLeft(), pic);
  painter->restore();
}

QTextCharFormat QCPDocumentObject::generatePlotFormat(QCustomPlot *plot, int width, int height)
{
  QPicture picture;
  QCPPainter qcpPainter;
  qcpPainter.begin(&picture);
  plot->toPainter(&qcpPainter, width, height);
  qcpPainter.end();
  
  QTextCharFormat result;
  result.setObjectType(QCPDocumentObject::PlotTextFormat);
  result.setProperty(QCPDocumentObject::PicturePropertyId, QVariant::fromValue(picture));
  return result;
}
