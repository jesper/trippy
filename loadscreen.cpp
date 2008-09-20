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

#include "loadscreen.h"

LoadScreen::LoadScreen(QWidget *parent)
  :QDialog(parent)
{
  ui.setupUi(this);
  showFailedPhotos(false);
}

void LoadScreen::clearFailedPhotos()
{
    ui.lw_failPhotos->clear();
}

void LoadScreen::showFailedPhotos(bool show)
{
  ui.gb_failures->setVisible(show);
  adjustSize();
}
