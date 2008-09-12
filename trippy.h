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

#ifndef TRIPPY_H
#define TRIPPY_H

#include <QtGui>
#include <QStandardItem>

#include "window.h"
#include "photo.h"
#include "roles.h"

class Trippy : public QObject
{
  Q_OBJECT
  public:
    Trippy();

  private:
    Window *m_window;
    LoadScreen *m_loadScreen;
    QFileDialog *m_fileDialog;
    QStandardItemModel m_photos;

  private slots:
    void filesSelected(const QStringList &files);
    void addPhoto(Photo photo);
    void sortPhotos();
};

#endif
