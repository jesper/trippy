#ifndef PHOTO_H
#define PHOTO_H

#include <QPixmap>
#include <QDateTime>
#include <QDebug>

class Photo : public QPixmap
{
  public:
    Photo(QString *path);

  private:
    QDateTime m_timestamp;
    QString m_gpsLatRef;
    QString m_gpsLat;
    QString m_gpsLongRef;
    QString m_gpsLong;
};

#endif

