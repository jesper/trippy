#include "trippymarblewidget.h"
#include <GeoPainter.h>

TrippyMarbleWidget::TrippyMarbleWidget(QWidget *parent)
  : MarbleWidget(parent)
{
}

void TrippyMarbleWidget::customPaint(GeoPainter *painter)
{
//  qDebug() << "Freaking drawing..." << this->parent()->getPhotos().size();
  QPen pen(Qt::blue);
  pen.setWidth(2);
  painter->setPen(pen);

  painter->drawLine(GeoDataCoordinates(qreal(10.7579), qreal(59.9369), 0 , GeoDataCoordinates::Degree),
                    GeoDataCoordinates(qreal(10), qreal(59), 0 , GeoDataCoordinates::Degree) );

  painter->setBrush(Qt::green);
  painter->drawEllipse(GeoDataCoordinates(qreal(10.7579), qreal(59.9369), 0 , GeoDataCoordinates::Degree)
                       , 20, 20);
  
  painter->setBrush(Qt::darkMagenta);
  
  painter->drawEllipse(GeoDataCoordinates(qreal(10), qreal(59), 0 , GeoDataCoordinates::Degree)
                       , 20, 20);
}
