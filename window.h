#ifndef WINDOW_H
#define WINDOW_H

#include <QtGui>

#include <MarbleWidget.h>

#include "ui_window.h"
#include "trippymarblewidget.h"
#include "photo.h"

using namespace Marble;

class Window : public QWidget
{
  Q_OBJECT
  public:
    Window(QWidget *parent);

  private:
    Ui::window ui;
    QFileDialog *m_fileDialog;
    TrippyMarbleWidget *m_marble;
    
    void centerMapOn(Photo *photo);
 
  private slots:
    void selectFile();
    void filesSelected(const QStringList &files);
    void photoClicked(QListWidgetItem *item);

};

#endif
