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

#include "trippy.h"

Trippy::Trippy()
{
  m_window = new Window();
  m_window->show();
  
  m_window->ui.lv_photos->setModel(&m_photos);
  m_window->m_marble->setPhotoModel(m_photos);

  QObject::connect(m_window, SIGNAL(selectedFiles(const QStringList &)), this, SLOT(filesSelected(const QStringList &)));

  m_loadScreen = new LoadScreen(m_window);
}

void Trippy::filesSelected(const QStringList &selected)
{
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
      QMessageBox::critical(m_window, "Cannot find any geotagging metadata",
                            QString("No geotag metadata was found in the specified photo: %1.\n").arg(selected[i]));
    }
    else
    {
      addPhoto(photo);
    }
    m_loadScreen->ui.progressBar->setValue(i + 1);
  }

  sortPhotos();
  m_window->repaintMarbleWidget();
}

void Trippy::addPhoto(Photo photo)
{
  QStandardItem *newItem = new QStandardItem(QIcon(photo.getThumbnail()), photo.getTimestamp().toString());
  newItem->setEditable(false);
  newItem->setData(QVariant::fromValue(photo), Qt::UserRole);
  newItem->setData(photo.getTimestamp(), Qt::UserRole + 1);
  newItem->setData(false, Qt::UserRole + 2);
  newItem->setData(photo.getFilename(), Qt::ToolTipRole);
  m_photos.appendRow(newItem);
}

void Trippy::sortPhotos()
{
  qDebug() << "Sort here please";  
}
