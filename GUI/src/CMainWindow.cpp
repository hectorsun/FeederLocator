#include <CMainWindow.h>

#include <QSplitter>
#include <QIcon>

#include <Camera/CCamera.h>

#include <iostream>
using std::cout;
using std::endl;


CMainWindow::CMainWindow()
{
  m_pSettingDlg = 0;
  this->setWindowState(Qt::WindowMaximized);
  this->setWindowTitle(tr("feeder locator"));
  
  m_pPaint = new CPaintWidget();
  m_pList = new QListWidget();

  m_pThread = new CThread(m_pList, m_pPaint);


  createActions();
  createToolBars();
  createStatusBar();
  
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

  m_pSettingAction = new QAction(tr("setting"), this);
  m_pSettingAction->setIcon(QIcon(":/icons/setting.png"));
  connect(m_pSettingAction, SIGNAL(triggered()),
	  this, SLOT(setting()));

  m_pSaveDataAction = new QAction(tr("save data"), this);
  m_pSaveDataAction->setIcon(QIcon(":/icons/save.png"));
  connect(m_pSaveDataAction, SIGNAL(triggered()),
	  this, SLOT(saveData()));

  m_pLoadDataAction = new QAction(tr("open data"), this);
  m_pLoadDataAction->setIcon(QIcon(":/icons/open.png"));
  connect(m_pLoadDataAction, SIGNAL(triggered()),
	  this, SLOT(loadData()));
  
}

void
CMainWindow::createToolBars()
{
  m_pEditToolBar=addToolBar(tr("&Edit"));
  m_pEditToolBar->addAction(m_pSnapAPictureAction);
  m_pEditToolBar->addAction(m_pStartProcessAction);
  m_pEditToolBar->addAction(m_pStopProcessAction);
  
  m_pEditToolBar->addAction(m_pSaveDataAction);
  m_pEditToolBar->addAction(m_pLoadDataAction);

  m_pEditToolBar->addAction(m_pSettingAction);
}

void
CMainWindow::createStatusBar()
{
  statusBar()->setVisible(true);
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

void
CMainWindow::setting()
{
  if (0 == m_pSettingDlg){
    m_pSettingDlg = new CSettingDlg(this);
  }

  m_pSettingDlg->show();
  m_pSettingDlg->raise();
  m_pSettingDlg->activateWindow();
}

void
CMainWindow::saveData()
{

}

void
CMainWindow::loadData()
{

}
