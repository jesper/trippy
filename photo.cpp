#include "photo.h"

#include <exiv2/image.hpp>
#include <exiv2/exif.hpp>
 
Photo::Photo(QString *path)
{
  qDebug() << "Created a photo out of:" << path;

  Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(path->toStdString());
  image->readMetadata();

  Exiv2::ExifData &exifData = image->exifData();
  
  if (exifData.empty()) {
    qDebug() << "Couldnt find anything in" << path << "...whoops.";  
  }
  
  m_gpsLat = QString::fromStdString(exifData["Exif.GPSInfo.GPSLatitude"].value().toString());
  m_gpsLong = QString::fromStdString(exifData["Exif.GPSInfo.GPSLongitude"].value().toString());

  m_gpsLatRef = QString::fromStdString(exifData["Exif.GPSInfo.GPSLatitudeRef"].value().toString());
  m_gpsLongRef = QString::fromStdString(exifData["Exif.GPSInfo.GPSLongitudeRef"].value().toString());

  m_timestamp = QDateTime::fromString(
                QString::fromStdString(exifData["Exif.Photo.DateTimeOriginal"].value().toString()),
                "yyyy:MM:dd HH:mm:ss");
}
