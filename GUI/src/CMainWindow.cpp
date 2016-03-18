#include <CMainWindow.h>

#include <QSplitter>
#include <QIcon>

#include <Camera/CCamera.h>

#include <iostream>
using std::cout;
using std::endl;


CMainWindow::CMainWindow()
{
  //this->setSizePolicy(QSizePolicy::Maximum);
  this->setWindowState(Qt::WindowMaximized);
  this->setWindowTitle("Feeder");

  createActions();
  createToolBars();

  
  m_pPaint = new CPaintWidget();
  m_pList = new QListWidget();
  
  QSplitter* mainSplitter = new QSplitter(Qt::Vertical);
  mainSplitter->addWidget(m_pPaint);
  mainSplitter->addWidget(m_pList);

  m_pThread = new CThread(m_pList);
  m_pThread->start();
  
  this->setCentralWidget(mainSplitter);
}

void
CMainWindow::createActions()
{
  //snap a picture
  m_pSnapAPictureAction = new QAction(tr("snap"), this);
  m_pSnapAPictureAction->setIcon(QIcon(":/icons/snap.png"));
  connect(m_pSnapAPictureAction,SIGNAL(triggered()), this, SLOT(snapAPicture()));

}

void
CMainWindow::createToolBars()
{
  m_pEditToolBar=addToolBar(tr("&Edit"));
  m_pEditToolBar->addAction(m_pSnapAPictureAction);
}

//slots
void
CMainWindow::snapAPicture()
{
  cout<<"snap a picture"<<endl;

  if (0 != CCamera::getInstance().snap()){
    return;
  }

  // 
  emit m_pPaint->refresh();

  //
  m_pList->addItem(QString("snap a picture"));
}
