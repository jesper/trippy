#include "window.h"
#include "photo.h"

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
  marble->setProjection(Mercator);
  ui.verticalLayout->addWidget(marble);

  Photo photo(new QString("tagged.jpg"));
}

