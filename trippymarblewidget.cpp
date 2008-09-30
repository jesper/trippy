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

#include <GeoDataPoint.h>

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

  GeoDataPoint selected;
  GeoDataPoint selected_source;

  bool selectionExists = false;
  bool selectionSourceExists = false;
  bool isSelected = false;

  for (int i=0; i<m_photoModel->rowCount(); ++i)
  {
    QVariant v = m_photoModel->item(i)->data(PhotoRole);
    Photo current = v.value<Photo>();
    isSelected = m_photoModel->item(i)->data(SelectedRole).toBool();

    if (isSelected)
    {
      selectionExists = true;
      selected = GeoDataPoint(current.getGpsLong(), current.getGpsLat(), 0 , GeoDataCoordinates::Degree);
    }
    
    painter->drawEllipse(GeoDataPoint(current.getGpsLong(), current.getGpsLat(), 0 , GeoDataCoordinates::Degree), 6, 6);

    if (i != 0)
    {
      QVariant v = m_photoModel->item(i - 1)->data(PhotoRole);
      Photo last = v.value<Photo>();

      if (isSelected)
      {
        selectionSourceExists = true;
        selected_source = GeoDataPoint(last.getGpsLong(), last.getGpsLat(), 0 , GeoDataCoordinates::Degree);
      }

      painter->drawLine(GeoDataPoint(current.getGpsLong(), current.getGpsLat(), 0 , GeoDataCoordinates::Degree), GeoDataPoint(last.getGpsLong(), last.getGpsLat(), 0 , GeoDataCoordinates::Degree));
    }
  }

  //re-drawing the currently selected item, this time in red to make it stand out.
  if (selectionExists)
  {
    pen.setColor(Qt::red);
    painter->setPen(pen);

    painter->drawEllipse(selected, 6, 6);
    if (selectionSourceExists)
    {
      painter->drawLine(selected, selected_source);
    }
  }
}
