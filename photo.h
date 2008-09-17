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

#ifndef PHOTO_H
#define PHOTO_H

#include <QMetaType>

#include <QPixmap>
#include <QDateTime>
#include <QDebug>

#include <exiv2/image.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/tags.hpp>



class Photo
{
  public:
    Photo(const QString &path = 0);
    bool isGeoTagged();
    QPixmap getImage();
    QPixmap getThumbnail();
    qreal getGpsLat();
    qreal getGpsLong();
    QDateTime getTimestamp();
    QString getFilename();

  private:
    bool exivHasKey(QString key, Exiv2::ExifData &data);
    qreal convertToCoordinate(QString coord, QString ref);

    QDateTime m_timestamp;
    qreal m_gpsLat;
    qreal m_gpsLong;
    QString m_filename;
};

Q_DECLARE_METATYPE(Photo)

#endif

