#include "photo.h"

#include <exiv2/image.hpp>
#include <exiv2/exif.hpp>
 
Photo::Photo(const QString &path)
  : QPixmap(path)
{
  Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(path.toStdString());
  image->readMetadata();
  Exiv2::ExifData &exifData = image->exifData();
 
  if (exifData.empty()) {
    qDebug() << "Whoops! Couldnt find any metadata in" << path;  
    return;
  }
  
  m_gpsLat = QString::fromStdString(exifData["Exif.GPSInfo.GPSLatitude"].value().toString());
  m_gpsLong = QString::fromStdString(exifData["Exif.GPSInfo.GPSLongitude"].value().toString());

  m_gpsLatRef = QString::fromStdString(exifData["Exif.GPSInfo.GPSLatitudeRef"].value().toString());
  m_gpsLongRef = QString::fromStdString(exifData["Exif.GPSInfo.GPSLongitudeRef"].value().toString());

  m_timestamp = QDateTime::fromString(
                QString::fromStdString(exifData["Exif.Photo.DateTimeOriginal"].value().toString()),
                "yyyy:MM:dd HH:mm:ss");

  m_thumbnail = this->scaled(QSize(128, 128), Qt::KeepAspectRatio);
}

QString Photo::getGpsLong()
{
  return m_gpsLong;
}

QString Photo::getGpsLat()
{
  return m_gpsLat;
}

QPixmap Photo::getThumbnail()
{
  return m_thumbnail;
}

bool Photo::isGeoTagged()
{
  return (!m_gpsLat.isEmpty()
          || !m_gpsLatRef.isEmpty()
          || !m_gpsLong.isEmpty()
          || !m_gpsLongRef.isEmpty()
          );
}

qreal Photo::convertToCoordinate(QString coord, QString ref)
{
 /*
 *Format comes in as "59/1 56/1 1288/100" and "E"
 *  Value = first + second/60 + third/3600
 *  Value *= -1 if ref is W || S
 */
  return 0;
}

