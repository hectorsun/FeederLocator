#include <boost/asio.hpp>
#include <CThread.h>
#include <string>

#include <iostream>
#include <sstream>

#include <Camera/CCamera.h>

using std::cout;
using std::endl;
using std::ostringstream;

CThread::CThread(QListWidget* pList, CPaintWidget* pPaint,QObject* parent/*=0*/)
  :QThread(parent),
   m_pList(pList),
   m_pPaint(pPaint)
{
  m_bWakeup = false;
  m_bFeedback = false;
  m_bStop = false;
  
  m_curMode = modeIdle;
  m_nextMode = modeIdle;

}


void
CThread::run()
{
  cout<<"enter CThread::run()"<<endl;
  forever{
    cout<<"start wait for wakeup"<<endl;

    {
      QMutexLocker locker(&m_muxStatus);
      m_curMode = modeIdle;
    }
    
    {     
      // wait for main thread call CThread::startProcess()
      QMutexLocker locker(&m_muxWakeup);
      while (true != m_bWakeup){
	m_cndWakeup.wait(&m_muxWakeup);
      }
      m_bWakeup = false;
    }
    
    cout<<" CThread waked"<<endl;

    {
      QMutexLocker locker(&m_muxStatus);
      m_curMode = m_nextMode;
    }
    
    // feed back to CThread::startProcess 
    {
      QMutexLocker locker(&m_muxFeedback);
      m_bFeedback = true;
      m_cndFeedback.wakeAll();
    }
    
    switch(m_nextMode){
    case modeProcess:
      //m_curMode = modeProcess;
      process();
      break;
      
    case modeCapture:
      //m_curMode = modeCapture;
      m_pPaint->setShowMode(CPaintWidget::onlyImage);
      forever{
	capture();
	
	// if m_bStop==true. 
	// stop catpure
	if ( m_bStop == true ){
	  // feed back to CThread::startProcess 
	  {
	    QMutexLocker locker(&m_muxFeedback);
	    m_bFeedback = true;
	    m_cndFeedback.wakeAll();
	  }
	  m_bStop = false;
	  break;
	}

	msleep(30);
      }
      break;
    case modeQuit:
      cout << "Thread quit" <<endl;

      {
	QMutexLocker locker(&m_muxFeedback);
	m_bFeedback = true;
	m_cndFeedback.wakeAll();
      }
      return;
      
    default:
      break;
    }


  }   
}

void
CThread::startProcess()
{
  m_bFeedback = false;
  m_bStop = false;

  m_nextMode = modeProcess;

  {
    QMutexLocker locker(&m_muxWakeup);
    m_bWakeup = true;
    m_cndWakeup.wakeAll();
  }

  // wait for feedback from run()
  {
    QMutexLocker locker(&m_muxFeedback);
    while (true != m_bFeedback){
      m_cndFeedback.wait(&m_muxFeedback);
    }
  }

}
void
CThread::stopProcess()
{
  cout<<"CThread::stopProcess()"<<endl;


  {
    QMutexLocker locker(&m_muxStatus);
    if (m_curMode != modeProcess){
      return;
    }
  }
  
  m_bFeedback = false;
  m_bStop = true;
  
  // wait for feedback of run()
  {
    QMutexLocker locker(&m_muxFeedback);
    while (true != m_bFeedback){
      m_cndFeedback.wait(&m_muxFeedback);
    }
  }

  m_bStop = false;
  
}

void
CThread::quitThread()
{
  cout<<"CThread::quitThread()"<<endl;
  

  if (m_curMode == modeCapture){
    stopCapture();
  }
  if (m_curMode == modeProcess){
    stopProcess();
  }
  
  m_bFeedback = false;
  m_nextMode = modeQuit;

  {
    QMutexLocker locker(&m_muxWakeup);
    m_bWakeup = true;
    m_cndWakeup.wakeAll();
  }

  
  {
    QMutexLocker locker(&m_muxFeedback);
    while (true != m_bFeedback){
      m_cndFeedback.wait(&m_muxFeedback);
    }
  }

  cout << "exit CThread::quitThread()" << endl;

}


void
CThread::startCapture(){
  m_bFeedback = false;

  
  m_nextMode = modeCapture;

  m_bStop = false;


  {
    QMutexLocker locker(&m_muxWakeup);
    m_bWakeup = true;
    m_cndWakeup.wakeAll();
  }

  
  {
    QMutexLocker locker(&m_muxFeedback);
    while (true != m_bFeedback){
      m_cndFeedback.wait(&m_muxFeedback);
    }
  }
}

void
CThread::stopCapture(){
  cout<<"CThread::stopCapture()"<<endl;

  {
    QMutexLocker locker(&m_muxStatus);
    if (modeCapture != m_curMode){
      return;
    }
  }
  
  m_bStop = true;
  m_bFeedback = false;
  
  // wait for feedback of run()
  {
    QMutexLocker locker(&m_muxFeedback);
    while (true != m_bFeedback){
      m_cndFeedback.wait(&m_muxFeedback);
    }
  }

  m_bStop =false;
}

///////////////////////////////////////////////////////////////
// process function

void
CThread::process(){
  // do the job
  for (int i = 0; i<40; i++){
    //cout << "job iterater"<< i << endl;
    ostringstream ostr;
    ostr<<"job iterater" << i;
    cout << ostr.str();
    m_pList->addItem(QString::fromStdString(ostr.str()));
    
    sleep(1);
	

    // refresh paint
    emit m_pPaint->refresh();

  }

}


void
CThread::capture(){
  CCamera::getInstance().snap();
  m_pPaint->refreshPaint();
}
