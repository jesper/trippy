#include "trippymarblewidget.h"
#include "photo.h"

TrippyMarbleWidget::TrippyMarbleWidget(QWidget *parent)
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
  QList<Photo *> photos;
  for (int i=0; i<m_photoModel->rowCount(); ++i)
  {
    QVariant v = m_photoModel->item(i)->data(16);
    Photo photo = v.value<Photo>();
    photos.append(&photo);
  }
  qDebug() << "Photo size:" << photos.size();

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
