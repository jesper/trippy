#include "window.h"
#include <MarbleWidget.h>

#include <exiv2/image.hpp>
#include <exiv2/exif.hpp>
 
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

  Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open("tagged.jpg");
  image->readMetadata();

  Exiv2::ExifData &exifData = image->exifData();
  
  if (exifData.empty()) {
    qDebug() << "Couldnt find anything in tagged.jpg...whoops.";  
  }

  Exiv2::ExifData::const_iterator end = exifData.end();

  for (Exiv2::ExifData::const_iterator i = exifData.begin(); i != end; ++i)
  {
    QString key = QString::fromStdString(i->key());
    QString value = QString::fromStdString(i->value().toString());
    qDebug() << "Key/Value is:" << key << "::" << value << "!";
  }
}

