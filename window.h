#ifndef WINDOW_H
#define WINDOW_H

#include <QtGui>

#include <MarbleWidget.h>

#include "ui_window.h"
#include "trippymarblewidget.h"
#include "photo.h"
#include "loadscreen.h"

using namespace Marble;

class Window : public QWidget
{
  Q_OBJECT
  public:
    Window(QWidget *parent);

  private:
    Ui::window m_window;
    LoadScreen m_loadScreen;
    QFileDialog *m_fileDialog;
    TrippyMarbleWidget *m_marble;
    
    void centerMapOn(Photo *photo);
 
  private slots:
    void selectFile();
    void filesSelected(const QStringList &files);
    void photoClicked(QListWidgetItem *item);

};

#endif
