
#include <QtWidgets>
#include <QApplication>
#include <QLabel>

#include <Camera/CCamera.h>

#include <CMainWindow.h>

#include <iostream>
using std::cout;
using std::endl;


int main(int argc, char* argv[]){
  QApplication app(argc, argv);

  CCamera::getInstance().init();
  
  cout<<"mainWin"<<endl;
  
  CMainWindow mainWin;
  mainWin.show();

  return app.exec();
}
