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
  m_loadScreen->ui.progressBar->setValue(0);
  m_loadScreen->ui.progressBar->setMaximum(selected.size());
  m_loadScreen->ui.l_currentPhoto->setText("");
  m_loadScreen->showFailedPhotos(false);

  m_loadScreen->show();

  for (int i=0; i<selected.size(); ++i)
  {
    m_loadScreen->ui.l_currentPhoto->setText(selected[i]);
    Photo photo(selected[i]);
    if (!photo.isGeoTagged())
    {
      m_loadScreen->showFailedPhotos(true); 
      m_loadScreen->ui.lw_failPhotos->addItem(selected[i]);
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

//Takes a Photo object and creates a QStandardItem, then places it into the model.
void Trippy::addPhoto(Photo photo)
{
  QStandardItem *newItem = new QStandardItem(QIcon(photo.getThumbnail()), photo.getTimestamp().toString());
  newItem->setEditable(false);
  newItem->setData(QVariant::fromValue(photo), PhotoRole);
  newItem->setData(photo.getTimestamp(), TimestampRole);
  newItem->setData(false, SelectedRole);
  newItem->setData(photo.getFilename(), Qt::ToolTipRole);
  m_photos.appendRow(newItem);
}

void Trippy::sortPhotos()
{
  QList<QStandardItem *> photos;

  //Move the items from the model to a list...
  while (m_photos.rowCount() > 0)
  {
    photos.append(m_photos.takeRow(0).first());
  }

  /* A very simple version of insertion sort from wikipedia...

  insertionSort(array A)
    for i = 1 to length[A]-1 do
    begin
        value = A[i]
        j = i-1
        while j ≥ 0 and A[j] > value do
        begin
            A[j + 1] = A[j]
            j = j-1
        end
        A[j+1] = value
    end
  */

  //Using insertion sort to sort the items in the List by timestamp.
  for (int n=0; n < photos.size(); ++n)
  {
    QStandardItem *temp = photos.at(n);
    int j = n - 1;
    while ((j >= 0) && 
          (photos.at(j)->data(TimestampRole).toDateTime() > temp->data(TimestampRole).toDateTime()))
    {
      photos[j + 1] = photos.at(j);
      j = j-1;
    }
    photos[j+1] = temp;
  }

  //Put the sorted items back into the model.
  for (int k=0; k < photos.size(); ++k)
  {
    m_photos.insertRow(k, photos.at(k));
  }
}
