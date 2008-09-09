/*
    Author: Jesper Thomschutz 2008, jesper@jespersaur.com

    This file is part of Trippy.

    Trippy is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Trippy is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Trippy.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "trippymarblewidget.h"
#include "photo.h"

TrippyMarbleWidget::TrippyMarbleWidget(QWidget *parent)
  : MarbleWidget(parent)
{

  m_photoModel = new QStandardItemModel();
}

void TrippyMarbleWidget::setPhotoModel(QStandardItemModel &model)
{
  delete m_photoModel;
  m_photoModel = &model;
}

void TrippyMarbleWidget::customPaint(GeoPainter *painter)
{
  QPen pen(Qt::blue);
  pen.setWidth(2);
  painter->setPen(pen);

  for (int i=0; i<m_photoModel->rowCount(); ++i)
  {
    QVariant v = m_photoModel->item(i)->data(16);
    Photo current = v.value<Photo>();
    painter->drawEllipse(GeoDataCoordinates(current.getGpsLong(), current.getGpsLat(), 0 , GeoDataCoordinates::Degree),10,10);
    if (i != 0)
    {
      QVariant v = m_photoModel->item(i - 1)->data(16);
      Photo last = v.value<Photo>();
      painter->drawLine(GeoDataCoordinates(current.getGpsLong(), current.getGpsLat(), 0 , GeoDataCoordinates::Degree), GeoDataCoordinates(last.getGpsLong(), last.getGpsLat(), 0 , GeoDataCoordinates::Degree) );
    }
  }
  

/*  QPen pen(Qt::blue);
  painter->setPen(pen);

  painter->drawLine(GeoDataCoordinates(qreal(10.7579), qreal(59.9369), 0 , GeoDataCoordinates::Degree),
                    GeoDataCoordinates(qreal(10), qreal(59), 0 , GeoDataCoordinates::Degree) );

  painter->setBrush(Qt::green);
  painter->drawEllipse(GeoDataCoordinates(qreal(10.7579), qreal(59.9369), 0 , GeoDataCoordinates::Degree)
                       , 20, 20);
  
  painter->setBrush(Qt::darkMagenta);
  
  painter->drawEllipse(GeoDataCoordinates(qreal(10), qreal(59), 0 , GeoDataCoordinates::Degree)
                       , 20, 20);
*/
}
