#include <CThread.h>


#include <iostream>
using std::cout;
using std::endl;

CThread::CThread(QListWidget* pList, QObject* parent/*=0*/)
  :QThread(parent),
   m_pList(pList)
{
 

}


void
CThread::run()
{
  cout<<"CThread::run()"<<endl;
  forever{
    


  }
}

void
CThread::startProcess()
{


}

void
CThread::stopProcess()
{

}

void
CThread::quitThread()
{


}
