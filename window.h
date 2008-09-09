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

class Window : public QDialog
{
  Q_OBJECT
  public:
    Window(QWidget *parent=0);
    Ui::window ui;
    void centerMapOn(Photo *photo);
    void addPhoto(Photo photo);
    void repaintMarbleWidget();

  private:
    QFileDialog *m_fileDialog;
    TrippyMarbleWidget *m_marble;
    QStandardItemModel m_photos;
    
 
  private slots:
    void selectFile();
    void filesSelected(const QStringList &files);
    void photoClicked(const QModelIndex &index);

  signals:  
    void selectedFiles(const QStringList &files);
};

#endif
