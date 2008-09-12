/*
    Author: Jesper Thomschutz 2008, jesper@jespersaur.com

    This file is part of Trippy.

    Trippy is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Trippy is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Trippy.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "window.h"

Window::Window(QWidget *parent)
    :QMainWindow(parent)
{
  ui.setupUi(this);

  ui.lv_photos->setIconSize(QSize(60, 60));
  m_marble = new TrippyMarbleWidget(this);

  //Default view for now is mercator and Atlas, since they're my favorite at the moment.
  ui.actionAtlas->trigger();
  atlasClicked();
  ui.actionMercator->trigger();
  mercatorClicked();

  ui.verticalLayout->addWidget(m_marble);
  
  m_fileDialog = new QFileDialog(this, "Select geo-tagged images");
  m_fileDialog->setNameFilter("Image Files (*.jpg)");
  m_fileDialog->setFileMode(QFileDialog::ExistingFiles);  

  m_previousItem = new QStandardItem;

  //Add photos button and menu item
  QObject::connect(ui.pb_addPhotos, SIGNAL(clicked()), this, SLOT(selectFile()));
  QObject::connect(ui.action_Add_Photos, SIGNAL(triggered()), this, SLOT(selectFile()));

  //Menubar items:
  QObject::connect(ui.actionAtlas, SIGNAL(triggered()), this, SLOT(atlasClicked()));
  QObject::connect(ui.actionOpen_Street_Map, SIGNAL(triggered()), this, SLOT(openStreetMapClicked()));
  QObject::connect(ui.actionFlat, SIGNAL(triggered()), this, SLOT(flatClicked()));
  QObject::connect(ui.actionMercator, SIGNAL(triggered()), this, SLOT(mercatorClicked()));
  QObject::connect(ui.actionGlobe, SIGNAL(triggered()), this, SLOT(globeClicked()));

  //Files selected from the file dialog
  QObject::connect(m_fileDialog, SIGNAL(filesSelected(const QStringList &)), this, SLOT(filesSelected(const QStringList &)));

  //An item (photo) was clicked in the list view.
  QObject::connect(ui.lv_photos, SIGNAL(clicked(const QModelIndex &)), this, SLOT(photoClicked(const QModelIndex &)));
  
  //Back and Next buttons
  QObject::connect(ui.pb_back, SIGNAL(clicked()), this, SLOT(backClicked()));
  QObject::connect(ui.pb_next, SIGNAL(clicked()), this, SLOT(nextClicked()));
}

void Window::hideMapClutter()
{
  m_marble->setShowCompass(false);
  m_marble->setShowScaleBar(false);
  m_marble->setShowOverviewMap(false);
}

void Window::repaintMarbleWidget()
{
  m_marble->repaint();
}

void Window::selectFile()
{
  m_fileDialog->show();
}

void Window::backClicked()
{
  int rowCount = ((QStandardItemModel *)ui.lv_photos->model())->rowCount();

  if (0 == rowCount)
  {
    return;
  }

  int currentRow = ui.lv_photos->currentIndex().row();
  QStandardItem *nextItem = ((QStandardItemModel *)ui.lv_photos->model())->item(currentRow-1);
  
  if (!nextItem)
  {
    nextItem = ((QStandardItemModel *)ui.lv_photos->model())->item(rowCount-1);
  }
  
  ui.lv_photos->setCurrentIndex(nextItem->index());
  photoClicked(nextItem->index());
}

void Window::nextClicked()
{
  int rowCount = ((QStandardItemModel *)ui.lv_photos->model())->rowCount();

  if (0 == rowCount)
  {
    return;
  }

  int currentRow = ui.lv_photos->currentIndex().row();
  
  QStandardItem *nextItem = ((QStandardItemModel *)ui.lv_photos->model())->item(currentRow+1);
  
  if (!nextItem)
  {
    nextItem = ((QStandardItemModel *)ui.lv_photos->model())->item(0);
  }
  
  ui.lv_photos->setCurrentIndex(nextItem->index());
  photoClicked(nextItem->index());
}

void Window::filesSelected(const QStringList &selected)
{
  m_fileDialog->hide();
  emit selectedFiles(selected);
}

void Window::photoClicked(const QModelIndex &index)
{
  QStandardItemModel *model = (QStandardItemModel *)ui.lv_photos->model();
  QStandardItem *item = model->itemFromIndex(index);
  item->setData(true, Qt::UserRole + 2);

  m_previousItem->setData(false, Qt::UserRole + 2);
  m_previousItem = item;
 
  QVariant v = item->data(Qt::UserRole);
  Photo photo = v.value<Photo>();
  centerMapOn(&photo);
}

void Window::centerMapOn(Photo *photo)
{
  ui.l_photo->setPixmap(photo->getThumbnail()); 
  m_marble->centerOn(photo->getGpsLong(), photo->getGpsLat());
  m_marble->zoomView(2500);
}


void Window::atlasClicked()
{
  m_marble->setMapThemeId(QLatin1String("earth/srtm/srtm.dgml"));
  ui.actionOpen_Street_Map->setChecked(false);
  hideMapClutter();
}

void Window::openStreetMapClicked()
{
  m_marble->setMapThemeId(QLatin1String("earth/openstreetmap/openstreetmap.dgml"));
  ui.actionAtlas->setChecked(false);
  hideMapClutter();
}

void Window::mercatorClicked()
{
  m_marble->setProjection(Mercator);
  ui.actionGlobe->setChecked(false);
  ui.actionFlat->setChecked(false);
}

void Window::flatClicked()
{
  m_marble->setProjection(Equirectangular);
  ui.actionGlobe->setChecked(false);
  ui.actionMercator->setChecked(false);
}

void Window::globeClicked()
{
  m_marble->setProjection(Spherical);
  ui.actionMercator->setChecked(false);
  ui.actionFlat->setChecked(false);
}
