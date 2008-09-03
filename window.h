#ifndef WINDOW_H
#define WINDOW_H

#include <QtGui>

#include "ui_window.h"

class Window : public QWidget
{
  public:
    Window(QWidget *parent);

  private:
    Ui::window ui;
};

#endif
