#ifndef TRIPPY_H
#define TRIPPY_H

#include <QtGui>

#include "window.h"
#include "photo.h"

class Trippy : public QObject
{
  Q_OBJECT
  public:
    Trippy();

  private:
    Window *m_window;
    LoadScreen *m_loadScreen;
    QFileDialog *m_fileDialog;
    QStandardItemModel m_photos;
    
  private slots:
    void filesSelected(const QStringList &files);
};

#endif
