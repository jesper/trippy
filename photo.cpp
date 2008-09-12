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

#include "photo.h"

Photo::Photo(const QString &path)
  : QPixmap(path), m_gpsLat(-1), m_gpsLong(-1), m_filename(path) 
{
  Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(path.toStdString());
  image->readMetadata();
  Exiv2::ExifData &exifData = image->exifData();
 
  if (exifData.empty()) {
    qDebug() << "Whoops! Couldnt find any metadata in" << path;  
    return;
  }

/*
  key = Exiv2::ExifKey("Exif.Image.PrimaryChromaticities");
  Exiv2::ExifData::iterator pos = exifData.findKey(key);
  if (pos == exifData.end()) throw Exiv2::Error(1, "Key not found");
*/
  //
  if (!exivHasKey("Exif.GPSInfo.GPSLatitudeRef", exifData))
  {
    return;
  }
  
  if (!exivHasKey("Exif.GPSInfo.GPSLongitudeRef", exifData))
  {
    return;
  }
  
  if (!exivHasKey("Exif.GPSInfo.GPSLatitude", exifData))
  {
    return;
  }
  
  if (!exivHasKey("Exif.GPSInfo.GPSLongitude", exifData))
  {
    return;
  }
  
  if (!exivHasKey("Exif.Photo.DateTimeOriginal", exifData))
  {
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

bool Photo::exivHasKey(QString key, Exiv2::ExifData &data)
{
  Exiv2::ExifData::iterator pos = data.findKey(Exiv2::ExifKey(key.toStdString()));
  return (pos != data.end());
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

QString Photo::getFilename()
{
  return m_filename;
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

