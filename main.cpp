#include <QtGui>
#include "window.h"

int main(int argc, char* argv[])
{
  QApplication app(argc, argv);
  qDebug("I work!");
  Window *win = new Window(0);
  win->show();
  return app.exec();
}
