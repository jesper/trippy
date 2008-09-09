#include "trippy.h"

Trippy::Trippy()
{
  m_window = new Window();
  m_window->show();

  QObject::connect(m_window, SIGNAL(selectedFiles(const QStringList &)), this, SLOT(filesSelected(const QStringList &)));

  m_loadScreen = new LoadScreen();
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
      m_window->addPhoto(photo);
    }
    m_loadScreen->ui.progressBar->setValue(i + 1);
    m_loadScreen->update();
  }
}

