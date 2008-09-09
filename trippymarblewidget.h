#ifndef TRIPPYMARBLEWIDGET_H
#define TRIPPYMARBLEWIDGET_H

#include <MarbleWidget.h>
#include <GeoPainter.h>

#include <QStandardItemModel>

using namespace Marble;

class TrippyMarbleWidget : public MarbleWidget
{
  public:
    TrippyMarbleWidget(QWidget *parent=0);
    void setPhotoModel(QStandardItemModel &model);

  protected:
    void customPaint(GeoPainter *painter);

  private:
    QStandardItemModel *m_photoModel;
};

#endif
