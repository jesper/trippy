#include "window.h"

Window::Window(QWidget *parent)
  :QWidget(parent)
{
  m_window.setupUi(this);

  m_marble = new TrippyMarbleWidget(this);
  m_marble->setMapThemeId(QLatin1String("earth/srtm/srtm.dgml"));
  m_marble->setShowCompass(false);
  m_marble->setShowScaleBar(false);
  m_marble->setShowOverviewMap(false);
  m_marble->setProjection(Mercator);
  m_window.verticalLayout->addWidget(m_marble);

  QObject::connect(m_window.pb_loadPhoto, SIGNAL(clicked()), this, SLOT(selectFile()));
  
  m_fileDialog = new QFileDialog(this, "Select geo-tagged images");
  m_fileDialog->setNameFilter("Image Files (*.jpg)");
  m_fileDialog->setFileMode(QFileDialog::ExistingFiles);  

  QObject::connect(m_fileDialog, SIGNAL(filesSelected(const QStringList &)), this, SLOT(filesSelected(const QStringList &)));

  QObject::connect(m_window.lw_photos, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(photoClicked(QListWidgetItem *)));
}

void Window::selectFile()
{
  m_fileDialog->show();
}

void Window::filesSelected(const QStringList &selected)
{
  qDebug() << "Selected:" << selected;
  m_loadScreen.show();

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
    m_window.lw_photos->addItem(newItem);
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
  m_window.l_photo->setPixmap(photo->getThumbnail()); 
  m_marble->centerOn(photo->getGpsLong(), photo->getGpsLat());
  m_marble->zoomView(2000);
}
