#include "window.h"

Window::Window(QWidget *parent)
  :QWidget(parent)
{
  ui.setupUi(this);

  m_marble = new TrippyMarbleWidget(this);
  m_marble->setMapThemeId(QLatin1String("earth/srtm/srtm.dgml"));
  m_marble->setShowCompass(false);
  m_marble->setShowScaleBar(false);
  m_marble->setShowOverviewMap(false);
  m_marble->setProjection(Mercator);
  ui.verticalLayout->addWidget(m_marble);

  QObject::connect(ui.pb_loadPhoto, SIGNAL(clicked()), this, SLOT(selectFile()));
  
  m_fileDialog = new QFileDialog(this, "Select geo-tagged images");
  m_fileDialog->setNameFilter("Image Files (*.jpg)");
  
  QObject::connect(m_fileDialog, SIGNAL(filesSelected(const QStringList &)), this, SLOT(filesSelected(const QStringList &)));

  QObject::connect(ui.lw_photos, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(photoClicked(QListWidgetItem *)));
}

void Window::selectFile()
{
  m_fileDialog->show();
}

void Window::filesSelected(const QStringList &selected)
{
  Photo photo(selected[0]);
  if (!photo.isGeoTagged())
  {
    QMessageBox::critical(this, "Cannot find any geotagging metadata",
                           "No geotag metadata was found in the selected image, please try again.\n");
    this->selectFile();
  }
  else
  {
    QListWidgetItem *newItem = new QListWidgetItem(QIcon(photo.getThumbnail()), photo.getTimestamp().toString());
    newItem->setData(16, QVariant::fromValue(photo));
    ui.lw_photos->addItem(newItem);
    centerMapOn(&photo);
  }
}

void Window::photoClicked(QListWidgetItem *item)
{
  QVariant v = item->data(16);
  Photo photo = v.value<Photo>();
  centerMapOn(&photo);
}

void Window::centerMapOn(Photo *photo)
{
  ui.l_photo->setPixmap(photo->getThumbnail()); 
  m_marble->centerOn(photo->getGpsLong(), photo->getGpsLat());
  m_marble->zoomView(2000);
}
