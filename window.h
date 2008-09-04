#ifndef WINDOW_H
#define WINDOW_H

#include <QtGui>

#include "ui_window.h"

class Window : public QWidget
{
  Q_OBJECT
  public:
    Window(QWidget *parent);

  private:
    Ui::window ui;
    QFileDialog *m_fileDialog;

  private slots:
    void selectFile();
    void filesSelected(const QStringList &files);
};

#endif
