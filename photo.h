#ifndef PHOTO_H
#define PHOTO_H

#include <QPixmap>
#include <QDateTime>
#include <QDebug>

class Photo : public QPixmap
{
  public:
    Photo(const QString &path);
    bool isGeoTagged();
    QPixmap getThumbnail();

  private:
    QPixmap m_thumbnail;
    QDateTime m_timestamp;
    QString m_gpsLatRef;
    QString m_gpsLat;
    QString m_gpsLongRef;
    QString m_gpsLong;
};

#endif

