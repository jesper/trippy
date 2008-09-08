#ifndef WINDOW_H
#define WINDOW_H

#include <QtGui>

#include <MarbleWidget.h>

#include "ui_window.h"
#include "trippymarblewidget.h"
#include "photo.h"
#include "loadscreen.h"
#include <QStandardItemModel>

using namespace Marble;

class Window : public QWidget
{
  Q_OBJECT
  public:
    Window(QWidget *parent=0);
    QList<Photo *> getPhotos();

  private:
    Ui::window m_window;
    LoadScreen *m_loadScreen;
    QFileDialog *m_fileDialog;
    TrippyMarbleWidget *m_marble;
    QStandardItemModel m_photos;
    
    void centerMapOn(Photo *photo);
 
  private slots:
    void selectFile();
    void filesSelected(const QStringList &files);
    void photoClicked(const QModelIndex &index);

};

#endif
