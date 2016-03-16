
#include <QtWidgets>
#include <QApplication>
#include <QLabel>

#include <CCamera.h>

#include "CMainWindow.h"


int main(int argc, char* argv[]){
  QApplication app(argc, argv);

  CCamera::getInstance().init();

  CMainWindow mainWin;
  mainWin.show();

  return app.exec();
}
