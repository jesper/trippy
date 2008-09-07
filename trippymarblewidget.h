#ifndef TRIPPYMARBLEWIDGET_H
#define TRIPPYMARBLEWIDGET_H

#include <MarbleWidget.h>

using namespace Marble;

class TrippyMarbleWidget : public MarbleWidget
{
  public:
    TrippyMarbleWidget(QWidget *parent=0);

  protected:
    void customPaint(GeoPainter *painter);
};

#endif
