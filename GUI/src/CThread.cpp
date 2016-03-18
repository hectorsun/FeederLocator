#include <CThread.h>


#include <iostream>
using std::cout;
using std::endl;

CThread::CThread(QListWidget* pList, QObject* parent/*=0*/)
  :QThread(parent),
   m_pList(pList)
{
  m_bWakeup = false;
  m_bQuit = false;
  m_bFeedback = false;

}


void
CThread::run()
{
  cout<<"enter CThread::run()"<<endl;
  forever{
    cout<<"start wait for wakeup"<<endl;
    
    {
      // wait for main thread call CThread::startProcess()
      QMutexLocker locker(&m_muxWakeup);
      while (true != m_bWakeup){
	m_cndWakeup.wait(&m_muxWakeup);
      }
      m_bWakeup = false;
    }
    
    cout<<" CThread waked"<<endl;

    // feed back to CThread::startProcess 
    {
      QMutexLocker locker(&m_muxFeedback);
      m_bFeedback = true;
      m_cndFeedback.wakeAll();
    }
    
    // check for quit
    if (true == m_bQuit){
      cout <<"quit thread" <<endl;
      return;
    }


    // do the job
    for (int i = 0; i<100; i++){	
    }
    
  }   
}

void
CThread::startProcess()
{
  //m_pList->addItem("CThread::startProcess()");
  cout<<"========================"<<endl;
  cout<< "enter CThread::startProcess()"<<endl;
  m_bFeedback = false;
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
  //m_pList->addItem("exit CThread::startProcess()");
  cout << "exit CThread::startProcess()"<<endl;
  cout << "============================"<<endl;
}
void
CThread::stopProcess()
{
  cout<<"CThread::stopProcess()"<<endl;

}

void
CThread::quitThread()
{
  cout<<"CThread::quitThread()"<<endl;

}
