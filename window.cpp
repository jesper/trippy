#include "window.h"
#include <MarbleWidget.h>

using namespace Marble;

Window::Window(QWidget *parent)
  :QWidget(parent)
{
  ui.setupUi(this);

  MarbleWidget *marble = new MarbleWidget(this);
  marble->setMapThemeId(QLatin1String("earth/srtm/srtm.dgml"));
  marble->setShowCompass(false);
  marble->setShowScaleBar(false);
  marble->setShowOverviewMap(false);
//  marble->set
  ui.verticalLayout->addWidget(marble);
  qDebug("Morn morn from window");
}
