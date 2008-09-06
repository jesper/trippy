#ifndef PHOTO_H
#define PHOTO_H

#include <QMetaType>

#include <QPixmap>
#include <QDateTime>
#include <QDebug>


class Photo : public QPixmap
{
  public:
    Photo(const QString &path = 0);
    bool isGeoTagged();
    QPixmap getThumbnail();
    qreal getGpsLat();
    qreal getGpsLong();
    QDateTime getTimestamp();

  private:
    qreal convertToCoordinate(QString coord, QString ref);

    QPixmap m_thumbnail;
    QDateTime m_timestamp;
    qreal m_gpsLat;
    qreal m_gpsLong;
};

Q_DECLARE_METATYPE(Photo)

#endif

