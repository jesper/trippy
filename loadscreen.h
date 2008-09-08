#ifndef LOADSCREEN_H
#define LOADSCREEN_H

#include <QtGui>

#include "ui_loadscreen.h"

class LoadScreen : public QDialog
{
  Q_OBJECT
  public:
    LoadScreen(QWidget *parent=0);
    Ui::loadScreen ui;
};

#endif
