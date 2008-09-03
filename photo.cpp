#include "photo.h"

Photo::Photo(QString &path, QChar gpsLatRef, QString gpsLat, QChar gpsLongRef, QString gpsLong)
  : QPixmap(path), m_gpsLatRef(gpsLatRef), m_gpsLat(gpsLat), m_gpsLongRef(gpsLongRef), m_gpsLong(gpsLong)
{
  qDebug() << "Created a photo out of:" << path;
}
