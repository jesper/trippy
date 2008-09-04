#include "window.h"
#include "photo.h"

#include <MarbleWidget.h>

#include <QFileDialog>

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

  QObject::connect(ui.pb_loadPhoto, SIGNAL(clicked()), this, SLOT(selectFile()));
  
  m_fileDialog = new QFileDialog(this, "Select geo-tagged images");
  m_fileDialog->setNameFilter("Image Files (*.jpg)");
  QObject::connect(m_fileDialog, SIGNAL(filesSelected(const QStringList &)), this, SLOT(filesSelected(const QStringList &)));
}

void Window::selectFile()
{
  m_fileDialog->show();
}

void Window::filesSelected(const QStringList &selected)
{
  qDebug() << "Selected:" << selected;
  Photo photo(selected[0]);
  if (!photo.isGeoTagged())
  {
    QMessageBox::critical(this, "Cannot find any geotagging metadata",
                           "No geotag metadata was found in the selected image, please try again.\n");
    this->selectFile();
  }
  else
  {
    ui.l_photo->setPixmap(photo.getThumbnail());
  }
}
