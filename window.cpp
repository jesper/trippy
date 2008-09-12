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
    :QDialog(parent)
{
  ui.setupUi(this);

  ui.lv_photos->setIconSize(QSize(64, 64));
  m_marble = new TrippyMarbleWidget(this);
  m_marble->setMapThemeId(QLatin1String("earth/srtm/srtm.dgml"));
  m_marble->setShowCompass(false);
  m_marble->setShowScaleBar(false);
  m_marble->setShowOverviewMap(false);
  m_marble->setProjection(Mercator);

  ui.verticalLayout->addWidget(m_marble);
  
  m_fileDialog = new QFileDialog(this, "Select geo-tagged images");
  m_fileDialog->setNameFilter("Image Files (*.jpg)");
  m_fileDialog->setFileMode(QFileDialog::ExistingFiles);  

  m_previousItem = new QStandardItem;
  QObject::connect(ui.pb_loadPhoto, SIGNAL(clicked()), this, SLOT(selectFile()));

  QObject::connect(m_fileDialog, SIGNAL(filesSelected(const QStringList &)), this, SLOT(filesSelected(const QStringList &)));

  QObject::connect(ui.lv_photos, SIGNAL(clicked(const QModelIndex &)), this, SLOT(photoClicked(const QModelIndex &)));
  
  QObject::connect(ui.pb_back, SIGNAL(clicked()), this, SLOT(backPressed()));
  QObject::connect(ui.pb_next, SIGNAL(clicked()), this, SLOT(nextPressed()));
}

void Window::repaintMarbleWidget()
{
  m_marble->repaint();
}

void Window::selectFile()
{
  m_fileDialog->show();
}

void Window::backPressed()
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

void Window::nextPressed()
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


