#include "window.h"

Window::Window(QWidget *parent)
  :QWidget(parent)
{
  m_window.setupUi(this);
  m_window.lw_photos->setModel(&m_photos);
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

  QObject::connect(m_window.lw_photos, SIGNAL(clicked(const QModelIndex &)), this, SLOT(photoClicked(const QModelIndex &)));

  m_loadScreen = new LoadScreen(this);
}

void Window::selectFile()
{
  m_fileDialog->show();
}

void Window::filesSelected(const QStringList &selected)
{
  m_fileDialog->hide();
  qDebug() << "Selected:" << selected;

  m_loadScreen->show();

  m_loadScreen->ui.progressBar->setValue(0);
  m_loadScreen->ui.progressBar->setMaximum(selected.size());
  m_loadScreen->ui.l_currentPhoto->setText("");


  for (int i=0; i<selected.size(); ++i)
  {
    m_loadScreen->ui.l_currentPhoto->setText(selected[i]);
    Photo photo(selected[i]);
    if (!photo.isGeoTagged())
    {
      QMessageBox::critical(this, "Cannot find any geotagging metadata",
                             QString("No geotag metadata was found in the specified photo: %1.\n").arg(selected[i]));
      this->selectFile();
    }
    else
    {
      QStandardItem *newItem = new QStandardItem(QIcon(photo.getThumbnail()), photo.getTimestamp().toString());
      newItem->setEditable(false);
      newItem->setData(QVariant::fromValue(photo), 16);
      m_photos.appendRow(newItem);
    }
    m_loadScreen->ui.progressBar->setValue(i + 1);
    m_loadScreen->update();
  }
//  centerMapOn(&photo);
//  m_loadScreen->hide();
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
  m_window.l_photo->setPixmap(photo->getThumbnail()); 
  m_marble->centerOn(photo->getGpsLong(), photo->getGpsLat());
  m_marble->zoomView(2000);
}

QList<Photo *> Window::getPhotos()
{
  QList<Photo *> photos;
  for (int i=0; i<m_photos.rowCount(); ++i)
  {
    QVariant v = m_photos.item(i)->data(16);
    Photo photo = v.value<Photo>();
    photos.append(&photo);
  }

  return photos;
}
