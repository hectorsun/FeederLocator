#include <boost/asio.hpp>
#include <QtWidgets>
#include <QApplication>
#include <QLabel>

#include <Camera/CCamera.h>

#include <CMainWindow.h>


#include <iostream>
using std::cout;
using std::endl;
#include <QDebug>
/*#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif*/

CMainWindow *mainWindowPtr = NULL;
int main(int argc, char* argv[]){
  QApplication app(argc, argv);

  CCamera::getInstance().init();
  
  cout<<"mainWin"<<endl;
  cout<<"你好"<<endl;
  CMainWindow mainWin;
  mainWindowPtr = &mainWin;
  mainWin.show();
  //mainWindowPtr = &mainWin;
  return app.exec();
}
