#ifndef PHOTO_H
#define PHOTO_H

#include <QPixmap>
#include <QDateTime>
#include <QtGui>
#include <QString>

class Photo : public QPixmap
{
  public:
    Photo(QString &path, QChar gpsLatRef, QString gpsLat, QChar gpsLongRef, QString gpsLong);

  private:
    QDateTime m_timestamp;
    QChar m_gpsLatRef;
    QString m_gpsLat;
    QChar m_gpsLongRef;
    QString m_gpsLong;
};

#endif

