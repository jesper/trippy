#include "photo.h"

#include <exiv2/image.hpp>
#include <exiv2/exif.hpp>

Photo::Photo(const QString &path)
  : QPixmap(path), m_gpsLat(-1), m_gpsLong(-1)
{
  Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(path.toStdString());
  image->readMetadata();
  Exiv2::ExifData &exifData = image->exifData();
 
  if (exifData.empty()) {
    qDebug() << "Whoops! Couldnt find any metadata in" << path;  
    return;
  }
  
  QString gpsLatRef = QString::fromStdString(exifData["Exif.GPSInfo.GPSLatitudeRef"].value().toString());
  QString gpsLongRef = QString::fromStdString(exifData["Exif.GPSInfo.GPSLongitudeRef"].value().toString());

  m_gpsLat = convertToCoordinate(
              QString::fromStdString(exifData["Exif.GPSInfo.GPSLatitude"].value().toString())
              , gpsLatRef
  );

  m_gpsLong = convertToCoordinate(
              QString::fromStdString(exifData["Exif.GPSInfo.GPSLongitude"].value().toString())
              , gpsLongRef
  );

  m_timestamp = QDateTime::fromString(
                QString::fromStdString(exifData["Exif.Photo.DateTimeOriginal"].value().toString()),
                "yyyy:MM:dd HH:mm:ss");

  m_thumbnail = this->scaled(QSize(280, 280), Qt::KeepAspectRatio);
}

qreal Photo::getGpsLong()
{
  return m_gpsLong;
}

qreal Photo::getGpsLat()
{
  return m_gpsLat;
}

QPixmap Photo::getThumbnail()
{
  return m_thumbnail;
}

QDateTime Photo::getTimestamp()
{
  return m_timestamp;
}

bool Photo::isGeoTagged()
{
  return ((m_gpsLat != -1) && (m_gpsLong != -1));
}

qreal Photo::convertToCoordinate(QString coord, QString ref)
{
  /*
  *Format comes in as "59/1 56/1 1288/100" and "E"
  *  Value = first + second/60 + third/3600
  *  Value *= -1 if ref is W || S
  */
 
  qreal total = 0;
  QStringList points = coord.split(" ");

  qreal temp = 0;

  for (int i=0; i < points.size(); ++i)
  {
    QStringList value = points[i].split("/");
    temp = value[0].toFloat() / value[1].toFloat();
    switch (i) 
    {
      case 0:
        total += temp;
        break;
      case 1:
        total += temp/60;
        break;
      case 2:
        total += temp/3600;
        break;
    }
  }

  if (ref == "W" || ref == "S")
    total *= -1;

  return total;
}

