#include "window.h"

Window::Window(QWidget *parent)
    :QDialog(parent)
{
  ui.setupUi(this);
  ui.lw_photos->setModel(&m_photos);
  
  m_marble = new TrippyMarbleWidget(this);
  m_marble->setMapThemeId(QLatin1String("earth/srtm/srtm.dgml"));
  m_marble->setShowCompass(false);
  m_marble->setShowScaleBar(false);
  m_marble->setShowOverviewMap(false);
  m_marble->setProjection(Mercator);

  m_marble->setPhotoModel(m_photos);
  ui.verticalLayout->addWidget(m_marble);

  QObject::connect(ui.pb_loadPhoto, SIGNAL(clicked()), this, SLOT(selectFile()));
  
  m_fileDialog = new QFileDialog(this, "Select geo-tagged images");
  m_fileDialog->setNameFilter("Image Files (*.jpg)");
  m_fileDialog->setFileMode(QFileDialog::ExistingFiles);  

  QObject::connect(m_fileDialog, SIGNAL(filesSelected(const QStringList &)), this, SLOT(filesSelected(const QStringList &)));

  QObject::connect(ui.lw_photos, SIGNAL(clicked(const QModelIndex &)), this, SLOT(photoClicked(const QModelIndex &)));
}

void Window::selectFile()
{
  m_fileDialog->show();
}

void Window::filesSelected(const QStringList &selected)
{
  m_fileDialog->hide();
  emit selectedFiles(selected);
}

void Window::photoClicked(const QModelIndex &index)
{
  QStandardItem *item = m_photos.itemFromIndex(index);
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

void Window::addPhoto(Photo photo)
{
  QStandardItem *newItem = new QStandardItem(QIcon(photo.getThumbnail()), photo.getTimestamp().toString());
  newItem->setEditable(false);
  newItem->setData(QVariant::fromValue(photo), 16);
  m_photos.appendRow(newItem);
}

