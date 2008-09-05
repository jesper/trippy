#include "trippymarblewidget.h"

TrippyMarbleWidget::TrippyMarbleWidget(QWidget *parent)
  : MarbleWidget(parent)
{
}

void TrippyMarbleWidget::paintEvent(QPaintEvent *event)
{
  qDebug("Custom painting goes here plz");
  MarbleWidget::paintEvent(event);
}
