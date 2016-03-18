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
  
  m_pThread = new CThread(m_pList);

  createActions();
  createToolBars();

  
  m_pPaint = new CPaintWidget();
  m_pList = new QListWidget();
  
  QSplitter* mainSplitter = new QSplitter(Qt::Vertical);
  mainSplitter->addWidget(m_pPaint);
  mainSplitter->addWidget(m_pList);


  m_pThread->start();
  
  this->setCentralWidget(mainSplitter);
}

void
CMainWindow::createActions()
{
  //snap a picture
  m_pSnapAPictureAction = new QAction(tr("snap"), this);
  m_pSnapAPictureAction->setIcon(QIcon(":/icons/snap.png"));
  connect(m_pSnapAPictureAction,SIGNAL(triggered()),
	  this, SLOT(snapAPicture()));
  
  // start process
  m_pStartProcessAction = new QAction(tr("Start Process"), this);
  m_pStartProcessAction->setIcon(QIcon(":/icons/start.png"));
  connect(m_pStartProcessAction, SIGNAL(triggered()),
	  m_pThread, SLOT(startProcess()));

  m_pStopProcessAction = new QAction(tr("Stop Process"), this);
  m_pStopProcessAction->setIcon(QIcon(":/icons/stop.png"));
  connect(m_pStopProcessAction, SIGNAL(triggered()),
	  m_pThread, SLOT(stopProcess()));

}

void
CMainWindow::createToolBars()
{
  m_pEditToolBar=addToolBar(tr("&Edit"));
  m_pEditToolBar->addAction(m_pSnapAPictureAction);
  m_pEditToolBar->addAction(m_pStartProcessAction);
  m_pEditToolBar->addAction(m_pStopProcessAction);
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
