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

#ifndef WINDOW_H
#define WINDOW_H

#include <QtGui>
#include <QStandardItemModel>

#include <MarbleWidget.h>

#include "ui_window.h"
#include "trippymarblewidget.h"
#include "photo.h"
#include "loadscreen.h"

using namespace Marble;

class Window : public QMainWindow
{
  Q_OBJECT
  public:
    Window(QWidget *parent=0);
    Ui::window ui;
    void centerMapOn(Photo *photo);
    void addPhoto(Photo photo);
    void sortPhotos();
    void repaintMarbleWidget();
    TrippyMarbleWidget *m_marble;

  private:
    QFileDialog *m_fileDialog;
    QStandardItem *m_previousItem; 
 
  private slots:
    void selectFile();
    void filesSelected(const QStringList &files);
    void photoClicked(const QModelIndex &index);
    void hideMapClutter();

    //Buttons/Menu items
    void backClicked();
    void nextClicked();
    void atlasClicked();
    void openStreetMapClicked();
    void mercatorClicked();
    void flatClicked();
    void globeClicked();
  
  signals:  
    void selectedFiles(const QStringList &files);
};

#endif
